#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "cartes.h"
#include "simpleio.h"

int nomDejaExistant(t_rondeJoueur *p_ronde,char nom[]){ /*valide*/
    if(nom[0]=='\0'){ /*on test aussi ici si la chaine n'est pas vide*/
        printf("\nChaine Vide.\n");
        return 1;
    }
    if((p_ronde==NULL)||(p_ronde->tete==NULL)){ /*si la ronde est initialement vide*/
        return 0; /*le nom n'est pas deja present*/
    }
    t_joueur *p_courant=p_ronde->tete; /*on cree un pointeur*/
    do{  /*qui parcourt toute la ronde de joueur*/
        if(strcmp(p_courant->nomJoueur,nom)==0){ /*s'il exsite deja le nom*/
            printf("\nNom deja existant.\n");
            return 1; /*le nom est deja present*/
        }
        p_courant=p_courant->nextJoueur;
    }while((p_courant!=NULL)&&(p_courant!=p_ronde->tete));
    return 0; /*donc le nom n'est pas deja present*/
}

t_joueur *creeJoueur(t_rondeJoueur *p_ronde){  /*valide*/
    t_joueur *p_joueur=(t_joueur *)malloc(sizeof(t_joueur)); /*on alloue la place pour le pointeur*/
    t_listeFrise *p_frise=(t_listeFrise *)malloc(sizeof(t_listeFrise));
    char *nom;
    if((p_joueur!=NULL)&&(p_frise!=NULL)){  /*on verifie que l'allocation s'est bien deroulee*/
        do{
            printf("\nEntrer le nom du joueur :\n");
            nom=lireChaine(); /*on lit la chaine entree par le joueur*/
        }while(nomDejaExistant(p_ronde,nom)!=0); /*tant que le nom propose existe deja dans la ronde*/
        p_joueur->nomJoueur=nom;  /*on definit un joueur*/
        p_joueur->nbCartes=0;
        p_frise->tete=NULL;
        p_joueur->frise=p_frise;
        printf("\nCreation du joueur %s.\n",p_joueur->nomJoueur);
        return p_joueur; /*on retourne l'adresse du joueur cree*/
    }
    else{  /*en cas d'erreur memoire*/
        printf("\nErreur memoire\n");
        return NULL;
    }
}

void printFrise(t_joueur *joueur){  /*valide*/
    if((joueur==NULL)||(joueur->nbCartes==0)||(joueur->frise==NULL)){ /*si le joueur n'existe pas ou n'a pas de cartes*/
        return;  /*on affiche rien*/
    }
    t_frise *p_courant=joueur->frise->tete; /*on cree un pointeur qui va parcourir les cartes du joueur*/
    printf("\nFrise de %s : \n",joueur->nomJoueur); /*on affiche le nom du joueur*/
    do{
        printCarte(p_courant->carte);  /*on affiche la carte*/
        p_courant=p_courant->nextCarte; /*la pointeur s'incremente*/
    }while(p_courant!=NULL); /*tant que le pointeur n'est pas null*/
    printf("\n");
}

t_joueur *ajoutCarteJoueur(t_joueur *joueur,t_carte *carte){  /*valide*/
    t_frise *p_courant,*p_ancien;
    p_ancien=NULL;
    t_frise *p_frise=(t_frise *)malloc(sizeof(t_frise));
    if(p_frise!=NULL){
        if((joueur->frise==NULL)||(joueur->frise->tete==NULL)){ /*si le joueur n'a pas de carte au depart*/
            p_frise->carte=carte;
            p_frise->precCarte=NULL;
            p_frise->nextCarte=NULL;
            joueur->frise->tete=p_frise;
            joueur->nbCartes+=1;
            return joueur;
        }
        p_courant=joueur->frise->tete;
        while((p_courant->nextCarte!=NULL)&&(p_courant->carte->date<=carte->date)){
            p_ancien=p_courant;
            p_courant=p_courant->nextCarte;
        }
        p_frise->carte=carte;
        if(p_courant->carte->date>=carte->date){
            p_frise->precCarte=p_ancien;
            if(p_ancien!=NULL){
                p_ancien->nextCarte=p_frise;
            }
            else{
                joueur->frise->tete=p_frise;
            }
            p_frise->nextCarte=p_courant;
            p_courant->precCarte=p_frise;
        }
        else{
            p_frise->precCarte=p_courant;
            p_frise->nextCarte=p_courant->nextCarte;
            if(p_courant->nextCarte!=NULL){
                p_courant->nextCarte->precCarte=p_frise;
            }
            p_courant->nextCarte=p_frise;
        }
        joueur->nbCartes+=1;
        return joueur;
    }
    else{
        printf("\nErreur memoire\n");
        return NULL;
    }

}

