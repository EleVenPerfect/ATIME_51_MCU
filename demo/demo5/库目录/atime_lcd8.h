/************************************
库功能：串行数码管显示
库要求：主函数中已定义：
		#include <reg52.h>
应用函数：
		printlcd8( unsigned int h_num, unsigned int l_num)	
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-10-07
作者： ATIME	版权所有
实例程序：
		#include "STC15F2K60S2.H"
		#include "atime_lcd8.h" 
		
		
		void main ()
		{
			while(1)
			{
				printlcd8(1234,5678);
			}
		}


常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
注：显示需要不断扫描才可以。	
***************************************/


#ifndef _ATIME_LCD8_H_ 
#define _ATIME_LCD8_H_


/************************************
库全局变量组
***************************************/

sbit LCD_DIO =P3^3;					   //定义接口DIO
sbit LCD_SCK =P3^2;					   //定义接口SCK
sbit LCD_RCK =P3^4;					   //定义接口RCK

unsigned char code num_lcd8[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char code bit_lcd8[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};


/************************************
函数功能：输出显示
传递参数：空
返回值：空
***************************************/
void lcd8_out_once( void)
{
	LCD_RCK =0;
	LCD_RCK =1;
}


/************************************
函数功能：发送一字节数据
传递参数：kk：数据
返回值：空
***************************************/
void lcd8_out_data(unsigned char kk)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
		LCD_SCK =0;
		LCD_DIO =kk&0x80;
		kk <<=1;
		LCD_SCK =1;	
	}
}


/************************************
函数功能：显示一次数字
传递参数：
		x:数字位置
		num:数字值
返回值：空
***************************************/
void print_lcd8_once( unsigned char num, unsigned char x)
{
	  lcd8_out_data(bit_lcd8[x]);
	  lcd8_out_data(num_lcd8[num]);
	  lcd8_out_once();
}


/************************************
函数功能：进行一次动态扫描
传递参数：
		h_num：高四位数字
		l_num：低四位数字
返回值：空
***************************************/
void printlcd8( unsigned int h_num, unsigned int l_num)
{
	unsigned char i,temp;
	for( i=0; i<4; i++)
	{
		temp =l_num%10;
		print_lcd8_once( temp, i);
		l_num =l_num/10;		
	}
	for( i=0; i<4; i++)
	{
		temp =h_num%10;
		print_lcd8_once( temp, i+4);
		h_num =h_num/10;		
	}
}


#endif