/************************************
库功能：DS1302时钟库（采用SPI三线接口）
库要求：程序已经载入：
		#include <reg52.h>
		如果已经#include "atime_lcd1602.h"，则要在此之前#include "atime_ds1302.h" 否则报错。
应用函数：
		 read1302(enum ds1302_address a)
		 setds1302(enum ds1302_address a,unsigned int b)
		 ele_mode(unsigned int i)
		 judge_pause(void)
修改历史：
		   	 ‘修改人’       ‘修改内容’  			‘修改时间’
			  ATIME		修改总线接口名称定义		2014-02-09
			  ATIME		删除无用的函数infrared_us(）	2014-02-09
			  ATIME		修改函数translate_print		2014-05-25
					增加数组结尾标志0x00
最后完成时间：2014-02-07
作者： ATIME	版权所有
实例程序：
			#include <reg52.h>
			#include "atime_ds1302.h"
			#include "atime_lcd1602.h"
			
			void main()
			{
				unsigned int i;
				unsigned char a[3];
				int_lcd1602(rightmove, cursornotdisplay);
				setds1302(second,0);
				setds1302(minute,42);
				setds1302(hour,19);
				setds1302(year,14);
				setds1302(month,2);
				setds1302(day,7);
				setds1302(weekday,5);
				ele_mode(1);
				while(1)
				{
					i =read1302(hour);
					translate_print(i,a);
					print1602(a,1,2);
				    
					i =read1302(minute);
					translate_print(i,a);
					print1602(a,1,5);
			
					i =read1302(second);
					translate_print(i,a);
					print1602(a,1,8);
			
					i =read1302(weekday);
					translate_print(i,a);
					print1602(a,1,14);
					print1602(" ",1,14);
			
					i =read1302(year);
					translate_print(i,a);
					print1602(a,2,3);
			
					i =read1302(month);
					translate_print(i,a);
					print1602(a,2,6);
			
					i =read1302(day);
					translate_print(i,a);
					print1602(a,2,9);
			
				}
			}

常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注意：本库函数默认24小时制
	  由于函数内部限制，年份范围为0~79
	  电源充电默认为2k电阻1个二极管	
	  需要其他选项可以通过readdate1302(unsigned char a)；
	  writedate1302(unsigned char a ,unsigned char b)自行设置
	  本函数库不依赖ATIME_SPI.H库函数，且与他相兼容
***************************************/


#ifndef _ATIME_DS1302_H_ 
#define _ATIME_DS1302_H_


/************************************
库全局变量组
***************************************/

sbit SCLK_DS1302 =P1^0;	 //位定义ds1302的SCLK接口位置
sbit DATA_DS1302 =P1^1;	 //位定义ds1302的DATA接口位置
sbit RES_DS1302  =P1^2;	 //位定义ds1302的RES 接口位置
enum ds1302_write_switch {on_1302, off_1302};			  //枚举写允许开关状态
enum ds1302_address{second, minute, hour, day, weekday, month, year};	   //枚举寄存器



/************************************
函数功能：向DS1302写一字节数据或指令
传递参数：a：要发送的数据
返回值：空
***************************************/
void writechar1302(unsigned char a)
{
	unsigned char i,j;
	SCLK_DS1302 =0;
	for(j=0; j<24; j++);
	for(i=0; i<8; i++)
	{
		DATA_DS1302 =a&0x01;
		for(j=0; j<24; j++);
		SCLK_DS1302 =1;
		for(j=0; j<24; j++);
		SCLK_DS1302 =0;
		a =a>>1;
		for(j=0; j<24; j++);
	}	
}




/************************************
函数功能：由ds1302读取一个字节数据
传递参数：空
返回值：读出的结果
***************************************/
unsigned char readchar1302(void)
{
	unsigned char i,j,a;
	for(j=0; j<24; j++);
	for(i=0; i<8; i++)
	{
		a =a>>1;
		if(DATA_DS1302 ==1)
			a =a|0x80;
		SCLK_DS1302 =1;
		for(j=0; j<24; j++);
		SCLK_DS1302 =0;
		for(j=0; j<24; j++);	
	}
	return (a);
}


/************************************
函数功能：向ds1302发出指令代码和指令内容
传递参数：a：指令代码  b：指令内容
返回值：
***************************************/
void writedate1302(unsigned char a ,unsigned char b)
{
	unsigned char j;
	RES_DS1302 =0;
	SCLK_DS1302 =0;
	for(j=0; j<=0; j++);
	RES_DS1302 =1;
	for(j=0; j<24; j++);
	writechar1302(a);
	writechar1302(b);
	SCLK_DS1302 =0;
	RES_DS1302 =0;
}



