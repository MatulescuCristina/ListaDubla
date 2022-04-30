#include<stdio.h>
#include<malloc.h>

// structura Oras
struct Oras
{
	char* denumire;
	int nrLocuitori;
	float suprafata;
};

// structura Nod
struct Nod
{
	struct Oras* info;
	struct Nod* next;
	struct Nod* prev;
};

// inserare nod la inceput
struct Nod* inserareInceput(struct Nod* prim, struct Oras* o)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	
	nou->info = (struct Oras*)malloc(sizeof(struct Oras));
	nou->info->denumire = (char*)malloc((strlen(o->denumire) + 1) * sizeof(char));
	strcpy(nou->info->denumire, o->denumire);

	nou->info->nrLocuitori = o->nrLocuitori;
	nou->info->suprafata = o->suprafata;

	nou->next = NULL;
	nou->prev = NULL;

	if (prim == NULL)
	{
		prim = nou;
		return prim;
	}
	else
	{
		nou->prev = prim;
		prim = nou;
		return prim;
	}
}

// inserare nod la final
struct Nod* inserareFinal(struct Nod* prim, struct Oras* o)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->info = (struct Oras*)malloc(sizeof(struct Oras));
	nou->info->denumire = (char*)malloc((strlen(o->denumire) + 1) * sizeof(char));
	strcpy(nou->info->denumire, o->denumire);

	nou->info->nrLocuitori = o->nrLocuitori;
	nou->info->suprafata = o->suprafata;

	nou->next = NULL;
	nou->prev = NULL;

	if (prim == NULL)
	{
		prim = nou;
	}
	else
	{
		struct Nod* aux = prim;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = nou;
		nou->prev = aux;
	}
	return prim;
}

// inserare nod in interior
struct Nod* inserareInterior(struct Nod* prim, struct Oras* o, struct Nod* pozitie)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->info = (struct Oras*)malloc(sizeof(struct Oras));
	nou->info->denumire = (char*)malloc((strlen(o->denumire) + 1) * sizeof(char));
	strcpy(nou->info->denumire, o->denumire);

	nou->info->nrLocuitori = o->nrLocuitori;
	nou->info->suprafata = o->suprafata;

	nou->next = NULL;
	nou->prev = NULL;

	if (prim == NULL)
	{
		prim = nou;
	}
	else if (prim == pozitie)
	{
		nou->next = prim;
		prim->prev = nou;
		prim = nou;
	}
	else
	{
		nou->next = pozitie->next;
		nou->prev = pozitie;
		pozitie->prev->next = nou;
		pozitie->next = nou;
	}
	return prim;
}

// afisare lista dubla inceput->final
void afisareInceputFinal(struct Nod* prim)
{
	struct Nod* aux = prim;
	while (aux != NULL)
	{
		printf("Denumire oras: %s, nr locuitori: %d, suprafata: %5.2f\n",
			aux->info->denumire, aux->info->nrLocuitori, aux->info->suprafata);
		aux = aux->next;
	}
}

// afisare lista dubla final->inceput
void afisareFinalInceput(struct Nod* ultim)
{
	struct Nod* aux = ultim;
	while (aux != NULL)
	{
		printf("Denumire oras: %s, nr locuitori: %d, suprafata: %5.2f\n",
			aux->info->denumire, aux->info->nrLocuitori, aux->info->suprafata);
		aux = aux->prev;
	}
}

void main()
{
	int nr;
	struct Nod* prim = NULL;
	struct Nod* ultim = NULL;
	struct Oras* o;
	char buffer[20];

	FILE* f = fopen("oras.txt", "r");
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++)
	{
		o = (struct Oras*)malloc(sizeof(struct Oras));

		fscanf(f, "%s", buffer);
		o->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(o->denumire, buffer);

		fscanf(f, "%d", &o->nrLocuitori);
		fscanf(f, "%f", &o->suprafata);

		prim = inserareInceput(prim, o);
		//prim = inserareFinal(prim, o);

		free(o);
	}
	fclose(f);

	//afisareInceputFinal(prim);
	afisareFinalInceput(prim);

}