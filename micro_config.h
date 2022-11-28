#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 8000000UL //1MHz Clock frequency
#endif  

//#include <avr/io.h>

#include <avr/interrupt.h>
#include <util/delay.h>
#include "Bit_Math.h"

#include "DIO_Interface.h"
#include "DIO_Register.h"
#include "DIO_Config.h"
#endif /* MICRO_CONFIG_H_ */
