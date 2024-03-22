#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mamifer Mamifer;
typedef struct Nod Nod;
typedef struct NodSimplu NodSimplu;

struct Mamifer {
	char* specie;
	int varstaMaxima;
	float greutateMedie;
	long int nrTotal;
};

struct Nod {
	Mamifer info;
	Nod* next;
	Nod* prev;
};

struct NodSimplu {
	Mamifer info;
	NodSimplu* next;
};

Nod* inserareLista(Nod* nod, Mamifer mamifer) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = mamifer;
	nodNou->next = nod;
	nodNou->prev = NULL;

	if (nod != NULL) {
		nod->prev = nodNou;
	}

	return nodNou;
}

Mamifer* inserareVector(Mamifer* vector, Mamifer mamifer, int* dim) {
	Mamifer* copie = (Mamifer*)malloc(sizeof(Mamifer) * ((*dim) + 1));

	for (int i = 0; i < (*dim); i++) {
		copie[i] = vector[i];
	}
	copie[*dim] = mamifer;

	if (vector != NULL) {
		free(vector);
	}

	return copie;
}

Nod* citireTXT(const char* nume, Nod* cap, int* dim) {

	FILE* f = fopen(nume, "r");
	if (!f) printf("Eroare la deschidere!");
	else {
		char buffer[100];
		while (fgets(buffer, 99, f)) {
			Mamifer mamifer;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			mamifer.specie = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(mamifer.specie, token);

			token = strtok(NULL, delimitator);
			mamifer.varstaMaxima = atoi(token);

			token = strtok(NULL, delimitator);
			mamifer.greutateMedie = atof(token);

			token = strtok(NULL, delimitator);
			mamifer.nrTotal = atol(token);

			cap = inserareLista(cap, mamifer);
			(*dim)++;

		}
		fclose(f);
	}
	return cap;
}

Nod* citireTXTSortat(const char* nume, Nod* cap, int* dim) {
	Mamifer* mamiferVector = NULL;
	FILE* f = fopen(nume, "r");
	if (!f) printf("Eroare la deschidere!");
	else {
		char buffer[100];
		while (fgets(buffer, 99, f)) {
			Mamifer mamifer;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			mamifer.specie = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(mamifer.specie, token);

			token = strtok(NULL, delimitator);
			mamifer.varstaMaxima = atoi(token);

			token = strtok(NULL, delimitator);
			mamifer.greutateMedie = atof(token);

			token = strtok(NULL, delimitator);
			mamifer.nrTotal = atol(token);

			mamiferVector = inserareVector(mamiferVector, mamifer, dim);
			(*dim)++;
		}
		fclose(f);

		for (int i = 0; i < (*dim) - 1; i++) {
			for (int j = i + 1; j < (*dim); j++) {
				if (mamiferVector[i].varstaMaxima < mamiferVector[j].varstaMaxima) {
					Mamifer temp = mamiferVector[i];
					mamiferVector[i] = mamiferVector[j];
					mamiferVector[j] = temp;
				}
			}
		}

		for (int i = 0; i < (*dim); i++) {
			cap = inserareLista(cap, mamiferVector[i]);
		}

		free(mamiferVector);
	}
	return cap;
}

void afisareMamifer(Mamifer m) {
	printf("Specie: %s\n", m.specie);
	printf("Varsta: %d\n", m.varstaMaxima);
	printf("Greutate: %.2f\n", m.greutateMedie);
	printf("Numar total pe glob: %ld\n\n", m.nrTotal);
}

void afisareListaSimpla(NodSimplu* nod) {
	while (nod != NULL) {
		afisareMamifer(nod->info);

		nod = nod->next;
	}
}

void afisareLista1(Nod* nod) {
	while (nod != NULL) {
		afisareMamifer(nod->info);

		nod = nod->next;
	}
}
void afisareLista2(Nod* nod) {
	while (nod->next != NULL) {
		nod = nod->next;
	}

	while (nod != NULL) {
		afisareMamifer(nod->info);
		nod = nod->prev;
	}
}

