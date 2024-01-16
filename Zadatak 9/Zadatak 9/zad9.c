#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _tree;
typedef struct _tree* PosT;
typedef struct _tree
{
    int number;
    PosT left;
    PosT right;
} tree;

struct _List;
typedef struct _List* PosL;
typedef struct _List
{
    int number;
    PosL next;
} List;

PosT Insert(PosT curr, PosT newElement);
PosT CreateNewElement(int number);
int Inorder(PosT curr);
int Replace(PosT curr);
int PrintinList(PosT curr, PosL head);
int AppendList(PosL head, int number);
PosL FindLast(PosL head);
PosL CreateNewListElement(int number);
int InsertAfter(PosL position, PosL newListElement);
int FileEntry(PosL head, char* FileName);

int main()
{
    srand(time(NULL));
    char dat[50] = { 0 };
    List head = { .next = NULL, .number = 0 };
    PosT root = NULL;
    PosT newElement = NULL;
    int i = 0;

    root = (PosT)malloc(sizeof(tree));
    root = (PosT)malloc(sizeof(tree));
    if (!root) {
        perror("Can't allocate memory!");
        return -1;
    }
    root->number = rand() % 81 + 10;
    root->left = NULL;
    root->right = NULL;

    for (i = 1; i < 10; i++)
    {
        newElement = CreateNewElement(rand() % 80 + 10);
        if (!newElement)
        {
            perror("Greska u alociranju");
            return -1;
        }
        root = Insert(root, newElement);
    }

    printf("Ime datoteke u koju zelite pohraniti svoju listu: ");
    if (scanf(" %s", dat) != 1) {
        perror("Error reading input");
        return -1;
    }
    printf("\n");

    // 1
    PrintinList(root, &head);
    printf("\n");
    FileEntry(&head, dat);
    printf("\n");

    // 2
    root->number = Replace(root);
    PrintinList(root, &head);
    printf("\n");
    FileEntry(&head, dat);

    return 0;
}

PosT Insert(PosT curr, PosT newElement)
{
    if (curr == NULL)
        return newElement;
    if (curr->number <= newElement->number)
        curr->right = Insert(curr->right, newElement);
    else if (curr->number > newElement->number)
        curr->left = Insert(curr->left, newElement);
    return curr;
}

PosT CreateNewElement(int number)
{
    PosT newElement = NULL;
    newElement = (PosT)malloc(sizeof(tree));
    if (!newElement)
    {
        perror("Can't allocate memory!");
        return NULL;
    }

    newElement->number = number;
    newElement->left = NULL;
    newElement->right = NULL;

    return newElement;
}

int Inorder(PosT curr)
{
    if (curr == NULL)
        return 0;
    Inorder(curr->left);
    printf("%d ", curr->number);
    Inorder(curr->right);

    return 0;
}

int Replace(PosT curr)
{
    if (curr == NULL)
        return 0;

    int temp = curr->number;
    curr->number = Replace(curr->right) + Replace(curr->left);

    curr->left = NULL;
    curr->right = NULL;

    return temp + curr->number;
}

int PrintinList(PosT curr, PosL head)
{
    if (curr == NULL)
        return 0;

    PrintinList(curr->left, head);
    printf("%d ", curr->number);
    AppendList(head, curr->number);
    PrintinList(curr->right, head);

    return 0;
}

int AppendList(PosL head, int number)
{
    PosL newListElement = NULL;
    PosL last = NULL;

    newListElement = CreateNewListElement(number);
    if (!newListElement) {
        return -1;
    }

    last = FindLast(head);
    InsertAfter(last, newListElement);

    return EXIT_SUCCESS;
}

PosL FindLast(PosL head)
{
    PosL temp = head;

    while (temp->next) {
        temp = temp->next;
    }

    return temp;
}

PosL CreateNewListElement(int number)
{
    PosL newListElement = NULL;
    newListElement = (PosL)malloc(sizeof(List));
    if (!newListElement)
    {
        perror("Can't allocate memory!");
        return NULL;
    }

    newListElement->number = number;
    newListElement->next = NULL;

    return newListElement;
}

int InsertAfter(PosL position, PosL newListElement)
{
    newListElement->next = position->next;
    position->next = newListElement;

    return EXIT_SUCCESS;
}

int FileEntry(PosL head, char* FileName)
{
    FILE* f = fopen(FileName, "w");
    PosL position = head->next;
    if (!f) {
        printf("Greska!");
        return -1;
    }
    while (position != NULL)
    {
        fprintf(f, "%d ", position->number);
        position = position->next;
    }
    fprintf(f, "\n");

    printf("Uspjesan ispis u datoteku!\n");
    fclose(f);

    return EXIT_SUCCESS;
}