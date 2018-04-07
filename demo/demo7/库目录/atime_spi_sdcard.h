/************************************
库功能：SPI模式SD卡控制库
库要求：程序已经载入：
		#include <reg52.h>
		#include "atime_spi.h"    //建议使用此底层库，因为调试SD卡过程中用的都是这个SPI库。
应用函数：
		 unsigned char sd_res(void)
		 unsigned char sd_write512(unsigned long add, unsigned char a[])
		 unsigned char sd_read512(unsigned long add, unsigned char a[])
修改历史：
		   	 ‘修改人’   ‘修改内容’  		‘修改时间’
			  ATIME		解决STC89C52		2014-03-03
			  			只读前256位数据问题。
			  ATIME		解决了				2014-03-26
			  			xdata不可以初始化的问题
			  ATIME		修改函数			2014-03-26
			  			，增强可靠性
			  			sd_write512(unsigned long add, unsigned char a[])
		 				sd_read512(unsigned long add, unsigned char a[])
						不再需要使用 sd_init(void)，而是每次调用读写函数前都会运行sd_init(void)函数
			  ATIME		修改函数			2014-04-08
			  			注释掉不需要的部分
						sd_write512(unsigned long add, unsigned char a[])
		 				sd_read512(unsigned long add, unsigned char a[])
						注释掉了sd_init();	如有读取后不能写入，或反之，可以尝试解除注释
			  ATIME		删除无用的函数		2014-04-09
			  			unsigned char sd_init(void)
						初始化过程中不需要此过程。
最后修改时间：2012-02-21
作者： ATIME	版权所有
实例程序：
#include <reg52.h>
#include "atime_serial.h"
#include "atime_spi.h"
#include "atime_spi_sdcard.h"

unsigned char xdata buff[512]={
0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,
0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,
0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,
0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,
0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,
1
};
	 


void main(void)
{
	unsigned int i;
	P0 =0X0F;
	serial_int(disable, baud9600, disable);
	for(i=0;i<100; i++);
	P0 =0X87;
	sd_res();
	P0 =0XC3;
	sd_write512(3,buff);
	P0 =0XE1;
	

	sd_read512(3,buff);
	P0 =0X0F;

	for(i=0; i<512; i++)
	{
		send_char(buff[i]);
		send_char(i);
	}
	P0 =0X00;
	while(1);
}





常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符

注：SD卡刚刚复位完成后，串口无法发送数据，需要执行一些读写、初始化指令后才可以（此情况在STC12中曾经出现）。
	写入错误数据会时SD卡出现错误
	用winhex查看时应该选择物理磁盘而不是逻辑磁盘，测试时用的1G的卡，FAT默认格式。
存在问题：读取和写入只有前256位是正确的：
解决：STC89C52内部xdata只有256byte，只能存储256位，需要更换单片机。
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
**************************************/
unsigned char sd_init(void)
{
	unsigned char i,temp;
	unsigned char zhiling[] ={0x41, 0x00, 0x00, 0x00, 0x00, 0xff};
	SPI_CS =1;
	for(i=0; i<=9; i++)
		spi_write_char_low(0xff);
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
	while(temp !=0X00);
	SPI_CS =1;
	spi_write_char_low(0xff);
	return (0);
}			   			 ////MMC卡版本
/*
unsigned char sd_init(void)
{
	unsigned char i,temp;
	unsigned char zhiling[] ={0x77, 0x00, 0x00, 0x00, 0x00, 0xff};
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_low(zhiling);
		i++;
		if(i >=300)
		{
			SPI_CS =1;
			return (0x02);
		}
	}
	while(temp !=0X01);
	SPI_CS =1;
	spi_write_char_low(0xff);

	zhiling[0] =0x69;
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_low(zhiling);
		i++;
		if(i >=300)
		{
			SPI_CS =1;
			return (0x03);		 ///
		}
	}
	while(temp !=0X00);
	SPI_CS =1;
	spi_write_char_low(0xff);
	return (0);				
}						*///不可用版本

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
	sd_init();		   //有时可能会需要每次读写都进行初始化
	add <<=9;		   //addr = addr * 512	将块地址（扇区地址）转为字节地址 ［这里就限制了SD卡的最大容量为4G］
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
		spi_read_char_high();			//原来是读，现在改成了写
	spi_write_char_high(0xfe);
	for(i=0; i<512; i++)
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
	sd_init(); 				 //有时可能会需要每次读写都进行初始化
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