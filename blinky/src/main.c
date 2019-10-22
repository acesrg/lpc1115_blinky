/**
  **********************************************************************
  * @file    main.c
  * @author  Marco Miretti https://github.com/MarcoMiretti
  * @brief   Code used to turn a built in led on and off
  *
  *	Just a blinky
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

	LPC_GPIO0->DIR	|= 0x80;		/* GPIO0_7 as output */
	LPC_GPIO0->DATA |= 0x80;		/* GPIO0_7 data = 1 */
	while(1)
	{
		volatile unsigned int i =0;
		for(i=0; i<1000000; ++i);	/* Not so fancy delay*/
		LPC_GPIO0->DATA &= ~0x80;	/* GPIO0_7 data = 0 */	
		for(i=0; i<1000000; ++i);
		LPC_GPIO0->DATA |= 0x80;
	}
	return 0;
}
