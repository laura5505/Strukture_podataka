#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struktura podataka za element liste
typedef struct _data {
    int value;         // Vrijednost elementa
    int priority;      // Prioritet elementa
    struct _data* next; // Pokazivaè na sljedeæi element u listi
} Data, * dataPosition;

dataPosition createElement(int value, int priority);
int insertSorted(dataPosition* head, int value, int priority);
int printList(dataPosition head);
int findAndPrintCommonElements(dataPosition list1, dataPosition list2);
int deleteCommonElements(dataPosition* list1, dataPosition* list2);
int createCommonList(dataPosition* newList, dataPosition list1, dataPosition list2);
int generateUniqueList1(dataPosition* list, int numElements);
int generateList2(dataPosition* list, int numElements);

int main() {
   
    srand(time(NULL));

    dataPosition list1 = NULL;
    dataPosition list2 = NULL;
    dataPosition commonList = NULL;

    generateUniqueList1(&list1, 20); // Prva lista s jedinstvenim vrijednostima
    generateList2(&list2, 20);       // Druga lista s moguæim ponavljanjima

    printf("Lista 1:\n");
    printList(list1);

    printf("\nLista 2:\n");
    printList(list2);

    printf("\nZajednièki elementi:\n");
    findAndPrintCommonElements(list1, list2);

    deleteCommonElements(&list1, &list2);

    printf("\nLista 1 nakon brisanja zajednièkih elemenata:\n");
    printList(list1);

    printf("\nLista 2 nakon brisanja zajednièkih elemenata:\n");
    printList(list2);

    createCommonList(&commonList, list1, list2);

    printf("\nNova lista sa zajednièkim elementima:\n");
    printList(commonList);

    return EXIT_SUCCESS;
}

dataPosition createElement(int value, int priority) {
    dataPosition newElement = (dataPosition)malloc(sizeof(Data)); // Alokacija memorije za novi element
    
    if (!newElement) {
        perror("Neuspjela alokacija memorije.\n");
        return NULL;
    }

    newElement->value = value;      // Postavljanje vrijednosti
    newElement->priority = priority; // Postavljanje prioriteta
    newElement->next = NULL;         // Inicijalizacija pokazivaèa na sljedeæi element
    return newElement;               // Povrat pokazivaèa na novi element
}

int insertSorted(dataPosition* head, int value, int priority) {
    dataPosition newElement = createElement(value, priority); // Stvaranje novog elementa
    if (!newElement) return EXIT_FAILURE;

    if (*head == NULL || (*head)->priority > priority ||((*head)->priority == priority && (*head)->value > value)) {

        newElement->next = *head;
        *head = newElement;
    }

    else {

        dataPosition current = *head;

        while (current->next != NULL &&(current->next->priority < priority || (current->next->priority == priority && current->next->value < value))) {
            
            current = current->next;

        }

        newElement->next = current->next;
        current->next = newElement;
    }
    return EXIT_SUCCESS;
}

int printList(dataPosition head) {
    while (head != NULL) {
        printf("Value: %d, Priority: %d\n", head->value, head->priority);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int valueExists(dataPosition head, int value) {
    while (head != NULL) {
        if (head->value == value) return 1; // Vrijednost postoji u listi
        head = head->next;
    }
    return 0; // Vrijednost ne postoji u listi
}

int findAndPrintCommonElements(dataPosition list1, dataPosition list2) {
    dataPosition temp1 = list1;
    while (temp1 != NULL) {
        dataPosition temp2 = list2;
        while (temp2 != NULL) {
            if (temp1->value == temp2->value) {
                printf("Zajednièka vrijednost: %d s prioritetima %d i %d\n", temp1->value, temp1->priority, temp2->priority);
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return EXIT_SUCCESS;
}

int deleteCommonElements(dataPosition* list1, dataPosition* list2) {
    dataPosition temp1 = *list1;
    dataPosition prev1 = NULL;

    while (temp1 != NULL) {
        dataPosition temp2 = *list2;
        dataPosition prev2 = NULL;
        int found = 0;

        while (temp2 != NULL) {
            if (temp1->value == temp2->value) {
                found = 1;
                if (prev2 == NULL) {
                    *list2 = temp2->next;
                }
                else {
                    prev2->next = temp2->next;
                }
                free(temp2);
                break;
            }
            prev2 = temp2;
            temp2 = temp2->next;
        }

        if (found) {
            if (prev1 == NULL) {
                *list1 = temp1->next;
            }
            else {
                prev1->next = temp1->next;
            }
            dataPosition toDelete = temp1;
            temp1 = temp1->next;
            free(toDelete);
        }
        else {
            prev1 = temp1;
            temp1 = temp1->next;
        }
    }
    return EXIT_SUCCESS;
}

// Funkcija za stvaranje nove liste sa zajednièkim elementima
int createCommonList(dataPosition* newList, dataPosition list1, dataPosition list2) {
    dataPosition temp1 = list1;
    while (temp1 != NULL) {
        dataPosition temp2 = list2;
        while (temp2 != NULL) {
            if (temp1->value == temp2->value) {
                insertSorted(newList, temp1->value, temp1->priority < temp2->priority ? temp1->priority : temp2->priority);
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return EXIT_SUCCESS;
}

int generateUniqueList1(dataPosition* list, int numElements) {
    int value;
    for (int i = 0; i < numElements; i++) {
        do {
            value = rand() % 31 + 100; // Vrijednost izmeðu 100 i 130
        } while (valueExists(*list, value)); // Provjerava je li vrijednost veæ u listi
        insertSorted(list, value, rand() % 5 + 1); // Prioritet izmeðu 1 i 5
    }
    return EXIT_SUCCESS;
}

int generateList2(dataPosition* list, int numElements) {
    for (int i = 0; i < numElements; i++) {
        int value = rand() % 31 + 100; // Vrijednost izmeðu 100 i 130
        insertSorted(list, value, rand() % 5 + 1); // Prioritet izmeðu 1 i 5
    }
    return EXIT_SUCCESS;
}
