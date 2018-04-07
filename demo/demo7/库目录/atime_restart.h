/************************************
库功能：冷启动复位
库要求：主函数中已定义：
		#include “STC12C5A60S2”
应用函数：
		 void rstart(void)
修改历史：
		   	 ‘修改人’   ‘修改内容’  				      修改时间’
				空			空								空
最后完成时间:2014-04-27
作者： ATIME	版权所有
实例程序：
	#include "STC12C5A60S2.H"
	#include "atime_restart.h"

	void waitms(unsigned int n)
	{
		int i;
		while(n--)
		{
			for( i=0; i<580; i++);
		}
	}

	void main()
	{
		P0 =0XF0;
		waitms(500);
		P0 =0x0f;
		waitms(500);
		restart();
		while(1);
	}

常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(13): warning C182: pointer to different objects  :将输出数据类型转为char型输出即可
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  重复定义了变量  解决方法：将本函数库的#define语句写在其他函数库后面即可
***************************************/

#ifndef _ATIME_RESTART_H_ 
#define _ATIME_RESTART_H_


/**************************************
函数功能：冷启动复位
传递参数：空
返回值：空
***************************************/
void restart(void)
{
	IAP_CONTR =0X60;
}

#endif	