 #include<lpc21xx.h>
 #include"header.h"
 unsigned char arr[12],flag=0,f;
 unsigned int count1=0;
 main()
 {
 int i,j,temp=0,len;
 uart0_init(9600);
 config_eint0();
 config_vic_for_uart0();
 uart0_tx_string("Enter the string\r\n");
 while(1)
 {
  //uart0_tx_string("Enter the string\r\n");

 if(flag==1) {
   	  flag=0;
	   len=strlen(arr);
	  for(i=0,j=len-1;i<j;i++,j--)
		{
		if(arr[i]!=arr[j])
		break;
		}
		uart0_tx_string(arr);
	if(arr[i]==arr[j])
	
       uart0_tx_string("\r\n Palindrome\n");
	   else
		    uart0_tx_string("\r\n not Palindrome\n");
//	for(i=0;i<len;i++)
		
}
}
}