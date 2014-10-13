/************************************
库功能：IIC通讯库
库要求：程序已经载入：
		#include <reg52.h>
应用函数：
		iic_write_char(unsigned char outside_address, unsigned char inside_address, unsigned char a)
		iic_read_char(unsigned char outside_address, unsigned char inside_address)
		iic_read_current_char(unsigned char outside_address)
		iic_read(unsigned char outside_address, unsigned char inside_address, unsigned int n, unsigned char a[])
修改历史：
		   	 ‘修改人’   ‘修改内容’  		‘修改时间’
			   ATIME	增加iic_read函数	 2014-02-09
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
***************************************/


#ifndef _ATIME_IIC_H_ 
#define _ATIME_IIC_H_


/************************************
库全局变量组
***************************************/

sbit SCL =P3^4;            //串行时钟总线SCL位
sbit SDA =P3^5; 		   //串行数据总线SDA位

/************************************
函数功能：IIC开始标志
传递参数：空
返回值：空
***************************************/
void iic_start(void)
{
	unsigned char i;
	SDA =1;
	SCL =1;
	for(i =0; i<1; i++);
	SDA =0;
	for(i =0; i<1; i++);
	SCL =0;
}


/************************************
函数功能：IIC终止标志
传递参数：空
返回值：空
***************************************/
void iic_stop(void)
{
	unsigned char i;
	SDA =0;
	SCL =1;
	for(i =0; i<1; i++);
	SDA =1;
	for(i =0; i<1; i++);
	SCL =0;
}


/************************************
函数功能：IIC应答识别
传递参数：空
返回值：0：正确传输； 1：错误传输
***************************************/
bit iic_ask_judge(void)
{
	bit ask;
	unsigned char i;
	SDA =1;
	;
	;
	SCL =1;
	for(i =0; i<1; i++);
	ask =SDA;
	SCL =0;
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
	SCL =1;
	for(i=0; i<1; i++);
	SCL =0;
	SDA =1;
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
	SCL =1;
	for(i =0; i<1; i++);
	SCL =0;
	SDA =0;
}




/************************************
函数功能：IIC 发送一个字符数或指令
传递参数：a：待发送数据
返回值：空
***************************************/
void iic_writeachar(unsigned char a)
{
	unsigned char i;
	for(i =0; i<=7; i++)
	{
		SDA =(bit)(a&0x80);
		;
		SCL =1;
		;
		;
		SCL =0;
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
	for(i=0; i<=7; i++)
	{
		SCL =1;
		a =a<<1;
		a |=(unsigned char)SDA;
		SCL =0;	
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
	unsigned char i;
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
	for(i=0; i<75; i++);
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