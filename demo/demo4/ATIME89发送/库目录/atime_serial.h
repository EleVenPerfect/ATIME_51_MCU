/************************************
�⹦�ܣ��첽����ͨѶ��
��Ҫ�����������Ѷ��壺
		#include <reg52.h>
		#include "atime_interrupt.c"
Ӧ�ú�����
		 send_char(unsigned char a)
		 send_serial(unsigned char a[])
		 receive_char(void)
		 serial_int(enum serial_receive a, enum serial_baud_rate b, enum serial_receive c)
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
			  ATIME		���ڳ�ʼ��	2014-03-26
			  			�����SD����д���봮���жϵ�BUG��SD����д��Ȼ��Ҫ��ֹ���ܴ���
����޸�ʱ�䣺2014-02-03
���ߣ� ATIME	��Ȩ����
ʵ������
		#include <reg52.h>
		#include <string.h>
		#include "atime_lcd1602.h"
		#include "atime_serial.h"
		#include "atime_interrupt.c"
		
		void main()
		{
			int_lcd1602(rightmove, cursornotdisplay);
			serial_int(enable, baud14400, disable);
			print1602("EleVenPerfect", 2, 3);
			while(1);
		}

		�жϷ������
		void interrupt_serial(void) interrupt 4
		{
			unsigned char k;
			k =receive_char();
			printchar1602(k , 1, 3);
			send_char(k);
		}	

����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
ע�������ڲ��ʺ���SPI��SD����д���ԣ���������
***************************************/


#ifndef _ATIME_SERIAL_H_ 
#define _ATIME_SERIAL_H_


/************************************
��ȫ�ֱ�����
***************************************/

enum serial_receive{ enable, disable};
enum serial_baud_rate{ baud28800, baud38400, baud9600, baud14400, baud7200, baud4800, baud2400, baud1200, baud600, baud300};




/************************************
�������ܣ����ڷ���һ���ַ�
���ݲ�����a���������ַ�
����ֵ����	
***************************************/
void send_char(unsigned char a)
{
	SBUF =a;
	while(TI ==0);
	TI =0;
}



/************************************
�������ܣ����ڷ����ַ���
���ݲ�����a���������ַ���
����ֵ����	
***************************************/
void send_serial(unsigned char a[])
{
	unsigned int i=0;
	for(i=0; a[i]!=0x00; i++)
		send_char(a[i]);
}



/************************************
�������ܣ����ڽ����ַ�
���ݲ�������
����ֵ�����ܵ��ַ�	
ע�⣺����ֵΪ�޷���char��
***************************************/
unsigned char receive_char(void)
{
	unsigned char i=' ';
	if(RI ==1)
	{
		RI =0;
		i =SBUF;
	}
	return (i);
}



/************************************
�������ܣ���ʼ������ͨ��
���ݲ�����
			a:��������
			b��������
			c�������ʼӱ�
����ֵ����	
***************************************/
void serial_int(enum serial_receive a, enum serial_baud_rate b, enum serial_receive c)
{
	TMOD =TMOD|0X20;
	switch(b)
	{
		case baud28800 : TL1 =TH1 =0XFF; break;			   //0%	���
		case baud38400 : TL1 =TH1 =0XFF; break;			   //25%���
		case baud14400 : TL1 =TH1 =0XFE; break;			   //0%	���
		case baud9600  : TL1 =TH1 =0XFD; break;			   //0%	���
		case baud7200  : TL1 =TH1 =0XFC; break;			   //0%	���
		case baud4800  : TL1 =TH1 =0XFA; break;			   //0%	���
		case baud2400  : TL1 =TH1 =0XF4; break;			   //0%	���
		case baud1200  : TL1 =TH1 =0XE8; break;			   //0%	���
		case baud600   : TL1 =TH1 =0XD0; break;			   //0%	���
		case baud300   : TL1 =TH1 =0XA0; break;			   //0%	���
		
		default  :break;	
	}
	TR1 =1;
	ET1 =0;
	EA  =1;
	SM0 =0;
	SM1 =1;
	if(a ==enable)
	{	
		REN =1;
		ES  =1;
	}
	else
	{
		REN =0;
		ES  =0;
	}
	if(c ==disable)
		PCON =0X00;
	else 
		PCON =0X80;
				
}



#endif