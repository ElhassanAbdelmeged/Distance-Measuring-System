/* Mini_Project4.c
 *  Created on: October 14, 2022
 *  Author: Hassan_Abdelmeged_Mohamed
 */
#include<avr/io.h>
#include"icu.h"
#include"ultrasonic.h"
#include"gpio.h"
#include"lcd.h"
int main (void){
	LCD_init();
	//Ultrasonic_init();
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	Ultrasonic_init();
	LCD_displayStringRowColumn(0,0,"Distance= ");
	uint16 distance = 0;

	while(1)
	{
		//LCD_moveCursor(0, 7);
		distance = Ultrasonic_readDistance();
		LCD_moveCursor(0, 9);
		LCD_intgerToString(distance);
		if (distance >=100){
			LCD_displayString(" cm");

		}
		else{

			//LCD_displayCharacter(' '); //to overWrite on the units of 100,101,102 when reach the tens
			LCD_displayString(" cm");
			LCD_displayCharacter(' ');


		}
	}
}
