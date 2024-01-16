#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define MAX_LINE 1024 


struct _broj;
typedef struct _broj* position;

struct _broj {
	int eksponent;
	int koeficijent;

	struct _broj* next;
};
typedef struct _broj broj;



int CitanjeIzDat(position, position, char*);
int Ispisivanje(position);
int Zbroj(position, position, position);
int Umnozak(position, position, position);
int UnosPolinoma(char*, position);
position Stvaranje(int, int);
int SortiraniUnos(position, position);
int Brisanje(position, position);
position Trazi(position, position);
int UnosIza(position, position);

int main()
{
	broj head1;
	head1.next = NULL;
	position pol1 = &head1;
	broj head2;
	head2.next = NULL;
	position pol2 = &head2;


	char imeDat[] = "lista.txt";
	CitanjeIzDat(pol1, pol2, imeDat);

	printf("\n1. polinom:\n");
	Ispisivanje(pol1->next);

	printf("\n2. polinom:\n");
	Ispisivanje(pol2->next);

	broj head3;
	head3.next = NULL;
	position pol3 = &head3;

	broj head4;
	head4.next = NULL;
	position pol4 = &head4;

	Zbroj(pol1, pol2, pol3);
	printf("\nZbroj polinoma:\n");
	Ispisivanje(pol3->next);

	Umnozak(pol1, pol2, pol4);
	printf("\nUmnozak polinoma:\n");
	Ispisivanje(pol4->next);


	return 0;


}

int CitanjeIzDat(position p1, position p2, char* ime)
{
	char buffer[MAX_LINE] = { 0 };

	FILE* f = NULL;
	f = fopen(ime, "r");

	if (!f) {
		printf("Datoteka %s ne postoji\r\n", ime);
		return ERROR;
	}

	fgets(buffer, MAX_LINE, f);
	UnosPolinoma(buffer, p1);

	fgets(buffer, MAX_LINE, f);
	UnosPolinoma(buffer, p2);

	fclose(f);

	return EXIT_SUCCESS;

}

int UnosPolinoma(char* buff, position head)
{
	int pomak = 0;
	int koef = 0;
	int eksp = 0;
	int n = 0;
	position temp = NULL;

	while (buff[pomak] != '\0')
	{
		int result = sscanf(buff + pomak, "%d %d %n", &koef, &eksp, &n);
		pomak += n;


		temp = Stvaranje(koef, eksp);
		if (!temp)
		{
			return ERROR;
		}

		SortiraniUnos(temp, head);
	}
	return EXIT_SUCCESS;

}

position Stvaranje(int koef, int eksp)
{
	position polinom = NULL;
	polinom = (position)malloc(sizeof(broj));

	if (!polinom)
	{
		return ERROR;
	}

	polinom->eksponent = eksp;
	polinom->koeficijent = koef;
	polinom->next = NULL;

	return polinom;
}

int SortiraniUnos(position element, position head)
{
	position temp = head->next;
	position prethodni = NULL;

	while ((temp != NULL) && (element->eksponent) < (temp->eksponent))
	{
		temp = temp->next;
	}

	if ((temp != NULL) && (element->eksponent == temp->eksponent))
	{
		if (temp->koeficijent + element->koeficijent == 0)
		{
			Brisanje(temp, head);
			free(element);
		}
		else
		{
			temp->koeficijent = temp->koeficijent + element->koeficijent;
		}
	}
	else {
		prethodni = Trazi(head, temp);
		UnosIza(prethodni, element);
	}

	return EXIT_SUCCESS;
}

int Brisanje(position tmp, position head)
{
	position temp = NULL;
	temp = Trazi(head, tmp);
	temp->next = tmp->next;
	free(tmp);

	return EXIT_SUCCESS;
}

position Trazi(position head, position tmp)
{
	position temp = head;
	while (temp->next != tmp)
	{
		temp = temp->next;
	}

	return temp;
}

int UnosIza(position prev, position tmp)
{
	tmp->next = prev->next;
	prev->next = tmp;

	return EXIT_SUCCESS;
}

int Ispisivanje(position head)
{
	position temp = head;
	printf("\n");
	while (temp != NULL)
	{
		printf("%dX^%d ", temp->koeficijent, temp->eksponent);
		temp = temp->next;
	}
	printf("\n");

	return EXIT_SUCCESS;
}

int Zbroj(position p1, position p2, position zbroj)
{
	position temp = NULL;
	position tmp = NULL;
	position ostali = NULL;
	while (p1 && p2)
	{
		if (p1->eksponent == p2->eksponent)
		{
			temp = Stvaranje(p1->koeficijent + p2->koeficijent, p1->eksponent);
			SortiraniUnos(temp, zbroj);
			p1 = p1->next;
			p2 = p2->next;
		}
		else if ((p1->eksponent) > (p2->eksponent))
		{
			temp = Stvaranje(p1->koeficijent, p1->eksponent);
			SortiraniUnos(temp, zbroj);
			p1 = p1->next;
		}
		else if ((p1->eksponent) < (p2->eksponent))
		{
			temp = Stvaranje(p2->koeficijent, p2->eksponent);
			SortiraniUnos(temp, zbroj);
			p2 = p2->next;
		}



	}
	if (p1 != NULL)
	{
		while (p1 != NULL)
		{

			ostali = Stvaranje(p1->koeficijent, p1->eksponent);
			SortiraniUnos(ostali, zbroj);
			p1 = p1->next;

		}
	}
	else if (p2 != NULL)
	{
		while (p2 != NULL)
		{
			ostali = Stvaranje(p2->koeficijent, p2->eksponent);
			SortiraniUnos(ostali, zbroj);
			p2 = p2->next;
		}
	}
	return EXIT_SUCCESS;
}
int Umnozak(position p1, position p2, position umnozak)
{
	position i = NULL;
	position j = NULL;
	position element;

	for (i = p1->next; i != NULL; i = i->next) {
		for (j = p2->next; j != NULL; j = j->next) {
			element = Stvaranje(i->koeficijent * j->koeficijent, i->eksponent + j->eksponent);
			SortiraniUnos(element, umnozak);
		}
	}
	return EXIT_SUCCESS;
}