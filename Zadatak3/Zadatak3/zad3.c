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

// Funkcija za dinamièko dodavanje novog elementa na poèetak liste
struct Osoba* dodajNaPocetak(struct Osoba *head, char ime[], char prezime[], int godina_rodenja) {
	struct Osoba *novaOsoba = (struct Osoba*)malloc(sizeof(struct Osoba));

	if (novaOsoba == NULL) {
		printf("Greška pri alociranju memorije.\n");
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
		printf("%s %s, Godina roðenja: %d\n", trenutna->ime, trenutna->prezime, trenutna->godina_rodenja);
		trenutna = trenutna->sljedeca;
	}
	printf("\n");
}

// Funkcija za dinamièko dodavanje novog elementa na kraj liste
struct Osoba* dodajNaKraj(struct Osoba *head, char ime[], char prezime[], int godina_rodenja) {
	struct Osoba *novaOsoba = (struct Osoba*)malloc(sizeof(struct Osoba));

	if (novaOsoba == NULL) {
		printf("Greška pri alociranju memorije.\n");
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

// Funkcija za dinamièko dodavanje novog elementa iza odreðenog elementa
struct Osoba* dodajIzaElementa(struct Osoba *head, char prezime[], char novoIme[], int novaGodina) {
	struct Osoba *noviElement = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (noviElement == NULL) {
		printf("Greška pri alociranju memorije.\n");
		exit(1);
	}

	struct Osoba *trenutni = head;
	while (trenutni != NULL && strcmp(trenutni->prezime, prezime) != 0) {
		trenutni = trenutni->sljedeca;
	}

	if (trenutni == NULL) {
		printf("Osoba s prezimenom %s nije pronaðena.\n", prezime);
		free(noviElement);
		return head;
	}

	strcpy(noviElement->ime, novoIme);
	strcpy(noviElement->prezime, trenutni->prezime);
	noviElement->godina_rodenja = novaGodina;
	noviElement->sljedeca = trenutni->sljedeca;
	trenutni->sljedeca = noviElement;

	return head;
}

// Funkcija za dinamièko dodavanje novog elementa ispred odreðenog elementa
struct Osoba* dodajIspredElementa(struct Osoba *head, char prezime[], char novoIme[], int novaGodina) {
	struct Osoba *noviElement = (struct Osoba*)malloc(sizeof(struct Osoba));
	if (noviElement == NULL) {
		printf("Greška pri alociranju memorije.\n");
		exit(1);
	}

	struct Osoba *trenutni = head;
	struct Osoba *prethodni = NULL;

	while (trenutni != NULL && strcmp(trenutni->prezime, prezime) != 0) {
		prethodni = trenutni;
		trenutni = trenutni->sljedeca;
	}

	if (trenutni == NULL) {
		printf("Osoba s prezimenom %s nije pronaðena.\n", prezime);
		free(noviElement);
		return head;
	}

	strcpy(noviElement->ime, novoIme);
	strcpy(noviElement->prezime, trenutni->prezime);
	noviElement->godina_rodenja = novaGodina;

	if (prethodni == NULL) {
		// Dodavanje ispred prvog elementa
		noviElement->sljedeca = head;
		head = noviElement;
	}
	else {
		// Dodavanje ispred trenutnog elementa
		prethodni->sljedeca = noviElement;
		noviElement->sljedeca = trenutni;
	}

	return head;
}

// Funkcija za sortiranje liste po prezimenima osoba
struct Osoba* sortirajListu(struct Osoba *head) {
	if (head == NULL || head->sljedeca == NULL) {
		return head; // Lista je veæ sortirana
	}

	struct Osoba *novaGlava = NULL;

	while (head != NULL) {
		struct Osoba *trenutna = head;
		head = head->sljedeca;

		if (novaGlava == NULL || strcmp(trenutna->prezime, novaGlava->prezime) < 0) {
			trenutna->sljedeca = novaGlava;
			novaGlava = trenutna;
		}
		else {
			struct Osoba *t = novaGlava;
			while (t->sljedeca != NULL && strcmp(trenutna->prezime, t->sljedeca->prezime) > 0) {
				t = t->sljedeca;
			}
			trenutna->sljedeca = t->sljedeca;
			t->sljedeca = trenutna;
		}
	}

	return novaGlava;
}

// Funkcija za upisivanje liste u datoteku
void upisiListuUDatoteku(struct Osoba *head, const char *datoteka) {
	FILE *file = fopen(datoteka, "w");
	if (file == NULL) {
		printf("Greška pri otvaranju datoteke za pisanje.\n");
		exit(1);
	}

	struct Osoba *trenutna = head;
	while (trenutna != NULL) {
		fprintf(file, "%s %s %d\n", trenutna->ime, trenutna->prezime, trenutna->godina_rodenja);
		trenutna = trenutna->sljedeca;
	}

	fclose(file);
}

// Funkcija za èitanje liste iz datoteke
struct Osoba* citajListuIzDatoteke(const char *datoteka) {
	FILE *file = fopen(datoteka, "r");
	if (file == NULL) {
		printf("Greška pri otvaranju datoteke za èitanje.\n");
		exit(1);
	}

	struct Osoba *head = NULL;

	while (!feof(file)) {
		char novoIme[50], novoPrezime[50];
		int novaGodina;

		if (fscanf(file, "%s %s %d", novoIme, novoPrezime, &novaGodina) != 3) {
			break; // Završetak datoteke
		}

		head = dodajNaKraj(head, novoIme, novoPrezime, novaGodina);
	}

	fclose(file);

	return head;
}

// Funkcija za oslobaðanje memorije alocirane za listu
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

	// Dodavanje na poèetak liste
	head = dodajNaPocetak(head, "Ivan", "Iviæ", 1990);
	head = dodajNaPocetak(head, "Ana", "Aniæ", 1985);

	// Ispisivanje liste
	ispisiListu(head);

	// Dodavanje na kraj liste
	head = dodajNaKraj(head, "Marko", "Markiæ", 2000);

	// Ispisivanje liste
	ispisiListu(head);

	// Dodavanje iza odreðenog elementa
	head = dodajIzaElementa(head, "Iviæ", "Novo", 1995);

	// Ispisivanje liste
	ispisiListu(head);

	// Dodavanje ispred odreðenog elementa
	head = dodajIspredElementa(head, "Markiæ", "Novo2", 1998);

	// Ispisivanje liste
	ispisiListu(head);

	// Sortiranje liste po prezimenima osoba
	head = sortirajListu(head);

	// Ispisivanje liste
	ispisiListu(head);

	// Upisivanje liste u datoteku
	upisiListuUDatoteku(head, "lista.txt");

	// Èitanje liste iz datoteke
	struct Osoba *novaLista = citajListuIzDatoteke("lista.txt");

	// Ispisivanje nove liste
	ispisiListu(novaLista);

	// Oslobaðanje memorije
	oslobodiMemoriju(head);
	oslobodiMemoriju(novaLista);

	return 0;
}