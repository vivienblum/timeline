#include <stdio.h>
#include <stdlib.h>
#include "cartes.h"
#include "joueur.h"
#include "lireFichier.h"

int main()
{
    t_listePile *p_pile;
    p_pile=initialisePileFichier(); /*on cree une pile de cartes a partir d'un fichier*/
    /*printPile(p_pile);*/

    t_pileCategory *p_pileCategory;
    p_pileCategory=creePileCategorie(p_pile); /*on cree une pile de categorie a partir de la pile de cartes*/
    /*printPileCategorie(p_pileCategory);*/

    t_rondeJoueur *p_ronde;

    printf("\nIl est conseille de mettre la console en plein ecran.\n\n");
    printf("Jeu Timeline :\n\n");
    p_ronde=creeRondeJoueur(); /*on cree une ronde de joueurs*/
    printRondeJoueurs(p_ronde); /*on affiche cette ronde*/
    printf("\n\n\n\n\n \n\n\n\n\n \n\n\n\n\n \n\n\n\n\n \n\n\n\n\n");  /*on effectue un decalage sur l'ecran afin de ne pas polluer l'ecran*/

    while(p_pile->nbCartes>0){ /*tant que la pile de carte n'est pas vide*/
        t_joueur *p_courant;
        int aGagne;
        p_courant=p_ronde->tete; /*pointeur courant pointe sur la tete de la ronde de joueurs*/
        do{
            printf("\n\n\n\n\n \n\n\n\n\n \n\n\n\n\n \n\n\n\n\n \n\n\n\n\n"); /*on effectue un decalage sur l'ecran afin de ne pas polluer l'ecran*/
            aGagne=0; /*on initialise aGagne a 0*/
            printf("\nA ton tour %s :\n",p_courant->nomJoueur); /*on affiche le nom du joueur a qui c'est le tour*/
            printFrise(p_courant); /*on affiche la frise du joueur a qui c'est le tour de jouer*/
            printf("\nTrouves la date de cette carte :\n");
            if(joueurChercheCarte(p_courant,p_pile->tete->carte)==1){ /*si le joueur a trouve la date de la carte*/
                p_courant=ajoutCarteJoueur(p_courant,p_pile->tete->carte); /*le joueur recupere la carte*/
                p_pile=enleverUneCarte(p_pile); /*on enleve la carte de la pile*/
                printf("\nLa nouvelle frise de %s est :\n",p_courant->nomJoueur);
                printFrise(p_courant);  /*on affiche la nouvelle frise de la carte*/
                aGagne=1; /*aGagne prend la valeur 1*/
            }
            else{ /*si le joueur n'a pas trouver la date de la carte*/
                p_courant=p_courant->nextJoueur; /*le joueur suivant tente a son tour*/
            }
        }while((aGagne!=1)&&(p_courant!=p_ronde->tete)); /*tant que la carte n'a pas ete gagne, et qu'on a pas fait le tour des joueurs*/
        if((aGagne==0)&&(p_courant==p_ronde->tete)){ /*si aucun joueur n'a trouve la date*/
            p_pile=enleverUneCarte(p_pile);  /*on enleve la carte*/
        }
        p_ronde=tourSuivant(p_ronde); /*on passe au tour suivant => c'est au tour du joueur suivant de joueur avec une nouvelle carte*/
    }
    printf("\n\n\n\n\n \n\n\n\n\n \n\n\n\n\n \n\n\n\n\n \n\n\n\n\n");  /*on effectue un decalage sur l'ecran afin de ne pas polluer l'ecran*/
    afficheVainqueur(p_ronde); /*on affiche le ou les vainqueur(s) de la ronde*/
    printf("\n\n");
    afficheVainqueurToutesCategories(p_ronde,p_pileCategory);
    return 0;
}
