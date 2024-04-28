#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	char* producator;
	int serie;
	int id;
};

struct Nod {
	Masina inf;
	Nod* next;
};

void afisareMasina(Masina masina) {
	printf("\n%ld. Masina %s are seria %d.",masina.id, masina.producator, masina.serie);
}

Masina initMasina(int id, const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.id = id;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void push(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = *cap;
	*cap = nou;
}

void traversareLista(Nod* cap) {
	while (cap) {
		afisareMasina(cap->inf);
		cap = cap->next;
	}
}

void put(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = NULL;
	if ((*cap) != NULL) {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

int nrMasini(Nod* cap)
{
	int nrMasini = 0;
	while (cap != NULL)
	{
		nrMasini++;
		cap = cap->next;
	}

	return nrMasini;
}

Nod* stergereUltimNod(Nod* cap, int nrMasini)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod) * (nrMasini - 1));
	
	for (int i = 0; i < nrMasini; i++)
	{
		nou->inf = cap->inf;
		nou = nou->next;
		cap = cap->next;
	}

	return nou;
	
}

Masina pop(Nod** varf) {
	Masina masina;
	masina.id = -1;
	masina.producator = NULL;
	masina.serie = -1;
	if (*varf) {
		masina = (*varf)->inf;
		Nod* temp = *varf;
		(*varf) = (*varf)->next;
		free(temp);
	}

	return masina;
}

Masina cautareDupaId(Nod** stiva, long id)
{
	Masina masina;
	masina.id = -1;
	masina.serie = -1;
	masina.producator = NULL;
	Nod* stivaAuxiliara = NULL;
	while ((*stiva) != NULL && (*stiva)->inf.id != id)
	{
		push(&stivaAuxiliara, pop(stiva));
	}
	if ((*stiva) != NULL)
	{
		masina = pop(stiva);
	}

	while (stivaAuxiliara)
	{
		push(stiva, pop(&stivaAuxiliara));
	}

	return masina;
}

void main() {
	Nod* stiva = NULL;
	Masina masina;
	push(&stiva, initMasina(1, "Renault", 1234));
	push(&stiva, initMasina(2, "Ford", 5678));
	push(&stiva, initMasina(3, "Ford", 5679));
	push(&stiva, initMasina(4, "Ford", 5677));
	push(&stiva, initMasina(5, "Peugeot", 9101));
	push(&stiva, initMasina(6, "Bmw", 1213));

	Masina masinaCautata = cautareDupaId(&stiva, 3);
	afisareMasina(masinaCautata);
	free(masinaCautata.producator);
	printf("\n Stiva: ");

	//int indexMasini = nrMasini(stiva);
	//stiva = stergereUltimNod(&stiva, indexMasini);

	while (stiva) {
		masina = pop(&stiva);
		afisareMasina(masina);
		free(masina.producator);
	}

	Nod* coada = NULL;
	put(&coada, initMasina(1, "Renault", 1234));
	put(&coada, initMasina(2, "Ford", 5678));
	put(&coada, initMasina(3, "Ford", 5679));
	put(&coada, initMasina(4, "Ford", 5677));
	put(&coada, initMasina(5, "Peugeot", 9101));
	put(&coada, initMasina(6, "Bmw", 1213));
	printf("Coada: \n");
	//int indexMasini = nrMasini(stiva);
	//stiva = stergereUltimNod(&stiva, indexMasini);

	while (coada) {
		masina = pop(&coada);
		afisareMasina(masina);
		free(masina.producator);
	}


	
}
