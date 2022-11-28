#ifndef SPI_H_
#define SPI_H_
#include <stdbool.h>

#include "DIO_Interface.h"
#define SPDR  *(volatile uint8 *) 0x2f
#define SPSR  *(volatile uint8 *) 0x2e
#define SPCR  *(volatile uint8 *) 0x2d

#define SPI_port PORTB_
#define SS_bar 4
#define MOSI 5
#define MISO 6
#define sck 7

void SPI_init_as_master(bool slow_mode);
void SPI_init_as_slave(bool slow_mode);
void SPI_send_char(uint8 data);
uint8 SPI_recieve_char_no_ISR();
uint8 SPI_recieve_char_ISR();
void SPI_turn_to_slave();
bool SPI_should_turn_to_master(uint8 data);
#endif