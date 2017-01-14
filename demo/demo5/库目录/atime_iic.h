/************************************
库功能：IIC通讯库
库要求：程序已经载入：
		#include "STC12C5A60S2.H"
应用函数：
		iic_write_char(unsigned char outside_address, unsigned char inside_address, unsigned char a)
		iic_read_char(unsigned char outside_address, unsigned char inside_address)
		iic_read_current_char(unsigned char outside_address)
		iic_read(unsigned char outside_address, unsigned char inside_address, unsigned int n, unsigned char a[])
修改历史：
		   	 ‘修改人’   	‘修改内容’  	 		‘修改时间’
			  ATIME		 增加iic_read函数	 		2014-02-09
			  ATIME		 修改函数					2014-05-01
			  			 iic_read(）
			  			 修改函数对STC12系列的兼容性
最后修改时间：2014-02-08
作者： ATIME	版权所有
实例程序：
***************************************************************
				24C08操作实例：当存储数据在0-Z时，直接引用eepROM数据否则清‘0’。
				#include <reg52.h>
				#include "atime_iic.h"
				#include "atime_lcd1602.h"
				
				void main()
				{
					unsigned char i =0x05;
					int_lcd1602(rightmove, cursornotdisplay);
					i =iic_read_char(0xa0,2);
					if(i <0x30)
						i =0x30;
					else 
						if(i >0x5a)
							i =0x30;
					while(1)
					{
						printchar1602(i, 1, 6);
						waitms(1000);
						i++;
						iic_write_char(0xa0,2,i);
					}
				}
************************************************************
				PCF8591操作实例：AD转换，显示出转换出的char结果
				注：由于PCF8591内部转换时序，当前读取的数据是之前通道AD转换的结果。
				存在问题：第一组数据是错位的，第一位数据偶尔会和第四位数据相同值。
				#include <reg52.h>
				#include "atime_lcd1602.h"
				#include "atime_iic.h"
				
				
				
				void main()
				{
					unsigned char a[5],b[15];
					a[4] =0x00;
					int_lcd1602(rightmove, cursornotdisplay);
					while(1)
					{
						iic_read(0x90,0x44,4,a) ;
				
						bcd_trans_char(a,b,4);
						print1602(b,2,1);
						waitms(500);
					}
				} 
************************************************************
常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注：不连续的读写操作中间最好延时
	内部地址为00H~FFH
    PCF8591建议在6M晶振下运行，否则IIC时序会出问题导致读取结果错乱，此现象尚未查明原因。
***************************************/


#ifndef _ATIME_IIC_H_ 
#define _ATIME_IIC_H_


/************************************
库全局变量组
***************************************/

sbit SCL =P1^7;            //串行时钟总线SCL位
sbit SDA =P1^6; 		   //串行数据总线SDA位

/************************************
函数功能：延时大约n 毫秒us
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
***************************************/
void wait_iicbus()
{
	int i;
	for(i=0; i<10; i++)
	{
		;
	}	
	
}


/************************************
函数功能：IIC开始标志
传递参数：空
返回值：空
***************************************/
void iic_start(void)
{
	SDA =1;
	wait_iicbus();
	SCL =1;
	wait_iicbus();
	SDA =0;
	wait_iicbus();
	SCL =0;
	wait_iicbus();
}


/************************************
函数功能：IIC终止标志
传递参数：空
返回值：空
***************************************/
void iic_stop(void)
{
	SDA =0;
	wait_iicbus();
	SCL =1;
	wait_iicbus();
	SDA =1;
	wait_iicbus();
	SCL =1;
	wait_iicbus();
}


/************************************
函数功能：IIC应答识别
传递参数：空
返回值：0：正确传输； 1：错误传输
***************************************/
bit iic_ask_judge(void)
{
	bit ask;
	SCL =0;
	wait_iicbus();
	SDA =1;
	wait_iicbus();
	SCL =1;
	wait_iicbus();
	ask =SDA;
	SCL =0;
	wait_iicbus();
	return (ask);
}



/************************************
函数功能：收到数据的IIC应答
传递参数：空
返回值：空
***************************************/
void iic_ask_receive(void)
{
	unsigned char i;
	SDA =0;
	wait_iicbus();
	SCL =1;
	for(i=0; i<1; i++);
	SCL =0;
	wait_iicbus();
	SDA =1;
	wait_iicbus();
}


