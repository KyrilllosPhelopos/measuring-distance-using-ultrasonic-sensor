/*
 * ============================================================
 * module         : Ultrasonic sensor
 *file name       : ultrasonic.h
 *Description     : header file for ultrasonic sensor
 *Author          : Kyrills Sawiris
 *==============================================================
 */



#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include"std_types.h"
#include"gpio.h"

/*
 * **************************************
 * configrations for the ultrasonic sensor
 * ***************************************
 */
#define TRIGGER_PORT_ID  PORTB_ID
#define TRIGGER_PIN_ID   PIN5_ID

/*****************************************
 functions declaration
 *****************************************/

/*
 * initializing ultrasonic sensor by
 * initializing ICU
 * Setting call back function
 * setting trigger pin
 */
void Ultrasonic_init(void);

/*
 * setting trigger pin to be high for 10us
 */
void Ultrasonic_Trigger(void);

/*
 * reading the distance from the sensor
 */
uint16 Ultrasonic_readDistance(void);


/*
 * setting the call back function to process the detected edge
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
