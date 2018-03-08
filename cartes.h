#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED
#include <string.h>

typedef struct{
    char *event;
    int date;
    char *category;
}t_carte;

typedef struct pile{
    t_carte *carte;
    struct pile *nextCarte;
}t_pile;

typedef struct listePile{
    t_pile *tete;
    int nbCartes;
}t_listePile;

typedef struct chaineCategory{
    char *nomCategory;
    struct chaineCategory *nextCategory;
}t_chaineCategory;

typedef struct pileCategory{
    t_chaineCategory *tete;
}t_pileCategory;

void printCarte(t_carte *carte);
void printCarteSansDate(t_carte *carte);
void printPile(t_listePile *p_pile);
int nbCartesChargees(t_pile *pile);
t_listePile *initialisePile(t_carte *t);
t_listePile *enleverUneCarte(t_listePile *p_listePile);
int categoryDejaPresente(t_pileCategory *p_pileCategory,char category[]);
t_pileCategory *creePileCategorie(t_listePile *p_pile);
void printPileCategorie(t_pileCategory *p_pileCategory);

#endif // CARTES_H_INCLUDED
