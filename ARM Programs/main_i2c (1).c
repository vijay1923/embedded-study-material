/*main_i2c.c
  i2c testing program
*/
#include "header.h"
main(){
	u8 h,m,s,dow;
	s8 arr[][4]={"","SUN","MON","TUE","WED","THU","FRI","SAT"};
	i2c_init();
	lcd_init();
	lcd_cmd(0x0C);//cursor off
	/*set rtc time to 11:59:55PM*/
	i2c_send(0xD0,0x2,0x23);//11pm  
	i2c_send(0xD0,0x1,0x59);//59mins
	i2c_send(0xD0,0x0,0x55);//55secs
	i2c_send(0xD0,0x3,0x6);//set fri
	/*read time from rtc & dump it on lcd*/
	while(1){
		h=i2c_read(0xD1,0x2);//read hrs
		m=i2c_read(0xD1,0x1);//read mins
		s=i2c_read(0xD1,0x0);//read secs
		dow=i2c_read(0xD1,0x3);//read dow
		//lcd_cmd(0x1);//clear screen
		lcd_cmd(0x80);//set cursor to home pos
		lcd_data((h/0x10)+48);
		lcd_data((h%0x10)+48);
		lcd_data(':');
		
		lcd_data((m/0x10)+48);
		lcd_data((m%0x10)+48);
		lcd_data(':');
		
		lcd_data((s/0x10)+48);
		lcd_data((s%0x10)+48);	

		lcd_cmd(0xC0);
		lcd_string(arr[dow]);	
	}
}




