/************************************
�ļ����ܣ�51��Ƭ���жϺ�����
��Ҫ�����������Ѷ��壺
		#include <reg52.h>
		#include "atime_timer.h"
		#include "atime_interrupt.c"
Ӧ�ú�����
		interrupt_int0()
		interrupt_timer0()
		interrupt_int1()
		interrupt_timer1()
		interrupt_serial()
		interrupt_serial2(void)
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
			    ATIME	���Ӻ���	2014-04-29
					����interrupt_serial2(void)	
����޸�ʱ�䣺2014-02-03
���ߣ� ATIME	��Ȩ����
����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
���ú�������������
		static����̬�������ڶ��ε���Ӧ���ϴε��ú��ֵ���������¿����ڴ�ռ��趨��ֵ��
***************************************/

/************************************
�жϿ���ȫ�ֱ�����
***************************************/
unsigned char temp_set=31;	//���ó�ʼ�¶�
float temperature;
sbit led_1 = P3^6;
sbit led_2 = P3^7; 
int aaa = 0;	//��Ƶ��ʱ����
bit ds18b20_exit;

/************************************
�������ܣ��ⲿ�ж�0���жϷ���
���ݲ�������
����ֵ����	
ע�⣺��
***************************************/
void interrupt_int0(void) interrupt 0
{
	temp_set++;
	if(temp_set>50)
		temp_set = 50;
}


/************************************
�������ܣ���ʱ��/������0���жϷ���
���ݲ�������
����ֵ����	
ע�⣺��
***************************************/
void interrupt_timer0(void) interrupt 1
{
	unsigned char temp_average;
	unsigned char distance;
	
	aaa++;	
	if(aaa>10)
	{
		aaa=0;

		temp_average = (unsigned char)temperature;//ǿ��ת��Ϊchar�͵ȴ����бȽ�
	
		if(temp_average>temp_set)
		{
			distance = temp_average - temp_set;	
			if( distance>1 )     //���ʵ���¶�ƽ��ֵ�������1���������³���
			{
				led_1 = 1;		 //�͵�ƽ������
			}
			else
			{
				led_1 = 0;
			}
		}
		else
		{
			distance = temp_set - temp_average;
			if( distance>1 )	 //���ʵ���¶�ƽ��ֵ�������1���������³���
			{
				led_2 = 1;        //�ߵ�ƽ����
			}
			else
			{
				led_2 = 0;	
			}
		}		
	
	}
}



/************************************
�������ܣ��ⲿ�ж�1���жϷ���
���ݲ�������
����ֵ����	
ע�⣺��
***************************************/
void interrupt_int1(void) interrupt 2
{
	temp_set--;	
	if(temp_set<10)
		temp_set = 10;	   
}



/************************************
�������ܣ���ʱ��/������1���жϷ���
���ݲ�������
����ֵ����	
ע�⣺��
***************************************/
void interrupt_timer1(void) interrupt 3
{

}


/************************************
�������ܣ�����1���жϷ���
���ݲ�������
����ֵ����	
ע�⣺��
***************************************/
void interrupt_serial1(void) interrupt 4
{
	unsigned char k;
	k =receive_char();
	printchar1602(k , 1, 15);
	if(k=='A')
	{
		temp_set++;
		if(temp_set>50)
			temp_set = 50;
	}
	if(k=='B')
	{
		temp_set--;	
		if(temp_set<10)
			temp_set = 10;		
	}

	send_char(k);
	send_char(' ');
	send_char('O');
	send_char('K');
	send_char('\n');
}	




/************************************
�������ܣ�����2���жϷ���
���ݲ�������
����ֵ����	
ע�⣺��
***************************************/
void interrupt_serial2(void) interrupt 8
{

}		


