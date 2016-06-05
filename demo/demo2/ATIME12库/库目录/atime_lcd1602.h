/************************************
�⹦�ܣ���������1602Һ��
��Ҫ�����������Ѷ��壺
		#include <reg52.h>
Ӧ�ú�����
		int_lcd1602(enum lcdint_ac a,enum lcdint_cursor b)
		print1602(unsigned char db[], unsigned int y, unsigned int x)
		printchar1602(unsigned char db, unsigned int y, unsigned int x)
		set1602(enum set a )
		bcd_trans_char(unsigned char a[], unsigned char b[],unsigned char j)
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  				      �޸�ʱ�䡯
			   ATIME	 print1602����					 2014-02-07
			   			�޸����ж��ַ������ȵķ��� ������Ҫ#include <string.h>
			   ATIME	 ���bcd_trans_char����			 2014-02-09
			   		 	 ����BCD���ֱ����ʾ
			   ATIME	 �޸���lcd1602���ݽӿڵĺ궨��	 2014-02-09
			   			 ����ˣ�error C231: 'P0': redefinition ����
			   ATIME	 �޸���print1602()��������	 2014-03-14
			   			 unsigned char print1602(unsigned char db[], unsigned int y, unsigned int x)�ԣ�0,0����Ϊ��ʼ��ַ����δ���ԣ�
			   ATIME	 �����˺���						 2014-04-16
			   			 print1602(unsigned char db[], unsigned int y, unsigned int x)
						 printchar1602(unsigned char db, unsigned int y, unsigned int x)
						 ȷ���˺������ܵ�ʵ��	
������ʱ�䣺2014-01-29
���ߣ� ATIME	��Ȩ����
ʵ������
		#include <reg52.h>
		#include "atime_lcd1602.h"

		void main()
		{
			char db[10]={"A T I M E"};
			int_lcd1602(rightmove, cursornotdisplay);
			print1602(db, 2, 6);							//	������������
			print1602("EleVenPerfect", 1, 3);				//	���������ַ���

			waitms(1000);
			while(set1602(right1602))
			waitms(1200);
		}

����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(13): warning C182: pointer to different objects  :�������������תΪchar���������
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д��������������漴��
***************************************/

#ifndef _ATIME_LCD1602_H_ 
#define _ATIME_LCD1602_H_


/************************************
��ȫ�ֱ�����
***************************************/
#define DATA_LCD1602 P2  //����lcd1602��8λ���ݿ�
sbit RS =P1^6;    //�Ĵ���ѡ��λ����RSλ����ΪP2.0���� ;1:���ݣ�0������
sbit RW =P1^5;    //��дѡ��λ����RWλ����ΪP2.1����	  ;1:��ȡ��0��д��
sbit EN =P1^4;    //ʹ���ź�λ����Eλ����ΪP2.2����
sbit BF =P2^7;    //æµ��־λ������BFλ����ΪP0.7���� ;1:��ֹ��0������

enum set{clear1602, left1602, right1602 }; 			                              //ö��:�趨���� ����186��ע��
enum lcdint_ac{leftmove, rightmove, left_move, right_move };  				      //ö��:��ʼ��AC�ƶ����� ����135��ע��
enum lcdint_cursor{notdisplay, cursornotdisplay, cursorflash, cursornotflash };    //ö��:��ʼ�����״̬	  ����143��ע��

/************************************
�������ܣ���ʱ��Լn ����ms
���ݲ�����n ʱ��
����ֵ����	
ע�⣺�˺������ܾ�ȷ��ʱ
***************************************/
void waitms(unsigned int n)
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




/**************************************
�������ܣ�lcd1602æ���
���ݲ�������
����ֵ��1��æ��0����æ
***************************************/
unsigned char mang(void)
{
	unsigned char result;
	RS =0;
	RW =1;
	EN =1;
	waitms(1);
	result =BF;
	EN =0;
	return (result);		
}


/************************************
�������ܣ�д����1bit
���ݲ�����db ����ָ������
����ֵ����
***************************************/
void writedata(char db)
{
	while(mang()==1);
	RS =1;
	RW =0;
	EN =0;
	DATA_LCD1602 =db;
	waitms(1);
	EN =1;
	waitms(1);
	EN =0;
}




/************************************
�������ܣ�дָ��1bit
���ݲ�����db  ����ָ������
����ֵ����
***************************************/
void writezhi(unsigned char db)
{
	while(mang()==1);
	RS =0;
	RW =0;
	EN =0;
	DATA_LCD1602 =db;
	waitms(1);
	EN =1;
	waitms(1);
	EN =0;
}



/************************************
�������ܣ�����1602
���ݲ�����a:
			clear1602: ����
			left1602 : ����
			right1602: ����

����ֵ��1���ɹ�����ʧ��0��
***************************************/
unsigned char set1602(enum set a )
{
	switch(a)
	{
		case clear1602 : writezhi(0x01);  break;
		case left1602  : writezhi(0x18);  break;
		case right1602 : writezhi(0x1C);  break;
		default :return (0);
	}
	EX0 =1;
	return (1);
}




