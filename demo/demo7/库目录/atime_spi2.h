/************************************
�⹦�ܣ�ͨ��SPI�ӿڿ⺬λ�����
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
����޸�ʱ�䣺2014-03-26
���ߣ���â ��Ȩ����
ʵ������
����������ͣ�
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д������������ǰ�漸��
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
***************************************/

#ifndef _ATIME_SPI2_H_ 
#define _ATIME_SPI2_H_

/************************************
��ȫ�ֱ�����
***************************************/
sbit SPI_CS   =P1^4;
sbit SPI_MOSI =P1^5; 
sbit SPI_SCLK =P1^6;   
sbit SPI_MISO =P1^7; 


unsigned char bdata dat;
sbit dat7=dat^7;
sbit dat6=dat^6;
sbit dat5=dat^5;
sbit dat4=dat^4;
sbit dat3=dat^3;
sbit dat2=dat^2;
sbit dat1=dat^1;
sbit dat0=dat^0;


/************************************
�������ܣ���ʱ
���ݲ�����time����ʱ
����ֵ����
***************************************/
void sd_delay(unsigned char time) 
{
while(time--);
}


/************************************
�������ܣ���SPI������дһ�ֽ����ݻ�ָ��
���ݲ�����a��Ҫ���͵�����
����ֵ����
***************************************/
void spi_write_char_low(unsigned char w_dat)
{
 dat=w_dat; 
 SPI_MOSI=dat7;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat6;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat5;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat4;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat3;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat2;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat1;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
 SPI_MOSI=dat0;SPI_SCLK=0;SPI_SCLK=1;sd_delay(200);
}


/************************************
�������ܣ���SPI������дһ�ֽ����ݻ�ָ��
���ݲ�����a��Ҫ���͵�����
����ֵ����
***************************************/
void spi_write_char_high(unsigned char w_dat) 
{
 dat=w_dat; 
 SPI_MOSI=dat7;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat6;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat5;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat4;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat3;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat2;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat1;SPI_SCLK=0;SPI_SCLK=1;
 SPI_MOSI=dat0;SPI_SCLK=0;SPI_SCLK=1;
}


/************************************
�������ܣ���SPI�����ٶ�һ�ֽ����ݻ�ָ��
���ݲ�����a��Ҫ���͵�����
����ֵ����
***************************************/
unsigned char spi_read_char_low(void)
{
 SPI_MISO=1;
 SPI_SCLK=1;SPI_SCLK=0;dat7=SPI_MISO;sd_delay(200); 
 SPI_SCLK=1;SPI_SCLK=0;dat6=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat5=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat4=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat3=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat2=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat1=SPI_MISO;sd_delay(200);
 SPI_SCLK=1;SPI_SCLK=0;dat0=SPI_MISO;sd_delay(200);
 return (dat);
}


/************************************
�������ܣ���SPI���ٶ�һ�ֽ����ݻ�ָ��
���ݲ�����a��Ҫ���͵�����
����ֵ����
***************************************/
unsigned char spi_read_char_high(void)
{  
 SPI_MISO=1;
 SPI_SCLK=1;SPI_SCLK=0;dat7=SPI_MISO; 
 SPI_SCLK=1;SPI_SCLK=0;dat6=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat5=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat4=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat3=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat2=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat1=SPI_MISO;
 SPI_SCLK=1;SPI_SCLK=0;dat0=SPI_MISO;
 return (dat);
}

#endif

