#ifndef TIMER_INT_H_
#define TIMER_INT_H_

#include "std_types.h"
#include "Bit_Math.h"
#include "Interrupt_vect.h"

/* common in all timers */
/* Timer/counter interrupt mask register */
#define	TIMSK	*((volatile uint8 *)0x59)
#define TOIE0	0
#define OCIE0	1
#define TOIE1	2
#define OCIE1B	3
#define OCIE1A	4
#define TICIE1	5
#define TOIE2	6
#define OCIE2	7

/* Timer/counter interrupt Flag register */
#define	TIFR	*((volatile uint8 *)0x58)
#define TOV0	0
#define OCF0	1
#define TOV1	2
#define OCF1B	3
#define OCF1A	4
#define ICF1	5
#define TOV2	6
#define OCF2	7

/* Select scaler */
typedef enum{
	Timer_Stop=0,
	Timer_Scaler_1,
	Timer_Scaler_8,
	Timer_Scaler_64,
	Timer_Scaler_256,
	Timer_Scaler_1024,
	External_FALLING,
	ExternalL_RISING
}TimerScale;


/************************ Timer0 registers ******************************/

/************************************************************************/
/*							Preprocessor                                */
/************************************************************************/

/* Timer/counter control register */
#define	TCCR0	*((volatile uint8 *)0x53)
#define CS00	0
#define CS01	1
#define CS02	2
#define WGM01	3
#define COM00	4
#define COM01	5
#define WGM00	6
#define FOC0	7

/* Timer/counter register */
#define	TCNT0	*((volatile uint8 *)0x52)

/* output compare register */
#define	OCR0	*((volatile uint8 *)0x5C)

/* Select Timer0 mode */
typedef enum
{
	Timer0_Normal_Mode,
	Timer0_PWM_Mode,
	Timer0_PhaseCorrect_Mode = 1,
	Timer0_CTC_Mode,
	Timer0_FastPWM_Mode
}Timer0Mode;

/* OC type */
typedef enum
{
	OCO_Disconnected=0,
	OCO_Toggle,
	OCO_NON_Inverting,
	OCO_Inverting
}OC0Mode;


/************************************************************************/
/*								Functions Prototypes                    */
/************************************************************************/

/*********************************************************************************************************
 * Function Name: Timer0_Init
 *
 * Description:  Function to initialize timer0 in its mode with the its frequency
 *
 * Function Parameters:	 First Parameter is mode of operation, Second Parameter is scaler, and Third parameter is oc0_mode        
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer0_Init(Timer0Mode t_mode, TimerScale scaler, OC0Mode oc0_mode);

/*********************************************************************************************************
 * Function Name: Timer0_OV_InterruptEnable
 *
 * Description:  Function to enable timer0 overflow interrupt
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer0_OV_InterruptEnable(void);

/*********************************************************************************************************
 * Function Name: Timer0_OV_InterruptEnable
 *
 * Description:  Function to disable timer0 overflow interrupt
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer0_OV_InterruptDisable(void);

/*********************************************************************************************************
 * Function Name: Timer0_OV_InterruptEnable
 *
 * Description:  Function to enable timer0 output compare interrupt
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer0_OC_InterruptEnable(void);

/*********************************************************************************************************
 * Function Name: Timer0_OV_InterruptEnable
 *
 * Description:  Function to enable timer0 output compare interrupt
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer0_OC_InterruptDisable(void);

/*********************************************************************************************************
 * Function Name: SetCallBack_Timer0_OVF
 *
 * Description:  Function to set a callback for ISR of over flow interrupt
 *
 * Function Parameters:	   Function to pointer
 *
 * Returns:						NONE
 ********************************************************************************************************/
void SetCallBack_Timer0_OVF(void(*LocalFptr)(void));

/*********************************************************************************************************
 * Function Name: SetCallBack_Timer0_OC0
 *
 * Description:  Function to set a callback for ISR
 *
 * Function Parameters:	    Function to pointer
 *
 * Returns:						NONE
 ********************************************************************************************************/
void SetCallBack_Timer0_OC0(void(*LocalFptr)(void));



/************************ Timer1 registers ******************************/

/************************************************************************/
/*							Preprocessor                                */
/************************************************************************/
/* TCCR1A */
#define	TCCR1A	*((volatile uint8*)0x4F)
#define WGM10	0
#define WGM11	1
#define FOC1B	2
#define FOC1A	3
#define COM1B0	4
#define COM1B1	5
#define COM1A0	6	
#define COM1A1	7

/* TCCR1A */
#define	TCCR1B	*((volatile uint8*)0x4E)
#define CS10	0
#define CS11	1
#define CS12	2
#define WGM12	3
#define WGM13	4
#define ICES1	6
#define ICNC1	7

