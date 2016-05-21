/************************************
库功能：51单片机18B20测温函数库
库要求：主函数中已定义：
		#include "STC12C5A60S2.H"
应用函数：
			translate(float i,unsigned char r[8])
			read_temper_1()
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2013-02-04
作者： ATIME	版权所有
实例程序：
			#include "STC12C5A60S2.H"
			#include "atime_lcd1602.h"
			#include "atime_18b20.h"
			
			void main()
			{
				unsigned char a[8];
				float i;
				bit j;
				int_lcd1602(rightmove, cursornotdisplay);
				while(1)
				{
					j =int_18b20_1();
					if(j ==0)
					{
						i =read_temper_1();
						translate(i,a);
						set1602(clear1602);
						print1602(a,1,3);
						waitms(1000);
					}
					else
					{
						print1602("Please Cheak",1,2);
					}
				}
			}
		
常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
***************************************/


#ifndef _ATIME_18B20_H_ 
#define _ATIME_18B20_H_


/************************************
库全局变量组
***************************************/

sbit  PIN_DQ_1 =P1^0;			//定义18B20的DQ引脚所在I/O口

/************************************
函数功能：初始化18B20
传递参数：空
返回值：0：成功，1：失败	
***************************************/
bit int_18b20_1(void)
{
	bit a;                         //存储是否检测到DS18B20，0存在，1不存在
	unsigned int i;
	PIN_DQ_1 =1;
	for(i=0; i<14; i++);
	PIN_DQ_1 =0;
	for(i=0; i<1400; i++);
	PIN_DQ_1 =1;
	for(i=0; i<70; i++);
	a =PIN_DQ_1;
	for(i=0; i<1400; i++);
	PIN_DQ_1 =1;
	for(i=0; i<14; i++);
	return (a);
}



/************************************
函数功能：向18B20写一字节
传递参数：a：待发送数据
返回值：空	
***************************************/
void write_18b20_1(unsigned char a)
{
	unsigned char i,j;
	for(i=8; i>0; i--)
	{
		PIN_DQ_1 =1;
		for(j=0; j<=7; j++);
		PIN_DQ_1 =0;
		PIN_DQ_1 =a&0x01;
		for(j=0; j<=70; j++);
		PIN_DQ_1 =1;
		for(j=0; j<7; j++);
		a >>=1;
	}
	for(j=0; j<28; j++);
}



/************************************
函数功能：从18B20读一字节
传递参数：空
返回值：a:读回的数据	
***************************************/
unsigned char read_18b20_1(void)
{
	unsigned char i,j,a =0x00;
	for(i=8; i>0; i--)
	{
		PIN_DQ_1 =1;
		for(j=0; j<=7; j++);
		PIN_DQ_1 =0;
		a >>=1;
		for(j=0; j<=7; j++);
		PIN_DQ_1 =1;
		for(j=0; j<14; j++);
		if(PIN_DQ_1 ==1)
			a =a|0x80;
		for(j=0; j<56; j++);
	}
	return (a);
}



/************************************
函数功能：读取温度
传递参数：空
返回值：浮点数值的温度值
注意：读取温度过程中不允许中断，运行完本函数后如果需要中断申请
	  需要重新开启总中断（EA）。	
***************************************/
float read_temper_1(void)
{
	float temper;
	unsigned char high,low;
	unsigned int i;
	EA =0;			 //读取温度过程中不允许中断，防止读取错误。
	int_18b20_1();
	write_18b20_1(0xcc);
	write_18b20_1(0x44);
	for(i=0; i<6500; i++);

	int_18b20_1();
	write_18b20_1(0xcc);
	write_18b20_1(0xbe);
	
	low =read_18b20_1();
	high =read_18b20_1();
/*
serial_int(enable, baud14400, disable);
send_char(high);					//检测程序是否能取得联系可以串口通信
send_char(low);						//已经设置14400波特率11.0592M晶振
*/
	if(high >248)
	{
		high =~high;
		low =~low;
		temper =(-0.0625)*(low+1+256.0*high);
	}
	else
		temper =0.0625*(low+256.0*high);

	return (temper);
}



/************************************
函数功能：优化显示数字
		  本函数可以去除数字前面无意义的零。
传递参数：
		a[8]:转换后的数组存储位置
返回值：空
注： 没有通过返回值返回结果，
	 而是利用函数调用数组是用原内存空间这一规则。
***************************************/
void zero_better(unsigned char a[8])
{
	unsigned int i;
	i =100*(a[1]-48)+10*(a[2]-48)+(a[3]-48);   //减48：char型转int型计算
	if(i >=100);
	else
	if(i >=10)
	{
		a[1] =a[0];
		a[0] =' ';	
	}
	else
	if(i >=0)
	{
		a[2] =a[0];
		a[1] =' ';
		a[0] =' ';
	}
}



/************************************
函数功能：浮点转字符数组
传递参数：
		i:	 待转换浮点数
		r[8]:转换后的数组存储位置
返回值：空
注： 没有通过返回值返回结果，
	 而是利用函数调用数组是用原内存空间这一规则。
***************************************/
void translate(float i,unsigned char r[8])
{
	unsigned int j;
	if(i >0.0)
		r[0] =' ';
	else 
	{
		r[0] ='-';
		i =(-1)*i;
	}
   	i =i*100;
	j =(int)i;
	r[1] =j/10000+48;
	r[2] =(j%10000)/1000+48;
	r[3] =(j%1000)/100+48;
	r[4] ='.';
	r[5] =(j%100)/10+48;
	r[6] =j%10+48;
	r[7] =0x00;	

	zero_better(r);
}



#endif