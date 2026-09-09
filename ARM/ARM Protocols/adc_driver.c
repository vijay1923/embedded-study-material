/* ADC DRIVER*/
#include<lpc21xx.h>
#include"header.h"
void adc_init(void)
{
  PINSEL1|=0x15400000; 		// P0.27 TO P0.30 ARE ANALOG PINS
	ADCR=0x00200400;
}
unsigned int adc_read(unsigned char ch_num)
{
  unsigned int result=0;
	
	// SELECT CHANNEL NUMBER
	ADCR|=1<<ch_num;
  // START ADC
	ADCR|=(1<<24);
	// MONITER THE DONE FLAG
	while(((ADDR>>31)&31)==0);
	// OFF THE ADC
	ADCR^=(1<<24);
	// DISSELECT THE CHANNEL
	ADCR^=(1<<ch_num);
	// EXTRACT THE RESULT 
	result=(ADDR>>6)&0x3ff;
	// RETURN THE RESULT 
	return result;	
}
