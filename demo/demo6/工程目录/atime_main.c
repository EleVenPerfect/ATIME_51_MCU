#include "STC12C5A60S2.H"		 //可以替换REG52.H，建议使用这个头文件
#include "atime_pwmpca.h"
#include "atime_iic.h"

sbit led0 = P1^0;
sbit led1 = P1^1;
sbit led2 = P1^2;
sbit led_gnd = P1^3;

sbit wlw_high = P1^4;
sbit wlw_k0 = P1^5;
sbit wlw_k1 = P1^6;
sbit wlw_k2 = P1^7;

sbit body0 = P3^0;
sbit body1 = P3^1;

unsigned char body_set = 0;//状态存储：是否是人体靠近引发的灯光亮起，0代表不是，1代表是因为人体靠近引发的灯光亮起

void main()
{
		P1 = 0XFF;
		P1M1 = 0x00;
		P1M0 = 0x17;//设置P1端口输出状态
		P3 = 0xff;//设置P3端口输出状态
		pwm_init( pwm_on, 0, 0x02);
		pwm_set(0, 100.0);

		while(1)
		{
				//通过I2C总线读取当前光强
				//读取物联网模块三组开关状态
				//读取人体感应模块状态	
				//根据光强设置总体光照亮度
				if( body_set==1 )//如果是因为人体靠近引发的灯光亮起
				{
						//当人体感应模块变化时需要重新设置灯光状态
						//当物联网模块发出指令时需要重新设置灯光状态
				}
				else
				{
						//当物联网模块发出指令时需要重新设置灯光状态
				}					
		}
}