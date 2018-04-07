#include "STC12C5A60S2.H"		 //可以替换REG52.H，建议使用这个头文件
#include "atime_project.c"


void main()
{
		io_init();
	
		while(1)
		{
				get_gq_data();						//通过I2C总线读取当前光强
				get_wlw_status();					//读取物联网模块三组开关状态
				get_body_status();				//读取人体感应模块状态	
			
				set_pwm_status();					//根据光强设置总体光照亮度
				set_led_status();					//设置led应输出状态
				set_led_output();					//设置led输出
			
				conversion(gq_int_status);
				send_char(wan);
				send_char(qian);
				send_char(bai);
				send_char(shi);
				send_char(ge);
				send_char('\n');
				delay_nms(200); 
		}
}