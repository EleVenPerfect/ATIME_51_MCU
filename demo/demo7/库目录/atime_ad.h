/************************************
�⹦�ܣ�Ӳ��ADת������
��Ҫ�󣺳����Ѿ����룺
		#include ��STC12C5A60S2��
Ӧ�ú�����
		void ad_start(void)
		void ad_init(unsigned char x)
		unsigned int ad_get(void)
		void ad_inter_main( unsigned char i)		 
		void ad_interrupt(void)	interrupt 5	//�жϷ�����
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-04-27
���ߣ� ATIME	��Ȩ����
ʵ������
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
			�жϷ�������
			unsigned int t;
			void ad_interrupt(void)	interrupt 5
			{
				ad_init(3);  //�� ADC_FLAG ����� 0 
				t =ad_get();
			}


����������ͣ�
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д������������ǰ�漸��
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
***************************************/

#ifndef _ATIME_AD_H_ 
#define _ATIME_AD_H_



/************************************
��ȫ�ֱ�����
***************************************/


/************************************
�������ܣ���ʱ��Լn ����ms
���ݲ�����n ʱ��
����ֵ����	
ע�⣺�˺������ܾ�ȷ��ʱ
***************************************/
void ad_waitms(unsigned int n)
{
	int i;
	while(n--)
	{
		for(i=0; i<580; i++)		  //89ϵ��ѡ��75,12ϵ��ѡ��750
		{
			;
		}	
	}
}


/****************************************************
�������ܣ���ADת���ܿ��أ���ʼADת��
�����������
����ֵ�� ��
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
�������ܣ���ʼ��ADת��
���������ѡͨ��ͨ������0~7��
����ֵ����
****************************************************/
void ad_init(unsigned char x)
{
	unsigned char temp =0xc0;
	temp =temp +x;
	ADC_CONTR =temp;	
}



/****************************************************
�������ܣ���ȡADת�����
�����������
����ֵ��ADת�����
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
�������ܣ�ADת���жϿ���
���������i:1�򿪣�0���ر�
����ֵ����
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
�������ܣ�ADת���ն˷������
�����������
����ֵ����
****************************************************/
unsigned int t;
void ad_interrupt(void)	interrupt 5
{
	ad_init(3);  //�� ADC_FLAG ����� 0���˾���뱣�� 
	t =ad_get();
}

#endif