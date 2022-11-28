#ifndef F_CPU
#define F_CPU	8000000UL
#endif

#include <util/delay.h>
#include <stdbool.h>

#include "LED_Interface.h"
#include "Servo.h"
#include "ADC_interface.h"

void Timer_ISR_Func(void);

#define	LIVING_ROOM_ON	1
#define	LIVING_ROOM_OFF	2
#define	TV_ON			3
#define	TV_OFF			4
#define	BED_ROOM_ON		5
#define	BED_ROOM_OFF	6
#define	KIDS_ROOM_ON	7
#define	KIDS_ROOM_OFF	8
#define	AIR_COND_ON		9
#define	AIR_COND_OFF	10
#define	RIGHT_PASSWARD	11
#define WRONG_FOR_3TIMES 12
#define SET_TEMPERATURE	13

#define ON	1
#define OFF	0

#define DOOR_DELAY 1000
volatile uint8 r_data = -1;
volatile uint16 desired_temp = 0;
volatile uint16 temp_sensor = 0;
volatile uint16 flame_sensor = 0;
volatile uint8 count = 0;
volatile uint8 air_condition = 0;
volatile uint8 AC_ON=0,force_AC_ON=0,set_temp=0;

int main(void)
{
    DIO_Init(); // initialization for DIO 
	ADC_Init(0); // initialization for ADC
	ADC_Init(1);
	SPI_init_as_slave(false); // initialization for SPI as slave mood
	Servo_Init(); // initialization for servo
	sei();
	Timer0_Init(Timer0_CTC_Mode, Timer_Scaler_1024, OCO_Disconnected); // initialization for timer
	OCR0 = 78;
	SetCallBack_Timer0_OC0(Timer_ISR_Func);
	Timer0_OC_InterruptEnable(); // enable interrupt
    while (1)
    {

		if ((set_temp==1)&&(r_data!=SET_TEMPERATURE)) // if condition for checking the temperature was set or not
		{
			desired_temp = r_data;
		}
		switch(r_data)
		{
			case LIVING_ROOM_ON:
				LED_On(PORTC_, 1);
				break;
			case LIVING_ROOM_OFF:
				LED_Off(PORTC_, 1);
				break;
			case TV_ON:
				LED_On(PORTC_, 2);
				break;
			case TV_OFF:
				LED_Off(PORTC_, 2);
				break;
			case BED_ROOM_ON:
				LED_On(PORTC_, 3);
				break;
			case BED_ROOM_OFF:
				LED_Off(PORTC_, 3);
				break;
			case KIDS_ROOM_ON:
				LED_On(PORTC_, 4);
				break;
			case KIDS_ROOM_OFF:
				LED_Off(PORTC_, 4);
				break;
			case AIR_COND_ON:
				LED_On(PORTC_, 0);
				force_AC_ON=1;
				break;
			case AIR_COND_OFF:
				AC_ON=0;
				force_AC_ON=0;
				LED_Off(PORTC_, 0);
				break;
			case RIGHT_PASSWARD:
				Servo_SetAngle(90);
				_delay_ms(DOOR_DELAY);
				Servo_SetAngle(0);
				r_data = -1;
				break;
			case WRONG_FOR_3TIMES:
				DIO_SetPinValue(PORTD_, 0, HIGH);
				_delay_ms(100);
				DIO_SetPinValue(PORTD_, 0, LOW);
				r_data = -1;
				break;
			case SET_TEMPERATURE:
				force_AC_ON=0;
				set_temp=1;
				AC_ON=1;
				break;
		}
    }
}

void Timer_ISR_Func(void)
{
	count++;
	if (count >= 10)
	{
		temp_sensor = ADC_GetTemp(0);
		flame_sensor = ADC_FlameState(1);
		if(flame_sensor == 1)
		{
			DIO_SetPinValue(PORTD_, 0, HIGH);
			_delay_ms(100);
			DIO_SetPinValue(PORTD_, 0, LOW);
			flame_sensor = 0;
		}
		if ((temp_sensor >= desired_temp+1)&&(AC_ON==1))
		{
			LED_On(PORTC_, 0);
			air_condition = 1;
		}
		else if ((temp_sensor <= desired_temp-1)&&(force_AC_ON==0))
		{
			LED_Off(PORTC_, 0);
			air_condition = 0;
		}
		else if ((temp_sensor == desired_temp)&&(AC_ON==1))
		{
			if (air_condition == 1)
			{
				LED_On(PORTC_, 0);
			}
			else if (air_condition == 0)
			{
				LED_Off(PORTC_, 0);
			}
		}
	}
}

ISR(SPI_STC_vect)
{
	r_data= SPI_recieve_char_ISR();
}
