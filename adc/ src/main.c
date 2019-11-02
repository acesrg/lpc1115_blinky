/**
  **********************************************************************
  * @file    main.c
  * @author  Fran Colombatti https://github.com/francolombatti
  * @brief   ADC code demo
  *
  *	Implementación de ejemplo ADC, se prende y apaga un LED a partir
  *	de los valores obtenidos de la conversión.
  *	
  *
  **********************************************************************
  * @section LICENSE GNU GPL-v3
  **********************************************************************
  */

#include "main.h"							/**< Se incluye CMSIS en el header */
int main(void) 
{
	/**
	 * \addtogroup Configuración del ADC
	 * @{
	 */
	LPC_SYSCON->SYSAHBCLKCTRL 	|=  (uint32_t)(0x2040);		///< Se le da potencia al CLOCK 
									///< y ADC

	LPC_IOCON->R_PIO0_11		=   (uint32_t)(0x42); 		///< Se configura el registro completo
    									///< del pin 0_11 como ADC

	LPC_SYSCON->PDRUNCFG 		&= ~(uint32_t)(0x10); 		///< Se le da potencia de run-time al 
    									///< ADC

	LPC_ADC->CR 			=   (uint32_t)(0x1000001);	///< Comienza la lectura del ADC
	
	volatile unsigned int Valor 	= 0;				///< Valor de la conversión
									///< inicializado en cero

	/** @} */
	
	/**
	 * \addtogroup Configuración del LED
	 * @{
	 */
	LPC_IOCON->PIO0_7 		=   (uint32_t)(0x0);		///< Se configura el registro completo
									///< del pin 0_7 como GPIO NOPULL
	
	LPC_GPIO0->DIR 			|=  (uint32_t)(0x80);		///< Se selecciona la dirección del
									///< pin 0_7 como GPIO out
	/** @} */

	while (1)
	{
		while (1)
		{
			if ((uint32_t)(0x80000000) && LPC_ADC->DR[0])	///< Si el bit DONE es 1 la sentencia
									///< califica como true, de lo contrario
									///< el bucle sigue hasta que lo haga
	    		{
				Valor = LPC_ADC->DR[0];			///< Guarda el resultado de la conversión

				LPC_ADC->CR = 0x1000001; 		///< Inicia una nueva lectura de ADC
	    			break;
	    		}
		}

		//printf("%d",Valor); 					// En caso de tener semihost, se puede
									// utilizar el printf
		
		
		if (Valor>0x1000)					///< En caso de que la lectura del ADC
									///< sea mayor a una referencia la
									///< sentencia se evalúa como true
		{
			LPC_GPIO0->DATA	|=  (uint32_t)(0x80);		///< Se enciende el LED
		}
		
		else
		{
			LPC_GPIO0->DATA	&=  (uint32_t)(0X7F);		///< Se apaga el LED
		}
	}

    return 0 ;
}
