/************************************
库功能：超声波测距模块
	※※※本函数库内部已经定义外部中断1的服务函数，如果还需要载入中断函数库，需要将中断函数库的外部中断1服务函数屏蔽掉。※※※
库要求：主函数中已定义：
		#include <reg52.h>
应用函数：
		 supersonic_test(void)
		 translate_code(unsigned int i,unsigned char a[])	
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-02-06
作者： ATIME	版权所有
实例程序：
		#include <reg52.h>
		#include <string.h>		  当用到lcd1602模块时，需要同时载入此函数库。
		#include "atime_lcd1602.h"
		#include "atime_supersonic.h"
		
		
		void main()
		{
			unsigned char a[5];
			unsigned int i;
			int_lcd1602(rightmove, cursornotdisplay);
			while(1)
			{
				i =supersonic_test();
				translate_code(i,a);
			    print1602(a,1,3);
			}
		}

常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注意：本函数库内部已经定义外部中断1的服务函数，如果还需要载入中断函数库，需要将中断函数库的外部中断1服务函数屏蔽掉。
	  本函数库不能精确测量距离（可以通过外加函数再调整输出数值）；
	  且在距离超声波发生器3cm范围内有盲区，无法提供准确结果。
***************************************/


#ifndef _ATIME_SUPERSONIC_H_ 
#define _ATIME_SUPERSONIC_H_


/************************************
库全局变量组
***************************************/

sbit STX = P3^2;      //产生脉冲引脚TX
sbit SRX = P3^3;      //回波引脚RX
unsigned char a[2];	  //存储TH/TL数据

/************************************
函数功能：延时大约n 毫秒ms
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
***************************************/
void wait_supersonic_ms(unsigned int n)
{
	int i;
	while(n--)
	{
		for(i=0; i<75; i++)
		{
			;
		}	
	}
}

/************************************
函数功能：延时大约0.2毫秒ms
传递参数：空
返回值：空	
注意：此函数不能精确定时
***************************************/
void wait_5khz(void)
{
	int i;
	for(i=0; i<30; i++);		 //调整超声波发声频率，如果总是零点离超声波发声处有一段距离，可以调整这里
}



/************************************
函数功能：16位不自动重装定时器设置
传递参数:空
返回值：空
***************************************/
void timer1_int( void)
{

 	ET1 =0;
	TMOD=TMOD|0x10;	   
	TH1 =0;
	TL1 =0;
}


/************************************
函数功能：超声波测距中断函数
传递参数：空
返回值：	
***************************************/
void super_interrupt(void)  interrupt 2
{
	TR1 =0;
	a[1] =TL1;
	a[0] =TH1;
	TH1 =TL1 =0;
	wait_supersonic_ms(15);
}


/************************************
函数功能：超声波测距转换mm单位整数
传递参数：空
返回值：整数距离，单位毫米	
***************************************/
unsigned int translate_supersonic()
{
	float j;
	unsigned int i;
	j =a[0]*256+a[1];
	j =j*0.175;
	i =(int)j;
	return (i);
}


/************************************
函数功能：超声波测距
传递参数：空
返回值：距离，单位毫米	
***************************************/
unsigned int supersonic_test(void)
{
	unsigned i;
	ET1 =0;
	EA = 1;
	TR1 =0;
	EX1 =0;
	timer1_int();
	EX1 =1;
	TR1 =1;	  			     //中断、定时器准备

	STX =0;
	wait_5khz();
	STX =1;				     //发出超声波

	TH1 =TL1 =0;
	wait_supersonic_ms(40);
	i =translate_supersonic();
	a[0] =0;
	a[1] =0;			     //中断后数据处理并清零
	return (i);		
}



/************************************
函数功能：超声波测距整数转数组
传递参数：空
返回值：距离，单位厘米	
***************************************/
void translate_code(unsigned int i,unsigned char a[])
{
	a[0] =(i%10000)/1000+48;
	a[1] =(i%1000)/100+48;
	a[2] =(i%100)/10+48;
	a[3] ='.';
	a[4] =i%10+48;
}



#endif