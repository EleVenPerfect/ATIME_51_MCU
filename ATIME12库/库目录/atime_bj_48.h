/************************************
库功能：四相八拍步进电机库
库要求：程序已经载入：
		#include <reg52.h>
应用函数：
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：
作者： ATIME	版权所有
实例程序：
常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注：不连续的读写操作中间最好延时
	内部地址为00H~FFH
***************************************/


#ifndef _ATIME_BJ_48_H_ 
#define _ATIME_BJ_48_H_


/************************************
库全局变量组
***************************************/

unsigned char ZZ[8]={0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09}; //转动编码
sbit BJA =P1^0;					   //定义接口A
sbit BJB =P1^1;					   //定义接口B
sbit BJC =P1^2;					   //定义接口C
sbit BJD =P1^3;					   //定义接口D

/************************************
函数功能：延时大约n*50微秒us
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
**************************************
void byj_us(unsigned int n)
{
	unsigned char i;
	while(n--)
		for(i=0; i<2; i++);	
}
								*/

/************************************
函数功能：延时大约n 毫秒ms
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
***************************************/
void wait_byj_ms(unsigned int n)
{
	int i;
	while(n--)
	{
		for(i=0; i<75; i++)
		{
			;
		}	
	}
}

/************************************
函数功能：步进电机进行一次正转
传递参数：空
返回值：空
***************************************/
void motor_byj_zz(unsigned int t)
{
	unsigned char i;
	for(i=8; i>0; i--)
	{
		BJA =(bit)((ZZ[i]&0x08)>>3);
		BJB =(bit)((ZZ[i]&0x04)>>2);
		BJC =(bit)((ZZ[i]&0x02)>>1);
		BJD =(bit)(ZZ[i]&0x01);	
		wait_byj_ms(t);
	}
}

/************************************
函数功能：步进电机进行一次反转
传递参数：空
返回值：空
***************************************/
void motor_byj_fz(unsigned int t)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
		BJA =(bit)((ZZ[i]&0x08)>>3);
		BJB =(bit)((ZZ[i]&0x04)>>2);
		BJC =(bit)((ZZ[i]&0x02)>>1);
		BJD =(bit)(ZZ[i]&0x01);		
		wait_byj_ms(t);
	}
}


#endif
