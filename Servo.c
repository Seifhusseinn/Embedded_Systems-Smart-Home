#include "Servo.h"

void Servo_Init(void)
{
	//Configure TIMER1
	Timer1_Init(Fast_PWM_ICR1, Timer_Scaler_64, OC1A_Inverting, OC1B_Inverting);

	ICR1=19999;  //fPWM=50Hz (Period = 20ms Standard).
	OCR1B = 97;
}

void Servo_SetAngle(uint8 angle)
{
	OCR1B = (((uint16)angle*100)/41.1)+97;
}
