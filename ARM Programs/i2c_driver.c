/*i2c_driver.c*/
#include <LPC21xx.H>
#include "header.h"

void i2c_init(void){
	PINSEL0|=0x50;//P0.2->SCL,P0.3->SDA
	I2SCLH=I2SCLL=75;//100Kbps freq
	I2CONSET=(1<<6);//En I2C Interface
									//& master mode selected
}

/*func to write 1byte data to slave*/
#define SI  ((I2CONSET>>3)&1)
void i2c_send(u8 sa,u8 mr,u8 data){
	/*1. start condi*/	
	I2CONSET=(1<<5);//STA=1
	I2CONCLR=(1<<3);//Clear SI
	while(SI==0);
	I2CONCLR=(1<<5);//STA=0*
	
	/*2. send SA+W & check ack*/
	I2DAT=sa;//send SA+W
	I2CONCLR=(1<<3);//Clear SI
	while(SI==0);
	if(I2STAT==0x20){
		uart0_tx_string("Err:SA+W\r\n");
		goto exit;
	}
	
	/*3. send memory addr & check ack*/
	I2DAT=mr;//send memory addr
	I2CONCLR=(1<<3);//Clear SI
	while(SI==0);
	if(I2STAT==0x30){
		uart0_tx_string("Err:Memory Addr\r\n");
		goto exit;
	}
	
	/*4. send data & check ack*/
	I2DAT=data;//send data
	I2CONCLR=(1<<3);//Clear SI
	while(SI==0);
	if(I2STAT==0x30){
		uart0_tx_string("Err:Data\r\n");
		goto exit;
	}
	
	/*5. stop condi*/
	exit:
			I2CONSET=(1<<4);//STO=1
			I2CONCLR=(1<<3);//Clear SI
}

/*func to read 1byte data from slave*/
u8 i2c_read(u8 sa,u8 mr){
	u8 data;
	/*1. start condi*/
	I2CONSET=(1<<5);//STA=1
	I2CONCLR=(1<<3);//Clear SI
	while(SI==0);
	I2CONCLR=(1<<5);//STA=0*
	
	/*2. send sa+w & check ack*/
	I2DAT=sa&0xFE;//send SA+W
	I2CONCLR=(1<<3);//Clear SI
	while(SI==0);
	if(I2STAT==0x20){
		uart0_tx_string("Err:SA+W\r\n");
		goto exit;
	}
	
	/*3. send m/r addr & check ack*/
	I2DAT=mr;//send memory addr
	I2CONCLR=(1<<3);//Clear SI
	while(SI==0);
	if(I2STAT==0x30){
		uart0_tx_string("Err:Memory Addr\r\n");
		goto exit;
	}
	
	/*4. restart condi*/
	I2CONSET=(1<<5);//STA=1
	I2CONCLR=(1<<3);//Clear SI
	while(SI==0);
	I2CONCLR=(1<<5);//STA=0*
	
	/*5. send sa+r & check ack*/
	I2DAT=sa;//send SA+R
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);
	if(I2STAT==0x48){
		uart0_tx_string("Err:SA+R\r\n");
		goto exit;
	}
	
	/*6. read data(from slave) & send noack*/
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//waiting for data
	data=I2DAT;
	
	/*7. stop condi*/
	exit:
			I2CONSET=(1<<4);//STO=1
			I2CONCLR=(1<<3);//Clear SI
	
	/*8. return data*/
	return data;
}





