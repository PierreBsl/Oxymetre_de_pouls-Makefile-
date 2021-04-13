#include "mesure.h"
#include "fichiers.h"

oxy mesureTest(char* filename){
	oxy myOxy;
	absorp myAbsorp;
    int file_state = 0;
    int half_period = 0;
	FILE* iirData = initFichier(filename);
    myAbsorp = lireFichier(iirData, &file_state); //on lit le fichier de sortie de IIR => correspond à l'entrée de Oxy
    init_mesure(myAbsorp,iirData, &file_state, half_period);

   /* while(file_state != EOF){ //End of file
        myAbsorp = lireFichier(iirData, &file_state); //on lit le fichier de sortie de IIR => correspond à l'entrée de Oxy
        if(file_state == EOF){
            return myOxy;
        }else{
            //myOxy = mesure(myAbsorp, );
        }
    }
    //nous voulons recuperer le signal d'entree de IRR correspondant donc au signal de sortie FIR

	return myOxy;*/

}
int init_mesure(absorp myAbsorp, FILE* pf,int* state, int half_period){
    absorp myAbsorp2;
    myAbsorp2 = lireFichier(pf, state); //on lit le fichier de sortie de IIR => correspond à l'entrée de Oxy
    if(myAbsorp.acr == myAbsorp2.acr){
        half_period++;
        init_mesure(myAbsorp2, pf, state, half_period);
    }else{
        while(myAbsorp.acr != myAbsorp2.acr && myAbsorp.acr < myAbsorp2.acr){
            half_period++;
            myAbsorp2 = lireFichier(pf, state);
        }
        return half_period;
    }
}

/*oxy mesure(absorp myAbsorp, ){

    oxy myOxy;


    return myOxy;
}*/

