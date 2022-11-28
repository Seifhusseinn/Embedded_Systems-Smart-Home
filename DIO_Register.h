#ifndef DIO_Register_H
#define DIO_Register_H

#include "std_types.h"

#define    PORTA_REG    *((volatile uint8 *)0X3B)  
#define    DDRA_REG     *((volatile uint8 *)0X3A)
#define    PINA_REG     *((volatile uint8 *)0X39) 

#define    PORTB_REG    *((volatile uint8 *)0X38) 
#define    DDRB_REG     *((volatile uint8 *)0X37) 
#define    PINB_REG     *((volatile uint8 *)0X36) 

#define    PORTC_REG    *((volatile uint8 *)0X35) 
#define    DDRC_REG     *((volatile uint8 *)0X34) 
#define    PINC_REG     *((volatile uint8 *)0X33) 
 
#define    PORTD_REG    *((volatile uint8 *)0X32) 
#define    DDRD_REG     *((volatile uint8 *)0X31) 
#define    PIND_REG     *((volatile uint8 *)0X30) 

#endif      