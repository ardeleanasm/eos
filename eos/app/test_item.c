#include <avr/io.h>
#include <stdlib.h>
#include "stdtypes.h"
#include "architecture.h"
#include "threading.h"
#include "driver_api.h"
#include "test_item.h"

/*
void init_port()
{
	DDRB=0xff;
	
	//toggle_led();
	
//	write(desc,&PORTB,(1<<PINB2));
	//driver_unload(gpio);
}
void toggle_led()
{
	//lock_mutex();
	PORTB^=(1<<PINB0);
//	unlock_mutex();
}*/

void init_port()
{
	
	DDRB=0xFF;
	S_Tasks_Struct task_20;
	u8 task_id;
	task_20.rub_Task_Priority=TASK_HIGH_PRIO;
	task_20.rub_Task_Schedule=E_Task_20ms;
	task_20.task=&toggle_led;
	if((task_id=task_push(task_20))>=0)
	{
		PORTB|=(1<<PINB3);
	}
	else
	{
		PORTB|=(1<<PINB4);
	}
	task_change_state(task_id,TASK_BLOCKED);

	
	
}
void toggle_led()
{
	lock_mutex();
	PORTB^=(1<<PINB0);
	unlock_mutex();
}

