#include "fichiers.h"

FILE* initFichier(char* nomFichier ){
	
	FILE* pf=fopen(nomFichier,"r");
	if(pf==NULL){
		printf("dans fichiers.c : erreur ouverture fichier %s\n",nomFichier);
		exit(EXIT_FAILURE);
	}
	return pf;
}

absorp lireFichier(FILE* pf, int* etat){
	absorp myAbsorp;
	char x,y;
	int a=0,b=0,c=0,d=0;
	*etat=fscanf(pf,"%d,%d,%d,%d%c%c",&a,&b,&c,&d,&x,&y);
	myAbsorp.acr=a;
	myAbsorp.dcr=b;
	myAbsorp.acir=c;
	myAbsorp.dcir=d;
	return myAbsorp;
}

void finFichier(FILE* pf){
	fclose(pf);


}

