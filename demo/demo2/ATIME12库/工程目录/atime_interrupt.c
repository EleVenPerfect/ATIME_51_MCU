/************************************
文件功能：51单片机中断函数组
库要求：主函数中已定义：
		#include <reg52.h>
		#include "atime_timer.h"
		#include "atime_interrupt.c"
应用函数：
		interrupt_int0()
		interrupt_timer0()
		interrupt_int1()
		interrupt_timer1()
		interrupt_serial()
		interrupt_serial2(void)
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
			    ATIME	增加函数	2014-04-29
					增加interrupt_serial2(void)	
最后修改时间：2014-02-03
作者： ATIME	版权所有
常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
常用函数变量声明：
		static：静态变量，第二次调用应用上次调用后的值，不再重新开辟内存空间设定初值。
***************************************/

/************************************
中断可用全局变量组
***************************************/
unsigned char temp_set=31;	//设置初始温度
float temperature;
sbit led_1 = P3^6;
sbit led_2 = P3^7; 
int aaa = 0;	//分频定时器用
bit ds18b20_exit;

/************************************
函数功能：外部中断0的中断服务
传递参数：空
返回值：空	
注意：空
***************************************/
void interrupt_int0(void) interrupt 0
{
	temp_set++;
	if(temp_set>50)
		temp_set = 50;
}


/************************************
函数功能：定时器/计数器0的中断服务
传递参数：空
返回值：空	
注意：空
***************************************/
void interrupt_timer0(void) interrupt 1
{
	unsigned char temp_average;
	unsigned char distance;
	
	aaa++;	
	if(aaa>10)
	{
		aaa=0;

		temp_average = (unsigned char)temperature;//强制转换为char型等待进行比较
	
		if(temp_average>temp_set)
		{
			distance = temp_average - temp_set;	
			if( distance>1 )     //检测实际温度平均值如果大于1则启动降温程序
			{
				led_1 = 1;		 //低电平发灯亮
			}
			else
			{
				led_1 = 0;
			}
		}
		else
		{
			distance = temp_set - temp_average;
			if( distance>1 )	 //检测实际温度平均值如果大于1则启动升温程序
			{
				led_2 = 1;        //高电平灯亮
			}
			else
			{
				led_2 = 0;	
			}
		}		
	
	}
}



/************************************
函数功能：外部中断1的中断服务
传递参数：空
返回值：空	
注意：空
***************************************/
void interrupt_int1(void) interrupt 2
{
	temp_set--;	
	if(temp_set<10)
		temp_set = 10;	   
}



/************************************
函数功能：定时器/计数器1的中断服务
传递参数：空
返回值：空	
注意：空
***************************************/
void interrupt_timer1(void) interrupt 3
{

}


/************************************
函数功能：串口1的中断服务
传递参数：空
返回值：空	
注意：空
***************************************/
void interrupt_serial1(void) interrupt 4
{
	unsigned char k;
	k =receive_char();
	printchar1602(k , 1, 15);
	if(k=='A')
	{
		temp_set++;
		if(temp_set>50)
			temp_set = 50;
	}
	if(k=='B')
	{
		temp_set--;	
		if(temp_set<10)
			temp_set = 10;		
	}

	send_char(k);
	send_char(' ');
	send_char('O');
	send_char('K');
	send_char('\n');
}	




/************************************
函数功能：串口2的中断服务
传递参数：空
返回值：空	
注意：空
***************************************/
void interrupt_serial2(void) interrupt 8
{

}		


