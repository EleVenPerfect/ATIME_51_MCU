/************************************
库功能：硬件PWM/PAC库
库要求：程序已经载入：
		#include “STC12C5A60S2”
应用函数：
		  void pwm_init( enum pwm_switch a, unsigned char pwm , unsigned char f)
		  unsigned char pwm_set( unsigned char f, float pp)
		  void pwm_contral( enum pwm_switch a)
		  unsigned char pca_init( unsigned char a, unsigned char b, enum pwm_switch c)
		  void pca_contral( enum pwm_switch a)
		  unsigned int pca_read( unsigned char a)
		  void pca_interrupt0(void) 				//PCA0中断服务函数
		  void pca_interrupt1(void) 				//PCA1中断服务函数
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-04-30
作者： ATIME	版权所有
实例程序：
功能：两路PWM输出：
		#include "STC12C5A60S2.H" 	
		#include "atime_pwmpac.h"
		
		void main()
		{
			P1 =0XFF;
			pwm_init( on, 1, 0x02);
			pwm_init( on, 0, 0x02);
			pwm_set(0, 37.5);
			pwm_set(1, 12.5);
			pwm_contral( on);
			while(1);	  
		}

常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
注意：库函数内部已经将中断区分为PC0和PCA1两个中断，且PCA0优先级比PCA1优先级高，
	  且标志位已经自动软件清零。
***************************************/

#ifndef _ATIME_PWMPCA_H_ 
#define _ATIME_PWMPCA_H_

/************************************
库全局变量组
***************************************/
sfr PCAPWM0     =   0xf2;
sfr PCAPWM1     =   0xf3;
enum pwm_switch { on, off};
/************************************
函数功能：PWM初始化设置
传递参数：
		a	:PWM开关设置
		pwm :PWM通道选择（0~1）
		f	:分频系数设置（1~255）
返回值：空	
注：分频系数：对输出PWM波频率的调节参数，
			  对系统时钟的256分频后在分频倍数。
			  两个通道输出频率一致，不一致的话，以最后一次设置的为准。
***************************************/
void pwm_init( enum pwm_switch a, unsigned char pwm , unsigned char f)
{
	CCON =0X40;
	CMOD =0X84;  				//默认设置以T0溢出脉冲作为脉冲源 
								//空闲模式下依旧工作
								//不允许CF中断
	CL =0;
	CH =0;
	AUXR |=0X80;			  	//定时器设置
	ET0 =0;
	TMOD =TMOD|0X02;
	f =0x100-f;
	TL0 =TH0 =f;
	if(pwm == 0)
	{
		if(a == on)
		{
			CCAPM0 =0x42;
			P1M1 &=0XF7;
			P1M0 &=0XF7;
		}
		else 
			CCAPM0 =0X00;	
	}
	if(pwm == 1)
	{
		if(a == on)
		{
			CCAPM1 =0x42;
			P1M1 &=0XEF;
			P1M0 &=0XEF;
		}
		else
			CCAPM1 =0X00;	
	}		
}


/************************************
函数功能：设置占空比
传递参数：
		f: 通道选择
		pp:占空比设置（浮点型0.0~100.0）
返回值：0:失败
		1:成功	
***************************************/
unsigned char pwm_set( unsigned char f, float pp)
{
	unsigned char a;
	if(pp > 100.0 || pp < 0)
		return(0);
	a =(unsigned char)(((100-pp)*256)/100);
	if(f == 0)
	{
		CCAP0H =CCAP0L =a;		
		PCAPWM0 =0X00;
	}
	if(f == 1)
	{
		CCAP1H =CCAP1L =a;		
		PCAPWM1 =0X00;
	}
	return (1);
}

/************************************
函数功能：PWM输出开关
传递参数：开关状态
返回值：空	
***************************************/
void pwm_contral( enum pwm_switch a)
{
	if(a == on)
	{
		CR =1;
		TR0 =1;
	}
	else 
	{
		CR =0;
		TR0 =0;
	}
}



/************************************
函数功能：PCA初始化
传递参数：
		a:PCA选择
		b:0：上升沿捕捉
		  1：下降沿捕捉
		  2：上升沿下降沿捕捉
		c:中断开关
返回值：0：失败
		1：成功	
***************************************/
unsigned char pca_init( unsigned char a, unsigned char b, enum pwm_switch c)
{
	unsigned char temp;
	CL = 0;                     
    CH = 0;
	CCON =0X00;
	if(c == on)
	{
		CMOD =0X89;					   //默认以是中频率为基准
		EA =1;
	}
	else 
	{
		CMOD =0X88;
		EA =0;
	}
	if(a == 0)
	{
		P1M1 &=0XF7;
		P1M0 &=0XF7;
		CCAP0L = 0;
   		CCAP0H = 0;
		switch(b)
		{
			case 0 :temp =0x20;break;
			case 1 :temp =0x10;break;
			case 2 :temp =0x30;break;
			default: return (0);
		}
		if(c == on)
			temp |=0x01;	
		CCAPM0 =temp;	
	}
	if(a == 1)
	{
		P1M1 &=0XEF;
		P1M0 &=0XEF;
		CCAP1L = 0;
    	CCAP1H = 0;
		switch(b)
		{
			case 0 :temp =0x20;break;
			case 1 :temp =0x10;break;
			case 2 :temp =0x30;break;
			default:return (0);
		}
		if(c == on)
			temp |=0x01;
		CCAPM1 =temp;	
	}
	return (1);
}



/************************************
函数功能：PCA运行控制
传递参数：a:
			on：开始运行
			off:停止运行
返回值：空	
***************************************/
void pca_contral( enum pwm_switch a)
{
	if(a == on)
		CR =1;
	else 
		CR =0;
}


/************************************
函数功能：PCA当前计数值读取
传递参数：空
返回值：计数值	
***************************************/
unsigned int pca_read( unsigned char a)
{
	if(a == 0)
		return ( CCAP0L+CCAP0H*256);
	if(a == 1)
	    return( CCAP1L+CCAP1H*256);

	return (0);
}


/****************************************************
函数功能：PCA中断服务程序
传入参数：空
返回值：空
注意：请不要修改此函数
****************************************************/
void pca_interrupt0(void);
void pca_interrupt1(void);
void ad_interrupt(void)	interrupt 7 
{
	CF =0;					//软件清零
	if(CCF0 == 1)
	{
		CCF0 =0;
		pca_interrupt0();	
	}
	if(CCF1 == 1)
	{
		CCF1 =0;
		pca_interrupt1();
	}
}

/************************************
函数功能：PCA通道0中断服务函数
传递参数：空
返回值：空	
注意：请不要修改此函数名称
***************************************/
void pca_interrupt0(void)
{

}



/************************************
函数功能：PCA通道1中断服务函数
传递参数：空
返回值：空	
注意：请不要修改此函数名称
***************************************/
void pca_interrupt1(void)
{

}





												

#endif