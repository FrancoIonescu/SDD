#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

void interschimbare(int* var1, int* var2)
{
	int aux;
	aux = *var1;
	*var1 = *var2;
	*var2 = aux;
}

void citireDeLaTastatura(int** vector, int* dimensiune)
{
	printf("Dimensiune: ");
	scanf("%d", dimensiune);

	*vector = (int**)malloc(*dimensiune * sizeof(int*));

	for(int i = 0; i < *dimensiune; i++)
	{
		printf("Vector[%i]: ", i);
		scanf("%d", &(*vector)[i]);
		//sau scanf("%d", *vector + i);
	}
}

void afisare(int* vector,int dimensiune)
{
	for (int i = 0; i < dimensiune; i++)
	{
		printf("\nvector[%d] = %d", i, vector[i]);
	}
}

int main()
{

	int numarIntreg;
	char caracter;
	float numarReal;

	numarIntreg = 7;
	caracter = 'A';
	numarReal = 70.5f;

	printf("%d\n", numarIntreg);
	printf("%c\n", caracter);
	printf("%d\n", caracter);
	printf("%.2f\n", numarReal);

	char sirCaractere[8];
	for (int i = 0; i < 8; i++)
	{
		sirCaractere[i] = 97 + i;
	}
	sirCaractere[7] = '\0';
	printf("%s\n", sirCaractere);

	char* sirAlocatDinamic = (char*)malloc(6 * sizeof(char));
	for (int i = 0; i < 6; i++)
	{
		sirAlocatDinamic[i] = 65 + i;
	}
	sirAlocatDinamic[5] = '\0';
	printf("%s\n", sirAlocatDinamic);
	free(sirAlocatDinamic);
	
	int var1 = 1, var2 = 10;
	interschimbare(&var1, &var2);
	printf("\n var1 = %d, var2 = %d\n", var1, var2);

	int* vector;
	int dimensiune;
	citireDeLaTastatura(&vector, &dimensiune);
	afisare(vector, dimensiune);

	return 0;
}
