#ifndef FICHIERS_H
#define FICHIERS_H
#include <stdio.h>
#include <stdlib.h>
#include "define.h"


FILE* initFichier(char* nomFichier );
absorp lireFichier(FILE* pf, int* etat);
void finFichier(FILE* pf);
#endif