void printRondeJoueurs(t_rondeJoueur *p_rondeJoueur){ /*valide*/
    t_joueur *p_courant; /*on cree un pointeur qui va parcourir les joueurs*/
    p_courant=p_rondeJoueur->tete; /*il prend la tete de la ronde*/
    printf("\nLes Joueurs sont :\n");
    do{
        printf("%s  ",p_courant->nomJoueur); /*affiche le nom du joueur*/
        p_courant=p_courant->nextJoueur; /*pointeur s'incremente*/
    }while((p_courant!=NULL)&&(p_courant!=p_rondeJoueur->tete)); /*tant qu'il ne rencontre pas a nouveau le pointeur tete*/
}

t_rondeJoueur *creeRondeJoueur(){ /*valide*/
    int nbJoueur,i;
    t_rondeJoueur *p_rondeJoueur=(t_rondeJoueur *)malloc(sizeof(t_rondeJoueur)); /*on alloue un pointeur*/
    if(p_rondeJoueur==NULL){ /*on teste l'allocation*/
        printf("\nErreur memoire\n");
        return;
    }
    t_joueur *p_ancien=NULL;  /*on cree un pointeur iniatelement a null*/
    do{  /*on demande a l'utilisateur d'entrer un nombre de joueur tant que celui-ci n'est pas valide*/
        printf("\nEntrer un nombre de joueur :\n");
        nbJoueur=lireEntier();
        if(nbJoueur<MIN_JOUEURS){ /*on considere qu'il faut au moins 2 joueurs pour lancer une partie*/
           printf("\nPas assez de joueurs.\n");
        }
    }while(nbJoueur<MIN_JOUEURS);
    printf("\nUne partie avec %d joueurs.\n",nbJoueur);
    p_rondeJoueur->tete=NULL;
    for(i=1;i<=nbJoueur;i=i+1){ /*on cree une boucle en fonction du nombre de joueurs dans la partie*/
        t_joueur *p_joueur=(t_joueur *)malloc(sizeof(t_joueur)); /*on alloue un pointeur qui pointe sur un type joueur*/
        p_joueur=creeJoueur(p_rondeJoueur); /*on cree un joueur*/
        p_joueur->nextJoueur=p_ancien; /*le pointeur pointe sur l'element precedent => on parcourt la ronde a l'envers au moment de l'initialisation*/
        p_rondeJoueur->tete=p_joueur; /*il devient la tete de la ronde*/
        p_ancien=p_joueur; /*la pointeur ancien prend la valeur actuelle*/
    }
    t_joueur *p_courant=p_rondeJoueur->tete;
    while(p_courant->nextJoueur!=NULL){ /*on parcourt la ronde des joueurs*/
            p_courant=p_courant->nextJoueur;
    }
    p_courant->nextJoueur=p_rondeJoueur->tete; /*afin de rendre la ronde circulaire, on lie les deux bouts*/
    p_rondeJoueur->nbJoueurs=nbJoueur;
    return p_rondeJoueur;  /*on retourner l'adresse de la tete de la ronde*/
}

