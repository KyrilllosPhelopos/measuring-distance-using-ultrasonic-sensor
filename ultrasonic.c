/*
 * ============================================================
 * module         : Ultrasonic sensor
 *file name       : ultrasonic.c
 *Description     : source file for ultrasonic sensor
 *Author          : Kyrillos Sawiris
 *==============================================================
 */


#include"ultrasonic.h"
#include"icu.h"
#include<util/delay.h>
#include"std_types.h"


uint8 g_edgeCount = 0; // to count the number of calling the call back function
uint16 g_timeHigh = 0;  // the time for the high edge of the ECHO signal

/*
 ********************************************************
 Functions Definitions
 ********************************************************
 */


void Ultrasonic_init(void)
{
	/*
	 * configrations for ICU module
	 * using the frequency of the CPU divided by 8 (F_CPU_8)
	 * setting the ICU to be interrupted when detecting rising edge
	 *
	 */
	Icu_ConfigType Config = {F_CPU_8,RISING};
	Icu_init(&Config);//initializing ICU

	Icu_setCallBack(Ultrasonic_edgeProcessing); // passing Ultrasonic_edgeProcessing to be called from ICU

	GPIO_setupPinDirection(TRIGGER_PORT_ID,TRIGGER_PIN_ID, PIN_OUTPUT); // setting PB5 to be output to be used as a trigger to the ultrasonic sensor
}

/*
 * setting the trigger pin for only 10 us
 */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_LOW);
}

/*
 * returning the distance away from an object
 */
uint16 Ultrasonic_readDistance(void)
{
	uint16 distance =0;
	Ultrasonic_Trigger();//calling trigger function
	/*
	 * The speed of sound waves is 340 m/s.
	 * Total Distance = 340∗Time of High(ECHO)𝑃𝑢𝑙𝑠𝑒2
	 * as the timer prescaler = F_CPU/8
	 * 17000 x (TIMER value) x 1 x 10^-6 cm
	 * = 0.017 x (TIMER value) cm
	 * = (TIMER value) / 58.8 cm
	 */
	distance = (uint16)(((float) g_timeHigh)/(58.8));
	return distance ;
}


/*
 * setting the function to process the ICU according to the edge
 *
 */

void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount==1)//entering the ISR for the first time and start calculating time
	{
		Icu_clearTimerValue();//initialize timer register
		Icu_setEdgeDetectionType(FALLING); // calculating time untill the following falling edge
	}
	else if (g_edgeCount==2)//entering ISR for the second time
	{
		g_timeHigh=Icu_getInputCaptureValue();// assignment the the time of high time
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(RISING); // reseting the ICU to detect the rising edge
		g_edgeCount=0;//reinitializing g_edgeCount
	}
}
