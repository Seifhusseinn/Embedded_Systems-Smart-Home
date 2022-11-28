#ifndef F_CPU
#define F_CPU	8000000UL
#endif

#include "Timer_INT.h"
#include <util/delay.h>

#define NULLPTR	((void*)0)

/**************************** Pointer to functions to be assigned to ISR *********************************/
static void (*Timer0_callBackPtr)(void) = NULLPTR;
static void (*Timer1_OVF_callBackPtr) (void)=NULLPTR;
static void (*Timer1_OCA_callBackPtr) (void)=NULLPTR;
static void (*Timer1_OCB_callBackPtr) (void)=NULLPTR;
static void (*Timer1_ICU_callBackPtr) (void)=NULLPTR;
static void (*Timer2_callBackPtr)(void) = NULLPTR;

/************************************************************************/
/*					   Timer0 Functions Definitions                     */
/************************************************************************/
void Timer0_Init(Timer0Mode t_mode, TimerScale scaler, OC0Mode oc0_mode)
{
	/* switch over all modes and set its bits from datasheet */
	switch(t_mode)
	{
		case Timer0_Normal_Mode:
			CLR_BIT(TCCR0, WGM00);
			CLR_BIT(TCCR0, WGM01);
			break;
		case Timer0_CTC_Mode:
			CLR_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			break;
		case Timer0_PhaseCorrect_Mode:
			SET_BIT(TCCR0, WGM00);
			CLR_BIT(TCCR0, WGM01);
			break;
		case Timer0_FastPWM_Mode:
			SET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			break;
	}
	switch(oc0_mode)
	{
		case OCO_Disconnected:
			CLR_BIT(TCCR0, COM00);
			CLR_BIT(TCCR0, COM01);
			break;
		case OCO_Toggle:
			SET_BIT(TCCR0, COM00);
			CLR_BIT(TCCR0, COM01);
			break;
		case OCO_NON_Inverting:
			CLR_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
			break;
		case OCO_Inverting:
			SET_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
			break;
	}
	/* set scaler for timer */
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
	TCCR0 |= scaler; 
}

void Timer0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK, TOIE0);
}

void Timer0_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK, TOIE0);
}

void Timer0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK, OCIE0);
}

void Timer0_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK, OCIE0);
}

/*********************** Timer 0 Call Back functions ********************/
void SetCallBack_Timer0_OC0(void(*LocalFptr)(void))
{
	Timer0_callBackPtr = LocalFptr;
}

void SetCallBack_Timer0_OVF(void(*LocalFptr)(void))
{
	Timer0_callBackPtr = LocalFptr;
}

/************************* Timer 0 ISR functions ************************/
ISR(TIMER0_OVF_vect)
{
	if(Timer0_callBackPtr != NULLPTR)
	{
		Timer0_callBackPtr();
	}
}
ISR(TIMER0_COMP_vect)
{
	if(Timer0_callBackPtr != NULLPTR)
	{
		Timer0_callBackPtr();
	}
}

/************************************************************************/
/*					   Timer1 Functions Definitions                     */
/************************************************************************/