int joueurChercheCarte(t_joueur *p_joueur,t_carte *carte){ /*valide*/
    int dateJoueur;
    t_frise *p_courant; /*on cree un pointeur qui va parcourir la frise du joueur*/
    printCarteSansDate(carte); /*on affiche la carte dont le joueur doit trouver la date*/
    printf("\nEntrer la date de cette carte :\n"); /*par convention on a choisit cette interactivite avec l'utilisateur*/
    dateJoueur=lireEntier();  /*on lit la date proposee par le joueur*/
    p_courant=p_joueur->frise->tete; /*le pointeur courant se place a la tete de la frise*/
    if(p_joueur->frise->tete==NULL){ /*dans le cas ou le joueur n'avait pas de carte*/
        printf("\nDate valide, vrai date : %d\n",carte->date);
        return 1; /*il l'a gagne forcement*/
    }
    if(dateJoueur<p_joueur->frise->tete->carte->date){ /*si la date proposee par le joueur est inferieur a sa carte la plus datee*/
        if(carte->date<p_joueur->frise->tete->carte->date){ /*et que la vrai date de la carte est inferieur a sa carte la plus datee*/
            printf("\nDate valide, vrai date : %d\n",carte->date); /*donc carte valide*/
            return 1;
        }
        else{
            printf("\nMauvaise date.\n");
            return 0;
        }
    }
    while((p_courant->nextCarte!=NULL)&&(dateJoueur>=p_courant->nextCarte->carte->date)){ /*tant que le pointeur ne pointe pas sur le dernier element*/
        p_courant=p_courant->nextCarte;                             /*et que la date proposee par le joueur est >= a la date du pointeur courant*/
    }                                                 /*on incremente le pointeur*/
    /*on se trouve ici dans l'intervalle propose par le joueur*/
    if(carte->date>=p_courant->carte->date){  /*on verifie que la vraie date de la carte est comprise dans l'intervalle proposee, ici par le min*/
        if(p_courant->nextCarte==NULL){  /*dans le cas ou c'est la derniere carte, intervalle vers l'infini*/
            printf("\nDate valide, vrai date : %d\n",carte->date); /*donc carte valide*/
            return 1;
        }
        else if(carte->date<p_courant->nextCarte->carte->date){  /*si comprise en dessous de son max*/
            printf("\nDate valide, vrai date : %d\n",carte->date); /*date carte valide*/
            return 1;
        }
        else{
            printf("\nMauvaise date.\n");  /*sinon date non valide*/
            return 0;
        }
    }
    else{
        printf("\nMauvaise date.\n");
        return 0;
    }

}

t_rondeJoueur *tourSuivant(t_rondeJoueur *p_ronde){ /*valide*/
    p_ronde->tete=p_ronde->tete->nextJoueur;  /*on incremente la tete de la ronde de joueurs*/
    return p_ronde; /*on retourne la ronde actuelle*/
}

