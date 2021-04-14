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
        myAbsorp = lireFichier(iirData, &file_state); //on lit le fichier de sortie de IIR
        if(file_state!=EOF){
            myOxy = mesure(myAbsorp, &ech, myOxy);//On applique la mesure du SpO2 et du Pouls
        }else{
            printf("End of file in Mesure\n");
        }
    }
	return myOxy;
}

oxy mesure(absorp myAbsorp, param_mesure* ech, oxy myOxy1){

    if (myAbsorp.acr >= ech->MaxAcr) { ech->MaxAcr = myAbsorp.acr; }//Calcul du Max des ACr pour 1 période
    if (myAbsorp.acr <= ech->MinAcr) { ech->MinAcr = myAbsorp.acr; }//Calcul du Min des ACr pour 1 période
    if (myAbsorp.acir >= ech->MaxAcir) { ech->MaxAcir = myAbsorp.acir; }//Calcul du Max des ACir pour 1 période
    if (myAbsorp.acir <= ech->MinAcir) { ech->MinAcir = myAbsorp.acir; }//Calcul du Min des ACir pour 1 période

    if (myAbsorp.acr < 0 && ech->passageParZero == 0) {//On vérifie que la courbe passe une première fois par 0 (demi-période)
        ech->passageParZero = 1;//Int jouant le rôle de booléen permettant d'attester le premier passage par 0
    }
    if (myAbsorp.acr > 0 && ech->passageParZero == 1){//On vérifie que la courbe jusque là dans les négatifs dépasse une deuxième fois la valeur 0 (période complète)
        ech->Dcr = myAbsorp.dcr; //On récupère la valeur de DCr
        ech->Dcir = myAbsorp.dcir; //On récupère la valeur de DCir

        float PtP_Acr;//PtP final pour la période

        float PtP_Acr1 = ech->MaxAcr - ech->MinAcr;//On calcul la différence entre le Max et le Min des ACr
        if(ech->PtP_ACr_prec==0){//Etape permettant de vérifier si l'on possède une valeur de PtP_ACr précédente. Si elle vaut 0 il s'agit de la première période
            PtP_Acr=PtP_Acr1;//Le PtP_ACr final vaut celui calculé précedemment
        }
        else {
            PtP_Acr = (PtP_Acr1 + ech->PtP_ACr_prec) / 2;//Si l'on possède une valeur de PtP_ACr précédente alors on réalise une moyenne des 2 pour renvoyer la valeur de PtP_ACr finale
        }
        ech->PtP_ACr_prec = PtP_Acr;//On récupère la nouvelle valeur de PtP_ACr et on la stocke dans une structure

        float PtP_Acir;
        //Ici on réalise exactement les mêmes étapes mais seulement pour le calcul de PtP_ACir
        float PtP_Acir1 = ech->MaxAcir - ech->MinAcir;
        if(ech->PtP_ACir_prec==0){
            PtP_Acir=PtP_Acir1;
        }
        else {
            PtP_Acir = (PtP_Acir1 + ech->PtP_ACir_prec) / 2;
        }
        ech->PtP_ACir_prec = PtP_Acir;

        float RsIR = (PtP_Acr / ech->Dcr) / (PtP_Acir / ech->Dcir);//Calcul du coefficient RsIR
        int SpO2;
        if (RsIR < 1) {
            SpO2 = RsIR * (-25) + 110;//fonction affine pour RsIR compris entre 0 et 1
        } else {
            SpO2 = RsIR * (-35.7) + 120;//fonction affine pour RsIR compris entre 1 et 3.4
        }

        float period=(float)ech->periode;//On récupère la valeur du nombre d'échantillon dans 1 période

        int pulseFinal;

        if(ech->poulsPeriod1 == 0){//On vérifie si l'on possède une valeur d'échantillons de la période précédente
            pulseFinal = 60 / (period * 0.002); //On détermine le pouls pour la première période toutes les 2ms
        }else{
            period= (period + ech->poulsPeriod1) / 2;//Si l'on a une valeur d'échantillonsde la période précédente, on fait la moyenne du nombre des échantillons
            pulseFinal = 60 / (period * 0.002); //On détermine le pouls avec la nouvelle valeur d'échantillons toutes les 2ms
        }

        ech->poulsPeriod1 = ech->periode; //On récupère la valeur d'échantillons pour la période en cours et on la place dans la structure afin de s'en souvenir à l'itération suivante

        myOxy1.spo2 = SpO2;//On attribue à myOxy1 la valeur de SpO2
        myOxy1.pouls = pulseFinal;//On attribue à myOxy1 la valeur de pouls
        ech->periode=0;//On remet la période à 0
        ech->passageParZero=0;//On ré-initialise le passage par 0

        // On remet les valeurs de MaxACr, MinACr, MaxACir, MinACir pour ne pas avoir de problèmes lors de l'itération suivant
        ech->MaxAcr=0;
        ech->MaxAcir=0;
        ech->MinAcr=0;
        ech->MinAcir=0;

        //printf("SpO2 = %d\n",myOxy1.spo2);
        //printf("Pouls = %d\n\n",myOxy1.pouls);
    }
    ech->periode++;//On incrémente la nouvelle période
    return myOxy1;//On retourne la valeur de myOxy
}
void init_mesure(param_mesure* ech){//On initialise les valeurs de la structure de mesure
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