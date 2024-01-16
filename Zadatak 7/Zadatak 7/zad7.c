#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Directory {
    char name[50];
    struct Directory* subdirectories;
    struct Directory* parent;
    struct Directory* next;
};

struct Directory* createDirectory(const char* name, struct Directory* parent) {
    struct Directory* newDir = (struct Directory*)malloc(sizeof(struct Directory));
    strcpy(newDir->name, name);
    newDir->subdirectories = NULL;
    newDir->parent = parent;
    newDir->next = NULL;
    return newDir;
}

void addSubdirectory(struct Directory** currentDir, const char* name) {
    struct Directory* newSubdir = createDirectory(name, *currentDir);
    newSubdir->next = (*currentDir)->subdirectories;
    (*currentDir)->subdirectories = newSubdir;

    // Promeni trenutni direktorijum na novo kreirani pod-direktorijum
    *currentDir = newSubdir;
}

void printDirectory(struct Directory* currentDir) {
    printf("\nSadrzaj direktorija %s:\n", currentDir->name);

    struct Directory* subdir = currentDir->subdirectories;
    while (subdir != NULL) {
        printf(" - %s\n", subdir->name);
        subdir = subdir->next;
    }
}

struct Directory* changeDirectory(struct Directory* currentDir, const char* name) {
    if (strcmp(name, "..") == 0) {
        // Ako je unesen "..", prelazak u prethodni direktorij
        if (currentDir->parent != NULL) {
            return currentDir->parent;
        }
        else {
            printf("Vec ste u korenskom direktoriju.\n");
            return currentDir;
        }
    }

    struct Directory* subdir = currentDir->subdirectories;
    while (subdir != NULL) {
        if (strcmp(subdir->name, name) == 0) {
            return subdir;
        }
        subdir = subdir->next;
    }

    printf("Direktorij %s nije pronadjen.\n", name);
    return currentDir;
}

int main() {
    struct Directory* root = createDirectory("C:", NULL);
    struct Directory* currentDir = root;

    int choice;
    char dirName[50];

    do {
        printf("\nDOS Meni:\n");
        printf("1 - md (kreiranje direktorija)\n");
        printf("2 - cd dir (promena direktorija)\n");
        printf("3 - cd.. (povratak u prethodni direktorij)\n");
        printf("4 - dir (ispis sadrzaja direktorija)\n");
        printf("5 - izlaz\n");
        printf("Izaberite opciju: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Unesite ime novog direktorija: ");
            scanf("%s", dirName);
            addSubdirectory(&currentDir, dirName);
            break;
        case 2:
            printf("Unesite ime direktorija: ");
            scanf("%s", dirName);
            currentDir = changeDirectory(currentDir, dirName);
            break;
        case 3:
            currentDir = changeDirectory(currentDir, "..");
            break;
        case 4:
            printDirectory(currentDir);
            break;
        case 5:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Nevažeæa opcija.\n");
        }
    } while (choice != 5);

    return 0;
}