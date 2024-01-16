#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktura osoba
struct Osoba {
	char ime[50];
	char prezime[50];
	int godina_rodenja;
	struct Osoba *sljedeca;
};

// Funkcija za dinami�ko dodavanje novog elementa na po�etak liste
struct Osoba* dodajNaPocetak(struct Osoba *head, char ime[], char prezime[], int godina_rodenja) {
	struct Osoba *novaOsoba = (struct Osoba*)malloc(sizeof(struct Osoba));

	if (novaOsoba == NULL) {
		printf("Gre�ka pri alociranju memorije.\n");
		exit(1);
	}

	strcpy(novaOsoba->ime, ime);
	strcpy(novaOsoba->prezime, prezime);
	novaOsoba->godina_rodenja = godina_rodenja;

	novaOsoba->sljedeca = head;
	head = novaOsoba;

	return head;
}

// Funkcija za ispisivanje liste
void ispisiListu(struct Osoba *head) {
	struct Osoba *trenutna = head;

	printf("Lista osoba:\n");
	while (trenutna != NULL) {
		printf("%s %s, Godina ro�enja: %d\n", trenutna->ime, trenutna->prezime, trenutna->godina_rodenja);
		trenutna = trenutna->sljedeca;
	}
	printf("\n");
}

// Funkcija za dinami�ko dodavanje novog elementa na kraj liste
struct Osoba* dodajNaKraj(struct Osoba *head, char ime[], char prezime[], int godina_rodenja) {
	struct Osoba *novaOsoba = (struct Osoba*)malloc(sizeof(struct Osoba));

	if (novaOsoba == NULL) {
		printf("Gre�ka pri alociranju memorije.\n");
		exit(1);
	}

	strcpy(novaOsoba->ime, ime);
	strcpy(novaOsoba->prezime, prezime);
	novaOsoba->godina_rodenja = godina_rodenja;
	novaOsoba->sljedeca = NULL;

	if (head == NULL) {
		return novaOsoba;
	}

	struct Osoba *trenutna = head;
	while (trenutna->sljedeca != NULL) {
		trenutna = trenutna->sljedeca;
	}

	trenutna->sljedeca = novaOsoba;
	return head;
}

// Funkcija za pronala�enje elementa u listi (po prezimenu)
struct Osoba* pronadiPoPrezimenu(struct Osoba *head, char prezime[]) {
	struct Osoba *trenutna = head;

	while (trenutna != NULL) {
		if (strcmp(trenutna->prezime, prezime) == 0) {
			return trenutna;
		}
		trenutna = trenutna->sljedeca;
	}

	return NULL;
}

// Funkcija za brisanje odre�enog elementa iz liste
struct Osoba* obrisiElement(struct Osoba *head, char prezime[]) {
	struct Osoba *trenutna = head;
	struct Osoba *prethodna = NULL;

	while (trenutna != NULL) {
		if (strcmp(trenutna->prezime, prezime) == 0) {
			if (prethodna == NULL) {
				head = trenutna->sljedeca;
			}
			else {
				prethodna->sljedeca = trenutna->sljedeca;
			}

			free(trenutna);
			return head;
		}

		prethodna = trenutna;
		trenutna = trenutna->sljedeca;
	}

	printf("Osoba s prezimenom %s nije prona�ena.\n", prezime);
	return head;
}

// Funkcija za osloba�anje memorije alocirane za listu
void oslobodiMemoriju(struct Osoba *head) {
	struct Osoba *trenutna = head;
	struct Osoba *sljedeca;

	while (trenutna != NULL) {
		sljedeca = trenutna->sljedeca;
		free(trenutna);
		trenutna = sljedeca;
	}
}

int main() {
	struct Osoba *head = NULL;

	// Dodavanje na po�etak liste
	head = dodajNaPocetak(head, "Ivan", "Ivi�", 1990);
	head = dodajNaPocetak(head, "Ana", "Ani�", 1985);

	// Ispisivanje liste
	ispisiListu(head);

	// Dodavanje na kraj liste
	head = dodajNaKraj(head, "Marko", "Marki�", 2000);

	// Ispisivanje liste
	ispisiListu(head);

	// Pronala�enje elementa po prezimenu
	struct Osoba *pronadenaOsoba = pronadiPoPrezimenu(head, "Ani�");
	if (pronadenaOsoba != NULL) {
		printf("Prona�ena osoba: %s %s, Godina ro�enja: %d\n", pronadenaOsoba->ime, pronadenaOsoba->prezime, pronadenaOsoba->godina_rodenja);
	}
	else {
		printf("Osoba nije prona�ena.\n");
	}

	// Brisanje elementa iz liste
	head = obrisiElement(head, "Ivi�");

	// Ispisivanje liste nakon brisanja
	ispisiListu(head);

	// Osloba�anje memorije
	oslobodiMemoriju(head);

	return 0;
}
