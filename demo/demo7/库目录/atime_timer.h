/************************************
库功能：51单片机 定时器、中断库
库要求：主函数中已定义：
		#include "STC12C5A60S2.H" 
		#include "atime_interrupt.c"
应用函数：	
		main_interrupt(enum condition_interrupt a)
		main_timer(enum condition_interrupt a,unsigned int b)
		int_interrupt( unsigned int a , enum mode_interrupt b)
		set_priority( enum priority_interrupt a, enum priority_interrupt b)
		timer_8_int(int a, unsigned int b, enum timer_start c)
		timer_16_int( unsigned int a, unsigned int b, enum timer_start c)
		timer_16_reload(unsigned char a, unsigned int b)
		number_count( unsigned int a)
修改历史：
		   	 ‘修改人’   ‘修改内容’  	‘修改时间’
			  ATIME		添加函数	  	2014-04-16
			  			timer_16_reload(unsigned char a, unsigned int b)
						增强了16位不自动重装定时器的定时准确性。
			  ATIME		修改函数		2014-04-29
			  			timer_8_int(int a, unsigned int b, enum timer_start c)
						timer_16_int( unsigned int a, unsigned int b, enum timer_start c)
						提高对12些列单片机的兼容性。
最后修改时间：2014-02-03
作者： ATIME	版权所有
实例程序：见各个函数说明的示例程序
常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注：可查询定时器溢出标志位：TF0;TF1;
	可查询定时器TL0 TH0 TL1 TH1;
	中断需要中断函数库（atime_interrupt.c）配合
	程序默认设置定时器对系统时钟12分频。
***************************************/


#ifndef _ATIME_TIMER_H_ 
#define _ATIME_TIMER_H_


/************************************
库全局变量组
***************************************/


enum condition_interrupt{ on, off}; 	    	//枚举定义开关状态
enum mode_interrupt{ low_ele, negative_jump};   //枚举定义触发方式：低电平触发，负跳变触发
enum timer_start{ normal, irregular}; 			//枚举定义定时器启动方式：normal：正常启动；irregular：同时需要外部中断的高电平
enum priority_interrupt{ zero_high, one_high};  //枚举定义中断优先级：以1为高优先级，以0为高优先级

/************************************
函数功能：总中断开关
传递参数：
			on  :	打开
			off	:	关闭
返回值：空	
***************************************/
#define MAIN_INTERRUPT_ON 	EA =1
#define MAIN_INTERRUPT_OFF  EA =0
void main_interrupt(enum condition_interrupt a)
{
	if(a ==on)
		EA =1;
	else
		EA =0;	
}

/************************************
函数功能：定时器启动开关
传递参数：a: on:启动定时器； off:关闭定时器；
		  b:0:设置定时器0; 1:设置定时器1;
返回值：1：成功 0：失败		
注意：b只能取值0,1；当输入其他值后，函数返回值为0；
***************************************/
unsigned char main_timer(enum condition_interrupt a,unsigned int b)
{
	if(a ==on)
		switch(b)
		{
			case 0 :TR0 =1; return(1); break;
			case 1 :TR1 =1; return(1); break;
			default :return (0);
		}
	else
		switch(b)
		{
			case 0 :TR0 =0; return(1); break;
			case 1 :TR1 =0; return(1); break;
			default :return (0);
		}
}



/************************************
函数功能：外部中断int0、int1设置
传递参数：a:外部中断号：0：int0；  1：int1；
		  b:外部中断触发方式选择：low_ele:低电平触发; negative_jump:负跳变触发；
返回值：1：成功 0：失败	
注意：空
***************************************/
unsigned char int_interrupt( unsigned int a , enum mode_interrupt b)
{
	switch(a)
		{
		case 0 :
			{
				EX0 =1;
				if(b ==low_ele)
					IT0 =0;
				else 
					IT0 =1;
				return (1);
				break;
			}
		case 1 :
			{
				EX1 =1;
				if(b ==low_ele)
					IT1 =0;
				else
					IT1 =1;
				return (1);
				break;
			}
		default : return (0);
		}
}


/************************************
函数功能：中断优先级控制
传递参数：a:外部中断控制：zero_high:以0结尾的优先级高; one_high:以1结尾的优先级高；
		  b:定时器中断控制：zero_high:以0结尾的优先级高; one_high:以1结尾的优先级高；
返回值：空	
注意：不确定函数正确
***************************************/
void set_priority( enum priority_interrupt a, enum priority_interrupt b)
{
	if(a ==zero_high)
	{
		PX0 =1;
		PX1 =0;
		if(b ==zero_high)
		{
			 PT0 =1;
			 PT1 =0;
		}
		else
		{
			 PT0 =0;
			 PT1 =1;
		}	
	}
	else
	{
		PX0 =0;
		PX1 =1;
		if(b ==zero_high)
		{
			 PT0 =1;
			 PT1 =0;
		}
		else
		{
			 PT0 =0;
			 PT1 =1;
		}	
	}
}


