#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include"std_types.h"

#define ADMUX_Reg   *((volatile uint8*)0x27)
#define ADCSRA_Reg  *((volatile uint8*)0x26)
#define ADCH_Reg    *((volatile uint8*)0x25)
#define ADCL_Reg    *((volatile uint8*)0x24)

//pinno is the pin number [0 for pin0 , 1 for pin 1,...]

void ADC_Init(uint8 pinno);       //Initiating the ADC
uint16 ADC_GetResult(uint8 pinno);//Returns an ADC value
uint16 ADC_GetTemp(uint8 pinno);  //Returns a Temperature value
uint8 ADC_FlameState(uint8 pinno);//Returns 1 if flame detected and 0 if not

#endif
