/************************************
库功能：串行数码管显示
库要求：主函数中已定义：
		#include <reg52.h>
应用函数：
		 dht11_int( void)
		 unsigned char read_dht11(unsigned char a[5])
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-10-07
作者： ATIME	版权所有
实例程序：
		#include "STC15F2K60S2.H"
		#include "atime_dht11.h" 
		#include "atime_lcd1602.h"
		
		void main ()
		{
			unsigned char t;
			unsigned char a[5];
			unsigned char b[15];
		
			int_lcd1602(rightmove, cursornotdisplay);
			dht11_int();
			while(1)
			{
				if(read_dht11(a)==1)
				{
					bcd_trans_char( a, b, 5);
					print1602( b, 1, 0);
					for( t=0; t<100; t++)
						wait_10us_dht11(1000);
				}
				else
					print1602("error", 1, 0);
			}
		}


常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告	
***************************************/


#ifndef _ATIME_DHT11_H_ 
#define _ATIME_DHT11_H_


/************************************
库全局变量组
***************************************/


sbit DTH11_DATA =P2^3;					   //定义接口DIO


/************************************
函数功能：精确延时10us
传递参数：延时时间
返回值：空
***************************************/
void wait_10us_dht11(unsigned int k)
{
	int i,j;
	for( i=0; i<k; i++)
	{
		for( j=0; j<7; j++)
		;
	}
}


/************************************
函数功能：初始化DHT11
传递参数：空
返回值：空
***************************************/
void dht11_int( void)
{
	unsigned char i;
	DTH11_DATA =1;
	for( i=0; i<100; i++)
	{
		wait_10us_dht11(1000);
	}
}


/************************************
函数功能：
传递参数：
返回值：
***************************************/
bit dht11_start( void)
{
	unsigned int i=0;
	bit err;
	DTH11_DATA =1;
	DTH11_DATA =0;
	wait_10us_dht11(2500);
	DTH11_DATA =1;
	while(DTH11_DATA == 1)
	{
		i++;
		if(i>65530)
			return (1);
	}	
	wait_10us_dht11(1);
	return (0);
}
/************************************
函数功能：读取数据并存储在数组中
传递参数：数组指针
返回值：空
***************************************/
void dht11_read40(unsigned char a[5])
{
	unsigned char i,j,temp=0x00;
	for( j=0; j<5; j++)
	{
		for( i=0; i<8; i++)
		{
			while(DTH11_DATA == 0);
			wait_10us_dht11(5);
			if(DTH11_DATA == 1)
			{
				temp |=0x01;
				while(DTH11_DATA == 1);
			}
			temp <<=1;
		}
		a[j] =temp;
	}
}

/************************************
函数功能：获取温湿度数据并校验
传递参数：a[5] ：数据数组
返回值：成功：1；
		失败：0；
***************************************/
unsigned char read_dht11(unsigned char a[5])
{
	if(dht11_start())
		return(0);
	dht11_read40(a);
	if( a[0]+a[2] != a[4])
		return(0);
	return (1);
}


#endif