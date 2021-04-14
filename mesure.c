#include "mesure.h"
#include "fichiers.h"

oxy mesureTest(char* filename){
	oxy myOxy;
	absorp myAbsorp;
	param_mesure ech;
    init_mesure(&ech);
    int file_state = 0;

	FILE* iirData = initFichier(filename);//lis le fichier une premiere fois pour calculer la période

    while(file_state != EOF) { //End of file
        myAbsorp = lireFichier(iirData, &file_state); //on lit le fichier de sortie de IIR => correspondant à l'entrée de Oxy
        if(file_state!=EOF){
            myOxy = mesure(myAbsorp, &ech, myOxy);
        }else{
            printf("End of file in Mesure\n");
        }
    }
	return myOxy;
}
oxy mesure(absorp myAbsorp, param_mesure* ech, oxy myOxy1){

    int SpO2 = 0;

    if (myAbsorp.acr >= ech->MaxAcr) { ech->MaxAcr = myAbsorp.acr; }
    if (myAbsorp.acr <= ech->MinAcr) { ech->MinAcr = myAbsorp.acr; }
    if (myAbsorp.acir >= ech->MaxAcir) { ech->MaxAcir = myAbsorp.acir; }
    if (myAbsorp.acir <= ech->MinAcir) { ech->MinAcir = myAbsorp.acir; }

    if (myAbsorp.acr < 0 && ech->passageParZero == 0) {
        ech->passageParZero = 1;
    }
    if (myAbsorp.acr > 0 && ech->passageParZero == 1){
        ech->Dcr = myAbsorp.dcr;
        ech->Dcir = myAbsorp.dcir;

        float PtP_Acr = ech->MaxAcr - ech->MinAcr;
        float PtP_Acir = ech->MaxAcir - ech->MinAcir;

        float RsIR = (PtP_Acr / ech->Dcr) / (PtP_Acir / ech->Dcir);
        if (RsIR < 1) {
            SpO2 = RsIR * -25 + 110;//fonction affine entre 0 et 1
        } else {
            SpO2 = RsIR * -35.7 + 120;//fonction affine entre 1 et 3.4
        }
        int SpO2Final=(SpO2+ech->SpO2Period1)/2;
        ech->SpO2Period1 = SpO2;

        float periode=ech->periode;
        int pouls = 60/(periode*0.002); //toutes les 2ms
        int poulsFinal=(pouls+ech->poulsPeriod1)/2;
        ech->poulsPeriod1 = pouls;

        myOxy1.spo2 = SpO2Final;
        myOxy1.pouls = poulsFinal;
        ech->periode=0;
        ech->passageParZero=false;
        return myOxy1;
    }
    ech->periode++;
    return myOxy1;
}
void init_mesure(param_mesure* ech){
    ech->MaxAcr=1;
    ech->MaxAcir=1;
    ech->MinAcr=0;
    ech->MinAcir=0;
    ech->Dcr=2030;
    ech->Dcir=2030;
    ech->premierePeriode=false;
    ech->passageParZero=false;
    ech->periode=0;
    ech->poulsPeriod1=0;
    ech->SpO2Period1=0;
}