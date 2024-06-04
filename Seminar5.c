#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>
// Tema : de folosit functia realloc la conversie

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
	Nod* prev;
};

struct LDI {
	Nod* prim;
	Nod* ultim;

};

void afisareMasina(Masina masina) {
	printf("\n Masina %s are seria %d.", masina.producator, masina.serie);
}

Masina initMasina(const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void inserareLaInceput(Masina masina, LDI* ldi) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->prev = NULL;
	nou->next = ldi->prim;
	if (ldi->prim != NULL)
	{
		ldi->prim->prev = nou;
		ldi->prim = nou;
	}
	else {
		ldi->ultim = nou;
		ldi->prim = nou;
	}
}

void traversareLista(LDI lista, int* nrMasini)
{
	while (lista.prim != NULL)
	{
		afisareMasina(lista.prim->inf);
		(*nrMasini)++;
		lista.prim = lista.prim->next;
	}
}

void inserareLaFinal(Masina masina, LDI* ldi) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->prev = ldi->ultim;
	nou->next = NULL;
	if (ldi->ultim != NULL)
	{
		ldi->ultim->next = nou;
		ldi->ultim = nou;
	}
	else {
		ldi->ultim = nou;
		ldi->prim = nou;
	}
}

void dezalocare(LDI* lista)
{
	Nod* copie = lista->prim;
	while (copie != NULL)
	{
		free(copie->inf.producator);
		copie = copie->next;
		if (copie != NULL)
		{
			free(copie->prev);
		}
	}
	free(lista->ultim);
	lista->prim = lista->ultim = NULL;
}

void conversieLaVector(LDI lista, Masina** vectorMasini)
{
	int nrMasini = 0;
	while (lista.prim)
	{
		(*vectorMasini)[nrMasini] = initMasina(lista.prim->inf.producator, lista.prim->inf.serie);
		nrMasini++;
		lista.prim = lista.prim->next;
	}
}

void traversareListaCirculara(LDI lista)
{
	Nod* aux = lista.prim;
	do
	{
		afisareMasina(aux->inf);
		aux = aux->next;
	} while (aux != lista.prim);
}

void stergere(LDI* ldi, const char* nume) {
	if (ldi) {
		Nod* copie = ldi->prim;
		while (copie) {
			if (strcmp(copie->info.nume, nume) == 0) {
				if (copie == ldi->prim) {
					ldi->prim = copie->next;
					if (ldi->prim) {
						ldi->prim->prev = NULL;
					}
					else {
						ldi->ultim = NULL;
					}
				}
				else if (copie == ldi->ultim) {
					ldi->ultim = copie->prev;
					ldi->ultim->next = NULL;
				}
				else {
					copie->next->prev = copie->prev;
					copie->prev->next = copie->next;
				}
				free(copie->info.nume);
				copie->info.nume = NULL;
				free(copie);
				copie = NULL;
				break;
			}

			copie = copie->next;
		}
	}
}

Student preluareStudentDinFisier(FILE* file) {
	Student student;

	char buffer[30];
	fgets(buffer, 30, file);
	char* nume = strtok(buffer, "\n");
	student.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(student.nume, nume);
	fgets(buffer, 30, file);
	student.varsta = atoi(buffer);

	return student;
}

void preluareStudentiInVector(FILE* file, Student** studenti, int* dimensiune) {
	while (!feof(file)) {
		*studenti = (Student*)realloc(*studenti, ((*dimensiune) + 1) * sizeof(Student));
		(*studenti)[*dimensiune] = preluareStudentDinFisier(file);
		(*dimensiune)++;
	}
}

void main() {

	LDI lista;
	int nrMasini = 0;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareLaInceput(initMasina("Ford", 1), &lista);
	inserareLaInceput(initMasina("Renault", 2), &lista);
	inserareLaInceput(initMasina("Mercedes", 3), &lista);
	inserareLaFinal(initMasina("BMW", 4), &lista);
	
	traversareLista(lista, &nrMasini);
	Masina* vectorMasini = (Masina*)malloc(sizeof(Masina) * nrMasini);
	conversieLaVector(lista, &vectorMasini);
	printf("\nAfisare masini din vector: ");
	for (int i = 0; i < nrMasini; i++)
	{
		afisareMasina(vectorMasini[i]);
		free(vectorMasini[i].producator);
	}
	free(vectorMasini);

	lista.ultim->next = lista.prim;
	lista.prim->prev = lista.ultim;
	traversareListaCirculara(lista);

	//dezalocare(&lista);
}
