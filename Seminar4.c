#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
// TEST SAPTAMANA 8
// PRIMUL ASSIGNMENT SAPTAMANA 6

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	char* producator;
	int serie;

};

struct Nod {
	Masina inf;
	Nod* next;
};

void afisareMasina(Masina masina)
{
	printf("Masina %s are seria %d\n", masina.producator,masina.serie);
}

Masina initMasina(const char* producator, int serie)
{
	Masina masinaNoua;
	masinaNoua.producator =(char*)malloc((strlen(producator) + 1) * sizeof(char));
	strcpy(masinaNoua.producator, producator);
	masinaNoua.serie = serie;

	return masinaNoua;
}

void inserareLaInceput(Nod** cap, Masina masina)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina; // shallow copy util
	nou->next = *cap;
	*cap = nou;
}

void traversareLista(Nod* cap)
{
	while (cap)
	{
		afisareMasina(cap->inf);
		cap = cap->next;
	}
}

void inserareLaFinal(Nod** cap, Masina masina)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = NULL;
	if (*cap != NULL)
	{
		Nod* aux = *cap;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		*cap = nou;
	}

}

//void cautareMasina(Nod* cap, char* denumireMasina)
//{
//	int numarMasini = 0;
//	while ((*cap) != NULL)
//	{
//		Nod* copie = *cap;
//		if(strcmp(copie->inf.producator,denumireMasina) == 0);
//	}
//}

int cautareMasina(Nod* cap, char* producator)
{
	int numar = 0;
	while (cap != NULL)
	{
		if (strcmp(cap->inf.producator, producator) == 0)
		{
			numar++;
		}
		cap = cap->next;
	}
	return numar;
}

void dezalocare(Nod** cap)
{
	while ((*cap) != NULL)
	{
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie->inf.producator);
		free(copie);
	}
}

int main()
{
	Nod* cap = NULL;
	inserareLaInceput(&cap, initMasina("Renault",1234));
	inserareLaInceput(&cap, initMasina("Ford", 5678));
	inserareLaInceput(&cap, initMasina("Mercedes", 4321));
	inserareLaInceput(&cap, initMasina("Dacia", 8765));
	inserareLaFinal(&cap, initMasina("BMW", 2345));

	traversareLista(cap);

	int nrAparitii = cautareMasina(cap, "Ford");
	printf("%d", nrAparitii);
	


	return 0;

}
