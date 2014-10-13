/************************************
�⹦�ܣ������������ʾ
��Ҫ�����������Ѷ��壺
		#include <reg52.h>
Ӧ�ú�����
		 dht11_int( void)
		 unsigned char read_dht11(unsigned char a[5])
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-10-07
���ߣ� ATIME	��Ȩ����
ʵ������
		#include "STC15F2K60S2.H"
		#include "atime_dht11.h" 
		#include "atime_lcd1602.h"
		
		void main ()
		{
			unsigned char t;
			unsigned char a[5];
			unsigned char b[15];
		
			int_lcd1602(rightmove, cursornotdisplay);
			dht11_int();
			while(1)
			{
				if(read_dht11(a)==1)
				{
					bcd_trans_char( a, b, 5);
					print1602( b, 1, 0);
					for( t=0; t<100; t++)
						wait_10us_dht11(1000);
				}
				else
					print1602("error", 1, 0);
			}
		}


����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���	
***************************************/


#ifndef _ATIME_DHT11_H_ 
#define _ATIME_DHT11_H_


/************************************
��ȫ�ֱ�����
***************************************/


sbit DTH11_DATA =P2^3;					   //����ӿ�DIO


/************************************
�������ܣ���ȷ��ʱ10us
���ݲ�������ʱʱ��
����ֵ����
***************************************/
void wait_10us_dht11(unsigned int k)
{
	int i,j;
	for( i=0; i<k; i++)
	{
		for( j=0; j<7; j++)
		;
	}
}


/************************************
�������ܣ���ʼ��DHT11
���ݲ�������
����ֵ����
***************************************/
void dht11_int( void)
{
	unsigned char i;
	DTH11_DATA =1;
	for( i=0; i<100; i++)
	{
		wait_10us_dht11(1000);
	}
}


/************************************
�������ܣ�
���ݲ�����
����ֵ��
***************************************/
bit dht11_start( void)
{
	unsigned int i=0;
	bit err;
	DTH11_DATA =1;
	DTH11_DATA =0;
	wait_10us_dht11(2500);
	DTH11_DATA =1;
	while(DTH11_DATA == 1)
	{
		i++;
		if(i>65530)
			return (1);
	}	
	wait_10us_dht11(1);
	return (0);
}
/************************************
�������ܣ���ȡ���ݲ��洢��������
���ݲ���������ָ��
����ֵ����
***************************************/
void dht11_read40(unsigned char a[5])
{
	unsigned char i,j,temp=0x00;
	for( j=0; j<5; j++)
	{
		for( i=0; i<8; i++)
		{
			while(DTH11_DATA == 0);
			wait_10us_dht11(5);
			if(DTH11_DATA == 1)
			{
				temp |=0x01;
				while(DTH11_DATA == 1);
			}
			temp <<=1;
		}
		a[j] =temp;
	}
}

/************************************
�������ܣ���ȡ��ʪ�����ݲ�У��
���ݲ�����a[5] ����������
����ֵ���ɹ���1��
		ʧ�ܣ�0��
***************************************/
unsigned char read_dht11(unsigned char a[5])
{
	if(dht11_start())
		return(0);
	dht11_read40(a);
	if( a[0]+a[2] != a[4])
		return(0);
	return (1);
}


#endif