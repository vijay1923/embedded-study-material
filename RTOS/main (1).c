#include <RTL.H>
unsigned long int count1,count2,count3;
OS_TID tid2,tid3;

__task void task3(void){
	for(;;){
		count3++;		
	}
}

__task void task2(void){
	for(;;){
		count2++;	
//		if(count2==9000000)
//			os_tsk_delete_self();
	}
}

__task void task1(void){
	tid2=os_tsk_create(task2,1);
	tid3=os_tsk_create(task3,1);
	for(;;){
		count1++;		
	}
}

 main(){
	os_sys_init(task1);
}
