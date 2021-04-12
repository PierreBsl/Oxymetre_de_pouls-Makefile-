#include "iir.h"

absorp iirTest(char* filename){
	absorp	myAbsorp;
	
	return myAbsorp;

}
float iir(int x, int old_x, int old_y){

    int valeur = x - old_x + alpha*old_y;

    return valeur;
}

void init_preAbsorp(param_iir* pre_absorp) {
    pre_absorp->pre_x_acr = 0;
    pre_absorp->pre_x_acir = 0;
    pre_absorp->pre_y_acr = 0;
    pre_absorp->pre_y_acir = 0;
}

