#include <RTL.H>
unsigned long int count1,count2,count3;
OS_TID tid2;
__task void task2(void){
	for(;;)
		count2++;	
}

__task void task1(void){
	tid2=os_tsk_create(task2,1);
	for(;;)
		count1++;	
}

main(){
	os_sys_init(task1);
	//count3++;
}
