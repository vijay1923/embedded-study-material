// LCD 4-BIT DRIVER 
#include<lpc21xx.h>
#include "header.h"
void lcd_data(unsigned char  data)
{
	IOCLR1=0X00FE0000;  // 0xFE<<16;        // higher enable
	IOSET1=(data & 0XF0)<<16;
	
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;
	
	IOCLR1=0X00FE0000;  // 0xFE<<16;        // lower enable
	IOSET1=(data & 0X0F)<<20;
	
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;
}
	void lcd_cmd(unsigned char cmd)
{
	IOCLR1=0X00FE0000;  // 0xFE<<16;        // higher enable cmd
	IOSET1=(cmd &0XF0)<<16;
	
	IOCLR1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;
	
	IOCLR1=0X00FE0000;  // 0xFE<<16;        // LOWER enable cmd
	IOSET1=(cmd & 0X0F)<<20;
	
	IOCLR1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;
	
}
	void lcd_init(void )
	{
		IODIR1=0X00FE0000;      // clear all gpio pins
    PINSEL2=0X0;   
		IOCLR1=1<<19;          		
		lcd_cmd(0x02);         // enable 4 bit mode
		lcd_cmd(0x28);         // set cursor in 4 bit mode
		lcd_cmd(0x0E);          // enable cursor
		lcd_cmd(0x01);          // clear screen
	}
	
void lcd_string(char *ptr)
{
 while(*ptr!=0)
 {                                //  string user defined function    
 lcd_data(*ptr);
 ptr++;
 }
}

void lcd_integer( long long int num)
{
	int a[20],i;
	if(num==0)
	{
		lcd_data('0');
	}
	if(num<0)
	{
		num=-num;
		lcd_data('-');
	}
	i=0;
	while(num>0)
	{
		a[i]=num%10+48;
		num=num/10;
		i++;
	}
for(i=i-1;i>=0;i--)
	{
		lcd_data(a[i]);
	}
}

//unsigned char  a[]={0x17,0x14,0x14,0x1f,0x05,0x05,0x1D,0x00};   //SWASTIK SYMBOL
//unsigned  char a[]={0x00,0x1A,0x15,0x15,0x11,0x0A,0X04,0X00};   // heart symbol
//unsigned char a[]={0x0A,0x0A,0x06,0x06,0x0A,0x10};
//unsigned char a[]={0x00,0x06,0x02,0x06,0x06,0x02};
//unsigned char a[]={0x00, 0x1C, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00}; // SMIELY
//unsigned char a[]={0x0A, 0x1F, 0x1F, 0x0A, 0x1F, 0x1F, 0x0A, 0x00};		 // HASH
//unsigned char a[]={0x00, 0x04, 0x0E, 0x1C, 0x18, 0x10, 0x00, 0x00};
//unsigned char a[]={0x0D, 0x08, 0x08, 0x0F, 0x08, 0x08, 0x09, 0x00};
unsigned char a[]={0x00,0x0C,0x0C,0x10,0x08,0x04,0x03,0x00};
unsigned char b[]={0x00,0x06,0x06,0x01,0x02,0x04,0x18,0x00};

void lcd_cgram(void )
{
	lcd_cmd(0x40);
	for( int i=0;i<8;i++)
	{
		lcd_data(a[i]);
	}
	
	lcd_cmd(0x48);
	for( int i=0;i<8;i++)
	{
		lcd_data(b[i]);
	}
}
