// Assignment arbori oarecare sau ultimele 2 seminare
// Assignment arbori oarecare sau ultimele 2 seminare
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Prajitura Prajitura;
typedef struct Nod Nod;

struct Prajitura {
	int id;
	char* denumire;
	float pret;
};

struct Nod {
	Prajitura prajitura;
	Nod* copilStanga;
	Nod* copilDreapta;
};

void afisarePrajitura(Prajitura prajitura) {
	printf("\n %d. Prajitura %s costa %.2f lei.", prajitura.id, prajitura.denumire, prajitura.pret);
}

Prajitura initPrajitura(int id, char* denumire, float pret) {
	Prajitura prajitura;
	prajitura.pret = pret;
	prajitura.id = id;
	prajitura.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(prajitura.denumire, denumire);

	return prajitura;
}

void inseareInArbore(Prajitura info, Nod** radacina) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->prajitura = info;
		nou->copilStanga = NULL;
		nou->copilDreapta = NULL;
		*radacina = nou;
	}
	else if (info.id < (*radacina)->prajitura.id) {
		inseareInArbore(info, &(*radacina)->copilStanga);
	}
	else {
		inseareInArbore(info, &(*radacina)->copilDreapta);
	}
}

void parcurgereInOrdine(Nod* radacina) {
	if (radacina) {
		parcurgereInOrdine(radacina->copilStanga);
		afisarePrajitura(radacina->prajitura);
		parcurgereInOrdine(radacina->copilDreapta);
	}
}


void parcurgerePostOrdine(Nod* radacina) {
	if (radacina) {
		parcurgerePostOrdine(radacina->copilStanga);
		parcurgerePostOrdine(radacina->copilDreapta);
		afisarePrajitura(radacina->prajitura);
	}
}

void parcurgerePreOrdine(Nod* radacina) {
	if (radacina) {
		parcurgerePreOrdine(radacina->copilStanga);
		parcurgerePreOrdine(radacina->copilDreapta);
		afisarePrajitura(radacina->prajitura);
	}
}

Prajitura cautarePrajitura(int id, Nod* radacina) {
	if (!radacina) {
		return initPrajitura(-1, "Neinitializat", 0.0f);
	}
	else if (radacina->prajitura.id == id) {
		return initPrajitura(radacina->prajitura.id, radacina->prajitura.denumire, radacina->prajitura.pret);
	}
	else if (id < radacina->prajitura.id) {
		return cautarePrajitura(id, radacina->copilStanga);
	}
	else {
		return cautarePrajitura(id, radacina->copilDreapta);
	}
}

void dezalocare(Nod** radacina) {
	if (*radacina) {
		dezalocare(&(*radacina)->copilStanga);
		dezalocare(&(*radacina)->copilDreapta);
		free((*radacina)->prajitura.denumire);
		free((*radacina));
	}
}

void main() {
	Nod* radacina = NULL;
	inseareInArbore(initPrajitura(5, "Profiterol", 20), &radacina);
	inseareInArbore(initPrajitura(2, "Amandina", 21.5), &radacina);
	inseareInArbore(initPrajitura(7, "Cheesecake", 30), &radacina);
	inseareInArbore(initPrajitura(4, "Ecler", 16), &radacina);
	inseareInArbore(initPrajitura(8, "Lavacake", 30), &radacina);
	inseareInArbore(initPrajitura(6, "Negresa", 21), &radacina);
	printf("Parcurgere in ordine: \n");
	parcurgereInOrdine(radacina);
	printf("\n\nParcurgere post ordine: \n");
	parcurgerePostOrdine(radacina);
	// De implementat pre-ordine PT CA ASTA NU E BUNA CRED!!!
	printf("\n\nParcurgere pre ordine: \n");
	parcurgerePreOrdine(radacina);

	Prajitura prajituraCautata = cautarePrajitura(6, radacina);
	printf("\n\nPrajitura cautata: \n");
	afisarePrajitura(prajituraCautata);
	dezalocare(&radacina);
}
