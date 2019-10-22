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

int main(void)
{
	/* LED2 Configuration */
	LPC_IOCON->PIO0_7 &= (uint32_t)~0x07; 		/* FUNC -> PIO0_7 */
        LPC_IOCON->PIO0_7 &= (uint32_t)~0x18; 		/* MODE -> inactive (NOPULL) */
        LPC_IOCON->PIO0_7 &= (uint32_t)~0x20; 		/* HYS -> disable */ 
	LPC_IOCON->PIO0_7 &= (uint32_t)~0x400; 		/* OD -> disable */

	LPC_GPIO0->DIR    |= (uint32_t)0x80;            /* Pin0_7 out */
        LPC_GPIO0->DATA   &= (uint32_t)~0x80;
        
	/* AD0 configuration */
	LPC_IOCON->R_PIO0_11 &= (uint32_t)~0x03;        /* Pin function ADC0 */
        LPC_IOCON->R_PIO0_11 |= (uint32_t)0x02;         /* Pin function ADC0 */
        LPC_IOCON->R_PIO0_11 &= (uint32_t)~0x18; 	/* MODE -> inactive (NOPULL) */
        LPC_IOCON->R_PIO0_11 &= (uint32_t)~0x20; 	/* HYS -> disable */ 
	LPC_IOCON->R_PIO0_11 &= (uint32_t)~0x80;        /* Analog input mode */
	LPC_IOCON->R_PIO0_11 &= (uint32_t)~0x400; 	/* OD -> disable */

        LPC_SYSCON->PDRUNCFG &= (uint32_t)~0x10;        /* Power ON ADC */
        LPC_SYSCON->SYSAHBCLKCTRL |= (uint32_t)0x2000;  /* Enable ADC clock */

        LPC_ADC->CR |= (uint32_t)0x01;                  /* Activate ADC0 */
        LPC_ADC->CR |= (uint32_t)0x0B00;                /* CLKDIV = 2 => ADCCLK=4MHz */

        LPC_ADC->CR |= (uint32_t)0x01000000; 		/* wololoooooo */

        while(1)
        {
        	uint32_t LPC_ADC_DR0;
        		while(1)
        		{
        			LPC_ADC_DR0 = LPC_ADC->GDR;
        			if((LPC_ADC_DR0 & (uint32_t)0x80000000) != 0) break;
        		}
        		LPC_ADC->CR &= (uint32_t)~0x01000000;
                if((LPC_ADC_DR0 & (uint32_t)0x0000FFC0) != 0)
                {
                        LPC_GPIO0->DATA |= (uint32_t)0x80;
                }
                else
                {
                        LPC_GPIO0->DATA &= (uint32_t)~0x80;
                }
                LPC_ADC->CR |= (uint32_t)0x01000000; 		/* wololoooooo */
        }
        return 0;
}
