/************************************
库功能：异步串口通讯库
库要求：主函数中已定义：
		#include <reg52.h>
		#include "atime_interrupt.c"
应用函数：
		 send_char(unsigned char a)
		 send_serial(unsigned char a[])
		 receive_char(void)
		 serial_int(enum serial_receive a, enum serial_baud_rate b, enum serial_receive c)
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
			  ATIME		串口初始化	2014-03-26
			  			解决了SD卡读写进入串口中断的BUG，SD卡读写仍然需要禁止接受串口
最后修改时间：2014-02-03
作者： ATIME	版权所有
实例程序：
		#include <reg52.h>
		#include <string.h>
		#include "atime_lcd1602.h"
		#include "atime_serial.h"
		#include "atime_interrupt.c"
		
		void main()
		{
			int_lcd1602(rightmove, cursornotdisplay);
			serial_int(enable, baud14400, disable);
			print1602("EleVenPerfect", 2, 3);
			while(1);
		}

		中断服务程序
		void interrupt_serial(void) interrupt 4
		{
			unsigned char k;
			k =receive_char();
			printchar1602(k , 1, 3);
			send_char(k);
		}	

常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注：本串口不适合于SPI—SD卡读写测试，存在问题
***************************************/


#ifndef _ATIME_SERIAL_H_ 
#define _ATIME_SERIAL_H_


/************************************
库全局变量组
***************************************/

enum serial_receive{ enable, disable};
enum serial_baud_rate{ baud28800, baud38400, baud9600, baud14400, baud7200, baud4800, baud2400, baud1200, baud600, baud300};




/************************************
函数功能：串口发送一个字符
传递参数：a：待发送字符
返回值：空	
***************************************/
void send_char(unsigned char a)
{
	SBUF =a;
	while(TI ==0);
	TI =0;
}



/************************************
函数功能：串口发送字符串
传递参数：a：待发送字符串
返回值：空	
***************************************/
void send_serial(unsigned char a[])
{
	unsigned int i=0;
	for(i=0; a[i]!=0x00; i++)
		send_char(a[i]);
}



/************************************
函数功能：串口接受字符
传递参数：空
返回值：接受的字符	
注意：返回值为无符号char型
***************************************/
unsigned char receive_char(void)
{
	unsigned char i=' ';
	if(RI ==1)
	{
		RI =0;
		i =SBUF;
	}
	return (i);
}



/************************************
函数功能：初始化串口通信
传递参数：
			a:接受允许
			b：波特率
			c：波特率加倍
返回值：空	
***************************************/
void serial_int(enum serial_receive a, enum serial_baud_rate b, enum serial_receive c)
{
	TMOD =TMOD|0X20;
	switch(b)
	{
		case baud28800 : TL1 =TH1 =0XFF; break;			   //0%	误差
		case baud38400 : TL1 =TH1 =0XFF; break;			   //25%误差
		case baud14400 : TL1 =TH1 =0XFE; break;			   //0%	误差
		case baud9600  : TL1 =TH1 =0XFD; break;			   //0%	误差
		case baud7200  : TL1 =TH1 =0XFC; break;			   //0%	误差
		case baud4800  : TL1 =TH1 =0XFA; break;			   //0%	误差
		case baud2400  : TL1 =TH1 =0XF4; break;			   //0%	误差
		case baud1200  : TL1 =TH1 =0XE8; break;			   //0%	误差
		case baud600   : TL1 =TH1 =0XD0; break;			   //0%	误差
		case baud300   : TL1 =TH1 =0XA0; break;			   //0%	误差
		
		default  :break;	
	}
	TR1 =1;
	ET1 =0;
	EA  =1;
	SM0 =0;
	SM1 =1;
	if(a ==enable)
	{	
		REN =1;
		ES  =1;
	}
	else
	{
		REN =0;
		ES  =0;
	}
	if(c ==disable)
		PCON =0X00;
	else 
		PCON =0X80;
				
}



#endif