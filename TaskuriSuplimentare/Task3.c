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
	printf("Specie: "); gets(m.specie);
	printf("Varsta: "); scanf("%d", &m.varstaMaxima);
	printf("Greutate: "); scanf("%f", &m.greutateMedie);
	printf("Numar total pe glob: "); scanf("%ld", &m.nrTotal);

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
	printf("Numar total pe glob: %ld\n\n", m->nrTotal);
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

//FISIERE-------------------------------------------------
void adaugareTXT(Mamifer m, FILE* f, int* nr) {
	fprintf(f, "%s\n", m.specie);
	fprintf(f, "%d\n", m.varstaMaxima);
	fprintf(f, "%.2f\n", m.greutateMedie);
	fprintf(f, "%ld\n", m.nrTotal);
	fprintf(f, "\n");
	++(*nr);
}

//INCERCARI CITIRE DIN FISIER INTR-UN VECTOR - EROARE--------------------------------

//void citireTXT(Mamifer* m,char*numef,int* dim) {
//
//	FILE* f = fopen(numef, "r");
//	if (!f) printf("Eroare la deschidere fisier");
//	else {
//		Mamifer mamifer;
//		while (!feof(f)) {
//			
//			mamifer.specie = (char*)malloc(100 * sizeof(char));
//			fgets(mamifer.specie, 100, f);
//			mamifer.specie[strcspn(mamifer.specie, "\n")] = NULL;
//
//			fscanf(f, "%d", &mamifer.varstaMaxima);
//			fscanf(f, "%.2f", &mamifer.greutateMedie);
//			fscanf(f, "%ld", &mamifer.nrTotal);
//
//			adaugaMamiferVector(&m, dim, &mamifer);
//			
//			fgetc(f);//pentru \n din cadrul fisierului la finalul unui obiect
//		}
//
//		fclose(f);
//	}
//}

//void citireTXT(Mamifer* m, int* dim) {
//	FILE* f = fopen("Elemente.txt", "r");
//
//	if (!f) printf("Eroare la deschidere");
//	else {
//		do {
//			Mamifer mam;
//			mam.specie = (char*)malloc(100 * sizeof(char));
//			fscanf(f, "%[^\n]", mam.specie);
//			fgetc(f);
//			fscanf(f, "%d", &mam.varstaMaxima);
//			fgetc(f);
//			fscanf(f, "%.2f", &mam.greutateMedie);
//			fgetc(f);
//			fscanf(f, "%ld", &mam.nrTotal);
//			fgetc(f);
//			fgetc(f);
//			(*dim)++; //dim=20?
//		} while (!feof(f));
//		fclose(f);
//	}
//}
//-----------------------------------------------------------------------

void main() {
	//Mamifere:----------------------------------------------------
	Mamifer m1;
	m1 = citire();
	display(&m1);

	Mamifer m2;
	m2.specie = (char*)malloc(strlen("Delfin") + 1);
	strcpy(m2.specie, "Delfin");
	m2.greutateMedie = 270;
	m2.nrTotal = 200000;
	m2.varstaMaxima = 20;
	display(&m2);

	Mamifer m3 = initializareMamifer("Leu", 35, 200, 54342);
	display(&m3);

	Mamifer m4 = initializareMamifer("Tigru siberian", 44, 250, 43534);
	display(&m4);

	Mamifer m5 = initializareMamifer("Urs polar", 50, 700, 22020);
	display(&m5);

	Mamifer m6 = initializareMamifer("Rechin alb", 30, 800, 23000);
	display(&m6);

	Mamifer m7 = initializareMamifer("Elefant", 60, 6000, 100000);
	display(&m7);

	Mamifer m8 = initializareMamifer("Oaie", 12, 100, 100000000);
	display(&m8);

	Mamifer m9 = initializareMamifer("Cal", 30, 420, 55000000);
	display(&m9);

	Mamifer m10 = initializareMamifer("Jaguar", 15, 100, 20000);
	display(&m10);
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
	adaugaMamiferVector(&vectorMamifere, &dimVector, &m6);
	adaugaMamiferVector(&vectorMamifere, &dimVector, &m7);
	adaugaMamiferVector(&vectorMamifere, &dimVector, &m8);
	adaugaMamiferVector(&vectorMamifere, &dimVector, &m9);
	adaugaMamiferVector(&vectorMamifere, &dimVector, &m10);

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

	//FISIERE---------------------------------------
	int nrElemente = 0;

	char* numeFisierElemente = "Elemente.txt";
	FILE* ft = fopen(numeFisierElemente, "w");
	adaugareTXT(m1, ft, &nrElemente);
	adaugareTXT(m2, ft, &nrElemente);
	adaugareTXT(m3, ft, &nrElemente);
	adaugareTXT(m4, ft, &nrElemente);
	adaugareTXT(m5, ft, &nrElemente);
	adaugareTXT(m6, ft, &nrElemente);
	adaugareTXT(m7, ft, &nrElemente);
	adaugareTXT(m8, ft, &nrElemente);
	adaugareTXT(m9, ft, &nrElemente);
	adaugareTXT(m10, ft, &nrElemente);
	fclose(ft);

	char* numef = "ZOO.txt";
	FILE* f = fopen(numef, "w");

	for (int i = 0; i < dimVector; i++) {
		fprintf(f, "%s\n", vectorMamifere[i].specie);
		fprintf(f, "%d\n", vectorMamifere[i].varstaMaxima);
		fprintf(f, "%.2f\n", vectorMamifere[i].greutateMedie);
		fprintf(f, "%ld\n", vectorMamifere[i].nrTotal);
		fprintf(f, "\n");
	}

	fclose(f);

	printf("NrElementeFisier: %d", nrElemente);
	//int dimVectorFisier = 0;
	//Mamifer* vectorFisier = (Mamifer*)malloc(dimVectorFisier * sizeof(Mamifer));
//	citireTXT(vectorFisier,&dimVectorFisier);
//	printf("Dimensiune fisier: %d\n",dimVectorFisier);
//	printf("------------ELEMENTE FISIER-----------------\n");
//	printMamiferVector(vectorFisier, dimVectorFisier);

	//DEZALOCARI:-------------------------------------------------------
	free(m1.specie);
	m1.specie = NULL;
	dezalocare(&m2);
	dezalocare(&m3);
	dezalocare(&m4);
	dezalocare(&m5);
	dezalocare(&m6);
	dezalocare(&m7);
	dezalocare(&m8);
	dezalocare(&m9);
	dezalocare(&m10);

	free(vectorMamifere);
	vectorMamifere = NULL;
	free(vectorMamifere2);
	vectorMamifere = NULL;
	free(vectorMamifere3);
	vectorMamifere3 = NULL;
	free(vectorConcatenat);
	vectorConcatenat = NULL;
	/*free(vectorFisier);
	vectorFisier = NULL;*/

}