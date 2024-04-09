#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
//test-2p

//avem minheap si maxheap = imi da minimul/maximul pe prima pozitie dintr-un vector
//arbore binar = fiecare nod are max 2 descendenti

typedef struct Heap Heap;
typedef struct Mesaj Mesaj;

struct Mesaj {
	char* text;
	int prioritate;
};

struct Heap {
	Mesaj* vector;
	int dimensiune;
	int dimensiuneTotala;
};

Mesaj init(const char* text, int prioritate) {
	Mesaj m;
	m.text = malloc(sizeof(char) * (1 + strlen(text)));
	strcpy(m.text, text);
	m.prioritate = prioritate;
	return m;
}

Heap initHeap(int dimensiune) {
	Heap h;
	h.vector = malloc(sizeof(Mesaj) * dimensiune);
	h.dimensiune = 0;
	h.dimensiuneTotala = dimensiune;

	return h;
}

void afisareMesaj(Mesaj m) {
	printf("Mesajul cu textul %s si prioritatea %d\n", m.text, m.prioritate);
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimensiune; i++) {
		afisareMesaj(h.vector[i]);
	}
}


void filtrareHeap(Heap h, int poz) {
	int poz_s = poz * 2 + 1;
	int poz_d = poz * 2 + 2;
	int poz_m = poz; //pozitia val maxime = presupunere
	if (poz_s < h.dimensiune && h.vector[poz_s].prioritate>h.vector[poz_m].prioritate) {
		poz_m = poz_s;
	}
	if (poz_d < h.dimensiune && h.vector[poz_d].prioritate>h.vector[poz_m].prioritate) {
		poz_m = poz_d;
	}
	if (poz_m != poz) {
		Mesaj aux = h.vector[poz];
		h.vector[poz] = h.vector[poz_m];
		h.vector[poz_m] = aux;

		if (poz_m * 2 + 1 < h.dimensiune) { //verificare dc nodul maxim mai are copii
			filtrareHeap(h, poz_m);
		}

	}
}

Mesaj ExtragereHeap(Heap* h) {
	if (h->dimensiune > 0) { //dc am elemente:
		Mesaj aux = h->vector[0];
		h->vector[0] = h->vector[h->dimensiune - 1];
		h->vector[h->dimensiune - 1] = aux;
		h->dimensiune--;

		for (int i = (h->dimensiune / 2) - 1; i >= 0; i--) {
			filtrareHeap(*h, i);
		}
		return aux;
	}
}

void afisareHeapTotal(Heap h) {
	for (int i = 0; i < h.dimensiuneTotala; i++) {
		afisareMesaj(h.vector[i]);
	}
}

void DezalocareHeap(Heap* h) {
	if (h->vector != NULL) {
		for (int i = 0; i < h->dimensiuneTotala; i++) {
			free(h->vector[i].text);
		}
		h->dimensiuneTotala = 0;
		free(h->vector);
		h->vector = NULL;
		h->dimensiune = 0;
	}
}

void main() {
	Heap h;
	h = initHeap(6);
	h.vector[0] = init("Salut", 3);
	h.vector[1] = init("Salut ce faci", 8);
	h.vector[2] = init("Buna", 6);
	h.vector[3] = init("Noroc", 2);
	h.vector[4] = init("Ce mai faci", 9);
	h.vector[5] = init("Pa pa", 4);
	h.dimensiune = 6;

	afisareHeap(h);
	printf("\nDupa filtrare:\n ");
	for (int i = (h.dimensiune / 2) - 1; i >= 0; i--) { //filtrarea e de jos in sus
		filtrareHeap(h, i);
	}
	afisareHeap(h);

	printf("\nExtragere:\n");
	afisareMesaj(ExtragereHeap(&h));
	afisareMesaj(ExtragereHeap(&h));
	afisareMesaj(ExtragereHeap(&h));
	afisareMesaj(ExtragereHeap(&h));
	afisareMesaj(ExtragereHeap(&h));
	afisareMesaj(ExtragereHeap(&h));

	printf("==============\n");
	afisareHeapTotal(h);
	DezalocareHeap(&h);
}