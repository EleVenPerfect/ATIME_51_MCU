/************************************
库功能：并行驱动1602液晶
库要求：主函数中已定义：
		#include <reg52.h>
应用函数：
		int_lcd1602(enum lcdint_ac a,enum lcdint_cursor b)
		print1602(unsigned char db[], unsigned int y, unsigned int x)
		printchar1602(unsigned char db, unsigned int y, unsigned int x)
		set1602(enum set a )
		bcd_trans_char(unsigned char a[], unsigned char b[],unsigned char j)
修改历史：
		   	 ‘修改人’   ‘修改内容’  				      修改时间’
			   ATIME	 print1602函数					 2014-02-07
			   			修改了判定字符串长度的方法 不再需要#include <string.h>
			   ATIME	 添加bcd_trans_char函数			 2014-02-09
			   		 	 利于BCD码的直接显示
			   ATIME	 修改了lcd1602数据接口的宏定义	 2014-02-09
			   			 解决了：error C231: 'P0': redefinition 问题
			   ATIME	 修改了print1602()函数参数	 2014-03-14
			   			 unsigned char print1602(unsigned char db[], unsigned int y, unsigned int x)以（0,0）作为起始地址（尚未测试）
			   ATIME	 调试了函数						 2014-04-16
			   			 print1602(unsigned char db[], unsigned int y, unsigned int x)
						 printchar1602(unsigned char db, unsigned int y, unsigned int x)
						 确认了函数功能的实现	
最后完成时间：2014-01-29
作者： ATIME	版权所有
实例程序：
		#include <reg52.h>
		#include "atime_lcd1602.h"

		void main()
		{
			char db[10]={"A T I M E"};
			int_lcd1602(rightmove, cursornotdisplay);
			print1602(db, 2, 6);							//	可以引用数组
			print1602("EleVenPerfect", 1, 3);				//	可以引用字符串

			waitms(1000);
			while(set1602(right1602))
			waitms(1200);
		}

常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(13): warning C182: pointer to different objects  :将输出数据类型转为char型输出即可
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库后面即可
***************************************/

#ifndef _ATIME_LCD1602_H_ 
#define _ATIME_LCD1602_H_


/************************************
库全局变量组
***************************************/
#define DATA_LCD1602 P2  //定义lcd1602的8位数据口
sbit RS =P1^6;    //寄存器选择位，将RS位定义为P2.0引脚 ;1:数据；0：命令
sbit RW =P1^5;    //读写选择位，将RW位定义为P2.1引脚	  ;1:读取；0：写入
sbit EN =P1^4;    //使能信号位，将E位定义为P2.2引脚
sbit BF =P2^7;    //忙碌标志位，，将BF位定义为P0.7引脚 ;1:禁止；0：允许

enum set{clear1602, left1602, right1602 }; 			                              //枚举:设定参数 ，见186行注解
enum lcdint_ac{leftmove, rightmove, left_move, right_move };  				      //枚举:初始化AC移动方向 ，见135行注解
enum lcdint_cursor{notdisplay, cursornotdisplay, cursorflash, cursornotflash };    //枚举:初始化光标状态	  ，见143行注解

/************************************
函数功能：延时大约n 毫秒ms
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
***************************************/
void waitms(unsigned int n)
{
	int i;
	while(n--)
	{
		for(i=0; i<580; i++)		  //89系列选择75,12系列选择750
		{
			;
		}	
	}
}




/**************************************
函数功能：lcd1602忙检测
传递参数：空
返回值：1：忙；0：不忙
***************************************/
unsigned char mang(void)
{
	unsigned char result;
	RS =0;
	RW =1;
	EN =1;
	waitms(1);
	result =BF;
	EN =0;
	return (result);		
}


/************************************
函数功能：写数据1bit
传递参数：db 数据指令内容
返回值：空
***************************************/
void writedata(char db)
{
	while(mang()==1);
	RS =1;
	RW =0;
	EN =0;
	DATA_LCD1602 =db;
	waitms(1);
	EN =1;
	waitms(1);
	EN =0;
}




/************************************
函数功能：写指令1bit
传递参数：db  数据指令内容
返回值：空
***************************************/
void writezhi(unsigned char db)
{
	while(mang()==1);
	RS =0;
	RW =0;
	EN =0;
	DATA_LCD1602 =db;
	waitms(1);
	EN =1;
	waitms(1);
	EN =0;
}



/************************************
函数功能：设置1602
传递参数：a:
			clear1602: 清屏
			left1602 : 左移
			right1602: 右移

返回值：1：成功；：失败0；
***************************************/
unsigned char set1602(enum set a )
{
	switch(a)
	{
		case clear1602 : writezhi(0x01);  break;
		case left1602  : writezhi(0x18);  break;
		case right1602 : writezhi(0x1C);  break;
		default :return (0);
	}
	EX0 =1;
	return (1);
}




