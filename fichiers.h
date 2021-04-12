#ifndef FICHIERS_H
#define FICHIERS_H
#include "define.h"


FILE* initFichier(char* nomFichier );
absorp lireFichier(FILE* pf, int* etat);
void finFichier(FILE* pf);
#endif

