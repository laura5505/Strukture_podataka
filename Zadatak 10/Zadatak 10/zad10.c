#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 50

struct _tree;
typedef struct _tree* PosT;
typedef struct _tree {
    char ime_grada[MAX_NAME];
    int broj_stanovnika;
    PosT left;
    PosT right;
}tree;

struct _drzava;
typedef struct _drzava* PosL;
typedef struct _drzava {
    char ime_drzave[MAX_NAME];
    PosT grad;
    PosL next;
}drzava;

int InsToListFromFile(PosL head, char* fileName);
int InsToTreeFromFile(PosL ime_drzave, char* fileName);
int SortedInputList(PosL head, PosL NewEl);
int InsertAfter(PosL head, PosL NewEl);
PosL MakeListEL(char* ime_drzave);
int PrintList(PosL first);
int PrintT(PosT curr);
PosT SortedInputTree(PosT curr, PosT NewEl);
PosT MakeTreeEl(char* ime_grada, int broj_stanovnika);
void SearchCities(PosL head, char* ime_drzave, int broj_stanovnika);
void SearchCitiesInTree(PosT curr, int broj_stanovnika);


int main() {

    drzava lstDrzava = { .ime_drzave = "", .grad = NULL, .next = NULL };
    PosL listaDrzava = &lstDrzava;

    char filename[] = "drzave.txt";
    InsToListFromFile(listaDrzava, filename);
    PrintList(listaDrzava);

    char searchCountry[MAX_NAME];
    int populationThreshold;

    printf("\nEnter the country name for population search: ");
    scanf("%s", searchCountry);

    printf("Enter the population threshold: ");
    scanf("%d", &populationThreshold);

    SearchCities(listaDrzava, searchCountry, populationThreshold);

    return 1;

}


int InsToListFromFile(PosL head, char* fileName) {

    FILE* f = NULL;
    f = fopen(fileName, "r");
    char ime_drzave[MAX_NAME] = { 0 };
    char datotekagrad[MAX_NAME] = { 0 };

    drzava t = { .ime_drzave = "", .grad = NULL, .next = NULL };
    PosL temp1 = &t;

    if (!f) {
        printf("File is invalid.\n");
        return -1;
    }

    while (!feof(f)) {

        fscanf(f, "%s %s\n", ime_drzave, datotekagrad);
        temp1 = MakeListEL(ime_drzave);

        InsToTreeFromFile(temp1, datotekagrad);

        SortedInputList(head, temp1);
    }

    fclose(f);
    return EXIT_SUCCESS;
}

int InsToTreeFromFile(PosL ime_drzave, char* fileName) {
    FILE* f = NULL;
    f = fopen(fileName, "r");

    char ime_grada[MAX_NAME] = { 0 };
    int broj_stanovnika = 0;

    if (!f) {
        perror("File is invalid\n");
        return -1;
    }

    while (!feof(f)) {
        fscanf(f, "%s %d", ime_grada, &broj_stanovnika);
        PosT temp2 = MakeTreeEl(ime_grada, broj_stanovnika);
        ime_drzave->grad = SortedInputTree(ime_drzave->grad, temp2);
    }

    fclose(f);

    return EXIT_SUCCESS;

}

int SortedInputList(PosL head, PosL NewEl) {

    while (head->next != NULL && strcmp(head->next->ime_drzave, NewEl->ime_drzave) < 0)
    {
        head = head->next;
    }

    InsertAfter(head, NewEl);
    return EXIT_SUCCESS;
}

int InsertAfter(PosL head, PosL NewEl) {

    NewEl->next = head->next;
    head->next = NewEl;

    return EXIT_SUCCESS;
}

PosL MakeListEL(char* ime_drzave) {
    PosL NewEl = NULL;
    NewEl = (PosL)malloc(sizeof(drzava));

    if (!NewEl) {
        perror("\nCan't allocate memory!");
        return NULL;
    }

    strcpy(NewEl->ime_drzave, ime_drzave);
    NewEl->grad = NULL;
    NewEl->next = NULL;

    return NewEl;
}

int PrintList(PosL first) {
    PosL temp = first->next;

    while (temp) {
        printf("%s\n ", temp->ime_drzave);
        PrintT(temp->grad);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

int PrintT(PosT curr) {
    if (curr == NULL)
        return 0;

    printf("\t%s - %d stanovnika\n", curr->ime_grada, curr->broj_stanovnika);
    PrintT(curr->left);
    PrintT(curr->right);

    return 0;
}

PosT SortedInputTree(PosT curr, PosT NewEl) {

    if (!curr)
        return NewEl;

    if (curr->broj_stanovnika < NewEl->broj_stanovnika) {
        curr->right = SortedInputTree(curr->right, NewEl);
    }

    else if (curr->broj_stanovnika > NewEl->broj_stanovnika) {
        curr->left = SortedInputTree(curr->left, NewEl);
    }
    else free(NewEl);

    return curr;
}

PosT MakeTreeEl(char* ime_grada, int broj_stanovnika) {
    PosT NewEl = (PosT)malloc(sizeof(tree));

    if (!NewEl) {
        printf("\nCan't allocate memory.");
        return NULL;
    }

    strcpy(NewEl->ime_grada, ime_grada);
    NewEl->broj_stanovnika = broj_stanovnika;
    NewEl->right = NULL;
    NewEl->left = NULL;

    return NewEl;
}

void SearchCities(PosL head, char* ime_drzave, int broj_stanovnika) {
    PosL temp = head->next;

    while (temp) {
        if (strcmp(temp->ime_drzave, ime_drzave) == 0) {
            printf("Cities in %s with population greater than %d:\n", ime_drzave, broj_stanovnika);
            SearchCitiesInTree(temp->grad, broj_stanovnika);
            return;
        }
        temp = temp->next;
    }

    printf("Country '%s' not found.\n", ime_drzave);
}

void SearchCitiesInTree(PosT curr, int broj_stanovnika) {
    if (curr == NULL)
        return;

    if (curr->broj_stanovnika > broj_stanovnika) {
        printf("\t%s - %d stanovnika\n", curr->ime_grada, curr->broj_stanovnika);
    }

    SearchCitiesInTree(curr->left, broj_stanovnika);
    SearchCitiesInTree(curr->right, broj_stanovnika);
}