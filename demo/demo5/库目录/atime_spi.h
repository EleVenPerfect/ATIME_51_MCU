/************************************
库功能：通用SPI接口库
库要求：程序已经载入：
		#include <reg52.h>
应用函数：
		 spi_write_char_high(unsigned char a)
		 spi_write_char_low(unsigned char a)
		 spi_read_char_high(void)
		 spi_read_char_low(void)
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-02-21
作者： ATIME	版权所有
实例程序：
常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
***************************************/


#ifndef _ATIME_SPI_H_ 
#define _ATIME_SPI_H_


/************************************
库全局变量组
***************************************/
 
sbit SPI_CS   =P1^4;
sbit SPI_MOSI =P1^5;
sbit SPI_SCLK =P1^6;
sbit SPI_MISO =P1^7;	  

/************************************
函数功能：向SPI高速速写一字节数据或指令
传递参数：a：要发送的数据
返回值：空
***************************************/
void spi_write_char_high(unsigned char a)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
		SPI_MOSI =(bit)(a&0x80);
		SPI_SCLK =0;
		SPI_SCLK =1;
		a =a<<1;
	}		
}

/************************************
函数功能：向SPI低速速写一字节数据或指令
传递参数：a：要发送的数据
返回值：空
***************************************/
void spi_write_char_low(unsigned char a)
{
	unsigned char i,j;
	j =200;
	while(j--);
	for(i=0; i<8; i++)
	{
		SPI_MOSI =(bit)(a&0x80);
		SPI_SCLK =0;
		SPI_SCLK =1;
		a =a<<1;
		j =200;
		while(j--);
	}	
}

/************************************
函数功能：由SPI低速读取一个字节数据
传递参数：空
返回值：读出的结果
***************************************/
unsigned char spi_read_char_low(void)
{
	unsigned char i,j,a;
	j =200;
	while(j--);
	SPI_MISO =1;
	for(i=0; i<8; i++)
	{
		a =a<<1;
		SPI_SCLK =1;
		SPI_SCLK =0;
		if(SPI_MISO ==1)
			a =a|0x01;
		j =200;
		while(j--);	
	}
	return (a);
}


/************************************
函数功能：由SPI高速读取一个字节数据
传递参数：空
返回值：读出的结果
***************************************/
unsigned char spi_read_char_high(void)
{
	unsigned char i,a;
	SPI_MISO =1;
	for(i=0; i<8; i++)
	{
		a =a<<1;
		SPI_SCLK =1;
		SPI_SCLK =0;
		if(SPI_MISO ==1)
			a =a|0x01;
	}
	return (a);	   
}




#endif