#include <LPC21xx.H>
#include "header1.h"

void uart0_init(u32 baud)
{
	unsigned int result=0,pclk;
	int a[]={15,60,30,15,15};
	pclk=a[VPBDIV]*1000000;
	result=pclk/(16*baud);
  PINSEL0|=5;
	U0LCR=0X83;
 	U0DLL=result & 0x00ff;                    // UART 0 INTILIZATION
	U0DLM=(result>>8)&0xff;
	U0LCR=3;
}
	#define THRE ((U0LSR>>5)&1)
void uart0_tx (u8 data)
	{
		U0THR=data;
		while (THRE==0);
	}


	#define RDR (U0LSR&1)
	void uart0_rx(void)
	{
		while(RDR==0);
  return U0RBR;
	}		
	
	void uart0_tx_string (s8 *ptr)
	{
		while(*ptr)
		{
			U0THR=*ptr;
			while(THRE==0);
			ptr++;
		}
	}
	