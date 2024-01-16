#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Struktura za �vor vezane liste (stoga)
struct Node {
	int data;
	struct Node* next;
};

// Funkcija za inicijalizaciju novog �vora
struct Node* createNode(int data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	if (newNode == NULL) {
		printf("Gre�ka pri alokaciji memorije.\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// Funkcija za dodavanje �vora na vrh stoga
void push(struct Node** top, int data) {
	struct Node* newNode = createNode(data);
	newNode->next = *top;
	*top = newNode;
}

// Funkcija za uklanjanje �vora s vrha stoga
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

// Funkcija za izra�unavanje rezultata postfiksnog izraza
int evaluatePostfix(char* postfix) {
	struct Node* stack = NULL;

	// Iteracija kroz postfiks izraz
	for (int i = 0; postfix[i] != '\0'; ++i) {
		if (isdigit(postfix[i])) {
			// Ako je znak operand, stavi ga na stog
			push(&stack, postfix[i] - '0');
		}
		else {
			// Ako je znak operator, uzmi dva operanda s vrha stoga, izra�unaj rezultat
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

	// Rezultat �e biti ostatak na vrhu stoga
	return pop(&stack);
}

int main() {
	FILE *file;
	char expression[100];

	// Otvori datoteku za �itanje
	file = fopen("postfix.txt", "r");

	// Provjeri jesu li otvaranje datoteke uspje�no izvr�eno
	if (file == NULL) {
		perror("Gre�ka pri otvaranju datoteke");
		return 1;
	}

	// �itaj postfiks izraz iz datoteke
	fscanf(file, "%s", expression);

	// Zatvori datoteku
	fclose(file);

	// Izra�unaj rezultat postfiksnog izraza
	int result = evaluatePostfix(expression);

	// Ispi�i rezultat
	printf("Rezultat postfiksnog izraza: %d\n", result);

	return 0;
}
