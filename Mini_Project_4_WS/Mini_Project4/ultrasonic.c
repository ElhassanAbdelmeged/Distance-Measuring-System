#define F_CPU 8000000UL
#include <util/delay.h>
#include"icu.h"
#include"ultrasonic.h"
#include"gpio.h"
Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
uint8 g_edgeCount=0;
uint16 g_timeHigh = 0;
void Ultrasonic_init(void)
{
	Icu_init(&Icu_Config);
	Icu_setCallBack(&Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(Ultrasonic_TR_PORT_ID,Ultrasonic_TR_PIN_ID,PIN_OUTPUT);


}

void Ultrasonic_Trigger(void)
{

	GPIO_writePin(Ultrasonic_TR_PORT_ID,Ultrasonic_TR_PIN_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(Ultrasonic_TR_PORT_ID,Ultrasonic_TR_PIN_ID,LOGIC_LOW);
}


uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	uint16 distance=0;
	distance= ((float)g_timeHigh*0.0171)+1;

   return distance;

}



void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(1==g_edgeCount){
		/*
		 * Clear the timer counter register to start measurements from the rising edge
		 */

		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	if(2==g_edgeCount){

		/* Store the Period time value */
		g_timeHigh=Icu_getInputCaptureValue();
		Icu_setEdgeDetectionType(RISING);
		Icu_clearTimerValue();
		g_edgeCount=0;
 	}

}



