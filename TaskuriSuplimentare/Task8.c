#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Heap Heap;
typedef struct Pacient Pacient;

struct Pacient {
	char* nume;
	int varsta;
	int gradDeUrgenta;
};

struct Heap {
	Pacient* vector;
	int dimensiune;
	int dimTotal;
};

Pacient initializarePacient(const char* nume, int varsta, int grad) {
	Pacient p;
	p.gradDeUrgenta = grad;
	p.varsta = varsta;
	p.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(p.nume, nume);

	return p;
}

Heap initializareHeap(int dim) {
	Heap h;
	h.vector = (Pacient*)malloc(sizeof(Pacient) * dim);
	h.dimensiune = 0;
	h.dimTotal = dim;
	return h;
}

void afisarePacient(Pacient p) {
	printf("Pacientul numit %s are varsta de %d ani. GRADUL DE URGENTA: %d", p.nume, p.varsta, p.gradDeUrgenta);
	if (p.gradDeUrgenta > 10) {
		printf(" | A fost adus cu ambulanta!\n", p.gradDeUrgenta);
	}
	else printf("\n");
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimensiune; i++) {
		afisarePacient(h.vector[i]);
	}
}

void sortareHeap(Heap h, int poz) {
	int poz_MAX = poz;
	int poz_s = poz * 2 + 1;
	int poz_d = poz * 2 + 2;

	if (poz_s < h.dimensiune && h.vector[poz_s].gradDeUrgenta > h.vector[poz_MAX].gradDeUrgenta) {
		poz_MAX = poz_s;
	}
	if (poz_d < h.dimensiune && h.vector[poz_d].gradDeUrgenta > h.vector[poz_MAX].gradDeUrgenta) {
		poz_MAX = poz_d;
	}

	if (poz_MAX != poz) {
		Pacient aux = h.vector[poz];
		h.vector[poz] = h.vector[poz_MAX];
		h.vector[poz_MAX] = aux;

		if (poz_MAX * 2 + 1 < h.dimensiune) {
			sortareHeap(h, poz_MAX);
		}
	}
}

void main() {
	Heap UPU = initializareHeap(8);
	UPU.vector[0] = initializarePacient("Andrei", 19, 5);
	UPU.vector[1] = initializarePacient("Iulian", 41, 22);
	UPU.vector[2] = initializarePacient("Marius", 36, 9);
	UPU.vector[3] = initializarePacient("Robert", 20, 11);
	UPU.vector[4] = initializarePacient("Ioana", 29, 7);
	UPU.vector[5] = initializarePacient("Corina", 40, 3);
	UPU.vector[6] = initializarePacient("Gabriel", 21, 4);
	UPU.vector[7] = initializarePacient("Florina", 18, 15);

	for (int i = 0; i < UPU.dimTotal; i++) {
		if (UPU.vector[i].gradDeUrgenta != NULL) {
			UPU.dimensiune++;
		}
	}
	afisareHeap(UPU);

	printf("\n------------Prelucrare pacienti------------\n");

	for (int i = (UPU.dimensiune / 2) - 1; i >= 0; i--) {
		sortareHeap(UPU, i);
	}
	afisareHeap(UPU);
}