void salvareInListaSimpla(NodSimplu** nodS, Nod* nodD, int* dim, int varsta) {
	(*dim) = 0;

	while (nodD != NULL) {
		if (nodD->info.varstaMaxima > varsta) {
			NodSimplu* nodSimplu = (NodSimplu*)malloc(sizeof(NodSimplu));

			nodSimplu->info = nodD->info;
			nodSimplu->info.specie = (char*)malloc(sizeof(char) * (strlen(nodD->info.specie) + 1));
			strcpy(nodSimplu->info.specie, nodD->info.specie);
			nodSimplu->next = (*nodS);
			(*nodS) = nodSimplu;

			(*dim)++;
		}
		nodD = nodD->next;
	}

}

void interschimbare(Nod** nod, int poz1, int poz2) {
	if (poz1 == poz2) exit(0);

	Nod* copie = (*nod);
	Nod* nod1 = (*nod);
	Nod* nod2 = (*nod);

	int i = 0;
	while (copie != NULL) {
		if (poz1 == i) {
			nod1 = copie;
		}
		else if (poz2 == i) {
			nod2 = copie;
		}
		i++;
		copie = copie->next;
	}

	Mamifer temp = nod1->info;
	nod1->info = nod2->info;
	nod2->info = temp;
}

void stergereNod(Nod** nod, int poz) {
	int i = 0;
	Nod* copie = (*nod);

	if ((*nod) == NULL) {
		printf("Lista este deja goala!\n");
	}
	else {
		while (copie->next != NULL && i != poz) {
			copie = copie->next;
			i++;
		}
		if (i == poz) {
			copie->prev->next = copie->next;
			copie->next->prev = copie->prev;
			free(copie->info.specie);
			free(copie);
		}
		else {
			printf("Nu a fost gasit nodul care trebuia sters!\n");
		}
	}
}

void stergeListaDubla(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.specie);
		Nod* copie = *cap;
		*cap = (*cap)->next;

		free(copie);
	}
}

void stergeListaSimpla(NodSimplu** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.specie);
		NodSimplu* copie = *cap;
		*cap = (*cap)->next;

		free(copie);
	}
}

void main() {
	int dim = 0;
	Nod* cap = NULL;
	cap = citireTXT("FisierMamifere.txt", cap, &dim);
	printf("=============AFISARE LISTA 1============\n");
	printf("DIMENSIUNE: %d\n", dim);
	afisareLista1(cap);

	printf("\n=============AFISARE LISTA 2============\n");
	int dim2 = 0;
	Nod* cap2 = NULL;
	cap2 = citireTXTSortat("FisierMamifere.txt", cap2, &dim2);
	printf("DIMENSIUNE: %d\n", dim2);
	afisareLista1(cap2);

	printf("\n=============LISTA SIMPLU INLANTUITA============\n");
	NodSimplu* capSimplu = NULL;
	int dimSimplu = 0;
	salvareInListaSimpla(&capSimplu, cap, &dimSimplu, 30);
	printf("DIMENSIUNE: %d\n", dimSimplu);
	afisareListaSimpla(capSimplu);

	printf("\n=============INTERSCHIMBARE============\n");
	interschimbare(&cap, 0, 9);
	afisareLista1(cap);

	printf("\n=============STERGERE NOD============\n");
	stergereNod(&cap, 4);
	afisareLista1(cap);

	stergeListaDubla(&cap);
	stergeListaDubla(&cap2);
	stergeListaSimpla(&capSimplu);
}

/*Delfin,27,158,2000000
Leu,35,200,54342
Tigru siberian,44,250,43534
Urs polar,50,700,22020
Rechin alb,30,800,23000
Elefant,60,6000,100000
Oaie,12,100,100000000
Cal,30,420,55000000
Jaguar,15,100,20000
Maimuta,20,33,4423234*/