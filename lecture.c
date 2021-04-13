#include "lecture.h"


absorp lecture(FILE* file_pf, int* file_state){

	absorp myAbsorp;
    myAbsorp.acr=0;
    myAbsorp.dcr=0;
    myAbsorp.acir=0;
    myAbsorp.dcir=0;

	float ACr=0, DCr=0, ACir=0, DCir=0;
	*file_state = fscanf(file_pf, "%f,%f,%f,%f", &ACr,&DCr,&ACir,&DCir);
	if(*file_state==EOF){
        printf("Limite de fichier atteinte par la fonction lecture!");
	    return myAbsorp;
	}
	while(*file_state!=4){
        *file_state= fscanf(file_pf, "%f,%f,%f,%f", &ACr,&DCr,&ACir,&DCir);
    }
    myAbsorp.acr=ACr-2048;
    myAbsorp.dcr=DCr;
    myAbsorp.acir=ACir-2048;
    myAbsorp.dcir=DCir;
	return myAbsorp; // return EOF flag

}

