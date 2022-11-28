#include "ultrasonic.h"
#include <avr/interrupt.h>
#include "DIO_Interface.h"
#include "DIO_Register.h"
#include "DIO_Config.h"
#include "std_types.h"
uint8 sensor_working=0;
uint8 rising_edge=0;
uint32 timer_counter=0;
uint32 distance;
uint8 distance_str[10];

void ultrasonic_init(void){

  DIO_SetPinDirection(TRIGGER_PORT,TRIGGER,OUTPUT);//trigger as output
  DIO_SetPinDirection( ECHO_PULLUP ,ECHO,INPUT);//echo as input
  DIO_SetPinValue(ECHO_PULLUP ,ECHO,HIGH);//set echo
  enable_ex_interrupt();
  timer0_init();
  return;
}

void enable_ex_interrupt(void){

  MCUCR |= (1<<ISC10);		// Trigger INT1 on any logic change falling edge on the INT1 pin generates an interrupt request..
  GICR  |= (1<<INT1);			// Enable INT1 interrupts in GICR register.

  return;
}
//
void ultrasonic_trigger(void){
	if(!sensor_working){
		DIO_SetPinValue(TRIGGER_PORT ,TRIGGER,HIGH);
		_delay_us(15);
		DIO_SetPinValue(TRIGGER_PORT ,TRIGGER,LOW);
		sensor_working=1;
	}
}


ISR(INT1_vect){
	if(sensor_working==1){
		if(rising_edge==0){
			TCNT0=0x00;
			rising_edge=1;
			timer_counter=0;
		}
		else{
			distance=(timer_counter*256+TCNT0)/466;
			if(distance<400){
				DIO_SetPinValue(TRIGGER_PORT ,7,HIGH);
			}
			_delay_ms(40);
			timer_counter=0;
			rising_edge=0;
		}
	}}

ISR(TIMER0_OVF_vect){
	timer_counter++;
	if(timer_counter >730){
		TCNT0=0x00;
		sensor_working=0;
		rising_edge=0;
		timer_counter=0;
	}

}
