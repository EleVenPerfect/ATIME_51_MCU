/************************************
�⹦�ܣ�������ң�ؼ���
��Ҫ�󣺳����Ѿ����룺
		#include <reg52.h>
		#include "atime_interrupt.c"
Ӧ�ú�����
		int_infrared(int i)
		start_code(void) //  interrupt 0
		read_infrared(unsigned char j[4])
		translate_bcd(unsigned char j[4],unsigned char k[8])
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-02-07
���ߣ� ATIME	��Ȩ����
ʵ������
			#include <reg52.h>
			#include <string.h>
			#include "atime_lcd1602.h"
			#include "atime_infrared.h"
			#include "atime_interrupt.c"
			
			void main()
			{
				unsigned char a[4],b[8];
				int_lcd1602(rightmove, cursornotdisplay);
				int_infrared(0);
				while(1)
				{
					read_infrared(a);
					translate_bcd(a,b);
					print1602(b,1,1);
				}
			}
			�жϷ�������
			void interrupt_int0(void) interrupt 0
			{
				start_code();
			}
����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
ע�⣺
***************************************/


#ifndef _ATIME_INFRARED_H_ 
#define _ATIME_INFRARED_H_


/************************************
��ȫ�ֱ�����
***************************************/

sbit HWJS =P3^2;       //�������������ڹܽţ��ⲿ�ж�0��
unsigned char a[4];	   //�洢������

/************************************
�������ܣ���ʱ��Լn*50΢��us
���ݲ�����n ʱ��
����ֵ����	
ע�⣺�˺������ܾ�ȷ��ʱ
***************************************/
void infrared_us(unsigned int n)
{
	unsigned char i;
	while(n--)
		for(i=0; i<2; i++);	
}


/************************************
�������ܣ���ʼ������ͨѶ
���ݲ����������ⲿ�жϺ�
����ֵ����	
ע�⣺��ʼ���������Զ��������ж�����EA��
***************************************/
void int_infrared(int i)
{
	EA =1;
	if(i ==1)
	{
		EX1 =1;
		IT1 =1;
	}
	else if(i ==0)
	{
		EX0 =1;
		IT0 =1;
	}
}



/************************************
�������ܣ������жϷ�����
���ݲ�������
����ֵ����
ע�⣺ֻ���Է����ⲿ�ж�0�У�������Ҫ�����ж�����EX��ֵ	 
***************************************/
void start_code(void) // interrupt 0
{
	unsigned i ,j ,temp =0;
	EX0 =0;
	infrared_us(150);
	if(HWJS ==0)
	{
		while(HWJS ==0);
		infrared_us(70);
		if(HWJS ==1)
		{			
			while(HWJS ==1);
			for(j =0; j<=3; j++)
			{
				for(i=0; i<=7; i++)
				{
					temp =temp>>1;
					while(HWJS ==0);
					infrared_us(26);	 //����������27�����Ե�������׼ȥ��
					if(HWJS ==1)
						temp =temp|0x80;
					else
						temp =temp|0x00;
					while(HWJS ==1);
				}
				a[j] = temp;	
			}
		}
	}
	EX0 =1;
}

/************************************
�������ܣ����ض�ȡ������
���ݲ�����j[4]
����ֵ��j[4]�����յ�������	
***************************************/
void read_infrared(unsigned char j[4])
{
	j[0] =a[0];
	j[1] =a[1];
	j[2] =a[2];
	j[3] =a[3];
	a[0] =0x00;
	a[1] =0x00;
	a[2] =0x00;
	a[3] =0x00;
}


/************************************
�������ܣ��Ż���ʾ
���ݲ�����j[4]:��ת������
����ֵ��k[8]:ת������������	
***************************************/
void translate_bcd(unsigned char j[4],unsigned char k[8])
{
	unsigned char temp,i;
	for(i=0; i<=3; i++)
	{
		temp =j[i];
		k[2*i+1] =(temp&0x0f)+48;
		temp =temp&0xf0	;
		temp =temp>>4;
		temp =temp&0x0f;
		k[2*i] =(temp+48);
		if(k[2*i+1] >57)
			k[2*i+1] +=7;
		if(k[2*i] >57)
			k[2*i] +=7;	
	}
}



#endif