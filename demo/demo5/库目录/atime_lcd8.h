/************************************
�⹦�ܣ������������ʾ
��Ҫ�����������Ѷ��壺
		#include <reg52.h>
Ӧ�ú�����
		printlcd8( unsigned int h_num, unsigned int l_num)	
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-10-07
���ߣ� ATIME	��Ȩ����
ʵ������
		#include "STC15F2K60S2.H"
		#include "atime_lcd8.h" 
		
		
		void main ()
		{
			while(1)
			{
				printlcd8(1234,5678);
			}
		}


����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
ע����ʾ��Ҫ����ɨ��ſ��ԡ�	
***************************************/


#ifndef _ATIME_LCD8_H_ 
#define _ATIME_LCD8_H_


/************************************
��ȫ�ֱ�����
***************************************/

sbit LCD_DIO =P3^3;					   //����ӿ�DIO
sbit LCD_SCK =P3^2;					   //����ӿ�SCK
sbit LCD_RCK =P3^4;					   //����ӿ�RCK

unsigned char code num_lcd8[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char code bit_lcd8[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};


/************************************
�������ܣ������ʾ
���ݲ�������
����ֵ����
***************************************/
void lcd8_out_once( void)
{
	LCD_RCK =0;
	LCD_RCK =1;
}


/************************************
�������ܣ�����һ�ֽ�����
���ݲ�����kk������
����ֵ����
***************************************/
void lcd8_out_data(unsigned char kk)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
		LCD_SCK =0;
		LCD_DIO =kk&0x80;
		kk <<=1;
		LCD_SCK =1;	
	}
}


/************************************
�������ܣ���ʾһ������
���ݲ�����
		x:����λ��
		num:����ֵ
����ֵ����
***************************************/
void print_lcd8_once( unsigned char num, unsigned char x)
{
	  lcd8_out_data(bit_lcd8[x]);
	  lcd8_out_data(num_lcd8[num]);
	  lcd8_out_once();
}


/************************************
�������ܣ�����һ�ζ�̬ɨ��
���ݲ�����
		h_num������λ����
		l_num������λ����
����ֵ����
***************************************/
void printlcd8( unsigned int h_num, unsigned int l_num)
{
	unsigned char i,temp;
	for( i=0; i<4; i++)
	{
		temp =l_num%10;
		print_lcd8_once( temp, i);
		l_num =l_num/10;		
	}
	for( i=0; i<4; i++)
	{
		temp =h_num%10;
		print_lcd8_once( temp, i+4);
		h_num =h_num/10;		
	}
}


#endif