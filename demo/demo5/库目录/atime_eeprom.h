/************************************
库功能：12单片机EEPROM库
库要求：主函数中已定义：
		#include "STC15F2K60S2.H" 
应用函数：	
修改历史：
		   	 ‘修改人’   ‘修改内容’  	‘修改时间’
			   空			空				空
最后修改时间：2014-04-29
作者： ATIME	版权所有
实例程序：
		#include "STC15F2K60S2.H" 
		#include "atime_eeprom.h"
		#include "atime_lcd1602.h"
		
		void main()
		{
				unsigned char i, j;
				int_lcd1602(rightmove, cursornotdisplay);
				i =eeprom_write( 0x00, 0x00, 0xff);
				j =eeprom_read( 0x00, 0x00);
				printint1602( i, 0, 1);
				printint1602( j, 1, 1);
				while(1);
		}


常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
***************************************/


#ifndef _ATIME_EEPROM_H_ 
#define _ATIME_EEPROM_H_


/************************************
库全局变量组
***************************************/
#define EEPROM_RW_FAIL	  0X00		//EEPROM操作错误
#define EEPROM_RW_SUCCESS 0X01		//EEPROM操作成功

/************************************
函数功能：写入EEPROM数据
传递参数：
返回值：EEPROM_RW_FAIL	 ：失败；
		EEPROM_RW_SUCCESS；成功；	
***************************************/
unsigned char eeprom_write( unsigned char addh, unsigned char addl, unsigned char temp)
{
	IAP_CONTR =0X80;
	IAP_ADDRL =addl;
	IAP_ADDRH =addh;
	IAP_DATA =temp;
	IAP_CMD =0X02;
	IAP_TRIG =0X5A;
	IAP_TRIG =0X5A;
	if((bit)((IAP_CONTR&0x10)>>4) ==1)	  //判断是否成功写入
	{
		IAP_CONTR =0X80;
		return (EEPROM_RW_FAIL);
	}
	return (EEPROM_RW_SUCCESS);
}

/************************************
函数功能：读取EEPROM数据
传递参数：
返回值：	
***************************************/
unsigned char eeprom_read( unsigned char addh, unsigned char addl)
{
	unsigned char temp;
	IAP_CONTR =0X80;
	IAP_ADDRL =addl;
	IAP_ADDRH =addh;
	IAP_CMD =0X01;
	IAP_TRIG =0X5A;
	IAP_TRIG =0X5A;
	if((bit)((IAP_CONTR&0x10)>>4) ==1)	  //判断是否成功读取成功
	{
		IAP_CONTR =0X80;
		return (EEPROM_RW_FAIL);						  //返回值为0可能是读取失败
	}
	temp =IAP_DATA;
	return (temp);
}




#endif