/************************************
函数功能：并行初始化lcd1602
传递参数：a:光标移动设置 ，详见a的注释
		  b:开关光标显示 ，详见b的注释
返回值：1：成功；：失败0；
***************************************/
unsigned char int_lcd1602(enum lcdint_ac a,enum lcdint_cursor b)
{
	writezhi(0x01);
	waitms(15);
    RS =0;
	EN =0;
	DATA_LCD1602 =0X38;
	waitms(1);
	EN =1;
	waitms(5);
	EN =0;
	DATA_LCD1602 =0X38;
	waitms(1);
	EN =1;
	waitms(5);
	EN =0;
	DATA_LCD1602 =0X38;
	waitms(1);
	EN =1;
	waitms(5);
	writezhi(0x01);
	switch(a)
	{
		case rightmove  : writezhi(0x06);  break;	  //画面不动，读写后AC自动+1
		case leftmove   : writezhi(0x04);  break;	  //画面不动，读写后AC自动-1
		case right_move : writezhi(0x07);  break;	  //画面向左平移1次，读写后AC自动+1
		case left_move  : writezhi(0x05);  break;	  //画面向右平移1次，读写后AC自动-1
		default : return (0);				     	  // 错误
	}
	switch(b)
	{
		case cursornotflash   : writezhi(0x0e);  break;	  //画面显示，光标显示，光标不闪动
		case cursorflash      : writezhi(0x0d);  break;	  //画面显示，光标显示，光标闪动
		case cursornotdisplay : writezhi(0x0c);  break;	  //画面显示，光标不显示，光标不闪动
		case notdisplay       : writezhi(0x08);  break;	  //画面不显示，光标不显示，光标不闪动
		default : return (0);					          // 错误
	}
	set1602(clear1602);
	return (1);
}




/************************************
函数功能：测试字符串长度
传递参数：字符串指针
返回值：字符串长度
***************************************/
unsigned int str_long(unsigned char db[])
{
	unsigned int i;
	for(i =0; db[i] !=0; i++) ;
	return (i);
}



/************************************
函数功能：显示数据、字母
传递参数：db[] : 显示的数据 
		  x:	 横向坐标
		  y:	 纵向坐标
		  坐标系左上角为（0,0）点向右向下为正
返回值：1：成功；：失败0；
特别注意：此函数只可以显示字符串、字符串数组，不可以显示单个字符
***************************************/
unsigned char print1602(unsigned char db[], unsigned int y, unsigned int x)
{
	unsigned int i; 
	writezhi (0x80 + 0x40*y + x );
	for(i=0; i< str_long(db); i++)		 //修改了判断字符串长度方式	由shrlen改为自定义的str_long
	{
		writedata(db[i]);
	}
	return (1);
}


/************************************
函数功能：设置自定义字符
传递参数：
		  i:设置的自定义字符标号
		  a[]:定义字符的数组数据
返回值：空
特别注意：i的取值：0~7；
显示自定义字符方法：
		用printchar1602函数，数据位写之前定义的字符标号即可
		如：printchar1602(0,2,1);
***************************************/
void setpic1602(unsigned char i, unsigned char a[])
{
	unsigned j;
	writezhi((0x40+0x08*i));
	waitms(5);
	for(j=0; j<8; j++)
	{	
		writedata(a[j]);
		waitms(1);	
	}				
}
		

/************************************
函数功能：显示数据、字母
传递参数：db : 显示的数据 
		  x:	 横向坐标
		  y:	 纵向坐标
		  坐标系左上角为（1,1）点向右向下为正
返回值：1：成功；：失败0；
特别注意：此函数只可以显示单个字符
***************************************/
unsigned char printchar1602(unsigned char db, unsigned int y, unsigned int x)
{
	writezhi (0x80 + 0x40*y + x);
	writedata(db);
	return (1);
}

/************************************
函数功能：1位BCD码转换3位可显示数字
传递参数：a[]，BCD数据;b[]，可显示数据
返回值：空
***************************************/
void bcd_trans_char(unsigned char a[], unsigned char b[],unsigned char j)
{
	unsigned int i;
	for(i=0; i<j; i++)
	{
		b[3*i] =a[i]/100+0x30;
		b[3*i+1] =(a[i]%100)/10+0x30;
		b[3*i+2] =(a[i]%10)+0x30;
	}
}

/************************************
函数功能：清屏行前十个位置
传递参数：行
返回值：空
***************************************/
void clear1602_10(unsigned int x)
{
	print1602("          ",x,0);	
}

#endif	