#include<lpc21xx.h>
#include"header.h"
static int i;
extern char flag1;
extern signed char arr[12],flag;

void UART0_Handler(void)__irq
{
int r=U0IIR;
r&=0x0E;
	if(r==4)
	{
	   arr[i]=U0RBR;
	  // U0THR=arr[i];
	    U0THR='*';

		 if(arr[i]=='\r')
		 {
			flag=1;
			arr[i]='\0';
			i=-1;
		 }
		else {
			flag=0;
		 }
		i++;
	}
	
VICVectAddr=0;
}

void config_vic_for_uart0(void)
{
VICVectCntl1=6|(1<<5);
VICVectAddr1=(unsigned int)UART0_Handler;
VICIntEnable|=(1<<6); //Enable UART0 intr in vic peri
U0IER=3;	 //Enable Tx&Rx intr in Uart0 peri
}
void config_eint0(void)
{
PINSEL1|=1; // p0.16-EINT0
EXTPOLAR=0; // all ext intrs are active low
EXTMODE=1; // EINT0 is edge triggered
}

