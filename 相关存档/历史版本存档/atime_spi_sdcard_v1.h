/************************************
库功能：SPI模式SD卡控制库
库要求：程序已经载入：
		#include <reg52.h>
应用函数：
		 sd_res(void)
		 sd_init(void)
		 sd_write512(unsigned long add, unsigned char a[])
		 sd_read512(unsigned long add, unsigned char a[])
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2012-02-21
作者： ATIME	版权所有
实例程序：
#include <reg52.h>
#include "atime_spi.h"
#include "atime_spi_sdcard.h"

unsigned char xdata buff[512];

/************************************
全局变量组
**************************************

enum serial_receive{ enable, disable};
enum serial_baud_rate{ baud28800, baud38400, baud9600, baud14400, baud7200, baud4800, baud2400, baud1200, baud600, baud300};

/************************************
函数功能：串口发送一个字符
传递参数：a：待发送字符
返回值：空	
**************************************
void send_char(unsigned char a)
{
	SBUF =a;
	while(TI ==0);
	TI =0;
}


/************************************
函数功能：初始化串口通信
传递参数：
			a:接受允许
			b：波特率
			c：波特率加倍
返回值：空	
**************************************
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
	ES =1;
	ET1 =0;
	EA =1;
	SM0 =0;
	SM1 =1;
	if(a ==enable)
		REN =1;
	else
		REN =0;
	if(c ==disable)
		PCON =0X00;
	else 
		PCON =0X80;				
}


void main(void)
{
	unsigned int i;
	serial_int(disable, baud9600, disable);
	for(i=0;i<100; i++);
	P0 =0X0F;
	sd_res();
	P0 =0X87;
	sd_init();
	P0 =0XC3;
//	sd_write512(3,buff);
	P0 =0XE1;

	sd_read512(3,buff);
	P0 =0X0F;
	for(i=0; i<512; i++)
		send_char(buff[i]);
	while(1);
}



常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符

注：写入错误数据会时SD卡出现错误
	用winhex查看时应该选择物理磁盘而不是逻辑磁盘，测试时用的1G的卡，FAT默认格式。
存在问题：读取和写入只有前256位是正确的。
可能存在BUG
***************************************/

#ifndef _ATIME_SPI_SDCARD_H_ 
#define _ATIME_SPI_SDCARD_H_

/************************************
函数功能：低速发送命令
传递参数：空
返回值：应答
***************************************/
unsigned char sd_write_zhi_low(unsigned char a[])
{
	unsigned char i,temp;
	SPI_CS =1;
	spi_write_char_low(0xff);
	SPI_CS =0;
	for(i=0; i<6; i++)
		spi_write_char_low(a[i]);
	i =0;
	do
	{
	 	temp =spi_read_char_low();
		i++;
	}
	while((temp==0xff)&&(i<100));
	return (temp);
}

/************************************
函数功能：高速发送指令
传递参数：空
返回值：应答
***************************************/
unsigned char sd_write_zhi_high(unsigned char a[])
{
	unsigned char i,temp;
	SPI_CS =1;
	spi_write_char_high(0xff);
	SPI_CS =0;
	for(i=0; i<6; i++)
		spi_write_char_high(a[i]);
	i =0;
	do
	{
	 	temp =spi_read_char_high();
		i++;
	}
	while((temp==0xff)&&(i<100));
	return (temp);
}



/************************************
函数功能：复位SD卡
传递参数：空
返回值：0:成功;1:失败
***************************************/
unsigned char sd_res(void)
{
	unsigned char temp ,i;
	unsigned char zhiling[] ={0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
	SPI_CS =1;
	for(i=0; i<0x0f; i++)
	{
		spi_write_char_low(0xff);
	}
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_low(zhiling);
		i++;
		if(i >=100)
		{
			SPI_CS =1;
			return (0x01);
		}
	}
	while(temp!=0x01);
	SPI_CS =1;
	spi_write_char_low(0xff);
	return (0);
}



/************************************
函数功能：初始化SD卡
传递参数：空
返回值：0:成功;1:失败
***************************************/
unsigned char sd_init(void)
{
	unsigned char i,temp;
	unsigned char zhiling[] ={0x41, 0x00, 0x00, 0x00, 0x00, 0xff};
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_low(zhiling);
		i++;
		if(i >=200)
		{
			SPI_CS =1;
			return (0x02);
		}
	}
	while(temp !=0);
	SPI_CS =1;
	spi_write_char_low(0xff);
	return (0);
}

/************************************
函数功能：向SD卡某地址写入512字节数据
传递参数：add:地址   a[]：待写入数据
返回值：0:成功;1:失败
***************************************/
unsigned char sd_write512(unsigned long add, unsigned char a[])
{
	unsigned char temp;
	unsigned int i;
	unsigned char zhiling[] ={0x58, 0x00, 0x00, 0x00, 0x00, 0xff}; 
	add <<=9;
	zhiling[1]=((add&0xff000000)>>24); 	
 	zhiling[2]=((add&0x00ff0000)>>16);
 	zhiling[3]=((add&0x0000ff00)>>8);
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_high(zhiling);
		i++;
		if(i ==100)
		{
			SPI_CS =1;
			return (temp);
		}
	}
	while(temp !=0);
	for(i=0; i<100; i++)
		spi_read_char_high();
	spi_write_char_high(0xfe);
	for(i=0; i<0x200; i++)
		spi_write_char_high(a[i]);
	spi_write_char_high(0xff);
	spi_write_char_high(0xff);
	temp =spi_read_char_high();
	if(temp&0x1f !=0x05)	
	{
		SPI_CS =1;
		return (0x03);
	}
	while(spi_read_char_high()!=0xff);
	SPI_CS =1;
	spi_write_char_high(0xff);
	return (0);
}

/************************************
函数功能：向SD卡某地址读取512字节数据
传递参数：add:地址   a[]：待写入数据
返回值：0:成功;1:失败
***************************************/
unsigned char sd_read512(unsigned long add, unsigned char a[])
{
	unsigned int i;
	unsigned char temp;
	unsigned char zhiling[] ={0x51, 0x00, 0x00, 0x00, 0x00, 0xff}; 
	add <<=9;
	zhiling[1]=((add&0xff000000)>>24); 	
 	zhiling[2]=((add&0x00ff0000)>>16);
 	zhiling[3]=((add&0x0000ff00)>>8);
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_high(zhiling);
		i++;
		if(i ==100)
		{
			return (0x04);
		}
	}
	while(temp!=0);
	while(spi_read_char_high()!=0xfe);
	for(i=0; i<512; i++)
		a[i] =spi_read_char_high();
	spi_read_char_high();
	spi_read_char_high();
	SPI_CS =1;
	spi_write_char_high(0xff);
	return (0);
}


#endif