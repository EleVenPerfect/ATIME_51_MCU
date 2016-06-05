/************************************
库功能：红外线遥控检测库
库要求：程序已经载入：
		#include <reg52.h>
		#include "atime_interrupt.c"
应用函数：
		int_infrared(int i)
		start_code(void) //  interrupt 0
		read_infrared(unsigned char j[4])
		translate_bcd(unsigned char j[4],unsigned char k[8])
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-02-07
作者： ATIME	版权所有
实例程序：
			#include <reg52.h>
			#include <string.h>
			#include "atime_lcd1602.h"
			#include "atime_infrared.h"
			#include "atime_interrupt.c"
			
			void main()
			{
				unsigned char a[4],b[8];
				int_lcd1602(rightmove, cursornotdisplay);
				int_infrared(0);
				while(1)
				{
					read_infrared(a);
					translate_bcd(a,b);
					print1602(b,1,1);
				}
			}
			中断服务函数：
			void interrupt_int0(void) interrupt 0
			{
				start_code();
			}
常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注意：
***************************************/


#ifndef _ATIME_INFRARED_H_ 
#define _ATIME_INFRARED_H_


/************************************
库全局变量组
***************************************/

sbit HWJS =P3^2;       //定义红外接收所在管脚（外部中断0）
unsigned char a[4];	   //存储解码结果

/************************************
函数功能：延时大约n*50微秒us
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
***************************************/
void infrared_us(unsigned int n)
{
	unsigned char i;
	while(n--)
		for(i=0; i<2; i++);	
}


/************************************
函数功能：初始化红外通讯
传递参数：所在外部中断号
返回值：空	
注意：初始化过程中自动开启总中断允许EA。
***************************************/
void int_infrared(int i)
{
	EA =1;
	if(i ==1)
	{
		EX1 =1;
		IT1 =1;
	}
	else if(i ==0)
	{
		EX0 =1;
		IT0 =1;
	}
}



/************************************
函数功能：红外中断服务函数
传递参数：空
返回值：空
注意：只可以放在外部中断0中，否则需要更改中断允许EX的值	 
***************************************/
void start_code(void) // interrupt 0
{
	unsigned i ,j ,temp =0;
	EX0 =0;
	infrared_us(150);
	if(HWJS ==0)
	{
		while(HWJS ==0);
		infrared_us(70);
		if(HWJS ==1)
		{			
			while(HWJS ==1);
			for(j =0; j<=3; j++)
			{
				for(i=0; i<=7; i++)
				{
					temp =temp>>1;
					while(HWJS ==0);
					infrared_us(26);	 //调节数字在27左右以调整译码准去度
					if(HWJS ==1)
						temp =temp|0x80;
					else
						temp =temp|0x00;
					while(HWJS ==1);
				}
				a[j] = temp;	
			}
		}
	}
	EX0 =1;
}

/************************************
函数功能：返回读取的数据
传递参数：j[4]
返回值：j[4]返回收到的数据	
***************************************/
void read_infrared(unsigned char j[4])
{
	j[0] =a[0];
	j[1] =a[1];
	j[2] =a[2];
	j[3] =a[3];
	a[0] =0x00;
	a[1] =0x00;
	a[2] =0x00;
	a[3] =0x00;
}


/************************************
函数功能：优化显示
传递参数：j[4]:待转换数组
返回值：k[8]:转换完成输出数组	
***************************************/
void translate_bcd(unsigned char j[4],unsigned char k[8])
{
	unsigned char temp,i;
	for(i=0; i<=3; i++)
	{
		temp =j[i];
		k[2*i+1] =(temp&0x0f)+48;
		temp =temp&0xf0	;
		temp =temp>>4;
		temp =temp&0x0f;
		k[2*i] =(temp+48);
		if(k[2*i+1] >57)
			k[2*i+1] +=7;
		if(k[2*i] >57)
			k[2*i] +=7;	
	}
}



#endif