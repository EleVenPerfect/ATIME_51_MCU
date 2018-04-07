/************************************
�⹦�ܣ�51��Ƭ�� ��ʱ�����жϿ�
��Ҫ�����������Ѷ��壺
		#include "STC12C5A60S2.H" 
		#include "atime_interrupt.c"
Ӧ�ú�����	
		main_interrupt(enum condition_interrupt a)
		main_timer(enum condition_interrupt a,unsigned int b)
		int_interrupt( unsigned int a , enum mode_interrupt b)
		set_priority( enum priority_interrupt a, enum priority_interrupt b)
		timer_8_int(int a, unsigned int b, enum timer_start c)
		timer_16_int( unsigned int a, unsigned int b, enum timer_start c)
		timer_16_reload(unsigned char a, unsigned int b)
		number_count( unsigned int a)
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  	���޸�ʱ�䡯
			  ATIME		��Ӻ���	  	2014-04-16
			  			timer_16_reload(unsigned char a, unsigned int b)
						��ǿ��16λ���Զ���װ��ʱ���Ķ�ʱ׼ȷ�ԡ�
			  ATIME		�޸ĺ���		2014-04-29
			  			timer_8_int(int a, unsigned int b, enum timer_start c)
						timer_16_int( unsigned int a, unsigned int b, enum timer_start c)
						��߶�12Щ�е�Ƭ���ļ����ԡ�
����޸�ʱ�䣺2014-02-03
���ߣ� ATIME	��Ȩ����
ʵ�����򣺼���������˵����ʾ������
����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
ע���ɲ�ѯ��ʱ�������־λ��TF0;TF1;
	�ɲ�ѯ��ʱ��TL0 TH0 TL1 TH1;
	�ж���Ҫ�жϺ����⣨atime_interrupt.c�����
	����Ĭ�����ö�ʱ����ϵͳʱ��12��Ƶ��
***************************************/


#ifndef _ATIME_TIMER_H_ 
#define _ATIME_TIMER_H_


/************************************
��ȫ�ֱ�����
***************************************/


enum condition_interrupt{ on, off}; 	    	//ö�ٶ��忪��״̬
enum mode_interrupt{ low_ele, negative_jump};   //ö�ٶ��崥����ʽ���͵�ƽ�����������䴥��
enum timer_start{ normal, irregular}; 			//ö�ٶ��嶨ʱ��������ʽ��normal������������irregular��ͬʱ��Ҫ�ⲿ�жϵĸߵ�ƽ
enum priority_interrupt{ zero_high, one_high};  //ö�ٶ����ж����ȼ�����1Ϊ�����ȼ�����0Ϊ�����ȼ�

/************************************
�������ܣ����жϿ���
���ݲ�����
			on  :	��
			off	:	�ر�
����ֵ����	
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
�������ܣ���ʱ����������
���ݲ�����a: on:������ʱ���� off:�رն�ʱ����
		  b:0:���ö�ʱ��0; 1:���ö�ʱ��1;
����ֵ��1���ɹ� 0��ʧ��		
ע�⣺bֻ��ȡֵ0,1������������ֵ�󣬺�������ֵΪ0��
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
�������ܣ��ⲿ�ж�int0��int1����
���ݲ�����a:�ⲿ�жϺţ�0��int0��  1��int1��
		  b:�ⲿ�жϴ�����ʽѡ��low_ele:�͵�ƽ����; negative_jump:�����䴥����
����ֵ��1���ɹ� 0��ʧ��	
ע�⣺��
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
�������ܣ��ж����ȼ�����
���ݲ�����a:�ⲿ�жϿ��ƣ�zero_high:��0��β�����ȼ���; one_high:��1��β�����ȼ��ߣ�
		  b:��ʱ���жϿ��ƣ�zero_high:��0��β�����ȼ���; one_high:��1��β�����ȼ��ߣ�
����ֵ����	
ע�⣺��ȷ��������ȷ
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
�������ܣ�8λ�Զ���װ��ʱ��
���ݲ���:
		a:��ʱ����ţ�0:��ʱ��0; 1:��ʱ��1;
		b:��Ҫ��ʱ�Ļ���������<256
		c����ʱ����������  normal������irregular����Ҫ�����ⲿ�ж�����	
����ֵ����
ע�⣺��ʱʱ��Ϊ1-255���������ڣ�1/12�ľ������ڣ�
	  ����������50kHz��
ʵ������:
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
		�����жϷ������
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
�������ܣ�16λ���Զ���װ��ʱ��
���ݲ���:
		a:��ʱ����ţ�0:��ʱ��0; 1:��ʱ��1;
		b:��Ҫ��ʱ�Ļ���������<65536
		c����ʱ���������� 
			 normal������
			 irregular����Ҫ�����ⲿ�ж�����
����ֵ��1���ɹ� 0��ʧ��
�������⣺���Ƶ����󲻳���350Hz	
ע�⣺ �����ѯTF0 TF1;
       ��ʱ��ɺ��Զ���װ��
       ��Ҫ���µ��ô˺�������װ
	   �����жϺ��������¸�ֵTH0 TL0 TH1 TL1
����취��
		�϶�ʱ�䶨ʱ��������ô˶�ʱ��ʽ����Ϊ��ʱ����׼ȷ����װ������Ҫʱ�䣩��
		С��1500���������ڵĶ�ʱ��������װʱ��ò����ú���������ֱ��TH/TL��ֵ��
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
�������ܣ�16λ���Զ���װ��ʱ����ֵ���ú���
���ݲ���:
		  b:��ֵ�趨
����ֵ����
���飺 С��1500���������ڵĶ�ʱ��������װʱ��ò����ú���������ֱ��TH/TL��ֵ��	
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
		TL1 =(65536-b+600)%256;			   //��600������һ������Ϊ�����ֵ�����ʱ�䣬ʵ�����ã������һ���ɿ�
	}
}




/************************************
�������ܣ���������ʼ������
���ݲ���:  a��������ѡ��
����ֵ��1���ɹ� 0��ʧ��	
ע�⣺������������16λ��ʱ��ģʽ���������Ҫ�ֶ���װ��ֵ
		�ɼ�����λ��TH0 TL0;TH1 TL1;
		(��������Ч)
����ʵ����	    
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