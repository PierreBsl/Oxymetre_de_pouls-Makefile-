#include "define.h"
#include "affichage.h"
#include "fichiers.h"
#include "fir.h"
#include "iir.h"
#include "integration.h"
#include "lecture.h"
#include "mesure.h"
void integrationTest(char* filename)
{
    int file_state=0;
    absorp myAbsorp;

    oxy myOxy;
    myOxy.spo2=0;
    myOxy.pouls=0;

    // Déclaration pour FIR
    param_fir firparam;
    init_fir(&firparam);

    // Déclaration pour IIR
    param_iir iirparam;
    init_iir(&iirparam);

    // Déclaration pour Mesure
    param_mesure mesureparam;
    init_mesure(&mesureparam);

    FILE* myFile = initFichier(filename); //mettre record.1.dat

    while(file_state != EOF){
        myAbsorp = lecture(myFile,&file_state);
        if(file_state!=EOF){
            myAbsorp = fir(myAbsorp,&firparam);//On applique le filtre fir
            myAbsorp = iir(myAbsorp,&iirparam);//On applique le filtre iir
            myOxy = mesure(myAbsorp,&mesureparam, myOxy);//On convertit les valeurs d'absorp en SpO2 et Pouls
            affichage(myOxy);//On affiche les valeurs contenues dans myOxy
            iteration++;
        }else{
            printf("End of file in Integration.c\n");
        }
    }
    finFichier(myFile);
}