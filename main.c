#include "define.h"

#include "affichage.h"
#include "fichiers.h"
#include "fir.h"
#include "iir.h"
#include "integration.h"
#include "lecture.h"
#include "mesure.h"

int main() {
   oxy myOxy;
   myOxy.spo2=96;
   myOxy.pouls=120;
   affichage(myOxy);

   /*
   //param_fir* myFIR = init_fir();//init FIR
   //param_iir* myIIR = init_iir();//initIIR
   //param_mesure* myMes = init_mesure();//init mesure
   FILE* myFile = initFichier("../fichiers/record1.dat");
   do{
       //myAbsorp = lireFichier(myFile, &etat);
       //myAbsorp = fir(myAbsorp, myFIR);
       //myAbsorp = iir(myAbsorp, myIIR);
       //myOxy = mesure(myAbsorp, myMes);
       //affichage(myOxy);
   }while (etat !=EOF);
   finFichier(myFile);
   //fin_mesure(myMes);
   //fin_iir(myIIR);
   //fin_fir(myFIR);
   //return EXIT_SUCESS;
    */
}
