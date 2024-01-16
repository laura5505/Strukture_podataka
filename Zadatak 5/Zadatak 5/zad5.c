#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Struktura za èvor vezane liste (stoga)
struct Node {
	int data;
	struct Node* next;
};

// Funkcija za inicijalizaciju novog èvora
struct Node* createNode(int data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	if (newNode == NULL) {
		printf("Greška pri alokaciji memorije.\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// Funkcija za dodavanje èvora na vrh stoga
void push(struct Node** top, int data) {
	struct Node* newNode = createNode(data);
	newNode->next = *top;
	*top = newNode;
}

// Funkcija za uklanjanje èvora s vrha stoga
int pop(struct Node** top) {
	if (*top == NULL) {
		printf("Stog je prazan.\n");
		exit(EXIT_FAILURE);
	}
	struct Node* temp = *top;
	int data = temp->data;
	*top = temp->next;
	free(temp);
	return data;
}

// Funkcija za izraèunavanje rezultata postfiksnog izraza
int evaluatePostfix(char* postfix) {
	struct Node* stack = NULL;

	// Iteracija kroz postfiks izraz
	for (int i = 0; postfix[i] != '\0'; ++i) {
		if (isdigit(postfix[i])) {
			// Ako je znak operand, stavi ga na stog
			push(&stack, postfix[i] - '0');
		}
		else {
			// Ako je znak operator, uzmi dva operanda s vrha stoga, izraèunaj rezultat
			// i stavi rezultat natrag na stog
			int operand2 = pop(&stack);
			int operand1 = pop(&stack);
			switch (postfix[i]) {
			case '+':
				push(&stack, operand1 + operand2);
				break;
			case '-':
				push(&stack, operand1 - operand2);
				break;
			case '*':
				push(&stack, operand1 * operand2);
				break;
			case '/':
				push(&stack, operand1 / operand2);
				break;
			}
		}
	}

	// Rezultat æe biti ostatak na vrhu stoga
	return pop(&stack);
}

int main() {
	FILE *file;
	char expression[100];

	// Otvori datoteku za èitanje
	file = fopen("postfix.txt", "r");

	// Provjeri jesu li otvaranje datoteke uspješno izvršeno
	if (file == NULL) {
		perror("Greška pri otvaranju datoteke");
		return 1;
	}

	// Èitaj postfiks izraz iz datoteke
	fscanf(file, "%s", expression);

	// Zatvori datoteku
	fclose(file);

	// Izraèunaj rezultat postfiksnog izraza
	int result = evaluatePostfix(expression);

	// Ispiši rezultat
	printf("Rezultat postfiksnog izraza: %d\n", result);

	return 0;
}
