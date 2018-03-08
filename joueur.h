#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include "cartes.h"

#define MIN_JOUEURS 2

typedef struct frise{
    t_carte *carte;
    struct frise *nextCarte;
    struct frise *precCarte;
}t_frise;

typedef struct listeFrise{
    t_frise *tete;
}t_listeFrise;

typedef struct joueur{
    char *nomJoueur;
    t_listeFrise *frise;
    int nbCartes;
    struct joueur *nextJoueur;
}t_joueur;

/*typedef struct listeJoueur{
    t_joueur *joueur;
    struct listeJoueur *nextJoueur;
}t_listeJoueur;*/

typedef struct rondeJoueur{
    t_joueur *tete;
    int nbJoueurs;
}t_rondeJoueur;

int nomDejaExistant(t_rondeJoueur *p_ronde,char nom[]);
t_joueur *creeJoueur(t_rondeJoueur *p_ronde);
int nbCartesJoueur(t_joueur *joueur);
t_joueur *ajoutCarteJoueur(t_joueur *joueur,t_carte *carte);
void printFrise(t_joueur *joueur);
t_rondeJoueur *creeRondeJoueur();
void printRondeJoueurs(t_rondeJoueur *p_rondeJoueur);
int joueurChercheCarte(t_joueur *p_joueur,t_carte *carte);
t_rondeJoueur *tourSuivant(t_rondeJoueur *p_ronde);
void afficheVainqueur(t_rondeJoueur *p_ronde);
int compteCartesCategorie(t_joueur *p_joueur,char categorie[]);
void afficheVainqueurCategorie(t_rondeJoueur *p_ronde, char categorie[]);
void afficheVainqueurToutesCategories(t_rondeJoueur *p_ronde,t_pileCategory *p_pileCategory);

#endif // JOUEUR_H_INCLUDED