/************************************
函数功能：收到数据的IIC非应答
传递参数：空
返回值：空
***************************************/
void iic_ask_not_receive(void)
{
	unsigned char i;
	SDA =1;
	wait_iicbus();
	SCL =1;
	for(i =0; i<1; i++);
	SCL =0;
	wait_iicbus();
	SDA =0;
	wait_iicbus();
}




/************************************
函数功能：IIC 发送一个字符数或指令
传递参数：a：待发送数据
返回值：空
***************************************/
void iic_writeachar(unsigned char a)
{
	unsigned char i;

	SCL =0;
	for(i =0; i<=7; i++)
	{
		SDA =(bit)(a&0x80);
		wait_iicbus();
		SCL =1;
		wait_iicbus();
		SCL =0;
		wait_iicbus();
		a =a<<1;
	}
}



/************************************
函数功能：从IIC读取一个字符数据或指令
传递参数：空
返回值：读取的数据或指令
***************************************/
unsigned char iic_readachar(void)
{
	unsigned char i, a;

	SCL =0;
	wait_iicbus();
	for(i=0; i<=7; i++)
	{
		SCL =1;
		wait_iicbus();
		a =a<<1;
		a |=(unsigned char)SDA;
		SCL =0;
		wait_iicbus();	
	}
	return (a);
}


/************************************
函数功能：向指定IIC芯片内指定芯片内地址发送数据
传递参数：
		  outside_address：片选地址
		  inside_address ：片内地址
		  a				 ：待发送数据
返回值：0:成功  1:失败
***************************************/
bit iic_write_char(unsigned char outside_address, unsigned char inside_address, unsigned char a)
{
	bit ok =1;
	iic_start();
	iic_writeachar(outside_address&0xfe);
	if(iic_ask_judge()==0)
	{
		iic_writeachar(inside_address);
		if(iic_ask_judge()==0)
		{
			iic_writeachar(a);
			if(iic_ask_judge()==0)
			{
				iic_stop();
				ok =0;
			}
		}
	}
	return (ok);	
}



/************************************
函数功能：从指定芯片指定地址读取一字节数据
传递参数：
		  outside_address：片选地址
		  inside_address ：片内地址
返回值：a：读取的数据
注：如果返回值总是“E”则读取过程错误
***************************************/
unsigned char iic_read_char(unsigned char outside_address, unsigned char inside_address)
{
	unsigned char a =0x45;

	iic_start();
	iic_writeachar(outside_address&0xfe);
	if(iic_ask_judge()==0)
	{
		iic_writeachar(inside_address);
		if(iic_ask_judge()==0)
		{
			iic_start();
			iic_writeachar(outside_address|0x01);
			if(iic_ask_judge()==0)
			{
				a =iic_readachar();
				iic_stop();
			}
		}
	}
	return (a);			
}


/************************************
函数功能：读取指定芯片当前地址一字节数据
传递参数：outside_address：片选地址
返回值：a：读取的数据
注：地址计数器内容为最后操作字节的地址加 1也就是说如果上次读/写
的操作地址为N 则立即读的地址从地址N+1开始
***************************************/
unsigned char iic_read_current_char(unsigned char outside_address)
{
	unsigned char a;
	iic_start();
	iic_writeachar(outside_address|0x01);
    if(iic_ask_judge()==0)
	{
		a =iic_readachar();
    	iic_stop();
	}
	return (a);	
}


/************************************
函数功能：读取n个数据
传递参数：
		  outside_address：片选地址
		  inside_address ：片内地址
		  n：	读取的字节数
		  a[]：读取的数据数组
返回值：用数组a返回数据
注：适用于支持连续读取的芯片，要知道将要收到多少数据
***************************************/
void iic_read(unsigned char outside_address, unsigned char inside_address, unsigned int n, unsigned char a[])
{
	unsigned char temp;
	unsigned int i =0;
	SCL =0;
	iic_stop();
	iic_start();
	iic_writeachar(outside_address&0xfe);		   //伪写，将操作地址指向目标位置
	if(iic_ask_judge()==0)
	{
		iic_writeachar(inside_address);
		if(iic_ask_judge()==0)
		{											
			iic_start();
			iic_writeachar(outside_address|0x01);  //写要读取的地址 
			if(iic_ask_judge()==0)
			{
				i =0;
				while(i <n-1)
				{
					temp =iic_readachar();
					a[i++] =temp;
				    iic_ask_receive();			  //收到数据作出应答
				}
				temp =iic_readachar();			  //最后一次读取不需要应答
				a[i++] =temp;
				iic_ask_not_receive();
			}
			iic_stop();
		}	
	}		
}




#endif