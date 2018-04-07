/************************************
�⹦�ܣ�SPI���߽ӿ�ͨ�ÿ�
��Ҫ�󣺳����Ѿ����룺
		#include <reg52.h>
		����Ѿ�#include "atime_lcd1602.h"����Ҫ�ڴ�֮ǰ#include "atime_spi.h" ���򱨴�
Ӧ�ú�����
		 spi_writeachar(unsigned char a)
		 spi_readachar(void)
		 spi_write_2char(unsigned char a ,unsigned char b)
		 spi_read_char(unsigned char a)

�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-02-09
���ߣ� ATIME	��Ȩ����
ʵ������
����������ͣ�
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д������������ǰ�漸��
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
***************************************/


#ifndef _ATIME_SPI_3_H_ 
#define _ATIME_SPI_3_H_


/************************************
��ȫ�ֱ�����
***************************************/
 
sbit SPI_CLK =P1^6;	 //λ���崮��ʱ�ӽӿ�λ��
sbit SPI_DATA =P1^4;	 //λ����DATA�ӿ�λ��
sbit SPI_SS =P1^5;	 //λ�������ѡ��ӿ�λ��

	  

/************************************
�������ܣ���SPIдһ�ֽ����ݻ�ָ��
���ݲ�����a��Ҫ���͵�����
����ֵ����
***************************************/
void spi_writeachar(unsigned char a)
{
	unsigned char i,j;
	SPI_CLK =0;
	for(j=0; j<2; j++);
	for(i=0; i<8; i++)
	{
		SPI_DATA =a&0x01;
		for(j=0; j<2; j++);
		SPI_CLK =1;
		for(j=0; j<2; j++);
		SPI_CLK =0;
		a =a>>1;
	}	
}


/************************************
�������ܣ���SPI��ȡһ���ֽ�����
���ݲ�������
����ֵ�������Ľ��
***************************************/
unsigned char spi_readachar(void)
{
	unsigned char i,j,a;
	for(j=0; j<2; j++);
	for(i=0; i<8; i++)
	{
		a =a>>1;
		if(SPI_DATA ==1)
			a =a|0x80;
		SPI_CLK =1;
		for(j=0; j<2; j++);
		SPI_CLK =0;
		for(j=0; j<2; j++);	
	}
	return (a);
}



/************************************
�������ܣ���SPIĳһ��ַд��һ�ֽ�����
���ݲ�����a����ַ  b��һ�ֽ�����
����ֵ����
***************************************/
void spi_write_2char(unsigned char a ,unsigned char b)
{
	unsigned char j;
	SPI_SS =0;
	SPI_CLK =0;
	SPI_SS =1;
	for(j=0; j<2; j++);
	spi_writeachar(a);
	spi_writeachar(b);
	SPI_CLK =0;
	SPI_SS =0;
}


/************************************
�������ܣ����Ͷ�ȡָ���ȡ����
���ݲ�����a��ȡָ��
����ֵ��temp����ȡ������
***************************************/
unsigned char spi_read_char(unsigned char a)
{
	unsigned char temp;
	SPI_SS =0;
	SPI_CLK =0;
	SPI_SS =1;
	spi_writeachar(a);
	temp =spi_readachar();
	SPI_CLK =1;
	SPI_SS =0;
	return (temp);
}


#endif