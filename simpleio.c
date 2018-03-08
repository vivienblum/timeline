#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleio.h"
#include "lireFichier.h"

char *lireChaine(){
    char * buffer = (char *)malloc(sizeof(char) * MAX_STRING_SIZE);
    if (buffer == NULL) return buffer;
    fgets(buffer, MAX_STRING_SIZE, stdin);
    size_t i = strlen(buffer) - 1;
    if (buffer[i] == '\n')
        buffer[i] = '\0';
    return buffer;
}

int lireEntier() {

  int entierLu;
  int nbEntiersLus;
  char videTampon;

  do {
    nbEntiersLus = scanf("%d", &entierLu);
    if (nbEntiersLus != 1) {
      printf("Erreur de format: veuillez saisir un entier.\n");

    }
    // vidage du reste du tampon (si plusieurs entiers ou saisie invalide)
    do {
      scanf("%c", &videTampon);
    } while (videTampon != '\n');
  } while (nbEntiersLus != 1);

  return entierLu;
}

int lireEntierEntre(int borneMin, int borneMax) {
    int result;
    int tampon;

    if (borneMax < borneMin) {
        tampon = borneMax;
        borneMax = borneMin;
        borneMin = tampon;
    }

    do {
        result = lireEntier();
        if (result < borneMin || result > borneMax) {
            printf("Erreur de bornes : la valeur saisie doit Ãªtre comprise entre %d et %d\n", borneMin, borneMax);
        }

    } while (result < borneMin || result > borneMax);
    return result;
}

void enleveSautDeLigne(char *t){ /*valide*/
    int i=0;
    while(t[i]!='\0'){ /*on parcourt la chaine de caractere*/
        if(t[i]=='\n'){ /*si on rencontre un caractere \n */
            t[i]='\0';   /*on le remplace par le caractere \0 */
        }
        i=i+1;
    }
}

void enleveAccents(char *t){ /*non fonctionnel*/
    int i=0;
    while(t[i]!='\0'){ /*on parcourt toute la chaine de caractere*/
        switch(t[i]){
            case 'e' : t[i]='e'; break; /*dans le cas ou on rencontre un accent aigu sur le e, on le remplace par un e*/
            default : break;                  /*PB: les accents ne sont pas interpretes comme des caracteres en C */
        }
        i=i+1;
    }
}

char *lireChaineFichier(FILE *fichier){ /*valide*/
    char chaine[TAILLE_MAX]; /*on cree un tableau de caractere*/
    char *p_chaine; /*on cree un pointeur qui pointra sur la chaine de caractere*/
    if(fichier==NULL){ /*on teste le cas ou le fichier n'existe pas*/
        return NULL;
    }
    if(fgets(chaine,TAILLE_MAX,fichier)==NULL){ /*on lit une ligne du fichier quand rentre dans la chaine de caractere*/
        return NULL;                                /*on teste si on est pas a la fin du fichier */
    }
    enleveSautDeLigne(chaine);  /*on enleve le caractere '\n' a la fin de la chaine de caractere*/
    /*enleveAccents(chaine);*/
    p_chaine=(char*)malloc((sizeof(char))*strlen(chaine)+1) ; /*on alloue la place memoire pour un pointeur sur la chaine de caractere relvee*/
    if (p_chaine==NULL){ /*on teste si l'allocation memoire s'est bien deroulee*/
        return NULL;
    }
    strcpy(p_chaine,chaine); /*on copie la chaine de caractere dans le pointeur */
    return p_chaine;
}
