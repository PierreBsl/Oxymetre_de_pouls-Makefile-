#include "mesure.h"
#include "fichiers.h"

oxy mesureTest(char* filename){
	oxy myOxy;
	absorp myAbsorp;
	echantillon ech;
    init_echantillon(&ech);
    int file_state = 0;

	FILE* iirData = initFichier(filename);//lis le fichier une premiere fois pour calculer la période

    while(file_state != EOF) { //End of file
        myAbsorp = lireFichier(iirData, &file_state); //on lit le fichier de sortie de IIR => correspondant à l'entrée de Oxy
        if(file_state!=EOF){
            myOxy = mesure(myAbsorp, &ech, myOxy);
            printf("SpO2=%d\n",myOxy.spo2);
            printf("Pouls=%d\n\n",myOxy.pouls);
        }else{
            printf("end of file\n");
        }
    }
    printf("retour de myOxy");
	return myOxy;
}
oxy mesure(absorp myAbsorp, echantillon* ech, oxy myOxy1){

    int SpO2 = 0;

    if (myAbsorp.acr == 0 && ech->periode<6 && ech->premierePeriode==false){
        ech->periode++;
        return myOxy1;
    }else{
        ech->premierePeriode=true;
        if (myAbsorp.acr >= ech->MaxAcr) { ech->MaxAcr = myAbsorp.acr; }
        if (myAbsorp.acr <= ech->MinAcr) { ech->MinAcr = myAbsorp.acr; }
        if (myAbsorp.acir >= ech->MaxAcir) { ech->MaxAcir = myAbsorp.acir; }
        if (myAbsorp.acir <= ech->MinAcir) { ech->MinAcir = myAbsorp.acir; }
    }
    if (myAbsorp.acr < 0 && ech->passageParZero == false) {
        ech->passageParZero = true;
    }
    if (myAbsorp.acr > 0 && ech->passageParZero == true){
        ech->Dcr = myAbsorp.dcr;
        ech->Dcir = myAbsorp.dcir;

        float PtP_Acr = ech->MaxAcr - ech->MinAcr;
        float PtP_Acir = ech->MaxAcir - ech->MinAcir;

        float RsIR = (PtP_Acr / ech->Dcr) / (PtP_Acir / ech->Dcir);
        if (RsIR < 1) {
            SpO2 = RsIR * -25 + 110;//fonction affine entre 0 et 1
        } else {
            SpO2 = RsIR * -33 + 120;//fonction affine entre 1 et 3.4
        }
        float periode=ech->periode;
        int pouls = 60/(periode*0.002);
        myOxy1.spo2 = SpO2;
        myOxy1.pouls = pouls;
        ech->periode=0;
        ech->passageParZero=false;
    }
    ech->periode++;
    return myOxy1;
}
void init_echantillon(echantillon* ech){
    ech->MaxAcr=1;
    ech->MaxAcir=1;
    ech->MinAcr=0;
    ech->MinAcir=0;
    ech->Dcr=2030;
    ech->Dcir=2030;
    ech->premierePeriode=false;
    ech->passageParZero=false;
    ech->periode=0;
}