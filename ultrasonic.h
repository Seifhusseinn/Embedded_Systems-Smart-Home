
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <avr/interrupt.h>
#include<string.h>
#include <stdlib.h>

#include <util/delay.h>
#include "timer.h"

#define F_CPU 8000000UL
#define   TRIGGER_DDR    DDRD
#define   ECHO_DDR      DDRD
#define   TRIGGER_PORT   PORTD
#define   ECHO_PULLUP   PORTD
#define   TRIGGER        0
#define   ECHO          3

/*************************************************
 *  API functions
 *************************************************/

void ultrasonic_init(void);
void enable_ex_interrupt(void);
void ultrasonic_trigger(void);
void ultrasonic_echo(void);




#endif /* ULTRASONIC_H_ */
