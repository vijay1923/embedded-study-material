#include<lpc21xx.h>
#include"header1.h"

char arr[13];
char temp1[50];
char temp[100];
char time[7];
int result;
char flag;

int main()
{
	char  h,m,s,d,mn,y,h1,day;
	int i=0;


	// char dow[][4]={"","SUN","MON","TUE","WED","THU","FRI","SAT"};
	i2c_init();
	uart0_init(9600);
	config_vic_for_uart0();
	lcd_init();

	lcd_cmd(0x01);
	i2c_send(0XD0,0X2,0X71);
	i2c_send(0XD0,0X1,0X59);
	i2c_send(0XD0,0X0,0X55);
	i2c_send(0xD0,0x3,0x6);
	i2c_send(0xD0,0x4,0x8);
	i2c_send(0xD0,0x5,0x3);
	i2c_send(0xD0,0x6,0x25);
	uart0_tx_string("ABCD");
	while(1)
	{

		h=i2c_read(0XD1,0X2);
		h1=h;
		h=h&0x1f;
		lcd_cmd(0x80);
		lcd_data((h/16)+48);
		lcd_data((h%16)+48);
		lcd_data(':');
		lcd_data((m/16)+48);
		lcd_data((m%16)+48);
		lcd_data(':');
		lcd_data((s/16)+48);
		lcd_data((s%16)+48);
		lcd_cmd(0x89);
		if((h1>>5)&1)
		{
			lcd_string("PM");
		}
		else
		{
			lcd_string("AM");
		}
		lcd_cmd(0xC0);
		lcd_string("SCAN YOUR ID");
		m=i2c_read(0XD1,0X1);
		s=i2c_read(0XD1,0X0);
		day=i2c_read(0xD1,0x3);
		d=i2c_read(0xD1,0x4);
		mn=i2c_read(0xD1,0x5);
		y=i2c_read(0xD1,0x6);

		if(flag==1)
		{

			flag=0;
			lcd_cmd(0x01);

			while(arr[i])
			{
				temp[i]=arr[i];
				i++;
			}
			//temp[i++]=32;
			temp[i++]= (h/16)+48;
			temp[i++]=(h%16)+48;
			temp[i++]=':';
			temp[i++]= (m/16)+48;
			temp[i++]=(m%16)+48;
			temp[i++]=':';
			temp[i++]= (s/16)+48;
			temp[i++]=(s%16)+48;

			if((h1>>5)&1)
			{
				temp[i++]='P';
				temp[i++]='M';
			}
			else
			{
				temp[i++]='A';
				temp[i++]='M';
			}
			temp[i++]=32;
			temp[i++]= (d/16)+48;
			temp[i++]=(d%16)+48;
			temp[i++]=':';

			temp[i++]= (mn/16)+48;
			temp[i++]=(mn%16)+48;
			temp[i++]=':';

			temp[i++]= (y/16)+48;
			temp[i++]=(y%16)+48;
			temp[i++]=32;
			//			 day=day+48;
			//			 switch(day){
			//			 case '2':temp[i++]='M';
			//			 		   temp[i++]='O';
			//					   temp[i++]='N';
			//					   break;
			//			case '3':temp[i++]='T';
			//			 		   temp[i++]='U';
			//					   temp[i++]='E';
			//					   break;
			//			case '4':temp[i++]='W';
			//			 		   temp[i++]='E';
			//					   temp[i++]='D';
			//					   break;
			//			case '5':temp[i++]='T';
			//			 		   temp[i++]='H';
			//					   temp[i++]='U';
			//					   break;
			//			case '6':temp[i++]='F';
			//			 		   temp[i++]='R';
			//					   temp[i++]='I';
			//					   break;
			//			case '7':temp[i++]='S';
			//			 		   temp[i++]='A';
			//					   temp[i++]='T';
			//					   break;
			//			case '0':temp[i++]='S';
			//			 		   temp[i++]='U';
			//					   temp[i++]='N';
			//					   break;
			//
			//			}			
			temp[i]='\0';
			uart0_tx_string(temp);
			uart0_tx_string("\r\n");
			i=0;
		}

	}
}
