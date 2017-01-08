/************************************
库功能：51单片机音乐发声
库要求：主函数中已定义：
		#include <reg52.h>
应用函数：
		 buzzer(enum pitch_buzzer a[])
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-02-01
作者： ATIME	版权所有
实例程序：
			#include <reg52.h>
			#include "atime_buzzer.h"
			
			void main()
			{
				int  i;
				enum pitch_buzzer ok[27] ={ h3,m0,h3,m0,h3
										   ,m0,m0,m0,h3,m0
										   ,h3,m0,h3,m0,m0
										   ,m0,h3,m0,h5,m0
										   ,h1,m0,h2,m0,h3
										   ,m0,mstop };			//定义音乐枚举数组数组名称可以改，枚举名称不能改
				for(i =0; i<=2; i++)				 //循环三次，播放3次
				{
					buzzer(ok);
					wait_buzzer_us(10000);			 //播放完1遍，延时1秒再继续播放
				}
				while(1);							 //使程序停在这里，防止跑飞
			}
		
常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
***************************************/


#ifndef _ATIME_BUZZER_H_ 
#define _ATIME_BUZZER_H_


/************************************
库全局变量组
***************************************/

sbit  FMQ =P3^6;			//定义所在I/O口

enum pitch_buzzer {mstop,m0,l1,l2,l3,l4,l5,l6,l7,m1,m2,m3,m4,m5,m6,m7,h1,h2,h3,h4,h5,h6,h7};		  //音调的枚举定义

/************************************
函数功能：延时大约n 微妙us
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
***************************************/
void wait_buzzer_us(unsigned int n)
{
	int i;
	while(n--)
	{
		for(i=0; i<59; i++)		 //89系列选择6,12系列选择55，尚未测试
		{
			;
		}	
	}
}



/************************************
函数功能：发声子调用函数发出一个音符60次
传递参数：a: 所要发声音符的名称
返回值：空	
注意：此函数不精确定发声，因为使用的是延时函数，要求精确发声可以用定时器定时
***************************************/
void buzzer_1(enum pitch_buzzer a)
{
	unsigned int cycle;
	unsigned char error_buzzer =0, i =0;						
	switch(a)
	{
		case l1 : cycle =38; break;
		case l2 : cycle =34; break;
		case l3 : cycle =30; break;
		case l4 : cycle =28; break;
		case l5 : cycle =25; break;
		case l6 : cycle =22; break;
		case l7 : cycle =20; break;
		
		case m1 : cycle =19; break;
		case m2 : cycle =17; break;
		case m3 : cycle =15; break;
		case m4 : cycle =14; break;
		case m5 : cycle =12; break;
		case m6 : cycle =11; break;
		case m7 : cycle =10; break;
		
		case h1 : cycle =9; break;
		case h2 : cycle =8; break;
		case h3 : cycle =7; break;
		case h4 : cycle =7; break;
		case h5 : cycle =6; break;
		case h6 : cycle =5; break;
		case h7 : cycle =5; break;

		case m0 : error_buzzer =2; break;			 //暂停100毫秒

		case mstop : cycle =10000; break;			 //发声终止
		
		default : {  cycle =20;error_buzzer =1;	}	 //如果传递错误参数，进入错误警报模块
	}
	if(error_buzzer ==0)
	{
		for(i=0; i<=60; i++ )
		{
			FMQ =0;
			wait_buzzer_us(cycle);
			FMQ =1;
			wait_buzzer_us(cycle);
		}
	}											   //正常发声模块
	else 
	{
		if(error_buzzer ==2)
		{
			 wait_buzzer_us(1000);				   //发声暂停100毫秒
		}
		else
		{
			FMQ =0;
			wait_buzzer_us(20);
			FMQ =1;
			wait_buzzer_us(20);
			wait_buzzer_us(10000);
			FMQ =0;
			wait_buzzer_us(20);
			FMQ =1;
			wait_buzzer_us(20);
			wait_buzzer_us(10000);
			FMQ =0;
			wait_buzzer_us(20);
			FMQ =1;
			wait_buzzer_us(20);					  //发声错误警报模块，发出三生滴滴声
		}
	}

}

/************************************
函数功能：发声函数
传递参数：a[] : 接受声音音符组成的数组
返回值：空	
注意：此函数不精确定发声，因为使用的是延时函数，要求精确发声可以用定时器定时
***************************************/
void buzzer(enum pitch_buzzer a[])
{
	unsigned int i;
	for(i =0; a[i] != mstop; i++)
	{
		buzzer_1(a[i]);	
	}

}


#endif