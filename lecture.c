#include "lecture.h"

absorp lecture(FILE* file_pf, int* file_state){

	absorp myAbsorp;//On initialise une valeur d'absorp temporaire
    myAbsorp.acr=0;
    myAbsorp.dcr=0;
    myAbsorp.acir=0;
    myAbsorp.dcir=0;

	float ACr=0, DCr=0, ACir=0, DCir=0;
	*file_state = fscanf(file_pf, "%f,%f,%f,%f", &ACr,&DCr,&ACir,&DCir);//On récupère les valeurs ACr, ACir, DCr, DCir correspondant au pointeurde lecture file_pf
	if(*file_state==EOF){
        //printf("Limite de fichier atteinte par la fonction lecture!");
	    return myAbsorp;
	}
	while(*file_state!=4){
        //Cette boucle permet de forcer la lecture si l'on ne possède pas 4 valeurs qui se suivent
        // et donc se déplacer dans le fichier jusqu'à obtenir 4 valeurs consécutives
        *file_state= fscanf(file_pf, "%f,%f,%f,%f", &ACr,&DCr,&ACir,&DCir);
    }
    myAbsorp.acr=ACr-2048;//Initialisation de la valeur d'ACr
    myAbsorp.dcr=DCr;
    myAbsorp.acir=ACir-2048;//Initialisation de la valeur d'ACir
    myAbsorp.dcir=DCir;
	return myAbsorp; // return EOF flag

}

