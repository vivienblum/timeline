#include <stdio.h>
#include <stdlib.h>
#include "cartes.h"

int nbCartesChargees(t_pile *pile){ /*valide*/
    int i=0;
    t_pile *p_courant=(t_pile *)malloc(sizeof(t_pile));
    if(p_courant!=NULL){
        p_courant=pile;
        if(pile==NULL){
            return 0; /*il n'y a aucunes cartes*/
        }
        while(p_courant->nextCarte!=NULL){
            i=i+1;
            p_courant=p_courant->nextCarte;
        }
        return i+1;
    }
    else{
        printf("\nErreur memoire\n");
    }
    return -1; /*en cas d'erreur*/
}

void printCarte(t_carte *carte){ /*valide*/
    printf("\n  %s (%s) : %d",carte->event,carte->category,carte->date);
}

void printCarteSansDate(t_carte *carte){ /*valide*/
    printf("\n  %s (%s) : ?\n",carte->event,carte->category);
}

t_listePile *initialisePile(t_carte *t){ /*fonction pour simuler une pile de cartes*/
    t_listePile *p_listePile=(t_listePile *)malloc(sizeof(t_listePile));
    p_listePile->nbCartes=0;
    t_pile *p_ancien=NULL;
    int i;
    for(i=0;i<5;i=i+1){
        t_pile *p_pile=(t_pile *)malloc(sizeof(t_pile));
        p_pile->carte=&t[i];
        p_pile->nextCarte=p_ancien;
        p_ancien=p_pile;
        p_listePile->nbCartes+=1;
    }
    p_listePile->tete=p_ancien;

    return p_listePile;
}

t_listePile *enleverUneCarte(t_listePile *p_listePile){ /*valide*/
    t_pile *p_pile; /*on cree un pointeur sur un type t_pile*/
    if((p_listePile==NULL)||(p_listePile->tete==NULL)||(p_listePile->nbCartes==0)){ /*on regarde si la pile de cartes n'est pas vide*/
        printf("\nIl n'y a plus de cartes.\n");  /*si c'est le cas*/
        return p_listePile;                     /*on retourne le pointeur tel quel*/
    }
    p_pile=p_listePile->tete; /*notre pointeur prend la valeur du sommet de la pile*/
    p_listePile->tete=p_pile->nextCarte; /*le sommet de la pile prend la valeur de la carte suivante*/
    p_listePile->nbCartes-=1; /*on decremente le nombre de cartes dans la pile*/
    return p_listePile; /*on retourne la nouvelle pile de cartes*/
}

void printPile(t_listePile *p_pile){  /*valide*/
    t_pile *p_courant; /*on cree un pointeur*/
    p_courant=p_pile->tete; /*il pointe sur la premiere carte*/
    printf("\n");
    while(p_courant!=NULL){ /*on parcourt toutes les cartes jusqu'a la derniere*/
        printCarte(p_courant->carte); /*on affiche les cartes*/
        p_courant=p_courant->nextCarte;
    }
    printf("\n");
}

int categoryDejaPresente(t_pileCategory *p_pileCategory,char category[]){ /*valide*/
    if((p_pileCategory==NULL)||(p_pileCategory->tete==NULL)){ /*si la pile de categroie est initialement vide*/
        return 0; /*la categorie n'est pas deja presente*/
    }
    t_chaineCategory *p_courant=p_pileCategory->tete; /*on cree un pointeur*/
    do{  /*qui parcourt toute la pile de categorie*/
        if(strcmp(p_courant->nomCategory,category)==0){ /*s'il exsite deja la categorie*/
            return 1; /*la categorie est deja presente*/
        }
        p_courant=p_courant->nextCategory;
    }while(p_courant!=NULL);
    return 0; /*donc la categorie n'est pas deja presente*/
}

t_pileCategory *creePileCategorie(t_listePile *p_pile){ /*valide*/
    if((p_pile==NULL)||(p_pile->tete==NULL)||(p_pile->nbCartes==0)){ /*si la pile de cartes est vide*/
        return NULL; /*on retourne NULL*/
    }
    t_pileCategory *p_pileCategory=(t_pileCategory *)malloc(sizeof(t_pileCategory)); /*on alloue la memoire*/
    if(p_pileCategory==NULL){ /*on verifie l'allocation*/
        printf("\nErreur memoire\n");
        return NULL;
    }
    p_pileCategory->tete=NULL; /*on initialise la tete de notre pile de categorie a null*/
    t_pile *p_courant; /*on cree un pointeur courant*/
    p_courant=p_pile->tete; /*qui prend la valeur de la tete de la pile de carte*/
    t_chaineCategory *p_ancien=NULL; /*on cree un pointeur ancien qui prend initialement la valeur NULL*/
    while(p_courant!=NULL){ /*on parcourt toutes les cartes de la pile*/
        if(categoryDejaPresente(p_pileCategory,p_courant->carte->category)==0){ /*si la carte n'est pas deja presente*/
            t_chaineCategory *p_chaineCategory=(t_chaineCategory *)malloc(sizeof(t_chaineCategory)); /*on alloue un pointeur*/
            p_chaineCategory->nomCategory=p_courant->carte->category; /*on definit notre pointeur categorie*/
            p_chaineCategory->nextCategory=p_ancien; /*notre pointeur suivant pointera sur ancien*/
            p_ancien=p_chaineCategory; /*le pointeur ancien prend la valeur du pointeur cree precedement*/
            p_pileCategory->tete=p_ancien; /*on definit le nouveau sommet de notre pile de categorie*/
        }
        p_courant=p_courant->nextCarte; /*on incremente le pointeur*/
    }
    p_pileCategory->tete=p_ancien; /*on definit le nouveau sommet de notre pile de categorie, ici plus necessaire*/
    return p_pileCategory; /*on retourne la pile de categories*/
}

void printPileCategorie(t_pileCategory *p_pileCategory){ /*valide*/
    t_chaineCategory *p_courant; /*on cree un pointeur courant*/
    p_courant=p_pileCategory->tete; /*qui prend la valeur de la tete de la pile de categories*/
    printf("Toutes les categories sont :\n");
    while(p_courant!=NULL){ /*on parcourt toutes les categories*/
        printf("%s\n",p_courant->nomCategory); /*on affiche la categorie*/
        p_courant=p_courant->nextCategory; /*on incremente le pointeur*/
    }
    printf("\n");
}

