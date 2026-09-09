#include<lpc21xx.h>
#include "header.h"
char temp[50];
int rfid=0;
main()
{
int f=0;
u8 h,m,s,date,month,year;
i2c_init();
lcd_init();
uart0_init(9600);
config_vic();
uart0_interrupt();

i2c_byte_write_frame(0xD0,0x2,0x51);
i2c_byte_write_frame(0xD0,0x1,0x41);
i2c_byte_write_frame(0xD0,0x0,0x11);
i2c_byte_write_frame(0xD0,0x2,0x52);
i2c_byte_write_frame(0xD0,0x5,0x05);
i2c_byte_write_frame(0xD0,0x6,0x24);

while(1)
{
if(rfid==1)
{
h=i2c_byte_read_frame(0xd0,0x2);
m=i2c_byte_read_frame(0xd0,0x1);
s=i2c_byte_read_frame(0xd0,0x0);
date=i2c_byte_read_frame(0xD0,0x04);
month=i2c_byte_read_frame(0xD0,0x05);
year=i2c_byte_read_frame(0xD0,0x06);

temp[12]=' ';
temp[15]=':';
temp[16]=(m/0x10)+48;
temp[17]=(m%0x10)+48;
temp[18]=':';
temp[19]=(s/0x10)+48;
temp[20]=(s%0x10)+48;
temp[21]=' ';
temp[22]=(date/0x10)+48;
temp[23]=(date%0x10)+48;
temp[24]='/';
temp[25]=(month/0x10)+48;
temp[26]=(month%0x10)+48;
temp[27]='/';
temp[28]=(year/0x10)+48;
temp[29]=(year%0x10)+48;
temp[30]=' ';
lcd_cmd(0x81);
if(((h>>6)&1)==0)
{
temp[13]=(h/0x10)+48;
temp[14]=(h%0x10)+48;
lcd_data((h/0x10)+48);
lcd_data((h%0x10)+48);
}
if(h>>6&1)
{
if((h&0x20)>>4)
f=1;
else
f=0;
temp[13]=(((h&0x10)>>4)+48);
temp[14]=(h&0x0f)+48;
lcd_data(((h&0x10)>>4)+48);
lcd_data(((h&0x10)>>4)+48);
}
lcd_data(':');
lcd_data((m/0x10)+48);
lcd_data((m%0x10)+48);
lcd_data(':');
lcd_data((s/0x10)+48);
lcd_data((s%0x10)+48);
if(f==1){
temp[31]='P';
temp[32]='M';
temp[33]='\n';
f=0;
lcd_data('P');
lcd_data('M');
}
else{
temp[31]='A';
temp[32]='M';
temp[33]='\n';
lcd_data('A');
lcd_data('M');
}
rfid=0;
uart0_tx_string(temp);
lcd_cmd(0x0c);
lcd_string("scanned id");
lcd_cmd(0x01);
}
else{
lcd_cmd(0xc0);
lcd_string("scan your id");
lcd_cmd(0x01);
}
}
}
