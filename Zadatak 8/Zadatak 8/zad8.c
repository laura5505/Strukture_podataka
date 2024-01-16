#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Struktura èvora binarnog stabla
struct Node {
    int key;
    struct Node* left, * right;
};

// Funkcija za kreiranje novog èvora
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Funkcija za dodavanje novog elementa u stablo
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// Funkcija za ispis elemenata inorder (u rastuæem redosledu)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Funkcija za ispis elemenata preorder
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// Funkcija za ispis elemenata postorder
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

// Funkcija za ispis elemenata level order
void levelOrder(struct Node* root) {
    if (root == NULL)
        return;

    // Korišæenje reda za obilazak stabla u level order
    struct Node* queue[100];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        struct Node* temp = queue[++front];
        printf("%d ", temp->key);

        if (temp->left != NULL)
            queue[++rear] = temp->left;
        if (temp->right != NULL)
            queue[++rear] = temp->right;
    }
}

// Funkcija za pronalaženje elementa u stablu
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Funkcija za pronalaženje najmanjeg elementa u stablu
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Funkcija za brisanje elementa iz stabla
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Èvor sa jednim ili bez dece
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Èvor sa dvoje dece: Pronalaženje naslednika (najmanjeg u desnom podstablu)
        struct Node* temp = minValueNode(root->right);

        // Kopiranje vrednosti naslednika u trenutni èvor
        root->key = temp->key;

        // Brisanje naslednika
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Funkcija za oslobaðanje memorije zauzete stablom
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;

    // Dodavanje elemenata u stablo
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    printf("Level Order: ");
    levelOrder(root);
    printf("\n");

    // Traženje elementa u stablu
    int searchKey = 40;
    struct Node* foundNode = search(root, searchKey);
    if (foundNode != NULL) {
        printf("Element %d pronadjen u stablu.\n", searchKey);
    }
    else {
        printf("Element %d nije pronadjen u stablu.\n", searchKey);
    }

    // Brisanje elementa iz stabla
    int deleteKey = 30;
    root = deleteNode(root, deleteKey);
    printf("Element %d obrisan iz stabla.\n", deleteKey);

    // Ispis nakon brisanja
    printf("Inorder nakon brisanja: ");
    inorder(root);
    printf("\n");

    // Oslobaðanje memorije
    freeTree(root);

    return 0;
}