/************************************
�⹦�ܣ�DS1302ʱ�ӿ⣨����SPI���߽ӿڣ�
��Ҫ�󣺳����Ѿ����룺
		#include <reg52.h>
		����Ѿ�#include "atime_lcd1602.h"����Ҫ�ڴ�֮ǰ#include "atime_ds1302.h" ���򱨴�
Ӧ�ú�����
		 read1302(enum ds1302_address a)
		 setds1302(enum ds1302_address a,unsigned int b)
		 ele_mode(unsigned int i)
		 judge_pause(void)
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-02-07
���ߣ� ATIME	��Ȩ����
ʵ������
			#include <reg52.h>
			#include "atime_ds1302.h"
			#include "atime_lcd1602.h"
			
			void main()
			{
				unsigned int i;
				unsigned char a[2];
				int_lcd1602(rightmove, cursornotdisplay);
				setds1302(second,0);
				setds1302(minute,42);
				setds1302(hour,19);
				setds1302(year,14);
				setds1302(month,2);
				setds1302(day,7);
				setds1302(weekday,5);
				ele_mode(1);
				while(1)
				{
					i =read1302(hour);
					translate_print(i,a);
					print1602(a,1,2);
				    
					i =read1302(minute);
					translate_print(i,a);
					print1602(a,1,5);
			
					i =read1302(second);
					translate_print(i,a);
					print1602(a,1,8);
			
					i =read1302(weekday);
					translate_print(i,a);
					print1602(a,1,14);
					print1602(" ",1,14);
			
					i =read1302(year);
					translate_print(i,a);
					print1602(a,2,3);
			
					i =read1302(month);
					translate_print(i,a);
					print1602(a,2,6);
			
					i =read1302(day);
					translate_print(i,a);
					print1602(a,2,9);
			
				}
			}

����������ͣ�
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д������������ǰ�漸��
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
ע�⣺���⺯��Ĭ��24Сʱ��
	  ���ں����ڲ����ƣ���ݷ�ΧΪ0~79
	  ��Դ���Ĭ��Ϊ2k����1��������	
	  ��Ҫ����ѡ�����ͨ��readdate1302(unsigned char a)��
	  writedate1302(unsigned char a ,unsigned char b)��������
***************************************/


#ifndef _ATIME_DS1302_H_ 
#define _ATIME_DS1302_H_


/************************************
��ȫ�ֱ�����
***************************************/

sbit SCLK =P1^0;	 //λ����ds1302��SCLK�ӿ�λ��
sbit DATA =P1^1;	 //λ����ds1302��DATA�ӿ�λ��
sbit RES  =P1^2;	 //λ����ds1302��RES �ӿ�λ��
enum ds1302_write_switch {on, off};			  //ö��д������״̬
enum ds1302_address{second, minute, hour, day, weekday, month, year};	   //ö�ټĴ���


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
�������ܣ���DS1302дһ�ֽ����ݻ�ָ��
���ݲ�����a��Ҫ���͵�����
����ֵ����
***************************************/
void writechar1302(unsigned char a)
{
	unsigned char i,j;
	SCLK =0;
	for(j=0; j<2; j++);
	for(i=0; i<8; i++)
	{
		DATA =a&0x01;
		for(j=0; j<2; j++);
		SCLK =1;
		for(j=0; j<2; j++);
		SCLK =0;
		a =a>>1;
	}	
}




/************************************
�������ܣ���ds1302��ȡһ���ֽ�����
���ݲ�������
����ֵ�������Ľ��
***************************************/
unsigned char readchar1302(void)
{
	unsigned char i,j,a;
	for(j=0; j<2; j++);
	for(i=0; i<8; i++)
	{
		a =a>>1;
		if(DATA ==1)
			a =a|0x80;
		SCLK =1;
		for(j=0; j<2; j++);
		SCLK =0;
		for(j=0; j<2; j++);	
	}
	return (a);
}


/************************************
�������ܣ���ds1302����ָ������ָ������
���ݲ�����a��ָ�����  b��ָ������
����ֵ��
***************************************/
void writedate1302(unsigned char a ,unsigned char b)
{
	unsigned char j;
	RES =0;
	SCLK =0;
	RES =1;
	for(j=0; j<2; j++);
	writechar1302(a);
	writechar1302(b);
	SCLK =0;
	RES =0;
}



