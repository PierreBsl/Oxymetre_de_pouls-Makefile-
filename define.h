#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*! ------------------------------------------------------------
  
  \struct absorp
 
  \brief measures
  
  ------------------------------------------------------------*/

typedef struct{
		float acr;  /*!< AC R */
		float dcr;  /*!< DC R */
		float acir;  /*!< AC IR */
		float dcir;  /*!< DC IR */
	} absorp;

/*! ------------------------------------------------------------
  
  \struct oxy
 
  \brief   
  
  ------------------------------------------------------------*/
typedef struct{
    int MaxAcr;
    int MaxAcir;
    int MinAcr;
    int MinAcir;
    int Dcr;
    int Dcir;
    int periode;
    bool premierePeriode;
    bool passageParZero;
}param_mesure;

typedef struct{
    int cmpt;
    absorp absorp1[51]; //on creer un tableau de 51 absorp
    bool premierRemplissage;
}param_fir;

typedef struct{
		int spo2;  /*!< SPO2 */
		int pouls;  /*!< Pouls */
	} oxy;


typedef struct{

    float x_moins_un_acr;
    float y_moins_un_acr;
    float x_moins_un_acir;
    float y_moins_un_acir;

} param_iir;

#endif // DEFINE_H
