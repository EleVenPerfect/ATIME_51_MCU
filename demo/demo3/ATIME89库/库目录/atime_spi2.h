/************************************
库功能：通用SPI接口库含位定义版
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
最后修改时间：2014-03-26
作者：光芒 版权所有
实例程序：
常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
***************************************/

#ifndef _ATIME_SPI2_H_ 
#define _ATIME_SPI2_H_

/************************************
库全局变量组
***************************************/
sbit SPI_CS   =P1^4;
sbit SPI_MOSI =P1^5; 
sbit SPI_SCLK =P1^6;   
sbit SPI_MISO =P1^7; 


unsigned char bdata dat;
sbit dat7=dat^7;
sbit dat6=dat^6;
sbit dat5=dat^5;
sbit dat4=dat^4;
sbit dat3=dat^3;
sbit dat2=dat^2;
sbit dat1=dat^1;
sbit dat0=dat^0;


/************************************
函数功能：延时
传递参数：time：延时
返回值：空
***************************************/
void sd_delay(unsigned char time) 
{
while(time--);
}


/************************************
函数功能：向SPI低速速写一字节数据或指令
传递参数：a：要发送的数据
返回值：空
***************************************/
void spi_write_char_low(unsigned char w_dat)
{
 dat=w_dat; 
 SPI_MOSI=dat7;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat6;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat5;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat4;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat3;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat2;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat1;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat0;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
}


/************************************
函数功能：向SPI高速速写一字节数据或指令
传递参数：a：要发送的数据
返回值：空
***************************************/
void spi_write_char_high(unsigned char w_dat) 
{
 dat=w_dat; 
 SPI_MOSI=dat7;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat6;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat5;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat4;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat3;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat2;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat1;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat0;SPI_SCLK=0;SPI_SCLK=1;
}


/************************************
函数功能：向SPI低速速读一字节数据或指令
传递参数：a：要发送的数据
返回值：空
***************************************/
unsigned char spi_read_char_low(void)
{
 SPI_MISO=1;
 SPI_SCLK=1;SPI_SCLK=0;dat7=SPI_MISO;sd_delay(200); 
 SPI_SCLK=1;SPI_SCLK=0;dat6=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat5=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat4=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat3=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat2=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat1=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat0=SPI_MISO;sd_delay(200);
 return (dat);
}


/************************************
函数功能：向SPI高速读一字节数据或指令
传递参数：a：要发送的数据
返回值：空
***************************************/
unsigned char spi_read_char_high(void)
{  
 SPI_MISO=1;
 SPI_SCLK=1;SPI_SCLK=0;dat7=SPI_MISO; 
 SPI_SCLK=1;SPI_SCLK=0;dat6=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat5=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat4=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat3=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat2=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat1=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat0=SPI_MISO;
 return (dat);
}

#endif

