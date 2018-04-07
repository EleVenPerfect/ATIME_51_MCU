/************************************
�⹦�ܣ�ͨ��SPI�ӿڿ�
��Ҫ�󣺳����Ѿ����룺
		#include <reg52.h>
Ӧ�ú�����
		 spi_write_char_high(unsigned char a)
		 spi_write_char_low(unsigned char a)
		 spi_read_char_high(void)
		 spi_read_char_low(void)
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-02-21
���ߣ� ATIME	��Ȩ����
ʵ������
����������ͣ�
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д������������ǰ�漸��
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
***************************************/


#ifndef _ATIME_SPI_H_ 
#define _ATIME_SPI_H_


/************************************
��ȫ�ֱ�����
***************************************/
 
sbit SPI_CS   =P1^4;
sbit SPI_MOSI =P1^5;
sbit SPI_SCLK =P1^6;
sbit SPI_MISO =P1^7;	  

/************************************
�������ܣ���SPI������дһ�ֽ����ݻ�ָ��
���ݲ�����a��Ҫ���͵�����
����ֵ����
***************************************/
void spi_write_char_high(unsigned char a)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
		SPI_MOSI =(bit)(a&0x80);
		SPI_SCLK =0;
		SPI_SCLK =1;
		a =a<<1;
	}		
}

/************************************
�������ܣ���SPI������дһ�ֽ����ݻ�ָ��
���ݲ�����a��Ҫ���͵�����
����ֵ����
***************************************/
void spi_write_char_low(unsigned char a)
{
	unsigned char i,j;
	j =200;
	while(j--);
	for(i=0; i<8; i++)
	{
		SPI_MOSI =(bit)(a&0x80);
		SPI_SCLK =0;
		SPI_SCLK =1;
		a =a<<1;
		j =200;
		while(j--);
	}	
}

/************************************
�������ܣ���SPI���ٶ�ȡһ���ֽ�����
���ݲ�������
����ֵ�������Ľ��
***************************************/
unsigned char spi_read_char_low(void)
{
	unsigned char i,j,a;
	j =200;
	while(j--);
	SPI_MISO =1;
	for(i=0; i<8; i++)
	{
		a =a<<1;
		SPI_SCLK =1;
		SPI_SCLK =0;
		if(SPI_MISO ==1)
			a =a|0x01;
		j =200;
		while(j--);	
	}
	return (a);
}


/************************************
�������ܣ���SPI���ٶ�ȡһ���ֽ�����
���ݲ�������
����ֵ�������Ľ��
***************************************/
unsigned char spi_read_char_high(void)
{
	unsigned char i,a;
	SPI_MISO =1;
	for(i=0; i<8; i++)
	{
		a =a<<1;
		SPI_SCLK =1;
		SPI_SCLK =0;
		if(SPI_MISO ==1)
			a =a|0x01;
	}
	return (a);	   
}




#endif