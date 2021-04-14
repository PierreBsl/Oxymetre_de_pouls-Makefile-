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
        int etat=0;
        absorp myAbsorp;
        oxy myOxy;
        FILE* myFile = initFichier(filename);
        do{
            myAbsorp = lireFichier(myFile,&etat);
            //myAbsorp = fir(myAbsorp,);
            //myAbsorp = iir(myAbsorp);
            //myOxy = mesure(myAbsorp,;
            affichage(myOxy);
        }while( etat != EOF );
        finFichier(myFile);
        //fin_mesure(myMes);
        //fin_iir(myIIR);
        //fin_fir(myFIR) ;
        return EXIT_SUCCESS;
}