void afficheVainqueur(t_rondeJoueur *p_ronde){ /*valide*/
    t_joueur *p_courant; /*on cree un pointeur courant sur un type joueur*/
    int maxCartes=0; /*on initialise un maximum*/
    if((p_ronde==NULL)||(p_ronde->tete==NULL)||(p_ronde->nbJoueurs<=0)){  /*si il n'y a pas de joueurs*/
        printf("\nIl n'y a aucun joueurs dans cette partie.\n");
        return;
    }
    else{
        p_courant=p_ronde->tete; /*le pointeur courant prend la valeur de la tete de la ronde*/
        t_rondeJoueur *p_rondeVainqueur=(t_rondeJoueur *)malloc(sizeof(t_rondeJoueur)); /*on alloue un pointeur sur la ronde des ou du vainqueur(s) */
        if(p_rondeVainqueur!=NULL){ /*si allocation reussie*/
            do{
                if(p_courant->nbCartes==0){ /*si le joueur courant n'a aucune carte*/
                    /*alors on ne fait rien*/
                }
                else if(p_courant->nbCartes>maxCartes){  /*si le joueur courant a plus de cartes que l'ancien maximum de cartes*/
                    t_joueur *p_vainqueur=(t_joueur *)malloc(sizeof(t_joueur)); /*on alloue un pointeur sur joueur*/
                    if(p_vainqueur!=NULL){ /*si allocation reussie*/
                        p_vainqueur->nomJoueur=p_courant->nomJoueur; /*on cree un nouveau joueur : vainqueur a partir du joueur courant*/
                        p_vainqueur->nbCartes=p_courant->nbCartes;
                        p_vainqueur->frise=p_courant->frise;
                        p_vainqueur->nextJoueur=NULL;
                        p_rondeVainqueur->tete=p_vainqueur; /*ce joueur prend la tete de la ronde car il est pour l'instant seul a avoir battu le record de nombre de cartes*/
                        p_rondeVainqueur->nbJoueurs=1; /*le nombre de joueur dans la ronde prend donc la valeur 1*/
                        maxCartes=p_courant->nbCartes; /*le maximum de cartes est donc remplace par le nouveau record*/
                    }
                    else{ /*si allocation echoue*/
                        printf("\nErreur memoire\n");
                        return;
                    }
                }
                else if(p_courant->nbCartes==maxCartes){ /*si le joueur courant a le meme nombre de cartes que le record actuel*/
                    t_joueur *p_vainqueur=(t_joueur *)malloc(sizeof(t_joueur)); /*on alloue un pointeur sur joueur*/
                    if(p_vainqueur!=NULL){ /*si allocation reussie*/
                        p_vainqueur->nomJoueur=p_courant->nomJoueur;  /*on cree un nouveau joueur : vainqueur a partir du joueur courant*/
                        p_vainqueur->nbCartes=p_courant->nbCartes;
                        p_vainqueur->frise=p_courant->frise;
                        p_vainqueur->nextJoueur=NULL;
                        if(p_rondeVainqueur->tete==NULL){
                            p_rondeVainqueur->tete=p_vainqueur;
                        }
                        t_joueur *p_courantVainqueur; /*on cree un nouveau pointeur courant*/
                        p_courantVainqueur=p_rondeVainqueur->tete; /*ce pointeur pointe sur la tete de la ronde des vainqueurs*/
                        while(p_courantVainqueur->nextJoueur!=NULL){ /*on parcourt la ronde des vainqueurs*/
                            p_courantVainqueur=p_courantVainqueur->nextJoueur;
                        }
                        p_courantVainqueur->nextJoueur=p_vainqueur; /*on ajoute le pointeur d'un nouveau vainquer a la suite de la ronde des vainqueurs*/
                        p_rondeVainqueur->nbJoueurs+=1; /*on incremente le nombre de joueurs dans la ronde*/
                    }
                    else{  /*si allocation echoue*/
                        printf("\nErreur memoire\n");
                        return;
                    }
                }
                p_courant=p_courant->nextJoueur; /*on incremente le pointeur courant*/
            }while(p_courant!=p_ronde->tete); /*tant qu'on a pas fait le tour de la ronde => on regarde tous les joueurs*/
        }
        else{ /*si allocation echoue*/
            printf("\nErreur memoire\n");
            return;
        }
        if(p_rondeVainqueur->tete->nextJoueur==NULL){ /*si il n'y qu'un seul vainqueur*/
            if(maxCartes==1){ /*si le maximum est d'une seule carte*/
                printf("\nLe vainqueur de la partie avec %d carte est : \n",maxCartes); /*on affiche carte sans 's'*/
            }
            else{
                printf("\nLe vainqueur de la partie avec %d cartes est : \n",maxCartes);
            }
        }
        else{ /*si il y en a plusieurs*/
            if(maxCartes==1){ /*si le maximum est d'une seule carte*/
                printf("\nLes vainqueurs de la partie avec %d carte sont : \n",maxCartes); /*on affiche carte sans 's'*/
            }
            else{
                printf("\nLes vainqueurs de la partie avec %d cartes sont : \n",maxCartes);
            }
        }
        p_courant=p_rondeVainqueur->tete; /*pointeur courant pointe sur la tete de la ronde des vainqueurs*/
        do{ /*on parcourt la liste des vainqueurs*/
            printf("%s\n",p_courant->nomJoueur); /*on affiche le nom du joueur gagnant*/
            p_courant=p_courant->nextJoueur; /*on incremente le pointeur*/
        }while(p_courant!=NULL);
    }
}

