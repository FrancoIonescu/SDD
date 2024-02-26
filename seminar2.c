#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void citireVector(const char* numeFisier, int** vector, int* dimensiune)
{
	FILE* streamFisier = NULL;
	streamFisier = fopen("Vector.txt", "r");
	if (streamFisier != NULL)
	{
		fscanf(streamFisier,"%d",dimensiune);
		*vector = (int**)malloc(sizeof(int*) * (*dimensiune));
		for (int i = 0; i < *dimensiune; i++)
		{
			fscanf(streamFisier, "%d", &(*vector)[i]);
		}

	}
	fclose(streamFisier);
}

 struct Produs
{
	 float pret;
	 int id;
	 char* denumire;
};

 struct Produs preluareProdusDinFisier(FILE* file)
 {
	 struct Produs produs;
	 if (file != NULL)
	 {
		 char buffer[20];

		 fgets(buffer, 10, file);
		 produs.pret = atof(buffer);

		 fgets(buffer, 5, file);
		 produs.id = atoi(buffer);

		 fgets(buffer, 20, file);
		 char* denumire = strtok(buffer ,"\n");
		 produs.denumire = malloc(sizeof(char) * (strlen(denumire) + 1));
		 strcpy(produs.denumire, &denumire);
	 }
	 return produs;
 }

 void afisareProdus(struct Produs produs)
 {
	 printf("\nProdusul %s are codul %d si pretul %.2f lei", produs.denumire, produs.id, produs.pret);
 }

int main()
{

	int val1 = 0, val2 = 0;
	FILE* streamFisier = NULL;
	streamFisier = fopen("Fisier.txt", "r");

	if (streamFisier != NULL)
	{
		fscanf(streamFisier, "%d", &val1);
		fscanf(streamFisier, "%d", &val2);
	}

	fclose(streamFisier);

	printf("\n Val1 = %d, Val2 = %d", val1, val2);

	int* vector = NULL;
	int dimensiune = 0;
	citireVector("Vector.txt", &vector, &dimensiune);

	for (int i = 0; i < dimensiune; i++)
	{
		printf("\n vector[%i] = %d", i, vector[i]);
	}

	FILE* file = NULL;
	file = fopen("Produs.txt", "r");
	struct Produs produs = preluareProdusDinFisier(file);

	afisareProdus(produs);

	free(vector);


	return 0;
}