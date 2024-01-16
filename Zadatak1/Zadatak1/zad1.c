#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX (1024)
#define DATOTEKA_SE_NE_MOZE_OTVORITI (-1)
#define NETOCNA_ALOKACIJA (-2)

typedef struct _student {

	char ime[50];
	char prezime[50];
	float bodovi;
}student;

int brojRedakaUDatoteci(char imeDatoteke[]);
int ucitavanjeDatoteke(char imeDatoteke[], int brStudenata, student* Stud);

int main() {

	char imeDatoteke[MAX];
	int brStudenata = 0;
	student* Stud;
	int kontrola;

	printf("Unesite ime datoteke: ");
	scanf(" %[^\n]", imeDatoteke);

	brStudenata = brojRedakaUDatoteci(imeDatoteke) + 1;

	if (brStudenata == -1)
		return DATOTEKA_SE_NE_MOZE_OTVORITI;

	Stud = (student*)malloc(brStudenata * sizeof(student));

	if (!Stud) {

		printf("Niz struktura nije dinamicki alociran!!\n");

		return NETOCNA_ALOKACIJA;
	}

	kontrola = ucitavanjeDatoteke(imeDatoteke, brStudenata, Stud);

	if (kontrola != 0)
		printf("Nesto nije u redu!!");

	return 0;
}

int brojRedakaUDatoteci(char imeDatoteke[]) {

	FILE* fp = NULL;
	int brRedaka = 0;
	char trenutnoSlovo;

	fp = fopen(imeDatoteke, "r");

	if (!fp) {

		printf("File se ne moze otvoriti!!\n");
		return DATOTEKA_SE_NE_MOZE_OTVORITI;
	}

	trenutnoSlovo = getc(fp);

	while (trenutnoSlovo != EOF) {

		if (trenutnoSlovo == '\n') {

			brRedaka++;
		}

		trenutnoSlovo = getc(fp);
	}

	fclose(fp);

	return brRedaka;
}

int ucitavanjeDatoteke(char imeDatoteke[], int brStudenata, student* Stud) {

	FILE* fp = NULL;
	int i;
	double relativanBrojBodova[50];
	float max = 0;

	fp = fopen(imeDatoteke, "r");

	if (!fp) {

		printf("File se ne moze otvoriti!!\n");
		return DATOTEKA_SE_NE_MOZE_OTVORITI;
	}

	for (i = 0; i < brStudenata; i++) {

		fscanf(fp, "%s %s %f\n", (*(Stud + i)).ime, (*(Stud + i)).prezime, &(*(Stud + i)).bodovi);
		relativanBrojBodova[i] = Stud[i].bodovi;
	}

	max = relativanBrojBodova[0];

	for (i = 1; i < brStudenata; i++) {

		if (relativanBrojBodova[i] > max)
			max = relativanBrojBodova[i];
	}

	for (i = 0; i < brStudenata; i++) {

		relativanBrojBodova[i] = Stud[i].bodovi / max * 100;
	}

	for (i = 0; i < brStudenata; i++) {

		printf("Ime i prezime: %s %s\t Bodovi: %.2f\t  Relativni bodovi: %.2f\n", (*(Stud + i)).ime, (*(Stud + i)).prezime, (*(Stud + i)).bodovi, relativanBrojBodova[i]);
	}

	return 0;
}