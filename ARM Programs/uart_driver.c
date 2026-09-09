#include<lpc21xx.h>
#include"header.h"

void uart0_init(unsigned int baud)
{
	//GETTING BAUDRATE BY USING PCLK//
	unsigned int result=0,pclk;
	int a[]={15,60,30,15,15};
	pclk=a[VPBDIV]*1000000;
	result=pclk/(16*baud);
	// SETTING BAUD RATE FOR COMMUNICATION//
	PINSEL0 |= 5;
	U0LCR=0X83;    //8N1 AND DLAB=1 that means baudrate setting unlock and Tx Rx data locked 
	U0DLM=(result>>8)&0xff;
	U0DLL=result&0x00ff;
	U0LCR=3;  // 	8N1 AND DLAB=0 that means baudrate setting locked and Tx Rx can be done.
}

// TRANSMIT 1BYTE OF DATA 
#define THRE ((U0LSR>>5)&1)  // transmission flag 
void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);S
}

//RECIEVE 1BYTE OF DATA
#define RDR  (U0LSR&1)    //RECEIVING FLG
unsigned char uart0_rx()
{
	while(RDR==0);
	return U0RBR;
}

//string print 
void uart0_tx_string(unsigned char *ptr)
{
	while(*ptr)
	{
		U0THR=*ptr;
		while(THRE==0);
			ptr++;
	}
}
