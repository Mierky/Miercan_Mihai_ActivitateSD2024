#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* specie;
    int varstaMaxima;
    float greutateMedie;
    long int nrTotal;
} Mamifer;

struct Nod {
    Mamifer mamifer;
    struct Nod* next;
};

void citireTXT(const char* numeFisier, struct Nod** nod, int* dim) {
    FILE* f = fopen(numeFisier, "r");

    if (f != NULL) {
        char buffer[100];
        while (fgets(buffer, 99, f) != NULL) {
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

            struct Nod* nodNou = (struct Nod*)malloc(sizeof(struct Nod));
            nodNou->mamifer = mamifer;
            nodNou->next = *nod;

            *nod = nodNou;
            (*dim)++;
        }
        fclose(f);
    }
}

Mamifer* adaugareInVector(Mamifer mamifer, Mamifer* vector, int* dim) {
    Mamifer* copie = (Mamifer*)malloc(sizeof(Mamifer) * ((*dim) + 1));

    for (int i = 0; i < (*dim); i++) {
        copie[i] = vector[i];
    }
    copie[*dim] = mamifer;

    if (vector != NULL)
        free(vector);

    (*dim)++;
    return copie;
}

void citireTXTSortat(const char* numeFisier, struct Nod** nod, int* dim) {
    FILE* f = fopen(numeFisier, "r");
    Mamifer* mamiferVector = NULL;

    if (f != NULL) {
        char buffer[100];
        while (fgets(buffer, 99, f) != NULL) {
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

            mamiferVector = adaugareInVector(mamifer, mamiferVector, dim);
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
            struct Nod* nodNou = (struct Nod*)malloc(sizeof(struct Nod));
            nodNou->mamifer = mamiferVector[i];
            nodNou->next = *nod;

            *nod = nodNou;
        }

        free(mamiferVector);
    }
}

void afisareMamifer(Mamifer m) {
    printf("Specie: %s\n", m.specie);
    printf("Varsta: %d\n", m.varstaMaxima);
    printf("Greutate: %.2f\n", m.greutateMedie);
    printf("Numar total pe glob: %ld\n\n", m.nrTotal);
}

void afisareLista(struct Nod* nod) {
    while (nod != NULL) {
        afisareMamifer(nod->mamifer);
        nod = nod->next;
    }
}

void afisareNod(struct Nod* nod) {
    if (nod != NULL) {
        afisareMamifer(nod->mamifer);
    }
    else {
        printf("Elementul nu exista.\n");
    }
}

void cautareNod(struct Nod* nod, int poz) {
    int i = 0;

    while (nod != NULL && i < poz) {
        nod = nod->next;
        i++;
    }
    afisareNod(nod);
}

Mamifer* inserareInVector_ConditieVarsta(Mamifer* vector, struct Nod* vf, int varsta, int* dim) {
    struct Nod* vf2 = vf;

    while (vf2 != NULL) {
        if (vf2->mamifer.varstaMaxima > varsta)
            (*dim)++;

        vf2 = vf2->next;
    }

    Mamifer* vectorAux = (Mamifer*)malloc(sizeof(Mamifer) * (*dim));

    int poz = 0;
    while (vf != NULL) {
        if (vf->mamifer.varstaMaxima > varsta) {
            vectorAux[poz] = vf->mamifer;
            vectorAux[poz].specie = (char*)malloc(sizeof(char) * (strlen(vf->mamifer.specie) + 1));
            strcpy(vectorAux[poz].specie, vf->mamifer.specie);
            poz++;
        }

        vf = vf->next;
    }

    return vectorAux;
}

void stergereNodDinLista(struct Nod** nod, int poz) {
    int i = 0;
    struct Nod* auxfirst = (*nod);
    struct Nod* auxlast = (*nod);

    if ((*nod) == NULL) {
        printf("Lista este deja goala!\n");
    }
    else {
        while (auxfirst->next != NULL && i != poz) {
            auxlast = auxfirst;
            auxfirst = auxfirst->next;
            i++;
        }
        if (i == poz) {
            auxlast->next = auxfirst->next;
            free(auxfirst->mamifer.specie);
            free(auxfirst);
        }
        else printf("Nu am gasit nodul care trebuia sters!\n");
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


void stergeLista(struct Nod** vf) {
    while ((*vf) != NULL) {
        free((*vf)->mamifer.specie);
        struct Nod* copie = *vf;
        *vf = (*vf)->next;

        free(copie);
    }
}

void main() {
    printf("\n=======================|LISTA 1|=======================\n");
    struct Nod* vf = NULL;
    int dim = 0;
    citireTXT("FisierMamifere.txt", &vf, &dim);
    afisareLista(vf);
    printf("Dimensiune Lista: %d\n", dim);

    printf("\n=======================|LISTA 2|=======================\n");
    struct Nod* vf2 = NULL;
    int dim2 = 0;
    citireTXTSortat("FisierMamifere.txt", &vf2, &dim2);
    afisareLista(vf2);

    printf("\n============================\n");
    printf("\n");
    cautareNod(vf, 10);
    printf("\n");

    printf("\n===========VECTOR=============\n");
    Mamifer* vector = NULL;
    int dimVector = 0;
    vector = inserareInVector_ConditieVarsta(vector, vf, 30, &dimVector);
    for (int i = 0; i < dimVector; i++) {
        afisareMamifer(vector[i]);
    }

    printf("\n===========AFISARE DUPA STERGERE NOD X=============\n");
    stergereNodDinLista(&vf, 3);
    afisareLista(vf);

    stergeLista(&vf);
    stergeLista(&vf2);
    dezalocareVector(&vector, &dimVector);
}
