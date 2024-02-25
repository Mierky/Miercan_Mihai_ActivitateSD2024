#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

struct Masina {
	char* marca;
	float capacitateCilindrica;
	int an;
};

void afisareMasina(const struct Masina* m) {
	if (m->marca != NULL) {
		printf("Marca: %s\n", m->marca);
	}
	printf("Capacitate Cilindrica: %5.2f\n", m->capacitateCilindrica);
	printf("An: %d\n\n", m->an);
}

struct Masina initializareMasina(const char* marca, int an, float cc) {
	struct Masina m;
	m.an = an;
	m.capacitateCilindrica = cc;
	if (marca != NULL) {
		m.marca = malloc(strlen(marca) + 1); //se face cast implicit dar putem pune si noi in fata malloc (char*)
		strcpy(m.marca, marca);
	}
	else {
		m.marca = malloc(strlen("N/A") + 1);
		strcpy(m.marca, "N/A");
	}
	return m;
}

void dezalocareMasina(struct Masina* masina) {

	free(masina->marca);
	masina->marca = NULL;
}

void main() {
	struct Masina masina1;
	//Dacia - (char*) este casting; fara e pointer la void
	masina1.marca = (char*)malloc(sizeof(char) * strlen("Dacia") + 1);
	strcpy(masina1.marca, "Dacia");
	masina1.capacitateCilindrica = 1.9;
	masina1.an = 2023;

	afisareMasina(&masina1);

	dezalocareMasina(&masina1);
	/*free(masina1.marca);
	masina1.marca = NULL;*/

	struct Masina masina2 = initializareMasina("Ford", 2022, 2.49);
	afisareMasina(&masina2);

	dezalocareMasina(&masina2);
	/*free(masina2.marca);
	masina2.marca = NULL;*/

	afisareMasina(&masina2);
}