/************************************
�������ܣ����г�ʼ��lcd1602
���ݲ�����a:����ƶ����� �����a��ע��
		  b:���ع����ʾ �����b��ע��
����ֵ��1���ɹ�����ʧ��0��
***************************************/
unsigned char int_lcd1602(enum lcdint_ac a,enum lcdint_cursor b)
{
	writezhi(0x01);
	waitms(15);
    RS =0;
	EN =0;
	DATA_LCD1602 =0X38;
	waitms(1);
	EN =1;
	waitms(5);
	EN =0;
	DATA_LCD1602 =0X38;
	waitms(1);
	EN =1;
	waitms(5);
	EN =0;
	DATA_LCD1602 =0X38;
	waitms(1);
	EN =1;
	waitms(5);
	writezhi(0x01);
	switch(a)
	{
		case rightmove  : writezhi(0x06);  break;	  //���治������д��AC�Զ�+1
		case leftmove   : writezhi(0x04);  break;	  //���治������д��AC�Զ�-1
		case right_move : writezhi(0x07);  break;	  //��������ƽ��1�Σ���д��AC�Զ�+1
		case left_move  : writezhi(0x05);  break;	  //��������ƽ��1�Σ���д��AC�Զ�-1
		default : return (0);				     	  // ����
	}
	switch(b)
	{
		case cursornotflash   : writezhi(0x0e);  break;	  //������ʾ�������ʾ����겻����
		case cursorflash      : writezhi(0x0d);  break;	  //������ʾ�������ʾ���������
		case cursornotdisplay : writezhi(0x0c);  break;	  //������ʾ����겻��ʾ����겻����
		case notdisplay       : writezhi(0x08);  break;	  //���治��ʾ����겻��ʾ����겻����
		default : return (0);					          // ����
	}
	set1602(clear1602);
	return (1);
}




/************************************
�������ܣ������ַ�������
���ݲ������ַ���ָ��
����ֵ���ַ�������
***************************************/
unsigned int str_long(unsigned char db[])
{
	unsigned int i;
	for(i =0; db[i] !=0; i++) ;
	return (i);
}



/************************************
�������ܣ���ʾ���ݡ���ĸ
���ݲ�����db[] : ��ʾ������ 
		  x:	 ��������
		  y:	 ��������
		  ����ϵ���Ͻ�Ϊ��0,0������������Ϊ��
����ֵ��1���ɹ�����ʧ��0��
�ر�ע�⣺�˺���ֻ������ʾ�ַ������ַ������飬��������ʾ�����ַ�
***************************************/
unsigned char print1602(unsigned char db[], unsigned int y, unsigned int x)
{
	unsigned int i; 
	writezhi (0x80 + 0x40*y + x );
	for(i=0; i< str_long(db); i++)		 //�޸����ж��ַ������ȷ�ʽ	��shrlen��Ϊ�Զ����str_long
	{
		writedata(db[i]);
	}
	return (1);
}


/************************************
�������ܣ������Զ����ַ�
���ݲ�����
		  i:���õ��Զ����ַ����
		  a[]:�����ַ�����������
����ֵ����
�ر�ע�⣺i��ȡֵ��0~7��
��ʾ�Զ����ַ�������
		��printchar1602����������λд֮ǰ������ַ���ż���
		�磺printchar1602(0,2,1);
***************************************/
void setpic1602(unsigned char i, unsigned char a[])
{
	unsigned j;
	writezhi((0x40+0x08*i));
	waitms(5);
	for(j=0; j<8; j++)
	{	
		writedata(a[j]);
		waitms(1);	
	}				
}
		

/************************************
�������ܣ���ʾ���ݡ���ĸ
���ݲ�����db : ��ʾ������ 
		  x:	 ��������
		  y:	 ��������
		  ����ϵ���Ͻ�Ϊ��1,1������������Ϊ��
����ֵ��1���ɹ�����ʧ��0��
�ر�ע�⣺�˺���ֻ������ʾ�����ַ�
***************************************/
unsigned char printchar1602(unsigned char db, unsigned int y, unsigned int x)
{
	writezhi (0x80 + 0x40*y + x);
	writedata(db);
	return (1);
}

/************************************
�������ܣ�1λBCD��ת��3λ����ʾ����
���ݲ�����a[]��BCD����;b[]������ʾ����
����ֵ����
***************************************/
void bcd_trans_char(unsigned char a[], unsigned char b[],unsigned char j)
{
	unsigned int i;
	for(i=0; i<j; i++)
	{
		b[3*i] =a[i]/100+0x30;
		b[3*i+1] =(a[i]%100)/10+0x30;
		b[3*i+2] =(a[i]%10)+0x30;
	}
}

/************************************
�������ܣ�������ǰʮ��λ��
���ݲ�������
����ֵ����
***************************************/
void clear1602_10(unsigned int x)
{
	print1602("          ",x,0);	
}

#endif	