#define ICR1         (*(volatile unsigned short*)0x46)
#define OCR1B     (*(volatile unsigned short*)0x48)
#define OCR1A     (*(volatile unsigned short*)0x4A)
#define TCNT1       (*(volatile unsigned short*)0x4C)

typedef enum
{
	OC1A_Disconnected=0,
	OC1A_Toggle,
	OC1A_NON_Inverting,
	OC1A_Inverting
}OC1A_Mode;

typedef enum
{
	OC1B_Disconnected=0,
	OC1B_Toggle,
	OC1B_NON_Inverting,
	OC1B_Inverting
}OC1B_Mode;

typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;

typedef enum
{
	Normal_Mode,
	PWM_Mode_8BIT,
	PWM_Mode_9BIT,
	PWM_Mode_10BIT,
	CTC_Mode_OCR1A,
	Fast_PWM_8BIT,
	Fast_PWM_9BIT,
	Fast_PWM_10BIT,
	PhaseCorrect_Mode_ICR1_BOTTOM,
	PhaseCorrect_Mode_OCR1A_BOTTOM,
	PhaseCorrect_Mode_ICR1_TOP,
	PhaseCorrect_Mode_OCR1A_TOP,
	CTC_Mode_ICR1,
	Fast_PWM_ICR1,
	Fast_PWM_OCR1A,
}Timer1_Mode;

/* TCNT1H */
#define	TCNT1H	*((volatile uint8*)0x4D)

/* TCNT1L */
#define	TCNT1L	*((volatile uint8*)0x4C)

/* OCR1AH */
#define	OCR1AH	*((volatile uint8*)0x4B)

/* OCR1AL */
#define	OCR1AL	*((volatile uint8*)0x4A)

/* OCR1BH */
#define	OCR1BH	*((volatile uint8*)0x49)

/* OCR1BL */
#define	OCR1BL	*((volatile uint8*)0x48)

/* ICR1H */
#define	ICR1H	*((volatile uint8*)0x47)

/* ICR1H */
#define	ICR1L	*((volatile uint8*)0x46)

/************************************************************************/
/*							 Functions Prototypes                       */
/************************************************************************/

/*********************************************************************************************************
 * Function Name: Timer1_Init
 *
 * Description:  Function to initialize timer1 in its mode with the its frequency
 *
 * Function Parameters:	 First Parameter is mode of operation, Second Parameter is scaler, and Third parameter is oc1a_mode
 *						 Fourth is oc1b        
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer1_Init( Timer1_Mode t_mode, TimerScale scaler,OC1A_Mode oc1a, OC1B_Mode oc1b);

/*********************************************************************************************************
 * Function Name: Timer1_InputCaptureEdge
 *
 * Description:  Function to initialize Input Capture Edge
 *
 * Function Parameters:	 type of edge   
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer1_InputCaptureEdge(ICU_Edge_type edge);

/*********************************************************************************************************
 * Function Name: Timer1_ICU_InterruptEnable
 *
 * Description:  Function to enable timer1 Input Capture Edge
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/

void Timer1_ICU_InterruptEnable(void);
/*********************************************************************************************************
 * Function Name: Timer1_ICU_InterruptDisable
 *
 * Description:  Function to disable timer1 Input Capture Edge
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer1_ICU_InterruptDisable(void);

/*********************************************************************************************************
 * Function Name: Timer1_OVF_InterruptEnable
 *
 * Description:  Function to enable timer1 overflow interrupt
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer1_OVF_InterruptEnable(void);

/*********************************************************************************************************
 * Function Name: Timer1_OVF_InterruptDisable
 *
 * Description:  Function to disable timer1 overflow interrupt
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer1_OVF_InterruptDisable(void);

/*********************************************************************************************************
 * Function Name: Timer1_OCA_InterruptEnable
 *
 * Description:  Function to enable timer1 output compare unit a
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer1_OCA_InterruptEnable(void);

/*********************************************************************************************************
 * Function Name: Timer1_OCA_InterruptDisable
 *
 * Description:  Function to disable timer1 output compare unit a
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer1_OCA_InterruptDisable(void);

/*********************************************************************************************************
 * Function Name: Timer1_OCB_InterruptEnable
 *
 * Description:  Function to enable timer1 output compare unit b
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer1_OCB_InterruptEnable(void);

/*********************************************************************************************************
 * Function Name: Timer1_OCB_InterruptDisable
 *
 * Description:  Function to disable timer1 output compare unit b
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer1_OCB_InterruptDisable(void);

/*********************************************************************************************************
 * Function Name: SetCallBack_Timer1_OVF
 *
 * Description:  Function to set a callback for ISR
 *
 * Function Parameters:	    Function to pointer
 *
 * Returns:						NONE
 ********************************************************************************************************/
void SetCallBack_Timer1_OVF(void(*LocalFptr)(void));

/*********************************************************************************************************
 * Function Name: SetCallBack_Timer1_OCA_
 *
 * Description:  Function to set a callback for ISR
 *
 * Function Parameters:	    Function to pointer
 *
 * Returns:						NONE
 ********************************************************************************************************/