void Timer1_Init( Timer1_Mode t_mode, TimerScale scaler,OC1A_Mode oc1a, OC1B_Mode oc1b)
{
	switch(t_mode)
	{
		case Normal_Mode:
			CLR_BIT(TCCR1A, WGM10);
			CLR_BIT(TCCR1A, WGM11);
			CLR_BIT(TCCR1B, WGM12);
			CLR_BIT(TCCR1B, WGM13);
			break;
		case PWM_Mode_8BIT:
			SET_BIT(TCCR1A, WGM10);
			CLR_BIT(TCCR1A, WGM11);
			CLR_BIT(TCCR1B, WGM12);
			CLR_BIT(TCCR1B, WGM13);
			break;
		case PWM_Mode_9BIT:
			CLR_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			CLR_BIT(TCCR1B, WGM12);
			CLR_BIT(TCCR1B, WGM13);
			break;
		case PWM_Mode_10BIT:
			SET_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			CLR_BIT(TCCR1B, WGM12);
			CLR_BIT(TCCR1B, WGM13);
			break;
		case CTC_Mode_OCR1A:
			CLR_BIT(TCCR1A, WGM10);
			CLR_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			CLR_BIT(TCCR1B, WGM13);
			break;
		case Fast_PWM_8BIT:
			SET_BIT(TCCR1A, WGM10);
			CLR_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			CLR_BIT(TCCR1B, WGM13);
			break;
		case Fast_PWM_9BIT:
			CLR_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			CLR_BIT(TCCR1B, WGM13);
			break;
		case Fast_PWM_10BIT:
			SET_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			CLR_BIT(TCCR1B, WGM13);
			break;
		case PhaseCorrect_Mode_ICR1_BOTTOM:
			CLR_BIT(TCCR1A, WGM10);
			CLR_BIT(TCCR1A, WGM11);
			CLR_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			break;
		case PhaseCorrect_Mode_OCR1A_BOTTOM:
			SET_BIT(TCCR1A, WGM10);
			CLR_BIT(TCCR1A, WGM11);
			CLR_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			break;
		case PhaseCorrect_Mode_ICR1_TOP:
			CLR_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			CLR_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			break;
		case PhaseCorrect_Mode_OCR1A_TOP:
			SET_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			CLR_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			break;
		case CTC_Mode_ICR1:
			CLR_BIT(TCCR1A, WGM10);
			CLR_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			break;
		case Fast_PWM_ICR1:
			CLR_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			break;
		case Fast_PWM_OCR1A:
			SET_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			break;
	}
	
	switch(oc1a)
	{
		case OC1A_Disconnected:
			CLR_BIT(TCCR1A, COM1A0);
			CLR_BIT(TCCR1A, COM1A1);
			break;
		case OC1A_Toggle:
			SET_BIT(TCCR1A, COM1A0);
			CLR_BIT(TCCR1A, COM1A1);
			break;
		case OC1A_Inverting:
			CLR_BIT(TCCR1A, COM1A0);
			SET_BIT(TCCR1A, COM1A1);
			break;
		case OC1A_NON_Inverting:
			SET_BIT(TCCR1A, COM1A0);
			SET_BIT(TCCR1A, COM1A1);
			break;
	}
	
	switch(oc1b)
	{
		case OC1B_Disconnected:
			CLR_BIT(TCCR1A, COM1B0);
			CLR_BIT(TCCR1A, COM1B1);
			break;
		case OC1B_Toggle:
			SET_BIT(TCCR1A, COM1B0);
			CLR_BIT(TCCR1A, COM1B1);
			break;
		case OC1B_Inverting:
			CLR_BIT(TCCR1A, COM1B0);
			SET_BIT(TCCR1A, COM1B1);
			break;
		case OC1B_NON_Inverting:
			SET_BIT(TCCR1A, COM1B0);
			SET_BIT(TCCR1A, COM1B1);
			break;
	}
	CLR_BIT(TCCR1B, CS10);
	CLR_BIT(TCCR1B, CS11);
	CLR_BIT(TCCR1B, CS12);
	TCCR1B |= scaler;
}

void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if (FALLING)
	{
		CLR_BIT(TCCR1B, ICES1);
	}
	else if(RISING)
	{
		SET_BIT(TCCR1B, ICES1);
	}
}

void Timer1_ICU_InterruptEnable(void)
{
	SET_BIT(TIMSK, TICIE1);
}

void Timer1_ICU_InterruptDisable(void)
{
	CLR_BIT(TIMSK, TICIE1);
}

void Timer1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK, TOIE1);
}

void Timer1_OVF_InterruptDisable(void)
{
	CLR_BIT(TIMSK, TOIE1);
}

void Timer1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK, OCIE1A);
}

void Timer1_OCA_InterruptDisable(void)
{
	CLR_BIT(TIMSK, OCIE1A);
}

void Timer1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK, OCIE1B);
}

void Timer1_OCB_InterruptDisable(void)
{
	CLR_BIT(TIMSK, OCIE1B);
}

/*********************** Timer 1 Call Back functions ********************/
void SetCallBack_Timer1_OVF(void(*LocalFptr)(void))
{
	Timer1_OVF_callBackPtr = LocalFptr;
}

