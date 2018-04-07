/************************************
库功能：硬件SPI接口库 BETA
库要求：程序已经载入：
		#include "STC12C5A60S2.H"
应用函数：
		 unsigned char spi_hardware_init( enum spi_enable a, enum spi_first b, unsigned char t, enum spi_first d)
		 void spi_send_char( unsigned char temp)
		 unsigned char spi_wr_char(unsigned char temp)
		 void spi_main(enum spi_enable a) 
		 void spi_interrupt(void) interrupt 9   ##SPI中断服务函数 
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-04-26
作者： ATIME	版权所有
实例程序：
			#include "STC12C5A60S2.H" 	
			#include "atime_lcd1602.h"
			#include "atime_spi_hardware.h"
			
			
								  
			void main()
			{
				unsigned char temp =0xaa;
				int_lcd1602(rightmove, cursornotdisplay);
				spi_hardware_init( spi_enable, spi_high, 3, spi_low);
				
				print1602("ATIME", 0, 3);
				spi_main(spi_enable);
				spi_send_char(0x01);
				spi_send_char(0x01);
				spi_send_char(0x01);
				spi_send_char(0x01);
				while(1);
			}
			中断程序：
			char i=0x30;
			void spi_interrupt(void) interrupt 9
			{
				SPSTAT =0XC0;		//清空标志位，此句要保留
				i++;
				printchar1602(i, 1, 3);
				waitms(500);
				set1602(clear1602);
			}

常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
说明：此函数库是硬件SPI函数库，仅支持STC12系列带有硬件SPI功能的单片机，本程序在STC12C5A60S2上测试，不能保证在其他平台上可靠。
	  程序目前尚未进行实际芯片测试，不能保证正确性。
***************************************/


#ifndef _ATIME_SPI_HARDWARE_H_ 
#define _ATIME_SPI_HARDWARE_H_


/************************************
库全局变量组
***************************************/
 
enum spi_enable{ spi_enable, spi_disable}; //SPI开关
enum spi_first{ spi_high, spi_low};		   //SPI高低位设置

/************************************
函数功能：SPI初始化
传递参数：
		a：SPI启动、关闭选择
		b：SPI数据发送顺序控制
		d：SPI空闲时高低电平控制
		t：SPI速度选择：1/4	；1/16；1/64；1/128	四种
				对应： 	 0  ； 1  ；  2	；  3
返回值：0：失败
		1：成功
***************************************/
unsigned char spi_hardware_init( enum spi_enable a, enum spi_first b, unsigned char t, enum spi_first d)
{
	unsigned char temp;
	temp =0x94;						//默认设置SS引脚作为I/O口使用，不作为片选信号
	if(a == spi_enable)
		temp |=0x40;
	if(b == spi_low)
		temp |=0x20;
	if(d == spi_high)
		temp |=0x08;
	if(t > 3 || t < 0)
		return (0);
	temp +=t;
	SPCTL =temp;
	return (1);		
}

/************************************
函数功能：SPI发送数据
传递参数：temp：待发送数据
返回值：空
***************************************/
void spi_send_char( unsigned char temp)
{
	SPSTAT =0xC0;
	SPDAT =temp;
	while(!(SPSTAT & 0x80));
	SPSTAT =0xC0;	
}


/************************************
函数功能：SPI写入并读取数据
传递参数：写入
返回值：待接收数据
***************************************/
unsigned char spi_wr_char(unsigned char temp)
{
	SPSTAT =0XC0;
	SPDAT =temp;
	while(!(SPSTAT & 0X80));
	temp =SPDAT;
	SPSTAT =0XC0;
	return (temp);	
}


/************************************
函数功能：SPI中断开关
传递参数：开关状态
			spi_enable,spi_disable
返回值：空
***************************************/
void spi_main(enum spi_enable a) 
{
	if(a == spi_enable)
	{
		EA =1;
		IE2 |=0X02;
	} 
	if(a == spi_disable)
	{
		EA =0;
		IE2 &=0XFD;
	}
}

/************************************
函数功能：SPI中断函数
传递参数：空
返回值：空
***************************************/
void spi_interrupt(void) interrupt 9
{
	SPSTAT =0XC0;		//清空标志位，此句要保留

}									  

#endif