/************************************
函数功能：8位自动重装定时器
传递参数:
		a:定时器标号：0:定时器0; 1:定时器1;
		b:所要计时的机器周期数<256
		c：定时器启动控制  normal：正常irregular：需要附加外部中断启动	
返回值：空
注意：定时时间为1-255个机器周期（1/12的晶振周期）
	  对外输出最大50kHz。
实例程序:
		#include "STC12C5A60S2.H" 
		#include "atime_lcd1602.h"
		#include "atime_timer.h"
		#include "atime_interrupt.c"			
		
		
		void main()
		{
			main_interrupt(on);
			main_timer(on,0);
			timer_8_int(0,100,normal);
			P0 =0XF0;
			while(1);
		}
		配套中断服务程序：
		void interrupt_timer0(void) interrupt 1
		{
			static unsigned int i=0;
			i++;
			if(i ==10000)
			{
				i =0;
				P0 =~P0;
			}	
		}
***************************************/
void timer_8_int(int a, unsigned int b, enum timer_start c)
{
	if(a ==0)
	{
		AUXR &=0X7F;
		ET0 =1;		
		if(c ==normal)
			TMOD =TMOD|0X02;
		else 
			TMOD =TMOD|0X0A;
	   TL0 =TH0 =(256-b);		 
	}
	else 
	{
		if(a ==1)
		{
	 		AUXR &=0XBF;
			ET1 =1;
			if(c ==normal)
				TMOD=TMOD|0X20;
			else
				TMOD =TMOD|0XA0;
			TL1 =TH1 =(256-b);
		}
		else  ;
	}
}							

/************************************
函数功能：16位不自动重装定时器
传递参数:
		a:定时器标号：0:定时器0; 1:定时器1;
		b:所要计时的机器周期数<65536
		c：定时器启动控制 
			 normal：正常
			 irregular：需要附加外部中断启动
返回值：1：成功 0：失败
存在问题：输出频率最大不超过350Hz	
注意： 溢出查询TF0 TF1;
       定时完成后不自动重装，
       需要重新调用此函数以重装
	   或在中断函数中重新赋值TH0 TL0 TH1 TL1
解决办法：
		较短时间定时不建议采用此定时方式，因为定时不够准确（重装数据需要时间）。
		小于1500个机器周期的定时，数据重装时最好不调用函数，而是直接TH/TL赋值。
***************************************/
unsigned char timer_16_int( unsigned int a, unsigned int b, enum timer_start c)
{
	if(a ==0)
	{
		
		AUXR &=0X7F;
		ET0 =1;
		if(c ==normal)
			TMOD =TMOD|0x01;
		else 
			TMOD =TMOD|0x09;
	   	TH0 =(65536-b)/256;
		TL0 =(65536-b)%256;
	   return (1);
	}
	else 
	{
		if(a ==1)
		{
	 		AUXR &=0XBF;
			ET1 =1;
			if(c ==normal)
				TMOD=TMOD|0x10;
			else
				TMOD =TMOD|0x90;
			TH1 =(65536-b)/256;
			TL1 =(65536-b)%256;
			return (1);
		}
		else
			return (0);
	}	
}

		

/************************************
函数功能：16位不自动重装定时器初值设置函数
传递参数:
		  b:初值设定
返回值：空
建议： 小于1500个机器周期的定时，数据重装时最好不调用函数，而是直接TH/TL赋值。	
***************************************/
void timer_16_reload(unsigned char a, unsigned int b)
{
	if( a == 0 )
	{
		TH0 =(65536-b+600)/256;
		TL0 =(65536-b+600)%256;
	}
	else
	{
	 	TH1 =(65536-b+600)/256;
		TL1 =(65536-b+600)%256;			   //加600：减少一部分因为计算初值耽误的时间，实验所得，结果不一定可靠
	}
}




/************************************
函数功能：计数器初始化启动
传递参数:  a：计数器选择
返回值：1：成功 0：失败	
注意：本计数器采用16位定时器模式，溢出后需要手动重装初值
		采集数据位：TH0 TL0;TH1 TL1;
		(上升沿有效)
程序实例：	    
				#include "STC12C5A60S2.H" 
				#include "atime_lcd1602.h"
				#include "atime_timer.h"
				#include "atime_interrupt.c"			
				
				
				void main()
				{
					unsigned char i,j;
					TH1 =TL1 ='0';
					TH0 =TL0 ='0';
					i =TL1;
					j =TL0;
					int_lcd1602(rightmove, cursornotdisplay);
					main_interrupt(on);
					main_timer(on,1);
					number_count(1);
					main_timer(on,0);
					number_count(0);
					waitms(1000);
					while(1)
					{
					printchar1602(i,1,1);	
					if(TL1 >'9'||TL1 <'0')
					{
						TL1 ='0';
						i =TL1;
					}
					else i =TL1;
					printchar1602(j,2,1);	
					if(TL0 >'9'||TL0 <'0')
					{
						TL0 ='0';
						j =TL0;
					}
					else j =TL0;
					waitms(500);
					}	
				}
***************************************/
unsigned char number_count( unsigned int a)
{
	if(a ==0)
	{
		TMOD =TMOD|0x05;
		return (1);
	}
	else
	{
		if(a ==1)
		{
			TMOD =TMOD|0x50;
			return (1);
		}
		else return (0);
	}

}





#endif