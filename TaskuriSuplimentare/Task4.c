#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char* specie;
	int varstaMaxima;
	float greutateMedie;
	long int nrTotal;
} Mamifer;

Mamifer* adaugaMamiferInVector(Mamifer* vector, Mamifer mamifer, int* dim) {
	Mamifer* copie = (Mamifer*)malloc(((*dim) + 1) * sizeof(Mamifer));

	for (int i = 0; i < *dim; i++) {
		copie[i] = vector[i];
	}
	copie[*dim] = mamifer;

	if (vector != NULL)
		free(vector);

	return copie;
}

Mamifer* citireTXT(const char* numeFisier, int* dimVector) {
	Mamifer* vector = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (!f) printf("Eroare la deschidere\n");
	else {
		(*dimVector) = 0;
		char buffer[100];
		char delimitator[] = ",\n";
		while (fgets(buffer, 99, f) != NULL) {
			Mamifer m;
			char* token = strtok(buffer, delimitator);
			m.specie = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(m.specie, token);

			token = strtok(NULL, delimitator);
			m.varstaMaxima = atoi(token);

			token = strtok(NULL, delimitator);
			m.greutateMedie = atof(token);

			token = strtok(NULL, delimitator);
			m.nrTotal = atol(token);

			vector = adaugaMamiferInVector(vector, m, dimVector);
			(*dimVector)++;
		}
	}

	return vector;
}

void printMamifer(Mamifer m) {
	printf("%s\n%d\n%5.2f\n%ld\n", m.specie, m.varstaMaxima, m.greutateMedie, m.nrTotal);
	printf("----------------------\n");
}

void printVector(Mamifer* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		printMamifer(vector[i]);
	}
}

void dezalocareVector(Mamifer** vector, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*vector)[i].specie);
		(*vector)[i].specie = NULL;
	}
	free(*vector);
	(*vector) = NULL;
	(*dim) = 0;
	printf("Vectorul a fost dezalocat cu succes!");
}

Mamifer** adaugaElementeInMatrice(Mamifer* vector, int dim) {

	Mamifer** copie = (Mamifer**)malloc(dim * sizeof(Mamifer*));
	for (int i = 0; i < dim; i++) {
		copie[i] = (Mamifer*)malloc(4 * sizeof(Mamifer));
		for (int j = 0; j < 4; j++) {
			copie[i][j].greutateMedie = vector[i].greutateMedie;
			copie[i][j].nrTotal = vector[i].nrTotal;
			copie[i][j].varstaMaxima = vector[i].varstaMaxima;

			copie[i][j].specie = (char*)malloc(strlen(vector[i].specie) + 1);
			strcpy(copie[i][j].specie, vector[i].specie);
		}
	}
	return copie;
}

void printMatrice(Mamifer** matrice, int dim) {
	for (int i = 0; i < dim; i++) {
		printMamifer(*(matrice)[i]);
	}
}

void printMatriceCuConditie(Mamifer** matrice, int dim) {
	for (int i = 0; i < dim; i++) {
		if (matrice[i]->varstaMaxima < 30) {
			printMamifer(*(matrice)[i]);
		}
	}
}

void dezalocareMatrice(Mamifer*** matrice, int dim) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < 4; j++) {
			free((*matrice)[i][j].specie);
		}
		free((*matrice)[i]);
	}
	free(*matrice);
}

void main() {
	Mamifer* vectorMamifere = NULL;
	int dimVector = 0;
	vectorMamifere = citireTXT("FisierMamifere.txt", &dimVector);
	printf("Dim vector: %d \n", dimVector);
	printVector(vectorMamifere, dimVector);

	printf("\n-------------------MATRICE-----------------------\n");
	Mamifer** matriceMamifer = (Mamifer**)malloc(dimVector * sizeof(Mamifer*));

	matriceMamifer = adaugaElementeInMatrice(vectorMamifere, dimVector);
	printMatrice(matriceMamifer, dimVector);

	printf("\n---------------MATRICE CU CONDITIE------------------\n");
	printMatriceCuConditie(matriceMamifer, dimVector);


	printf("\n");


	dezalocareMatrice(&matriceMamifer, dimVector);
	dezalocareVector(&vectorMamifere, &dimVector);
}

/*Delfin,270,200000,20
Leu,35,200,54342
Tigru siberian,44,250,43534
Urs polar,50,700,22020
Rechin alb,30,800,23000
Elefant,60,6000,100000
Oaie,12,100,100000000
Cal,30,420,55000000
Jaguar,15,100,20000
Maimuta,20,33,4423234*/