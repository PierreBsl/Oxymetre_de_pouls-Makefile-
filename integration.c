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
            myAbsorp = fir(myAbsorp,&firparam);
            myAbsorp = iir(myAbsorp,&iirparam);
            myOxy = mesure(myAbsorp,&mesureparam, myOxy);
            affichage(myOxy);
        }else{
            printf("End of file in Integration.c\n");
        }
    }
    finFichier(myFile);
}