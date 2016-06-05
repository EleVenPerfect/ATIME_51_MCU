#include "STC12C5A60S2.H" 
#include "atime_lcd1602.h"
#include "atime_18b20.h"
#include "atime_serial.h"
#include "atime_timer.h"
#include "atime_interrupt.c"


void main()
{
	unsigned char display_temp[8];		//显示缓存

	jdq_1 = 1;
	jdq_2 = 1;							//为1时开启
	serial_int(enable, baud9600, disable); //串口初始化
	int_lcd1602( rightmove, cursornotdisplay); //1602初始化
	int_interrupt( 0, negative_jump);		   //外部中断0，下降沿触发
	int_interrupt( 1, negative_jump);
	main_timer(on,0);						//开启定时器
	timer_8_int(0,240,normal);				//定时器设置240个脉冲后溢出，并触发中断
	main_interrupt(on);						//开启总中断

	while(1)
	{
		/*显示控制阈值*/
		display_temp[0] = temp_set%100/10+0x30;	 //任何数字加0x30转换为可以显示的ASCII码
		display_temp[1] = temp_set%10+0x30;
		display_temp[2] = '\0';
		print1602( display_temp, 0,14);
		printchar1602(' ', 1, 15);


		/*读取温度传感器1并显示，当读取温度为85时为错误数据，不显示*/
		ds18b20_1_exist =int_18b20_1();	//判断传感器是否存在
		if( ds18b20_1_exist ==0 )		   //为0时存在
		{
			temperature1 = read_temper_1();	  //读取温度数据
			if(temperature1<85.0)			  //去除开机第一次显示的错误数据
			{
				translate( temperature1, display_temp);	//把float型数据转换为可以显示的数据并放到显示缓存
				print1602( display_temp, 0, 0);			//显示
			}
		}
		else											//若不存在
		{
			print1602( "Check 1", 0, 1);
			waitms(500);								 //清除显示的数据
			clear1602_10(0);
		}
		/*读取温度传感器2，当读取温度为85时为错误数据，不显示*/
		ds18b20_2_exist =int_18b20_2();
		if( ds18b20_2_exist ==0 )
		{
			temperature2 = read_temper_2();
			if(temperature2<85.0)
			{
				translate( temperature2, display_temp);
				print1602( display_temp, 1, 0);
			}
		}
		else
		{
			print1602( "Check 2", 1, 1);
			waitms(500);
			clear1602_10(1);
		}
		waitms(300);
	}
}
