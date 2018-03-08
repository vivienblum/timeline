#ifndef SIMPLEIO_H_INCLUDED
#define SIMPLEIO_H_INCLUDED
#include <string.h>

#define MAX_STRING_SIZE 100
/*const MAX_STRING_SIZE = 100;*/
char* lireChaine();
int lireEntier();
int lireEntierEntre(int borneMin, int borneMax);
void enleveSautDeLigne(char *t);
void enleveAccents(char *t);
char *lireChaineFichier(FILE *fichier);

#endif // SIMPLEIO_H_INCLUDED
