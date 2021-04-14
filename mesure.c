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

        float PtP_Acr;
        float PtP_Acr1 = ech->MaxAcr - ech->MinAcr;
        if(ech->PtP_ACr_prec==0){
            PtP_Acr=PtP_Acr1;
        }
        else {
            PtP_Acr = (PtP_Acr1 + ech->PtP_ACr_prec) / 2;
        }
        ech->PtP_ACr_prec = PtP_Acr;

        float PtP_Acir;
        float PtP_Acir1 = ech->MaxAcir - ech->MinAcir;
        if(ech->PtP_ACir_prec==0){
            PtP_Acir=PtP_Acir1;
        }
        else {
            PtP_Acir = (PtP_Acir1 + ech->PtP_ACir_prec) / 2;
        }
        ech->PtP_ACir_prec = PtP_Acir;

        float RsIR = (PtP_Acr / ech->Dcr) / (PtP_Acir / ech->Dcir);
        printf("******* Period *******\nPtP_ACr = %f\nPtP_ACir = %f\nDCr = %f\nDCir = %f\n-----------\n",PtP_Acr,PtP_Acir,ech->Dcr,ech->Dcir);
        int SpO2;
        if (RsIR < 1) {
            SpO2 = RsIR * (-25) + 110;//fonction affine entre 0 et 1
        } else {
            SpO2 = RsIR * (-35.7) + 120;//fonction affine entre 1 et 3.4
        }

        float period=(float)ech->periode;

        int pulseFinal;

        if(ech->poulsPeriod1 == 0){
            pulseFinal = 60 / (period * 0.002); //toutes les 2ms
        }else{
            period= (period + ech->poulsPeriod1) / 2;
            pulseFinal = 60 / (period * 0.002); //toutes les 2ms
        }

        ech->poulsPeriod1 = ech->periode;

        myOxy1.spo2 = SpO2;
        myOxy1.pouls = pulseFinal;
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
    ech->PtP_ACr_prec=0;
    ech->PtP_ACir_prec=0;


}