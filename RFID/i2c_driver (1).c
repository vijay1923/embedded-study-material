#include<lpc21xx.h>
#include "header.h"
void i2c_init(void){
PINSEL0|=0X50;
I2SCLH=I2SCLL=75;
I2CONSET=(1<<6);
}
#define SI ((I2CONSET>>3)&1)
void i2c_byte_write_frame(u8 sa,u8 mr,u8 data)
{
////generate start condition///
I2CONSET=(1<<5);
I2CONCLR=(1<<3);
while(SI==0);
I2CONCLR=(1<<5);
///SEND SA+W&CHECK ACK///
I2DAT=sa;
I2CONCLR=(1<<3);
while(SI==0);
if(I2STAT==0x20){
uart0_tx_string("err:SA+W\r\n");
goto exit;
}
///3.send mr addr&check ack///
I2DAT=mr;
I2CONCLR=(1<<3);
while(SI==0);
if(I2STAT==0x30){
uart0_tx_string("err:mr\r\n");
goto exit;
}
///4.send data &check ack///
I2DAT=data;
I2CONCLR=(1<<3);
while(SI==0);
if(I2STAT==0x30){
uart0_tx_string("err:data\r\n");
goto exit;
}
///5.generate stop condition///
exit:
I2CONCLR=(1<<3);
I2CONSET=(1<<4);
}
u8 i2c_byte_read_frame(u8 sa,u8 mr){
u8 temp;
///1.generate start condition///
I2CONSET=(1<<5);
I2CONCLR=(1<<3);
while(SI==0);
I2CONCLR=(1<<5);
///2.send sa+w & check ack///
I2DAT=sa;
I2CONCLR=(1<<3);
while(SI==0);
if(I2STAT==0x20){
uart0_tx_string("err:sa+w\r\n");
goto exit;
}
///3.send mr addr&check ack///
I2DAT=mr;
I2CONCLR=(1<<3);
while(SI==0);
if(I2STAT==0x30){
uart0_tx_string("err:mr \r\n");
goto exit;
}
///4.generate restart condition///
I2CONSET=(1<<5);
I2CONCLR=(1<<3);
while(SI==0);
I2CONCLR=(1<<5);
///5.send sa+r &check ack///
I2DAT=sa|1;
I2CONCLR=(1<<3);
while(SI==0);
if(I2STAT==0x48){
uart0_tx_string("err:sa+r\r\n");
goto exit;
}
///6.read data &send no ack
I2CONCLR=(1<<3);
while(SI==0);
temp=I2DAT;
///7.generate stop condition///
exit:
I2CONCLR=(1<<3);
I2CONSET=(1<<4);
return temp;
}

