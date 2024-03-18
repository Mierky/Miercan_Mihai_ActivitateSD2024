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


void main() {
    struct Nod* vf = NULL;
    int dim = 0;
    citireTXT("FisierMamifere.txt", &vf, &dim);
    afisareLista(vf);
    printf("Dimensiune Lista: %d\n", dim);

    printf("\n");
    cautareNod(vf, 9);
    printf("\n");

}
