#include "affichage.h"

void affichage(oxy myOxy){

    //si .verrouData est présent => opération lecture/écriture en cours => on ne peut rien faire
    //si pas de .verrouData alors on peut écrire ou lire le fichier

		if(  access( ".verrouData", F_OK) != -1){ //Le fichier existe
            printf("Il existe .verrouData. Aucune action n'est possible !");
        } else { //Le fichier n'existe pas
            FILE* P_VERROU = fopen(".verrouData", "w");
            FILE* data = fopen("Data.txt","w+");
            int spo2 = myOxy.spo2;
            int pouls = myOxy.pouls;
            fprintf(data,"%d\n%d", spo2,pouls); //ajoute les valeurs de spo2 et pouls dans le fichier Data.txt
            fclose(data);
            fclose(P_VERROU);
            remove(".verrouData");
		}

}

