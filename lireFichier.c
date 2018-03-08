#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lireFichier.h"
#include "cartes.h"
#include "simpleio.h"

t_listePile *initialisePileFichier(){ /*valide*/
    FILE* fichier = NULL; /*on initialise le fichier a null*/
    fichier = fopen("timeline.dat", "r"); /*on ouvre le fichier en mode lecture seule*/
    if(fichier==NULL){ /*on teste si le fichier a bien ete importe*/
        printf("\nErreur : le fichier contenant les cartes n'a pu etre importe.\n");
        return NULL;
    }

    t_listePile *p_listePile=(t_listePile *)malloc(sizeof(t_listePile)); /*on alloue un pointeur pour une pile de carte*/
    if(p_listePile==NULL){ /*on teste l'allocation*/
        printf("\nErreur memoire\n");
        return NULL;
    }
    p_listePile->tete=NULL; /*la tete de ka pile prend la valeur null*/
    p_listePile->nbCartes=0; /*nombrre de cartes initialise a 0*/
    t_pile *p_ancien=NULL; /*on cree un pointeur ancien initialement a null*/

    char chaineDate[TAILLE_MAX] = ""; /*on cree une chaine de caractere*/
    while(fgets(chaineDate, TAILLE_MAX, fichier) != NULL){ /*on lit une ligne du fchier tant que celle ci n'est pas null*/
        t_carte *p_carte=(t_carte *)malloc(sizeof(t_carte)); /*on alloue la memoire pour une carte*/
        if(p_carte==NULL){ /*on teste l'allocation*/
            printf("\nErreur memoire\n");
            return NULL;
        }
        int date=atoi(chaineDate); /*on convertit la chaine lu dans le fichier en entier*/
        p_carte->date=date; /*on definit la date d'une carte*/

        p_carte->event=lireChaineFichier(fichier); /*l'evenement de la carte pointe sur la ligne suivante*/

        p_carte->category=lireChaineFichier(fichier);  /*la categorie de la carte pointe sur la ligne suivante*/

        t_pile *p_pile=(t_pile *)malloc(sizeof(t_pile)); /*on alloue un etage de la pile de carte*/
        if(p_pile==NULL){ /*on teste l'allocation*/
            printf("\nErreur memoire\n");
            return NULL;
        }
        p_pile->carte=p_carte; /*la pile pointe sur la carte*/
        p_pile->nextCarte=p_ancien; /*l'etage suivant de la pile prend la valeur d'ancien*/
        p_ancien=p_pile; /*et l'etage de la pile devient la valeur d'ancien*/
        p_listePile->nbCartes+=1; /*on increment le nombre de cartes*/
    }
    p_listePile->tete=p_ancien; /*la tete de la pile de cartes pointe sur la derniere carte cree*/
    /*printPile(p_listePile);*/

    if(fclose(fichier)!=0){ /*on ferme le fichier*/
        printf("\nErreur lors de la fermeture du fichier.");
    }
    return p_listePile; /*on retourne un pointeur sur la pile*/
}
