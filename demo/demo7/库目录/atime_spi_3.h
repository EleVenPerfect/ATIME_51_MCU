/************************************
库功能：SPI三线接口通用库
库要求：程序已经载入：
		#include <reg52.h>
		如果已经#include "atime_lcd1602.h"，则要在此之前#include "atime_spi.h" 否则报错。
应用函数：
		 spi_writeachar(unsigned char a)
		 spi_readachar(void)
		 spi_write_2char(unsigned char a ,unsigned char b)
		 spi_read_char(unsigned char a)

修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-02-09
作者： ATIME	版权所有
实例程序：
常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
***************************************/


#ifndef _ATIME_SPI_3_H_ 
#define _ATIME_SPI_3_H_


/************************************
库全局变量组
***************************************/
 
sbit SPI_CLK =P1^6;	 //位定义串行时钟接口位置
sbit SPI_DATA =P1^4;	 //位定义DATA接口位置
sbit SPI_SS =P1^5;	 //位定义从属选择接口位置

	  

/************************************
函数功能：向SPI写一字节数据或指令
传递参数：a：要发送的数据
返回值：空
***************************************/
void spi_writeachar(unsigned char a)
{
	unsigned char i,j;
	SPI_CLK =0;
	for(j=0; j<2; j++);
	for(i=0; i<8; i++)
	{
		SPI_DATA =a&0x01;
		for(j=0; j<2; j++);
		SPI_CLK =1;
		for(j=0; j<2; j++);
		SPI_CLK =0;
		a =a>>1;
	}	
}


/************************************
函数功能：由SPI读取一个字节数据
传递参数：空
返回值：读出的结果
***************************************/
unsigned char spi_readachar(void)
{
	unsigned char i,j,a;
	for(j=0; j<2; j++);
	for(i=0; i<8; i++)
	{
		a =a>>1;
		if(SPI_DATA ==1)
			a =a|0x80;
		SPI_CLK =1;
		for(j=0; j<2; j++);
		SPI_CLK =0;
		for(j=0; j<2; j++);	
	}
	return (a);
}



/************************************
函数功能：向SPI某一地址写入一字节数据
传递参数：a：地址  b：一字节数据
返回值：空
***************************************/
void spi_write_2char(unsigned char a ,unsigned char b)
{
	unsigned char j;
	SPI_SS =0;
	SPI_CLK =0;
	SPI_SS =1;
	for(j=0; j<2; j++);
	spi_writeachar(a);
	spi_writeachar(b);
	SPI_CLK =0;
	SPI_SS =0;
}


/************************************
函数功能：发送读取指令并读取内容
传递参数：a读取指令
返回值：temp：读取的数据
***************************************/
unsigned char spi_read_char(unsigned char a)
{
	unsigned char temp;
	SPI_SS =0;
	SPI_CLK =0;
	SPI_SS =1;
	spi_writeachar(a);
	temp =spi_readachar();
	SPI_CLK =1;
	SPI_SS =0;
	return (temp);
}


#endif