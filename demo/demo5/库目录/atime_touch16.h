/************************************
�⹦�ܣ���������16��
��Ҫ�����������Ѷ��壺
		#include <reg52.h>
Ӧ�ú�����
		unsigned char touch16(void)	
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-10-07
���ߣ� ATIME	��Ȩ����
ʵ������
		#include "STC15F2K60S2.H"
		#include "atime_touch16.h" 
		#include "atime_lcd1602.h"
		
		void main ()
		{
			unsigned char tt,a[2];
			P0 =0X00;
			int_lcd1602(rightmove, cursornotdisplay);
			while(1)
			{
				tt =touch16();
				a[0] =tt/10+0x30;
				a[1] =tt%10+0x30;
				print1602( a, 1, 1);
				P0 =~P0;
			}
		}


����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���	
ע��
	��·����2�ߴ���ͨ�ţ��͵�ƽ��Ч��16��ģʽ,ֻ���һ����������
***************************************/


#ifndef _ATIME_TOUCH16_H_ 
#define _ATIME_TOUCH16_H_


/************************************
��ȫ�ֱ�����
***************************************/

sbit TOUCH_SDO =P2^5;					   //����ӿ�SDO
sbit TOUCH_SCL =P2^4;					   //����ӿ�SCL


/************************************
�������ܣ�ȷ������ֵ
���ݲ�������
����ֵ����0~16��16��ʾû�а�������
***************************************/
unsigned char touch16(void)
{
	unsigned char i,j;
	i =0;
	for( j=0; j<16; j++)
	{
		TOUCH_SCL =0;
		if(TOUCH_SDO ==0)
			i =j+1;
		TOUCH_SCL =1;
	}
	return (i);
}


#endif