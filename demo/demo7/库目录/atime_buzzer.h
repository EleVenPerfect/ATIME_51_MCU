/************************************
�⹦�ܣ�51��Ƭ�����ַ���
��Ҫ�����������Ѷ��壺
		#include <reg52.h>
Ӧ�ú�����
		 buzzer(enum pitch_buzzer a[])
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-02-01
���ߣ� ATIME	��Ȩ����
ʵ������
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
										   ,m0,mstop };			//��������ö�������������ƿ��Ըģ�ö�����Ʋ��ܸ�
				for(i =0; i<=2; i++)				 //ѭ�����Σ�����3��
				{
					buzzer(ok);
					wait_buzzer_us(10000);			 //������1�飬��ʱ1���ټ�������
				}
				while(1);							 //ʹ����ͣ�������ֹ�ܷ�
			}
		
����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
***************************************/


#ifndef _ATIME_BUZZER_H_ 
#define _ATIME_BUZZER_H_


/************************************
��ȫ�ֱ�����
***************************************/

sbit  FMQ =P3^6;			//��������I/O��

enum pitch_buzzer {mstop,m0,l1,l2,l3,l4,l5,l6,l7,m1,m2,m3,m4,m5,m6,m7,h1,h2,h3,h4,h5,h6,h7};		  //������ö�ٶ���

/************************************
�������ܣ���ʱ��Լn ΢��us
���ݲ�����n ʱ��
����ֵ����	
ע�⣺�˺������ܾ�ȷ��ʱ
***************************************/
void wait_buzzer_us(unsigned int n)
{
	int i;
	while(n--)
	{
		for(i=0; i<59; i++)		 //89ϵ��ѡ��6,12ϵ��ѡ��55����δ����
		{
			;
		}	
	}
}



/************************************
�������ܣ������ӵ��ú�������һ������60��
���ݲ�����a: ��Ҫ��������������
����ֵ����	
ע�⣺�˺�������ȷ����������Ϊʹ�õ�����ʱ������Ҫ��ȷ���������ö�ʱ����ʱ
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

		case m0 : error_buzzer =2; break;			 //��ͣ100����

		case mstop : cycle =10000; break;			 //������ֹ
		
		default : {  cycle =20;error_buzzer =1;	}	 //������ݴ��������������󾯱�ģ��
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
	}											   //��������ģ��
	else 
	{
		if(error_buzzer ==2)
		{
			 wait_buzzer_us(1000);				   //������ͣ100����
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
			wait_buzzer_us(20);					  //�������󾯱�ģ�飬���������ε���
		}
	}

}

/************************************
�������ܣ���������
���ݲ�����a[] : ��������������ɵ�����
����ֵ����	
ע�⣺�˺�������ȷ����������Ϊʹ�õ�����ʱ������Ҫ��ȷ���������ö�ʱ����ʱ
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