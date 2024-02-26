#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char* specie;
	int varstaMaxima;
	float greutateMedie;
	long int nrTotal;
} Mamifer;

Mamifer citire() {
	Mamifer m;

	m.specie = (char*)malloc(100 * sizeof(char));
	printf("Specie: "); fgets(m.specie, 100, stdin);
	m.specie[strcspn(m.specie, "\n")] = NULL;
	printf("Varsta: "); scanf("%d", &m.varstaMaxima);
	printf("Greutate: "); scanf("%f", &m.greutateMedie);
	printf("Numar total pe glob: "); scanf("%d", &m.nrTotal);

	return m;
}

double GreutateTotala(Mamifer* m1) {
	double val;
	val = m1->greutateMedie * m1->nrTotal;
	return val;
}

int getVarstaMaxima(Mamifer* m) {
	return m->varstaMaxima;
}

void setVarstaMaxima(Mamifer* m1, int nouaVarstaMaxima) {
	if (nouaVarstaMaxima > 0) {
		m1->varstaMaxima = nouaVarstaMaxima;
	}
	else printf("Varsta trebuie sa fie pozitiva");
}

void display(Mamifer* m) {
	printf("Specie: %s\n", m->specie);
	printf("Varsta: %d\n", m->varstaMaxima);
	printf("Greutate: %.2f\n", m->greutateMedie);
	printf("Varsta: %d\n\n", m->nrTotal);
}

Mamifer initializareMamifer(const char* specie, int vm, float gm, long int nr) {
	Mamifer m;
	if (specie != NULL) {
		m.specie = malloc(strlen(specie) + 1);
		strcpy(m.specie, specie);
	}
	else {
		m.specie = malloc(strlen("N/A") + 1);
		strcpy(m.specie, "N/A");
	}

	m.nrTotal = nr;
	m.greutateMedie = gm;
	m.varstaMaxima = vm;

	return m;
}

void dezalocare(Mamifer* m) {
	free(m->specie);
	m->specie = NULL;
}

//VECTOR:

void adaugaMamiferVector(Mamifer** vector, int* dim, Mamifer* m) {
	*dim += 1;
	*vector = (Mamifer*)realloc(*vector, (*dim) * sizeof(Mamifer));
	(*vector)[(*dim - 1)] = *m;
}

void printMamiferVector(Mamifer* vector, int dim) {
	printf("\n");
	for (int i = 0; i < dim; i++) {
		printf("Mamifer %d:\n", i + 1);
		display(&vector[i]);
	}
}

Mamifer* copiereVector(Mamifer* m, int dim, int limitaVarsta, int* size) {

	Mamifer* v = (Mamifer*)malloc(*size * sizeof(Mamifer));

	for (int i = 0; i < dim; i++) {
		if (m[i].varstaMaxima < limitaVarsta) {
			(*size) += 1;
			v = (Mamifer*)realloc(v, (*size) * sizeof(Mamifer));
			v[(*size) - 1] = m[i];

		}
	}

	return v;
}

Mamifer* concatenareVector(Mamifer* m1, Mamifer* m2, int dim1, int dim2, int* dimVC) {

	*dimVC = dim1 + dim2;
	Mamifer* concat = (Mamifer*)malloc((*dimVC) * sizeof(Mamifer));

	for (int i = 0; i < dim1; i++) {
		concat[i] = m1[i];
	}
	for (int i = 0; i < dim2; i++) {
		concat[dim1 + i] = m2[i];
	}

	return concat;
}

void main() {
	//Mamifere:----------------------------------------------------
	Mamifer m1;
	m1 = citire();
	display(&m1);

	Mamifer m2;
	m2.specie = (char*)malloc(strlen("Delfin") + 1);
	strcpy(m2.specie, "Delfin");
	m2.greutateMedie = 40;
	m2.nrTotal = 200000;
	m2.varstaMaxima = 20;
	display(&m2);

	Mamifer m3 = initializareMamifer("Leu", 35, 200, 54342);
	display(&m3);

	Mamifer m4 = initializareMamifer("Tigru siberian", 44, 250, 43534);
	display(&m4);

	Mamifer m5 = initializareMamifer("Urs polar", 50, 700, 22020);
	display(&m5);
	/////////////////////////////////////////////////////////////////

	//VECTOR:
	printf("--------------------VECTOR 1-------------------");
	int dimVector = 0;
	Mamifer* vectorMamifere = (Mamifer*)malloc(dimVector * sizeof(Mamifer));

	adaugaMamiferVector(&vectorMamifere, &dimVector, &m1);
	adaugaMamiferVector(&vectorMamifere, &dimVector, &m2);
	adaugaMamiferVector(&vectorMamifere, &dimVector, &m3);
	adaugaMamiferVector(&vectorMamifere, &dimVector, &m4);
	adaugaMamiferVector(&vectorMamifere, &dimVector, &m5);

	printMamiferVector(vectorMamifere, dimVector);

	printf("DIMENSIUNE VECTOR: %d\n", dimVector);

	int dimVector2 = 0;
	Mamifer* vectorMamifere2 = copiereVector(vectorMamifere, dimVector, 10, &dimVector2);
	printf("DIMENSIUNE VECTOR 2: %d\n", dimVector2);
	printf("----------------VECTOR 2-----------------");
	printMamiferVector(vectorMamifere2, dimVector2);

	int dimVector3 = 0;
	Mamifer* vectorMamifere3 = (Mamifer*)malloc(dimVector3 * sizeof(Mamifer));
	adaugaMamiferVector(&vectorMamifere3, &dimVector3, &m4);
	adaugaMamiferVector(&vectorMamifere3, &dimVector3, &m5);
	printf("----------------VECTOR 3-----------------");
	printMamiferVector(vectorMamifere3, dimVector3);

	int dimVectorConcatenat;
	Mamifer* vectorConcatenat = concatenareVector(vectorMamifere2, vectorMamifere3, dimVector2, dimVector3, &dimVectorConcatenat);
	printf("DIMENSIUNE VECTOR CONCATENAT: %d\n", dimVectorConcatenat);
	printf("----------------VECTOR CONCATENAT-----------------");
	printMamiferVector(vectorConcatenat, dimVectorConcatenat);

	//DEZALOCARI:-------------------------------------------------------
	free(m1.specie);
	m1.specie = NULL;
	dezalocare(&m2);
	dezalocare(&m3);
	free(vectorMamifere);
	vectorMamifere = NULL;
	free(vectorMamifere2);
	vectorMamifere = NULL;
	free(vectorMamifere3);
	vectorMamifere3 = NULL;
	free(vectorConcatenat);
	vectorConcatenat = NULL;

}