int compteCartesCategorie(t_joueur *p_joueur,char categorie[]){ /*valide*/
    int nbCartesCategory=0; /*on initialise le nombre de cartes a 0*/
    if((p_joueur==NULL)||(p_joueur->frise==NULL)||(p_joueur->frise->tete==NULL)||(p_joueur->nbCartes<=0)){ /*si le joueur n'existe pas ou s'il n'a pas de cartes*/
        return nbCartesCategory; /*on retourne 0*/
    }
    t_frise *p_courant=p_joueur->frise->tete; /*on cree un pointeur courant qui va parcourir toutes les cartes du joueur*/
    do{
        if(strcmp(p_courant->carte->category,categorie)==0){ /*si une carte appartient a la categorie demandee*/
            nbCartesCategory+=1; /*on incremente le nombre de cartes*/
        }
        p_courant=p_courant->nextCarte;  /*on incremente le pointeur*/
    }while(p_courant!=NULL);
    return nbCartesCategory; /*on retourne le nombre de cartes*/
}

void afficheVainqueurCategorie(t_rondeJoueur *p_ronde, char categorie[]){ /*valide*/
    t_joueur *p_courant; /*on cree un pointeur courant sur un type joueur*/
    int maxCartes=0; /*on initialise un maximum a 0*/
    if((p_ronde==NULL)||(p_ronde->tete==NULL)||(p_ronde->nbJoueurs<=0)){  /*si il n'y a pas de joueurs*/
        printf("\nIl n'y a aucun joueurs dans cette partie.\n");
        return;
    }
    else{
        p_courant=p_ronde->tete; /*le pointeur courant prend la valeur de la tete de la ronde*/
        t_rondeJoueur *p_rondeVainqueur=(t_rondeJoueur *)malloc(sizeof(t_rondeJoueur)); /*on alloue un pointeur sur la ronde des ou du vainqueur(s) */
        if(p_rondeVainqueur!=NULL){ /*si allocation reussie*/
            do{
                if(compteCartesCategorie(p_courant,categorie)==0){ /*si le joueur courant n'a pas de cartes dans cette categorie*/
                    /*alors on ne fait rien*/
                }
                else if(compteCartesCategorie(p_courant,categorie)>maxCartes){  /*si le joueur courant a plus de cartes dans la categorie que l'ancien maximum de cartes*/
                    t_joueur *p_vainqueur=(t_joueur *)malloc(sizeof(t_joueur)); /*on alloue un pointeur sur joueur*/
                    if(p_vainqueur!=NULL){ /*si allocation reussie*/
                        p_vainqueur->nomJoueur=p_courant->nomJoueur; /*on cree un nouveau joueur : vainqueur a partir du joueur courant*/
                        p_vainqueur->nbCartes=p_courant->nbCartes;
                        p_vainqueur->frise=p_courant->frise;
                        p_vainqueur->nextJoueur=NULL;
                        p_rondeVainqueur->tete=p_vainqueur; /*ce joueur prend la tete de la ronde car il est pour l'instant seul a avoir battu le record de nombre de cartes dans la categorie*/
                        p_rondeVainqueur->nbJoueurs=1; /*le nombre de joueur dans la ronde prend donc la valeur 1*/
                        maxCartes=compteCartesCategorie(p_courant,categorie); /*le maximum de cartes dans la categorie est donc remplace par le nouveau record*/
                    }
                    else{ /*si allocation echoue*/
                        printf("\nErreur memoire\n");
                        return;
                    }
                }
                else if(compteCartesCategorie(p_courant,categorie)==maxCartes){ /*si le joueur courant a le meme nombre de cartes dans la categorie que le record actuel*/
                    t_joueur *p_vainqueur=(t_joueur *)malloc(sizeof(t_joueur)); /*on alloue un pointeur sur joueur*/
                    if(p_vainqueur!=NULL){ /*si allocation reussie*/
                        p_vainqueur->nomJoueur=p_courant->nomJoueur;  /*on cree un nouveau joueur : vainqueur a partir du joueur courant*/
                        p_vainqueur->nbCartes=p_courant->nbCartes;
                        p_vainqueur->frise=p_courant->frise;
                        p_vainqueur->nextJoueur=NULL;
                        if(p_rondeVainqueur->tete==NULL){ /*si la ronde des vainqueurs ne contient aucun vainqueur, ce qui correspond au cas ou le nb de cartes = 0, ici plus necessaire car le cas est traite avant*/
                            p_rondeVainqueur->tete=p_vainqueur; /*on definit une nouvelle tete de la ronde*/
                        }
                        t_joueur *p_courantVainqueur; /*on cree un nouveau pointeur courant*/
                        p_courantVainqueur=p_rondeVainqueur->tete; /*ce pointeur pointe sur la tete de la ronde des vainqueurs*/
                        while(p_courantVainqueur->nextJoueur!=NULL){ /*on parcourt la ronde des vainqueurs*/
                            p_courantVainqueur=p_courantVainqueur->nextJoueur;
                        }
                        p_courantVainqueur->nextJoueur=p_vainqueur; /*on ajoute le pointeur d'un nouveau vainquer a la suite de la ronde des vainqueurs*/
                        p_rondeVainqueur->nbJoueurs+=1; /*on incremente le nombre de joueurs dans la ronde*/
                    }
                    else{  /*si allocation echoue*/
                        printf("\nErreur memoire\n");
                        return;
                    }
                }
                p_courant=p_courant->nextJoueur; /*on incremente le pointeur courant*/
            }while(p_courant!=p_ronde->tete); /*tant qu'on a pas fait le tour de la ronde => on regarde tous les joueurs*/
        }
        else{ /*si allocation echoue*/
            printf("\nErreur memoire\n");
            return;
        }
        if(maxCartes==0){ /*dans le cas ou aucun joueur ne possede une carte dans cette categorie*/
            printf("\nIl n'y a aucun vainqueur dans la categorie %s.\n",categorie);
            return;
        }
        if(p_rondeVainqueur->tete->nextJoueur==NULL){ /*si il n'y qu'un seul vainqueur*/
            if(maxCartes==1){ /*si le maximum est d'une seule carte*/
                printf("\nLe vainqueur de la partie dans la categorie %s avec %d carte est : \n",categorie,maxCartes); /*on affiche carte sans 's'*/
            }
            else{
                printf("\nLe vainqueur de la partie dans la categorie %s avec %d cartes est : \n",categorie,maxCartes);
            }
        }
        else{ /*si il y en a plusieurs*/
            if(maxCartes==1){ /*si le maximum est d'une seule carte*/
                printf("\nLes vainqueurs de la partie dans la categorie %s avec %d carte sont : \n",categorie,maxCartes); /*on affiche carte sans 's'*/
            }
            else{
                printf("\nLes vainqueurs de la partie dans la categorie %s avec %d cartes sont : \n",categorie,maxCartes);
            }
        }
        p_courant=p_rondeVainqueur->tete; /*pointeur courant pointe sur la tete de la ronde des vainqueurs*/
        do{ /*on parcourt la liste des vainqueurs*/
            printf("%s\n",p_courant->nomJoueur); /*on affiche le nom du joueur gagnant*/
            p_courant=p_courant->nextJoueur; /*on incremente le pointeur*/
        }while(p_courant!=NULL);
    }
}

void afficheVainqueurToutesCategories(t_rondeJoueur *p_ronde,t_pileCategory *p_pileCategory){ /*valide*/
    if(p_pileCategory==NULL){ /*si la pile de categorie est vide*/
        printf("\nIl n'y aucunes categories enregistrees.\n");
        return;
    }
    t_chaineCategory *p_courant; /*on cree un pointeur courant*/
    p_courant=p_pileCategory->tete; /*qui prend la valeur de la tete de la pile de categorie*/
    while(p_courant!=NULL){ /*on parcourt toutes les categories*/
        afficheVainqueurCategorie(p_ronde,p_courant->nomCategory); /*on affiche le ou les vainqueur(s) dans chaque categorie*/
        p_courant=p_courant->nextCategory; /*on incremente le pointeur courant sur les categories*/
    }
}
