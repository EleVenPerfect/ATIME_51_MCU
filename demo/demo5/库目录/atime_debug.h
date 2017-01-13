/************************************
库功能：15系列单片机DEBUG小程序
库要求：主函数中已定义：
		#include <reg52.h>
		#include "atime_interrupt.c"
应用函数：
		 void debug_init( void)
		 printf( const char* format, [argument] ...)
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
			  ATIME		串口初始化	2014-03-26
			  			解决了SD卡读写进入串口中断的BUG，SD卡读写仍然需要禁止接受串口
最后修改时间：2017-01-13
作者： ATIME	版权所有
实例程序：
		#include "STC15F2K60S2.H"		 //可以替换REG52.H，建议使用这个头文件
		#include "atime_iic.h"
		#include "atime_debug.h"
		#include "atime_app.c"
		
		
		void main()
		{
			unsigned int i;
			debug_init();
		
			while(1)
			{
				printf("atime");
				for(i=0;i<50000;i++)
					wait_iicbus();
		
			}
		}	

常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注：使用9600波特率进行printf形式输出
***************************************/


#ifndef _ATIME_DEBUG_H_ 
#define _ATIME_DEBUG_H_
#include <stdio.h>

/************************************
库全局变量组
***************************************/


/************************************
函数功能：串口发送一个字符
传递参数：a：待发送字符
返回值：空	
***************************************/
void send_char(char a)
{
	SBUF =a;
	while(TI ==0);
	TI =0;
}


/************************************
函数功能：串口发送一个字符
传递参数：a：待发送字符
返回值：空	
***************************************/
char putchar(char ch)
{
    send_char(ch);
    return (ch);
}


/************************************
函数功能：串口初始化
传递参数：空
返回值：空	
***************************************/
void debug_init(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xDC;		//设定定时初值
	TH1 = 0xDC;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}


/************************************
函数功能：延时大约n 毫秒ms
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
***************************************/
void debug_delay(unsigned int n)
{
	int i;
	while(n--)
	{
		for(i=0; i<580; i++)		  //89系列选择75,12系列选择580,15系列选择580
		{
			;
		}	
	}
}


/************************************
函数功能：产生随机数
传递参数：空
返回值：空	
***************************************/
unsigned char debug_rand(void)
{
	static unsigned char i;
	i = i + TL1;
	debug_delay((i%10)/2+1);
	return (i%10)/2+1;
}


#endif