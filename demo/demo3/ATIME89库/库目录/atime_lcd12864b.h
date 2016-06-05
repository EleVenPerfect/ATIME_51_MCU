/************************************
库功能：8位并行驱动无字库12864液晶
库要求：主函数中已定义：
		#include <reg52.h>
应用函数：
		 set_clear(void)
		 lcd12864b_int(void)
		 print_ch12864b(unsigned char a[],unsigned char n, unsigned char y, unsigned char x)
		 print_en12864b(unsigned char a[],unsigned char n, unsigned char y, unsigned char x)
修改历史：
		   	 ‘修改人’   ‘修改内容’  				      修改时间’
最后完成时间：2014-02-10
作者： ATIME	版权所有
实例程序：
		#include <reg52.h>
		#include "atime_lcd12864b.h"
		
		void main()
		{
			unsigned char i;
			lcd12864b_int();
			while(1)
			{
				for(i=0; i<6; i++)
					print_ch12864b(a,i,4,i+1);
				for(i=0; i<6; i++)
					print_en12864b(b,i,1,i+5);
				wait_12864bms(1000);
				set_clear();
				wait_12864bms(500);
			}
		}

常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(13): warning C182: pointer to different objects  :将输出数据类型转为char型输出即可
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库后面即可
取模方法：
	汉字/字母：纵向8点下高位16*16/8*16点阵
***************************************/

#ifndef _ATIME_LCD12864B_H_ 
#define _ATIME_LCD12864B_H_


/************************************
库全局变量组
***************************************/
#define DATA_12864B P0   //定义8位数据口
sbit RS_12864B =P2^0;    //寄存器选择位，将RS位定义为P2.0引脚 ;1:数据；0：命令
sbit RW_12864B =P2^1;    //读写选择位，将RW位定义为P2.1引脚   ;1:读取；0：写入
sbit EN_12864B =P2^2;    //使能信号位，将E位定义为P2.2引脚
sbit CS1_12864B=P2^3;	  //串并口选择；1：并口； 0：串口；
sbit CS2_12864B=P2^4;	  //并口片选
sbit RES_12864B=P2^5;	  //复位端低电平有效

/************************************
示例取模数组
***************************************/
unsigned char code a[]={
	  0x40,0x40,0x48,0x48,0x48,0xC8,0x78,0x4F,
      0x48,0x48,0x48,0x4C,0x48,0x60,0x40,0x00,
      0x00,0x00,0x00,0x00,0x02,0x23,0x22,0x42,
      0x62,0x92,0x0A,0x06,0x02,0x00,0x00,0x00,	//专
	  0x10,0x22,0x64,0x0C,0x80,0x08,0x08,0x08,
      0x09,0xFE,0x08,0x08,0x88,0x0C,0x08,0x00,
      0x04,0x04,0xFE,0x01,0x40,0x41,0x41,0x41,
      0x41,0x7F,0x41,0x41,0x41,0x61,0x40,0x00,	//注
  	  0x80,0x40,0xF0,0x4C,0x43,0x44,0xC8,0x10,
      0x30,0x00,0xF8,0x00,0x00,0xFF,0x00,0x00,
      0x00,0x00,0x3F,0x40,0x42,0x44,0x43,0x70,
      0x00,0x00,0x07,0x40,0x80,0x7F,0x00,0x00, //创
      0x40,0x42,0x44,0xCC,0x00,0x50,0x4E,0x48,
      0x48,0x7F,0x48,0x4C,0xC8,0x60,0x40,0x00,
      0x00,0x40,0x20,0x1F,0x20,0x40,0x5F,0x51,
      0x51,0x51,0x51,0x51,0x5F,0x61,0x20,0x00, //造
      0x40,0x40,0x44,0x44,0x64,0x54,0x4C,0x47,
      0x4C,0x54,0x74,0xC6,0x44,0x60,0x40,0x00,
      0x00,0x00,0x00,0x3E,0x12,0x12,0x12,0x12,
      0x3F,0x42,0x80,0x7F,0x00,0x00,0x00,0x00, //奇
      0x40,0x42,0xCC,0x00,0x08,0xC8,0x08,0xF9,
      0x0A,0x0E,0xF8,0x08,0x4C,0x88,0x00,0x00,
      0x40,0x20,0x1F,0x20,0x42,0x41,0x50,0x4F,
      0x40,0x50,0x5F,0x40,0x40,0x63,0x20,0x00};	//迹
