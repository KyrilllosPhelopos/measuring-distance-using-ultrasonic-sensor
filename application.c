
/*
 * ========================================================================
 * Name           : application.c
 * Author         : Kyrillos Sawiris
 * Description    : Measure the distance away from an object
 * Data           : 20/10/2021
 * =========================================================================
 */


#include"lcd.h" //to use LCD functions
#include"ultrasonic.h" // to use Ultrasonic module functions
#include<avr/interrupt.h> // to enable I-bit
#include<util/delay.h>

int main()
{
	SREG|=(1<<7); // enabling I-bit
	Ultrasonic_init();
	LCD_init(); // initializing LCD
	LCD_displayString("Distance= "); //displaying word "distance" on LCD
	uint16 distance=0,preDistance=0;
	while(1)
	{
		LCD_moveCursor(0, 10); // setting the cursor to start evey one loop on this position
		distance=Ultrasonic_readDistance();//reading from ultrasonic sensor
		if (distance != preDistance)//entering this condition only if the current distance different from the previous distance
		{
				if(distance >=100)
				{
					LCD_intgerToString(Ultrasonic_readDistance());
					LCD_displayString(" cm");
				}
				else if (distance >=10 && distance <100 )
				{
					LCD_intgerToString(Ultrasonic_readDistance());
					LCD_displayString(" cm ");//to write back in the same location as if distance >=100
				}
				else
				{
					LCD_intgerToString(Ultrasonic_readDistance());
					LCD_displayString(" cm  ");//to write back in the same location as if distance >=10
				}
		}
		preDistance= distance; // set the previous distance to be equal to the current position
		_delay_ms(100);
	}
	return 0;
}
