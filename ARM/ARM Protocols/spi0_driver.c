#include<lpc21xx.h>
#include"header.h"

//SPI INIT FUNCTION 
void spi0_init(void )
{
PINSEL0|=1500; // SELECT SPI0 PORT 
IODIR0|=1<<7;
IOSET0|=1<<7;
S0SPCR=0x20;
S0SPCCR=15;
}
// SPI DATA TRANSFER 
#define spif ((S0SPSR>>7)&1)
unsigned char spi0(unsigned char data)
{
S0SPDR=data; // SEND DATA FROM MASTER->SLAVE
while(spif==0);	// WAITNG FOR SPI TRANSFER TO COMPLETE 
return S0SPDR;
}
