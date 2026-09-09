 #include<lpc21xx.h>
 #include<string.h>
 #include"header.h"
  signed char arr[12]="yash",flag=0;
 int main()
 {
 int i,j,temp=0,len;
 uart0_init(9600);
 config_eint0();
 config_vic_for_uart0();
 uart0_tx_string("Enter the string\r\n");
 while(1)
 {
 // uart0_tx_string("Enter the string\r\n");
 if(flag==1) 
 {
 flag=0;
	//uart0_tx_string("Enter the string\r\n");
 //uart0_tx_string(arr);
 len=strlen(arr);
 //for(len=0;arr[len];len++)
		for(i=0,j=len-1;i<j;i++,j--)
		{
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
		}
		//for(i=0;i<len;i++)
				uart0_tx_string(arr);
				uart0_tx_string("\r\n");
		}
		}
		}


