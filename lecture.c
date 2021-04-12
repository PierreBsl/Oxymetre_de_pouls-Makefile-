#include "lecture.h"


absorp lecture(FILE* file_pf, int* file_state){

	absorp myAbsorp;

	int ACr=0, DCr=0, ACir=0, DCir=0;
	*file_state= fscanf(file_pf, "%d,%d,%d,%d", &ACr,&DCr,&ACir,&DCir);
    myAbsorp.acr=ACr;
    myAbsorp.dcr=DCr;
    myAbsorp.acir=ACir;
    myAbsorp.dcir=DCir;
	return myAbsorp; // return EOF flag

}

