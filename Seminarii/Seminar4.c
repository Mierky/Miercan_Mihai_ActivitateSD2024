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

void citireMatriceFisier(const char* numeFisier, int* nrAeroporturiLinie, int nrClustere, struct Aeroport** aeroporturi) {

	FILE* f = fopen(numeFisier, "r");

	if (f != NULL) {
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;

			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);

			token = strtok(NULL, delimitator);
			aeroport.nume = malloc(sizeof(char*) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);

			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			int poz = aeroport.nrTerminale % 2;


			aeroporturi[poz] = adaugaAeroport(aeroporturi[poz], aeroport, &(nrAeroporturiLinie[poz]));
		}
		fclose(f);
	}

}

void afisareAeroport(struct Aeroport* aeroport) {
	if (aeroport != NULL) {
		printf("%d. %s are %d terminale\t", aeroport->id, aeroport->nume, aeroport->nrTerminale);
	}
	else printf("Nu exista acest aeroport!!");
}

void afisareMatrice(struct Aeroport** matrice, int nrClustere, int* nrColoane) {
	for (int i = 0; i < nrClustere; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			afisareAeroport(&matrice[i][j]);
		}
		printf("\n");
	}
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

void dezalocareMatrice(struct Aeroport*** matrice, int** nrColoane, int* nrClustere) {
	for (int i = 0; i < (*nrClustere); i++) {
		dezalocareVector(&((*matrice)[i]), &((*nrColoane)[i]));
	}
	free(*matrice);
	(*matrice) = NULL;
	free(*nrColoane);
	(*nrColoane) = NULL;
	(*nrClustere) = 0;
}

float mediaTerminale(struct Aeroport** matrice, int* nrAeroporturiLinie, int paritate) {
	paritate = paritate % 2;
	int suma = 0;
	for (int i = 0; i < nrAeroporturiLinie[paritate]; i++) {
		suma += matrice[paritate][i].nrTerminale;
	}
	if (nrAeroporturiLinie[paritate])
		return suma / nrAeroporturiLinie[paritate];

	return 0;
}

struct Aeroport* cautareAeroportID(struct Aeroport** matrice, int* nrColoane, int nrLinii, int id) {

	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			if (matrice[i][j].id == id) {
				return &(matrice[i][j]);
			}
		}
	}
	return NULL;
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
	struct Aeroport** aeroporturi;
	int nrLinii = 2; //nrCLUSTERE
	int* nrColoane = (int*)malloc(sizeof(int) * nrLinii);

	aeroporturi = (struct Aeroport**)malloc(sizeof(struct Aeroport*) * nrLinii);
	for (int i = 0; i < nrLinii; i++) {
		nrColoane[i] = 0;
		aeroporturi[i] = NULL;
	}

	citireMatriceFisier("aeroporturi.txt", nrColoane, nrLinii, aeroporturi);
	afisareMatrice(aeroporturi, nrLinii, nrColoane);
	float medie = mediaTerminale(aeroporturi, nrColoane, 12);
	printf("Media paritate -> para: %.2f", medie);

	printf("\n\n");
	afisareAeroport(cautareAeroportID(aeroporturi, nrColoane, nrLinii, 4)); printf("\n");
	afisareAeroport(cautareAeroportID(aeroporturi, nrColoane, nrLinii, 10));

	dezalocareMatrice(&aeroporturi, &nrColoane, &nrLinii);

}

//txt: 
//1, Otopeni, 20
//2, Baneasa, 10
//3, Sibiu, 15
//4, Baia mare, 12
//5, Frankfurt, 41