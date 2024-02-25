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
	printf("------Mamifer citit-------\n");
	printf("Specie: %s\n", m->specie);
	printf("Varsta: %d\n", m->varstaMaxima);
	printf("Greutate: %.2f\n", m->greutateMedie);
	printf("Varsta: %d\n", m->nrTotal);
}

void main() {
	Mamifer m1;
	m1 = citire();

	display(&m1);

	printf("\nGreutatea tuturor mamiferelor \"%s\": %.2f\n", m1.specie, GreutateTotala(&m1));
	int val;
	printf("Noua Varsta: "); scanf("%d", &val);

	setVarstaMaxima(&m1, val);

	display(&m1);

	printf("\n%d", getVarstaMaxima(&m1));
	free(m1.specie);
}