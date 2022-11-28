#include"ADC_interface.h"
#include"Bit_Math.h"
#include"std_types.h"




void ADC_Init(uint8 pinno) {
	SET_BIT(ADCSRA_Reg, 7);//Enabling the ADC
	SET_BIT(ADCSRA_Reg, 6);//Start of conversion
	CLR_BIT(ADCSRA_Reg, 5);//Disabling AutoTrigger
	SET_BIT(ADCSRA_Reg, 4);//Clearing the ADC Flag 
	CLR_BIT(ADCSRA_Reg, 3);//Disabling Interrupt
	CLR_BIT(ADCSRA_Reg, 2);//Setting the pre-scaler 128
	CLR_BIT(ADCSRA_Reg, 1);//Setting the pre-scaler 128
	CLR_BIT(ADCSRA_Reg, 0);//Setting the pre-scaler 128


	if (pinno == 0) {
		CLR_BIT(ADMUX_Reg, 0);//Selecting ADC0
		CLR_BIT(ADMUX_Reg, 1);//Selecting ADC0
		CLR_BIT(ADMUX_Reg, 2);//Selecting ADC0
		CLR_BIT(ADMUX_Reg, 3);//Selecting ADC0
		CLR_BIT(ADMUX_Reg, 4);//Selecting ADC0
	}
	if (pinno == 1) {
		SET_BIT(ADMUX_Reg, 0);//Selecting ADC1
		CLR_BIT(ADMUX_Reg, 1);//Selecting ADC1
		CLR_BIT(ADMUX_Reg, 2);//Selecting ADC1
		CLR_BIT(ADMUX_Reg, 3);//Selecting ADC1
		CLR_BIT(ADMUX_Reg, 4);//Selecting ADC1
	}
	if (pinno == 2) {
		CLR_BIT(ADMUX_Reg, 0);//Selecting ADC2
		SET_BIT(ADMUX_Reg, 1);//Selecting ADC2
		CLR_BIT(ADMUX_Reg, 2);//Selecting ADC2
		CLR_BIT(ADMUX_Reg, 3);//Selecting ADC2
		CLR_BIT(ADMUX_Reg, 4);//Selecting ADC2
	}
	if (pinno == 3) {
		SET_BIT(ADMUX_Reg, 0);//Selecting ADC3
		SET_BIT(ADMUX_Reg, 1);//Selecting ADC3
		CLR_BIT(ADMUX_Reg, 2);//Selecting ADC3
		CLR_BIT(ADMUX_Reg, 3);//Selecting ADC3
		CLR_BIT(ADMUX_Reg, 4);//Selecting ADC3
	}

	if (pinno == 4) {
		CLR_BIT(ADMUX_Reg, 0);//Selecting ADC4
		CLR_BIT(ADMUX_Reg, 1);//Selecting ADC4
		SET_BIT(ADMUX_Reg, 2);//Selecting ADC4
		CLR_BIT(ADMUX_Reg, 3);//Selecting ADC4
		CLR_BIT(ADMUX_Reg, 4);//Selecting ADC4
	}

	if (pinno == 5) {
		SET_BIT(ADMUX_Reg, 0);//Selecting ADC5
		CLR_BIT(ADMUX_Reg, 1);//Selecting ADC5
		SET_BIT(ADMUX_Reg, 2);//Selecting ADC5
		CLR_BIT(ADMUX_Reg, 3);//Selecting ADC5
		CLR_BIT(ADMUX_Reg, 4);//Selecting ADC5
	}

	if (pinno == 6) {
		CLR_BIT(ADMUX_Reg, 0);//Selecting ADC6
		SET_BIT(ADMUX_Reg, 1);//Selecting ADC6
		SET_BIT(ADMUX_Reg, 2);//Selecting ADC6
		CLR_BIT(ADMUX_Reg, 3);//Selecting ADC6
		CLR_BIT(ADMUX_Reg, 4);//Selecting ADC6
	}
	if (pinno == 7) {
		SET_BIT(ADMUX_Reg, 0);//Selecting ADC7
		SET_BIT(ADMUX_Reg, 1);//Selecting ADC7
		SET_BIT(ADMUX_Reg, 2);//Selecting ADC7
		CLR_BIT(ADMUX_Reg, 3);//Selecting ADC7
		CLR_BIT(ADMUX_Reg, 4);//Selecting ADC7
	}

	CLR_BIT(ADMUX_Reg, 5);//ADC Right Adjustment
	SET_BIT(ADMUX_Reg, 6);//Selecting AVCC as Vref
	CLR_BIT(ADMUX_Reg, 7);//Selecting AVCC as Vref
}


uint16 ADC_GetResult(uint8 pinno){

	uint16 ADC_Result = 0;//Result

	SET_BIT(ADCSRA_Reg, 6);//Starting a single Conversion
	
	while (RD_BIT(ADCSRA_Reg, 4) == 0);//checking for the ADC Flag 

	ADC_Result = (ADCL_Reg | (ADCH_Reg << 8));

	SET_BIT(ADCSRA_Reg, 4);//Clearing the ADC Flag

	return ADC_Result;
}

uint16 ADC_GetTemp(uint8 pinno) {

	ADC_Init(pinno);

	return ADC_GetResult(pinno) / 2;
}

uint8 ADC_FlameState(uint8 pinno) {

	ADC_Init(pinno);
    if(ADC_GetResult(pinno)==1023)return 1;
    else return 0;

}


