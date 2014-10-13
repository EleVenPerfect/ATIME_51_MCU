/************************************
库功能：矩阵键盘扫描库
库要求：主函数中已定义：
		#include <reg52.h>
应用函数：
			key4_4( )
修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’
				空			空			空
最后修改时间：2014-01-29
作者： ATIME	版权所有
实例程序：
		#include <reg52.h>
		#include <string.h>
		#include "atime_key4_4.h"
		#include "atime_lcd1602.h"

		void main()
		{
			unsigned char i[1];
			int_lcd1602(rightmove, cursornotdisplay);
			print1602("You Press",1,1);
			while(1)
			{
				 i[0] =key4_4();
				 print1602(i,1,11);
				 wait_key4_4_ms(10);
			} 
		}

常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
***************************************/


#ifndef _ATIME_KEY4_4_H_ 
#define _ATIME_KEY4_4_H_


/************************************
库全局变量组
***************************************/

#define KEY4 P0			//定义键盘所在I/O口


/************************************
函数功能：延时大约n 毫秒ms
传递参数：n 时间
返回值：空	
注意：此函数不能精确定时
***************************************/
void wait_key4_4_ms(unsigned int n)
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
函数功能：扫描键盘按下的按键
传递参数：空
返回值：0--9  A--E  ‘ ’	
注意：不按任何按键时返回空格
***************************************/
unsigned char key4_4(void )
{
	KEY4 =0xf0;
	if(KEY4|0XF0 !=0XF0)
	{
		wait_key4_4_ms(10);					   //软件延时10ms去抖
		if(KEY4|0XF0 !=0XF0)
		{
			KEY4 =0xfe;
			switch(KEY4)
			{
				case 0xee : return('0') ; break;
				case 0xde : return('1') ; break;
				case 0xbe : return('2') ; break;
				case 0x7e : return('3') ; break;
				default :
				{
					KEY4 =0xfd;
					switch(KEY4)
					{
						case 0xed : return('4') ; break;
						case 0xdd : return('5') ; break;
						case 0xbd : return('6') ; break;
						case 0x7d : return('7') ; break;
						default : 
						{
							KEY4 =0xfb;
							switch(KEY4)
							{
								case 0xeb : return('8') ; break;
								case 0xdb : return('9') ; break;
								case 0xbb : return('A') ; break;
								case 0x7b : return('B') ; break;
								default : 
								{
								 	KEY4 =0xf7;
									switch(KEY4)
									{
										case 0xe7 : return('C') ; break;
										case 0xd7 : return('D') ; break;
										case 0xb7 : return('E') ; break;
										case 0x77 : return('F') ; break;
										default : return (' ');	
									}
								}
							}
						}	
					}	
				}
			}
		}
		else return (' ');
	}
	else return (' ');
}		



#endif