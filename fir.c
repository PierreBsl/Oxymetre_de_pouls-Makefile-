#include "fir.h"
#include "fichiers.h"

//tableau des coefficients du filtre FIR
float FIR_TAPS[51]={1.4774946e-019, 1.6465231e-004, 3.8503956e-004, 7.0848037e-004, 1.1840522e-003, 1.8598621e-003, 2.7802151e-003, 3.9828263e-003, 5.4962252e-003,7.3374938e-003, 9.5104679e-003, 1.2004510e-002, 1.4793934e-002, 1.7838135e-002, 2.1082435e-002, 2.4459630e-002, 2.7892178e-002, 3.1294938e-002, 3.4578348e-002, 3.7651889e-002, 4.0427695e-002, 4.2824111e-002, 4.4769071e-002, 4.6203098e-002, 4.7081811e-002, 4.7377805e-002, 4.7081811e-002, 4.6203098e-002, 4.4769071e-002, 4.2824111e-002, 4.0427695e-002, 3.7651889e-002, 3.4578348e-002, 3.1294938e-002, 2.7892178e-002, 2.4459630e-002, 2.1082435e-002, 1.7838135e-002, 1.4793934e-002, 1.2004510e-002, 9.5104679e-003, 7.3374938e-003, 5.4962252e-003, 3.9828263e-003, 2.7802151e-003, 1.8598621e-003, 1.1840522e-003, 7.0848037e-004, 3.8503956e-004, 1.6465231e-004, 1.4774946e-019};

absorp firTest(char* filename){
    absorp myAbsorp;
    absorp myAbsorpFinal;
    param_fir firparam;
    init_fir(&firparam);

    int state =0; //fichier variable
	FILE* data = initFichier(filename); //creation du fichier correspondant à l'entrée

	while (state != EOF){ //on parcourt jusqu'à la fin du fichier
	    myAbsorp = lireFichier(data,&state);
	    if(state!=EOF){
            myAbsorpFinal = fir(myAbsorp, &firparam); //On applique le filtre à la valeur d'absorp myAbsorp
        }else{
	        printf("End of file in Fir\n");
	    }
	}
	return myAbsorpFinal;
}

absorp fir(absorp myAbsorpS, param_fir * cpt){
    absorp myAbsorpTmp; //represente la valeur temporaire
    myAbsorpTmp.acr=0; //initialisation de toutes nos valeurs à zéro
    myAbsorpTmp.acir=0;
    myAbsorpTmp.dcr=0;
    myAbsorpTmp.dcir=0;
    int j, k;

    for(k=50; k>0; k--){ //Gestion du buffer circulaire
        cpt->absorp1[k]=cpt->absorp1[k-1];
    }
    cpt->absorp1[0] = myAbsorpS; //On attribue la nouvelle valeur d'absorp à la première place du buffer
    for(j=0; j<51; j++){
        myAbsorpTmp.acr+=FIR_TAPS[j]*cpt->absorp1[50-j].acr; //application de la formule du filtrage FIR
        myAbsorpTmp.acir+=FIR_TAPS[j]*cpt->absorp1[50-j].acir; //application de la formule du filtrage FIR
    }
    myAbsorpTmp.dcr=myAbsorpS.dcr; //on garde inchangés les composantes dcr et dcir
    myAbsorpTmp.dcir=myAbsorpS.dcir;

    return myAbsorpTmp;
}
void init_fir(param_fir * cpt){ //Fonction qui initialise le tableau de 51 absorp
    int i;
    for(i=0; i<51; i++){
        cpt->absorp1[i].acr=0;
        cpt->absorp1[i].acir=0;
        cpt->absorp1[i].dcr=0;
        cpt->absorp1[i].dcir=0;
    }
}