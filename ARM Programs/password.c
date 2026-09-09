#include<lpc21xx.h>
#include"header.h"
extern unsigned char b[4]="YASH";
 unsigned char flag,arr[12];
main(){
int i,len=0;							  
uart0_init(9600);
config_vic_for_uart0();
uart0_tx_string("\r\nEnter the string\r\n");
while(1)
{
 if(flag==1)
 {
 flag=0;
 len=strlen(arr);
 for(i=0;i<len;i++)
 {
 if(arr[i]!=b[i])
 break;
 }
 if(arr[i]==b[i])  
 uart0_tx_string("\r\n correct\r\n");
 
else
  uart0_tx_string("\r\n incorrect\r\n");
}
}
}
  
