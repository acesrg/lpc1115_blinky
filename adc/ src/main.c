/**
  **********************************************************************
  * @file    main.c
  * @author  Marco Miretti https://github.com/MarcoMiretti
  * @brief   ADC code demo
  *
  *	Code for the 
  *
  **********************************************************************
  * @section LICENSE TODO: choose license
  **********************************************************************
  */

#include "main.h"				/* CMSIS is included in header */
int main(void) {
    LPC_SYSCON->SYSAHBCLKCTRL |= 0x2040;
    LPC_IOCON->R_PIO0_11 = 0x42; //configure el registro completo
    LPC_SYSCON->PDRUNCFG &= ~0x10; //le di potencia
    LPC_ADC->CR = 0x1000001; //inicia a leer
    volatile unsigned int Valor=0;

    LPC_IOCON->PIO0_7 = 0;
    LPC_GPIO0->DIR |= 0x80;


while (1){
while (1){

	if (0x80000000 && LPC_ADC->DR[0])
	    {
	    	Valor = LPC_ADC->DR[0];
	    	//printf(Valor);
	    	LPC_ADC->CR = 0x1000001; //inicia a leer
	    	break;
	    }
}
//printf("%d",Valor);
if (Valor>0x1000){
	LPC_GPIO0->DATA |= 0X80;
	 }
else{
	LPC_GPIO0->DATA &= 0X7F;
}
}


    return 0 ;

}
