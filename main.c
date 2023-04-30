/*
 * main.c
 *
 *  Created on: Apr 28, 2023
 *      Author: User
 */

#include "STD_TYPES.h"
#include "BIT_MATHS.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include <util/delay.h>

#define WDTCR           *((volatile u8*)0x41)     /* WatchDog Timer control Register*/

#define WDTCR_WDP0           0                    /* WatchDog Timer Prescaler bit 0 */
#define WDTCR_WDP1           1                    /* WatchDog Timer Prescaler bit 1 */
#define WDTCR_WDP2           2                    /* WatchDog Timer Prescaler bit 2 */

#define WDTCR_WDE            3                    /* WatchDog Enable */

#define WDTCR_WDTOE          4                    /* Watchdog Turn-off Enable */

/*To disable an enabled WatchDog Timer , the following procedure must be followed:

1. In the same operation, write a logic one to WDTOE and WDE. A logic one must
be written to WDE even though it is set to one before the disable operation starts.

2. Within the next four clock cycles, write a logic 0 to WDE. This disables the
WatchDog.
*/

void WDT_voidSleep(u8 copy_u8SleepTime);

void WDT_voidEnable(void);

void WDT_voidDisable(void);

void main(void){

	PORT_voidInit();

	DIO_u8SetPinValue(DIO_U8PORTA,DIO_U8PIN0,DIO_U8PIN_HIGH);

	_delay_ms(1000);

	DIO_u8SetPinValue(DIO_U8PORTA,DIO_U8PIN0,DIO_U8PIN_LOW);

	WDT_voidEnable();

	/* watch dog sleep for 1 Second */

	WDT_voidSleep(6);

	while(1){

	}
}



void WDT_voidSleep(u8 copy_u8SleepTime){

	/* Clear prescaler Bits */
	WDTCR &= 11111000;
	/* Set the required prescaler */
	WDTCR |= copy_u8SleepTime;
}

void WDT_voidEnable(void){

	SET_BIT(WDTCR,WDTCR_WDE);

}

void WDT_voidDisable(void){

	WDTCR |= 0b00011000;

	WDTCR  = 0;
}
