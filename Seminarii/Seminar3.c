#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h> //pt atoi ascii to int

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune) {
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));

	copie[(*dimensiune)] = aeroport;	//shallow copy
	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];
	}

	if (vector != NULL)
		free(vector);

	(*dimensiune)++;
	return copie;
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi) {
	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL;

	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) { //BUFFER = LINIA PE CARE O CITIM DIN FISIER
		(*nrAeroporturi) = 0;
		char buffer[100];//fie ca-l alocam static, fie dinamic => ii vom da mereu dim 100 -> e mai usor sa folosim static pt dezalocare
		//		fgets(buffer, 99, f);//returneaza adresa a ceea a citit
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;

			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);

			token = strtok(NULL, delimitator); //dupa delimitator, inceputul adresei urmatorului token e NULL
			aeroport.nume = malloc(sizeof(char*) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);

			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);
		}
		fclose(f);
	}

	return vectorAeroporturi;
}

void afisareAeroport(struct Aeroport* aeroport) {
	printf("Aeroportul cu ID: %d cu numele: %s are %d terminale\n", aeroport->id, aeroport->nume, aeroport->nrTerminale);
}

void afisareVectorAeroport(struct Aeroport* aeroporturi, int dim) {
	printf("AFISARE VECTOR:\n");

	for (int i = 0; i < dim; i++) {
		afisareAeroport(&aeroporturi[i]);
	}
}


void dezalocareVector(struct Aeroport** aeroporturi, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*aeroporturi)[i].nume);
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}

struct Aeroport idCautat(struct Aeroport* aeroporturi, int dim, int id) {
	for (int i = 0; i < dim; i++) {
		if (aeroporturi[i].id == id) {
			return aeroporturi[i];
		}
	}
	struct Aeroport aeroport;
	aeroport.id = -1;
	aeroport.nrTerminale = -1;
	aeroport.nume = NULL;

	return aeroport;
}

void main() {
	int dimensiune = 0;

	struct Aeroport* aeroporturi = NULL;
	aeroporturi = citireFisier("aeroporturi.txt", &dimensiune);

	afisareVectorAeroport(aeroporturi, dimensiune);
	dezalocareVector(&aeroporturi, &dimensiune);

}

//txt: 
//1, Otopeni, 20
//2, Baneasa, 10
//3, Sibiu, 15