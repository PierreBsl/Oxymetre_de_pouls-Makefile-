#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


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
    float MaxAcr;
    float MaxAcir;
    float MinAcr;
    float MinAcir;
    float Dcr;
    float Dcir;
    int periode;
    int passageParZero;
    int poulsPeriod1;
    int SpO2Period1;
}param_mesure;

typedef struct{
    absorp absorp1[51]; //on creer un tableau de 51 absorp
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
