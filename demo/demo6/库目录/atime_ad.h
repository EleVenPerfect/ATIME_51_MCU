/************************************
库功能：硬件AD转换器库
库要求：程序已经载入：
		#include “STC12C5A60S2”
应用函数：
		void ad_start(void)
		void ad_init(unsigned char x)
		unsigned int ad_get(void)
		void ad_inter_main( unsigned char i)		 
		void ad_interrupt(void)	interrupt 5	//中断服务函数
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-04-27
作者： ATIME	版权所有
实例程序：
			#include "STC12C5A60S2.H" 	
			#include "atime_ad.h"
			#include "atime_lcd1602.h"
			
			
			void main()
			{
				
				int_lcd1602(rightmove, cursornotdisplay);
				ad_inter_main(1);
				ad_init(3);
				
				while(1)
				{
					ad_start();
					waitms(500);
					printint1602(t, 1, 1);
				}
			}
			中断服务函数：
			unsigned int t;
			void ad_interrupt(void)	interrupt 5
			{
				ad_init(3);  //将 ADC_FLAG 软件清 0 
				t =ad_get();
			}


常见错误解释：
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库前面几行
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
***************************************/

#ifndef _ATIME_AD_H_ 
#define _ATIME_AD_H_



/************************************
库全局变量组
***************************************/


/************************************
函数功能：延时大约n 毫秒ms
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
***************************************/
void ad_waitms(unsigned int n)
{
	int i;
	while(n--)
	{
		for(i=0; i<580; i++)		  //89系列选择75,12系列选择750
		{
			;
		}	
	}
}


/****************************************************
函数功能：打开AD转换总开关，开始AD转换
传入参数：空
返回值： 空
****************************************************/
void ad_start(void)
{
	unsigned char temp;
	temp =ADC_CONTR;
	temp =temp|0x88;
	ADC_CONTR =temp;
	AUXR1 &=0XFB;		
}

/****************************************************
函数功能：初始化AD转换
传入参数：选通的通道数（0~7）
返回值：空
****************************************************/
void ad_init(unsigned char x)
{
	unsigned char temp =0xc0;
	temp =temp +x;
	ADC_CONTR =temp;	
}



/****************************************************
函数功能：获取AD转换结果
传入参数：空
返回值：AD转换结果
****************************************************/
unsigned int ad_get(void)
{
	unsigned int temp;
	temp =ADC_RES;
	temp <<=2;
	temp +=(ADC_RESL&0X03);
	return (temp);
}

/****************************************************
函数功能：AD转换中断开关
传入参数：i:1打开；0：关闭
返回值：空
****************************************************/
void ad_inter_main(	unsigned char i)
{
	if(i == 1)
	{
		EA =1;
		EADC =1;
	}
	else
	{
		EA =0;
		EADC =0;
	}
}

/****************************************************
函数功能：AD转换终端服务程序
传入参数：空
返回值：空
****************************************************/
unsigned int t;
void ad_interrupt(void)	interrupt 5
{
	ad_init(3);  //将 ADC_FLAG 软件清 0，此句必须保留 
	t =ad_get();
}

#endif