unsigned char code b[]={
	0xE0,0xF0,0x98,0x8C,0x98,0xF0,0xE0,0x00,  // -A-
	0x0F,0x0F,0x00,0x00,0x00,0x0F,0x0F,0x00,
	0x00,0x1C,0x0C,0xFC,0xFC,0x0C,0x1C,0x00,  // -T-
	0x00,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,
	0x00,0x00,0x04,0xFC,0xFC,0x04,0x00,0x00,  // -I-
	0x00,0x00,0x08,0x0F,0x0F,0x08,0x00,0x00,
	0xFC,0xFC,0x38,0x70,0x38,0xFC,0xFC,0x00,  // -M-
	0x0F,0x0F,0x00,0x00,0x00,0x0F,0x0F,0x00,
	0x04,0xFC,0xFC,0x44,0xE4,0x0C,0x1C,0x00,  // -E-
	0x08,0x0F,0x0F,0x08,0x08,0x0C,0x0E,0x00,
	0x00,0x00,0x38,0xFC,0xFC,0x38,0x00,0x00,  // -!-
	0x00,0x00,0x00,0x0D,0x0D,0x00,0x00,0x00,};


/************************************
函数功能：延时大约n 毫秒ms
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
***************************************/
void wait_12864bms(unsigned int n)
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
函数功能：忙检测并等待直到不忙
传递参数：空
返回值：空
***************************************/
void check_busy_b(void)
{
	unsigned char busy;
	RS_12864B =0;
	RW_12864B =1;
	for(busy=0x01; busy==0x00; )
	{
		EN_12864B =1;
		busy =DATA_12864B;
		EN_12864B =0;
		busy =busy&0x80;
	}
}


/************************************
函数功能：写指令到12864
传递参数：a：指令
返回值：空
***************************************/
void write_zhi12864(unsigned char a)
{
	check_busy_b();
	RS_12864B =0;
	RW_12864B =0;
	DATA_12864B =a;
	EN_12864B =1;
	EN_12864B =0;		
}


/************************************
函数功能：写数据到12864
传递参数：a：数据
返回值：空
***************************************/
void write_shu12864(unsigned char a)
{
	check_busy_b();
	RS_12864B =1;
	RW_12864B =0;
	DATA_12864B =a;
	EN_12864B =1;
	EN_12864B =0;		
}

/************************************
函数功能：屏幕选择
传递参数：a左半屏  b右半屏， 1为选择
返回值：空
***************************************/
void select_12864(unsigned char a,unsigned char b)
{
	CS1_12864B =(bit)a;
	CS2_12864B =(bit)b;
}

/************************************
函数功能：写入地址
传递参数：y:纵向行数;x:横向列数;
返回值：空
注以左上角为（0,0）
***************************************/
void set_address_12864b(unsigned char y, unsigned char x)
{
	write_zhi12864(y|0xB8);
	write_zhi12864(x|0x40);		
}



/************************************
函数功能：清屏							
传递参数：空							
返回值：空
***************************************/
void set_clear(void)
{
	unsigned char i,j,k;
	for(i=0; i<64; i++)
		for(j=0; j<8; j++)
		{
			set_address_12864b(j,i);
			CS1_12864B =1;
			CS2_12864B =1;
			for(k=0; k<16; k++)
				write_shu12864(0x00);
		}
}



/************************************
函数功能：初始化液晶
传递参数：空
返回值：空
***************************************/
void lcd12864b_int(void)
{
	RES_12864B =0;
	;
	RES_12864B =1;
	select_12864(1,1);
	write_zhi12864(0x3f);
	set_clear();
}

/************************************
函数功能：在指定地点写一个汉字
传递参数：
			a[]:要操作的汉字组
			n:	要显示汉字所在顺序位置
			y:	要显示行数（0~7）每 8个点为一个单位
			x:	要显示列数（0~7）每16个点为一个单位
返回值：空
***************************************/
void print_ch12864b(unsigned char a[],unsigned char n, unsigned char y, unsigned char x)
{
	unsigned char i;
	x =x*16;
	if(x >=64)
	{	
		x =x-64;
		select_12864(0,1);
	}
	else 
		select_12864(1,0);
	set_address_12864b(y,x);
	for(i=0;i<16; i++)
		write_shu12864(a[i+n*32]);	
	set_address_12864b(y+1,x);
	for(i=0;i<16; i++)
		write_shu12864(a[i+16+n*32]);	
}


/************************************
函数功能：在指定地点写一个英文字符
传递参数：
			a[]:要操作的字符组
			n:	要显示汉字所在顺序位置
			y:	要显示行数（0~7）每 8个点为一个单位
			x:	要显示列数（0~15）每 8个点为一个单位
返回值：空
***************************************/
void print_en12864b(unsigned char a[],unsigned char n, unsigned char y, unsigned char x)
{
	unsigned char i;
	x =x*8;
	if(x >=64)
	{	
		x =x-64;
		select_12864(0,1);
	}
	else 
		select_12864(1,0);
	set_address_12864b(y,x);
	for(i=0;i<8; i++)
		write_shu12864(a[i+n*16]);	
	set_address_12864b(y+1,x);
	for(i=0;i<8; i++)
		write_shu12864(a[i+8+n*16]);	
}

#endif	