#include "iir.h"
#include "fichiers.h"

float alpha = 0.992;

absorp iirTest(char* filename){
	absorp myAbsorp;
	absorp myAbsorpTmp;
    param_iir preAbsorp;
    init_iir(&preAbsorp);
    int file_state = 0;
    FILE* firData = initFichier(filename);

    //nous voulons recuperer le signal d'entree de IRR correspondant donc au signal de sortie FIR
    while(file_state != EOF){ //End of file
        myAbsorpTmp = lireFichier(firData, &file_state); //on lit le fichier de sortie de FIR => correspond à l'entrée de IIR
        if(file_state == EOF){
            return myAbsorp;
        }else{
            myAbsorp = iir(myAbsorpTmp, &preAbsorp); //on applique le filtre
        }
    }
    return myAbsorp;
}
absorp iir(absorp myAbsorp, param_iir* preAbsorp){

    //on applique la formule du filtrage IIR sur les composantes acr et acir
    preAbsorp->y_moins_un_acr = myAbsorp.acr - preAbsorp->x_moins_un_acr + alpha*preAbsorp->y_moins_un_acr;
    preAbsorp->y_moins_un_acir = myAbsorp.acir - preAbsorp->x_moins_un_acir + alpha*preAbsorp->y_moins_un_acir;
    preAbsorp->x_moins_un_acr = myAbsorp.acr;
    preAbsorp->x_moins_un_acir = myAbsorp.acir;

    myAbsorp.acr = preAbsorp->y_moins_un_acr;
    myAbsorp.acir = preAbsorp->y_moins_un_acir;

    return myAbsorp;//retour de la nouvelle valeur d'absorp
}

void init_iir(param_iir* pre_absorp) {//Initialisation du tableau précédent la valeur d'absorp courante
    pre_absorp->x_moins_un_acr = 0;
    pre_absorp->x_moins_un_acir = 0;
    pre_absorp->y_moins_un_acr = 0;
    pre_absorp->y_moins_un_acir = 0;
}