/************************************
�������ܣ����Ͷ�ȡָ���ȡ����
���ݲ�����a��ȡָ��
����ֵ��temp����ȡ������
***************************************/
unsigned char readdate1302(unsigned char a)
{
	unsigned char temp;
	RES =0;
	SCLK =0;
	RES =1;
	writechar1302(a);
	temp =readchar1302();
	SCLK =1;
	RES =0;
	return (temp);
}



/************************************
�������ܣ�ʱ���ת��
���ݲ�������������ʱ��
����ֵ��BCD���ʱ��
***************************************/
unsigned char trans_time1(unsigned int i)
{
	return ((i/10)<<4|(i%10));
}

/************************************
�������ܣ�ʱ���ת��
���ݲ�����BCD���ʱ��
����ֵ����������ʱ��
***************************************/
unsigned int trans_time2(unsigned char i)
{
	unsigned int j;
	j =((i&0x70)>>4)*10 + (i&0x0f);
	return (j);	
}





/************************************
�������ܣ��ж�ʱ��оƬ��ͣ
���ݲ�������
����ֵ��1���Ѿ���ͣ   0����������
***************************************/
bit judge_pause(void) 
{
	bit i =0;
	i =readdate1302(0x81);
	i =i&0x80;
	if(i ==0)
		return (0);
	else
	    return (1);
}


/************************************
�������ܣ�д������
���ݲ�����a��on���򿪣�off���رգ�
����ֵ����
***************************************/
void write1302switch(enum ds1302_write_switch a)
{
	if(a ==on)
		writedate1302(0x8E,0X00);
	else
		writedate1302(0x8E,0x80);	
}

/************************************
�������ܣ�д�Ĵ���ת��
���ݲ�����ö�ټĴ�������
����ֵ��д�Ĵ���ת�����
***************************************/
unsigned char trans_1302_write(enum ds1302_address a)
{
	unsigned char b;
	switch (a)
	{
		case second :b  =0x80;  break;
		case minute :b  =0x82;  break;
		case hour   :b  =0x84;  break;
		case weekday :b =0x8a;  break;
		case day    :b  =0x86;  break;
		case month  :b  =0x88;  break;
		case year   :b  =0x8c;  break;
						   
		default : b =0x00;
	}
	return (b);
}



/************************************
�������ܣ�����DS1302����
���ݲ�����a:�Ĵ�������
		  b:��������
����ֵ����
second, minute, hour24, hour12, day, weekday, month, year
***************************************/
void setds1302(enum ds1302_address a,unsigned int b)
{
	write1302switch(on);
	writedate1302(trans_1302_write(a), trans_time1(b));
	write1302switch(off);	
}



/************************************
�������ܣ�д�Ĵ���ת��
���ݲ�����ö�ټĴ�������
����ֵ��д�Ĵ���ת�����
***************************************/
unsigned char trans_1302_read(enum ds1302_address a)
{
	unsigned char b;
	switch (a)
	{
		case second :b  =0x81;  break;
		case minute :b  =0x83;  break;
		case hour   :b  =0x85;  break;
		case weekday :b =0x8b;  break;
		case day    :b  =0x87;  break;
		case month  :b  =0x89;  break;
		case year   :b  =0x8d;  break;
						   
		default : b =0x00;
	}
	return (b);
}


/************************************
�������ܣ���DS1302ָ���Ĵ�������
���ݲ�����a:�Ĵ�������
����ֵ����������
***************************************/
unsigned int read1302(enum ds1302_address a)
{
	unsigned int i;
	unsigned char j;
	j =readdate1302(trans_1302_read(a));
	i =trans_time2(j);
	return (i);
}

/************************************
�������ܣ�ת����ֱ����ʾ��ASCII����
���ݲ�����i������ʾ����
		  a[2]:ת�����
����ֵ��a[0]��ʮλ  a[1]����λ
ע�⣺��ת������λ����ʾ����
***************************************/
void translate_print(unsigned int i, unsigned char a[2])
{
	a[0] =(i%100)/10+48;
	a[1] =(i%10)+48;
}


/************************************
�������ܣ����״̬�������
���ݲ�����i:���״̬����:0:�����; ���������
����ֵ��
***************************************/
void ele_mode(unsigned int i)
{
	if(i ==0)
		writedate1302(0x90,0x5c);
	else 
		writedate1302(0x90,0xa5);

}

#endif