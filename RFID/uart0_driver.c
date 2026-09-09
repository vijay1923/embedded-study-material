#include<lpc21xx.h>
#include "header.h"
void uart0_init(u32 baud){
s32 a[]={15,60,30,15,15};
u32 result=0,pclk;
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
PINSEL0|=5;
U0LCR=0x83;
U0DLL=result&0xFF;
U0DLM=(result>>8)&0xFF;
U0LCR=0x03;
}
///transmit///
#define THRE ((U0LSR>>5)&1)
void uart0_tx(u8 data){
U0THR=data;
while(THRE==0);
}
//string
void uart0_tx_string(s8 *ptr){
while(*ptr!='\0'){
U0THR=*ptr;
while(THRE==0);
ptr++;
}
}
//receiver
#define RDR (U0LSR&1)
u8 uart0_rx(void)
{
while(RDR==0);
return U0RBR;
}