void SetCallBack_Timer1_OCA_(void(*LocalFptr)(void))
{
	Timer1_OCA_callBackPtr = LocalFptr;
}

void SetCallBack_Timer1_OCB(void(*LocalFptr)(void))
{
	Timer1_OCB_callBackPtr = LocalFptr;
}

void SetCallBack_Timer1_ICU(void(*LocalFptr)(void))
{
	Timer1_ICU_callBackPtr = LocalFptr;
}


/************************* Timer 1 ISR functions ************************/

ISR(TIMER1_OVF_vect)
{
	if (Timer1_OVF_callBackPtr != NULLPTR)
	{
		Timer1_OVF_callBackPtr();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (Timer1_OCA_callBackPtr != NULLPTR)
	{
		Timer1_OCA_callBackPtr();
	}
}


ISR(TIMER1_COMPB_vect)
{
	if (Timer1_OCA_callBackPtr != NULLPTR)
	{
		Timer1_OCA_callBackPtr();
	}
}

ISR(TIMER1_CAPT_vect)
{
	if (Timer1_ICU_callBackPtr != NULLPTR)
	{
		Timer1_ICU_callBackPtr();
	}
}

/************************************************************************/
/*					   Timer1 Functions Definitions                     */
/************************************************************************/

void Timer2_Init(Timer2Mode t_mode, Timer2Scale scaler, OC2Mode oc2_mode)
{
	/* switch over all modes and set its bits from datasheet */
	switch(t_mode)
	{
		case Timer2_Normal_Mode:
		CLR_BIT(TCCR2, WGM20);
		CLR_BIT(TCCR2, WGM21);
		break;
		case Timer2_CTC_Mode:
		CLR_BIT(TCCR2, WGM20);
		SET_BIT(TCCR2, WGM21);
		break;
		case Timer2_PhaseCorrect_Mode:
		SET_BIT(TCCR2, WGM20);
		CLR_BIT(TCCR2, WGM21);
		break;
		case Timer2_FastPWM_Mode:
		SET_BIT(TCCR2, WGM20);
		SET_BIT(TCCR2, WGM21);
		break;
	}
	switch(oc2_mode)
	{
		case OC2_Disconnected:
		CLR_BIT(TCCR2, COM20);
		CLR_BIT(TCCR2, COM21);
		break;
		case OC2_Toggle:
		SET_BIT(TCCR2, COM20);
		CLR_BIT(TCCR2, COM21);
		break;
		case OC2_NON_Inverting:
		CLR_BIT(TCCR2, COM20);
		SET_BIT(TCCR2, COM21);
		break;
		case OC2_Inverting:
		SET_BIT(TCCR2, COM20);
		SET_BIT(TCCR2, COM21);
		break;
	}
	/* set scaler for timer */
	CLR_BIT(TCCR2, CS20);
	CLR_BIT(TCCR2, CS21);
	CLR_BIT(TCCR2, CS22);
	TCCR2 |= scaler;
}

void Timer2_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK, TOIE2);
}

void Timer2_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK, TOIE2);
}

void Timer2_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK, OCIE2);
}

void Timer2_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK, OCIE2);
}

/*********************** Timer 2 Call Back functions ********************/
void SetCallBack_Timer2_OC2(void(*LocalFptr)(void))
{
	Timer2_callBackPtr = LocalFptr;
}

void SetCallBack_Timer2_OVF(void(*LocalFptr)(void))
{
	Timer2_callBackPtr = LocalFptr;
}

/************************* Timer 2 ISR functions ************************/
ISR(TIMER2_OVF_vect)
{
	if(Timer2_callBackPtr != NULLPTR)
	{
		Timer2_callBackPtr();
	}
}
ISR(TIMER2_COMP_vect)
{
	if(Timer2_callBackPtr != NULLPTR)
	{
		Timer2_callBackPtr();
	}
}


void WDT_ON(void)
{
	/* 2.1s time out session*/
	WDTCR = (1<<WDE) | (1 << WDP2) | (1 << WDP1) | (1 << WDP2);
}

void WDT_OFF(void)
{
	WDTCR = (1 << WDTOE) | (1 << WDE);
	/* wait to clear WDE */
	_delay_us(4);
	WDTCR = 0;
}