/************************************
函数功能：发送读取指令并读取内容
传递参数：a读取指令
返回值：temp：读取的数据
***************************************/
unsigned char readdate1302(unsigned char a)
{
	unsigned char temp;
	RES_DS1302 =0;
	SCLK_DS1302 =0;
	RES_DS1302 =1;
	writechar1302(a);
	temp =readchar1302();
	SCLK_DS1302 =1;
	RES_DS1302 =0;
	return (temp);
}



/************************************
函数功能：时间的转换
传递参数：整形数据时间
返回值：BCD码的时间
***************************************/
unsigned char trans_time1(unsigned int i)
{
	return ((i/10)<<4|(i%10));
}

/************************************
函数功能：时间的转换
传递参数：BCD码的时间
返回值：整形数据时间
***************************************/
unsigned int trans_time2(unsigned char i)
{
	unsigned int j;
	j =((i&0x70)>>4)*10 + (i&0x0f);
	return (j);	
}





/************************************
函数功能：判断时钟芯片暂停
传递参数：空
返回值：1：已经暂停   0：正在运行
***************************************/
bit judge_pause(void) 
{
	bit i =0;
	i =readdate1302(0x81);
	i =i&0x80;
	if(i ==0)
		return (0);
	else
	    return (1);
}


/************************************
函数功能：写允许开关
传递参数：a：on：打开；off：关闭；
返回值：空
***************************************/
void write1302switch(enum ds1302_write_switch a)
{
	if(a ==on_1302)
		writedate1302(0x8E,0X00);
	else
		writedate1302(0x8E,0x80);	
}

/************************************
函数功能：写寄存器转换
传递参数：枚举寄存器名称
返回值：写寄存器转换结果
***************************************/
unsigned char trans_1302_write(enum ds1302_address a)
{
	unsigned char b;
	switch (a)
	{
		case second :b  =0x80;  break;
		case minute :b  =0x82;  break;
		case hour   :b  =0x84;  break;
		case weekday :b =0x8a;  break;
		case day    :b  =0x86;  break;
		case month  :b  =0x88;  break;
		case year   :b  =0x8c;  break;
						   
		default : b =0x00;
	}
	return (b);
}



/************************************
函数功能：设置DS1302数据
传递参数：a:寄存器设置
		  b:内容设置
返回值：空
second, minute, hour24, hour12, day, weekday, month, year
***************************************/
void setds1302(enum ds1302_address a,unsigned int b)
{
	write1302switch(on_1302);
	writedate1302(trans_1302_write(a), trans_time1(b));
	write1302switch(off_1302);	
}



/************************************
函数功能：写寄存器转换
传递参数：枚举寄存器名称
返回值：写寄存器转换结果
***************************************/
unsigned char trans_1302_read(enum ds1302_address a)
{
	unsigned char b;
	switch (a)
	{
		case second :b  =0x81;  break;
		case minute :b  =0x83;  break;
		case hour   :b  =0x85;  break;
		case weekday :b =0x8b;  break;
		case day    :b  =0x87;  break;
		case month  :b  =0x89;  break;
		case year   :b  =0x8d;  break;
						   
		default : b =0x00;
	}
	return (b);
}


/************************************
函数功能：读DS1302指定寄存器内容
传递参数：a:寄存器名称
返回值：整型内容
***************************************/
unsigned int read1302(enum ds1302_address a)
{
	unsigned int i;
	unsigned char j;
	j =readdate1302(trans_1302_read(a));
	i =trans_time2(j);
	return (i);
}

/************************************
函数功能：转换成直接显示的ASCII数组
传递参数：i：待显示数字
		  a[2]:转换结果
返回值：a[0]：十位  a[1]：个位
注意：制转换成两位可显示数组
***************************************/
void translate_print(unsigned int i, unsigned char a[2])
{
	a[0] =(i%100)/10+48;
	a[1] =(i%10)+48;
	a[2] =0x00;
}


/************************************
函数功能：充电状态检测设置
传递参数：i:充电状态设置:0:不充电; 其他：充电
返回值：
***************************************/
void ele_mode(unsigned int i)
{
	if(i ==0)
		writedate1302(0x90,0x5c);
	else 
		writedate1302(0x90,0xa5);

}

#endif