#include "SPI.h"

void SPI_init_as_master(bool slow_mode)
{
	DIO_SetPinDirection(SPI_port,MISO,INPUT);
	DIO_SetPinDirection(SPI_port,MOSI,OUTPUT);
	DIO_SetPinDirection(SPI_port,sck,OUTPUT);
	DIO_SetPinDirection(SPI_port,SS_bar,OUTPUT);
	DIO_SetPinValue(SPI_port,SS_bar,HIGH);       //disable slave selection
	if (slow_mode){                    //speed = Fosc/128
			SPCR = 0x53;               //SPIE=0 SPE=1 Master=1 SPR0=1 SPR1=1
			SPSR = 0x00;               //SPI2X = 0
	}
	else{							   //speed = Fosc/2
			SPCR = 0x50;               //SPIE=0 SPE=1 Master=1 SPR0=0 SPR1=0
			SPSR = 0x01;               //SPI2X = 1
	}
}

void SPI_init_as_slave(bool slow_mode)
{
	DIO_SetPinDirection(SPI_port,MISO,OUTPUT);
	DIO_SetPinDirection(SPI_port,MOSI,INPUT);
	DIO_SetPinDirection(SPI_port,sck,INPUT);
	DIO_SetPinDirection(SPI_port,SS_bar,INPUT);
	DIO_SetPinValue(SPI_port,SS_bar,HIGH);       //pull up for ss_bar pin 
		if (slow_mode){                //speed = Fosc/128
			SPCR = 0xC3;               //SPIE=1 SPE=1 Master=0 SPR0=1 SPR1=1
			SPSR = 0x00;               //SPI2X = 0
		}
		else{						   //speed = Fosc/2
			SPCR = 0xC0;               //SPIE=1 SPE=1 Master=0 SPR0=0 SPR1=0
			SPSR = 0x01;               //SPI2X = 1
		}

}


void SPI_send_char(uint8 data)
{
	DIO_SetPinValue(SPI_port,SS_bar,LOW);   //select slave     
	SPDR=data;
	while((SPSR & (1<<7))==0) ;     //wait for SPIF to set (transfer of data is complete )
	DIO_SetPinValue(SPI_port,SS_bar,HIGH);   //leave slave
	
}


uint8 SPI_recieve_char_no_ISR()
{
	while((SPSR & (1<<7))==0) ;    //wait for SPIF to set (transfer of data is complete )
	return SPDR;

}
uint8 SPI_recieve_char_ISR()
{
	return SPDR;
}

void SPI_turn_to_slave(){

	SPI_send_char(0x7f);           //code for swapping master and slave
	SPI_init_as_slave(false);
	
}

bool SPI_should_turn_to_master(uint8 data){
	if (data==0x7f)                //code for swapping master and slave
	{
		SPI_init_as_master(false);
		return true;

	}
	return false;
}


