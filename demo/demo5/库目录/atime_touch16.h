/************************************
库功能：触摸键盘16键
库要求：主函数中已定义：
		#include <reg52.h>
应用函数：
		unsigned char touch16(void)	
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-10-07
作者： ATIME	版权所有
实例程序：
		#include "STC15F2K60S2.H"
		#include "atime_touch16.h" 
		#include "atime_lcd1602.h"
		
		void main ()
		{
			unsigned char tt,a[2];
			P0 =0X00;
			int_lcd1602(rightmove, cursornotdisplay);
			while(1)
			{
				tt =touch16();
				a[0] =tt/10+0x30;
				a[1] =tt%10+0x30;
				print1602( a, 1, 1);
				P0 =~P0;
			}
		}


常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告	
注：
	电路设置2线串口通信，低电平有效，16键模式,只检测一个按键按下
***************************************/


#ifndef _ATIME_TOUCH16_H_ 
#define _ATIME_TOUCH16_H_


/************************************
库全局变量组
***************************************/

sbit TOUCH_SDO =P2^5;					   //定义接口SDO
sbit TOUCH_SCL =P2^4;					   //定义接口SCL


/************************************
函数功能：确定按键值
传递参数：空
返回值：（0~16）16表示没有按键按下
***************************************/
unsigned char touch16(void)
{
	unsigned char i,j;
	i =0;
	for( j=0; j<16; j++)
	{
		TOUCH_SCL =0;
		if(TOUCH_SDO ==0)
			i =j+1;
		TOUCH_SCL =1;
	}
	return (i);
}


#endif