void SetCallBack_Timer1_OCA_(void(*LocalFptr)(void));

/*********************************************************************************************************
 * Function Name: SetCallBack_Timer1_OCB
 *
 * Description:  Function to set a callback for ISR
 *
 * Function Parameters:	    Function to pointer
 *
 * Returns:						NONE
 ********************************************************************************************************/
void SetCallBack_Timer1_OCB(void(*LocalFptr)(void));

/*********************************************************************************************************
 * Function Name: SetCallBack_Timer1_ICU
 *
 * Description:  Function to set a callback for ISR
 *
 * Function Parameters:	    Function to pointer
 *
 * Returns:						NONE
 ********************************************************************************************************/
void SetCallBack_Timer1_ICU(void(*LocalFptr)(void));


/************************ Timer1 registers ******************************/

/************************************************************************/
/*							Preprocessor                                */
/************************************************************************/

/* Timer/counter control register */
#define	TCCR2	*((volatile uint8 *)0x45)
#define CS20	0
#define CS21	1
#define CS22	2
#define WGM21	3
#define COM20	4
#define COM21	5
#define WGM20	6
#define FOC2	7

/* Timer/counter register */
#define	TCNT2	*((volatile uint8 *)0x44)

/* output compare register */
#define	OCR2	*((volatile uint8 *)0x43)

/* Select Timer2 mode */
typedef enum
{
	Timer2_Normal_Mode,
	Timer2_PhaseCorrect_Mode,
	Timer2_CTC_Mode,
	Timer2_FastPWM_Mode
}Timer2Mode;

/* OC type */
typedef enum
{
	OC2_Disconnected=0,
	OC2_Toggle,
	OC2_NON_Inverting,
	OC2_Inverting
}OC2Mode;

typedef enum{
	Timer2_Stop=0,
	Timer2_Scaler_1,
	Timer2_Scaler_8,
	Timer2_Scaler_32,
	Timer2_Scaler_64,
	Timer2_Scaler_128,
	Timer2_Scaler_256,
	Timer2_Scaler_1024
}Timer2Scale;


/************************************************************************/
/*								Functions Prototypes                    */
/************************************************************************/

/*********************************************************************************************************
 * Function Name: Timer2_Init
 *
 * Description:  Function to initialize timer2 in its mode with the its frequency
 *
 * Function Parameters:	 First Parameter is mode of operation, Second Parameter is scaler, and Third parameter is oc0_mode        
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer2_Init(Timer2Mode t_mode, Timer2Scale scaler, OC2Mode oc2_mode);

/*********************************************************************************************************
 * Function Name: Timer2_OV_InterruptEnable
 *
 * Description:  Function to enable timer2 overflow interrupt
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer2_OV_InterruptEnable(void);

/*********************************************************************************************************
 * Function Name: Timer2_OV_InterruptEnable
 *
 * Description:  Function to disable timer2 overflow interrupt
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer2_OV_InterruptDisable(void);

/*********************************************************************************************************
 * Function Name: Timer2_OV_InterruptEnable
 *
 * Description:  Function to enable timer2 output compare interrupt
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer2_OC_InterruptEnable(void);

/*********************************************************************************************************
 * Function Name: Timer2_OV_InterruptEnable
 *
 * Description:  Function to enable timer2 output compare interrupt
 *
 * Function Parameters:	        NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void Timer2_OC_InterruptDisable(void);

/*********************************************************************************************************
 * Function Name: SetCallBack_Timer2_OVF
 *
 * Description:  Function to set a callback for ISR of over flow interrupt
 *
 * Function Parameters:	   Function to pointer
 *
 * Returns:						NONE
 ********************************************************************************************************/
void SetCallBack_Timer2_OVF(void(*LocalFptr)(void));

/*********************************************************************************************************
 * Function Name: SetCallBack_Timer2_OC2
 *
 * Description:  Function to set a callback for ISR
 *
 * Function Parameters:	    Function to pointer
 *
 * Returns:						NONE
 ********************************************************************************************************/
void SetCallBack_Timer2_OC2(void(*LocalFptr)(void));


/* Watchdog Timer */
#define WDTCR	*((volatile uint8 *)0x41)
#define WDTOE	4
#define WDE		3
#define WDP2	2
#define WDP1	1
#define WDP0	0


/*********************************************************************************************************
 * Function Name: WDT_ON
 *
 * Description:  Function to Enable Watchdog timer
 *
 * Function Parameters:			NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void WDT_ON(void);

/*********************************************************************************************************
 * Function Name: WDT_ON
 *
 * Description:  Function to Disable Watchdog timer
 *
 * Function Parameters:			NONE
 *
 * Returns:						NONE
 ********************************************************************************************************/
void WDT_OFF(void);


#endif /* TIMER_INT_H_ */