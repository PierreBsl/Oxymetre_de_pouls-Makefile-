#include "fir.h"

typedef struct{
    float acr;
    float dcr;
    float acir;
} absorp;
absorp firTest(char* filename){
    absorp myAbsorp;
    absorp myAbsorpFinal;
    param_fir firparam;
    init_fir(&firparam);

    int state =0; //fichier variable
	FILE* data = initFichier(filename); //creation du fichier correspondant à l'entrée (ici record1.dat)

	while (state != EOF){ //on parcourt jusqu'à la fin du fichier
	    myAbsorp = lireFichier(data,&state);
	    if(state!=EOF){
            myAbsorpFinal = fir(myAbsorp, &firparam);
        }else{
	        printf("End of file in Fir\n");
	    }
	}
	return myAbsorpFinal;
}
absorp fir(absorp myAbsorpS, param_fir * cpt){ //changer avec myAbsorpTmp
    absorp myAbsorpTmp; //valeur temporaire
    myAbsorpTmp.acr=0; //initialisation de toutes nos valeurs à zéro
    myAbsorpTmp.acir=0;
    myAbsorpTmp.dcr=0;
    myAbsorpTmp.dcir=0;
    int j, k;

    for(k=50; k>0; k--){
        cpt->absorp1[k]=cpt->absorp1[k-1];
    }
    cpt->absorp1[0] = myAbsorpS;
    for(j=0; j<51; j++){
        myAbsorpTmp.acr+=FIR_TAPS[j]*cpt->absorp1[50-j].acr;
        myAbsorpTmp.acir+=FIR_TAPS[j]*cpt->absorp1[50-j].acir;
    }
    myAbsorpTmp.dcr=myAbsorpS.dcr;
    myAbsorpTmp.dcir=myAbsorpS.dcir;

    return myAbsorpTmp;
}
void init_fir(param_fir * cpt){
    int i;
    for(i=0; i<51; i++){
        cpt->absorp1[i].acr=0;
        cpt->absorp1[i].acir=0;
        cpt->absorp1[i].dcr=0;
        cpt->absorp1[i].dcir=0;
    }
    cpt->premierRemplissage = true;
}