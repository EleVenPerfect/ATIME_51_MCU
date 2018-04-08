#include <reg52.H>
#include "cejv.h"
#include "guangqiang.h"
#include "wulianwang.h"
#include "led.h"
#include "kongzhi.c"


void main(void)
{  
		cj_init();
		gq_init(); 
		led_init();
		key_init();
		wlw_init();
	
		while(1)
		{		
				if(key4==1)
				{
						cj_run();
						get_gq_data();
						led_body10cm();
						led_body20cm();
				}
				else
				{
						get_wlw_data();
						get_key_data();
						led_kongzhi();
						delayms(10);		//10MS
				}
		}
}              