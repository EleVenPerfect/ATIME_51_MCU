/************************************
�⹦�ܣ�SPIģʽSD�����ƿ�
��Ҫ�󣺳����Ѿ����룺
		#include <reg52.h>
		#include "atime_spi.h"    //����ʹ�ô˵ײ�⣬��Ϊ����SD���������õĶ������SPI�⡣
Ӧ�ú�����
		 unsigned char sd_res(void)
		 unsigned char sd_write512(unsigned long add, unsigned char a[])
		 unsigned char sd_read512(unsigned long add, unsigned char a[])
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  		���޸�ʱ�䡯
			  ATIME		���STC89C52		2014-03-03
			  			ֻ��ǰ256λ�������⡣
			  ATIME		�����				2014-03-26
			  			xdata�����Գ�ʼ��������
			  ATIME		�޸ĺ���			2014-03-26
			  			����ǿ�ɿ���
			  			sd_write512(unsigned long add, unsigned char a[])
		 				sd_read512(unsigned long add, unsigned char a[])
						������Ҫʹ�� sd_init(void)������ÿ�ε��ö�д����ǰ��������sd_init(void)����
			  ATIME		�޸ĺ���			2014-04-08
			  			ע�͵�����Ҫ�Ĳ���
						sd_write512(unsigned long add, unsigned char a[])
		 				sd_read512(unsigned long add, unsigned char a[])
						ע�͵���sd_init();	���ж�ȡ����д�룬��֮�����Գ��Խ��ע��
			  ATIME		ɾ�����õĺ���		2014-04-09
			  			unsigned char sd_init(void)
						��ʼ�������в���Ҫ�˹��̡�
����޸�ʱ�䣺2012-02-21
���ߣ� ATIME	��Ȩ����
ʵ������
#include <reg52.h>
#include "atime_serial.h"
#include "atime_spi.h"
#include "atime_spi_sdcard.h"

unsigned char xdata buff[512]={
0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,
0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,
0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,
0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,
0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,
1
};
	 


void main(void)
{
	unsigned int i;
	P0 =0X0F;
	serial_int(disable, baud9600, disable);
	for(i=0;i<100; i++);
	P0 =0X87;
	sd_res();
	P0 =0XC3;
	sd_write512(3,buff);
	P0 =0XE1;
	

	sd_read512(3,buff);
	P0 =0X0F;

	for(i=0; i<512; i++)
	{
		send_char(buff[i]);
		send_char(i);
	}
	P0 =0X00;
	while(1);
}





����������ͣ�
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д������������ǰ�漸��
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�

ע��SD���ոո�λ��ɺ󣬴����޷��������ݣ���Ҫִ��һЩ��д����ʼ��ָ���ſ��ԣ��������STC12���������֣���
	д��������ݻ�ʱSD�����ִ���
	��winhex�鿴ʱӦ��ѡ��������̶������߼����̣�����ʱ�õ�1G�Ŀ���FATĬ�ϸ�ʽ��
�������⣺��ȡ��д��ֻ��ǰ256λ����ȷ�ģ�
�����STC89C52�ڲ�xdataֻ��256byte��ֻ�ܴ洢256λ����Ҫ������Ƭ����
***************************************/

#ifndef _ATIME_SPI_SDCARD_H_ 
#define _ATIME_SPI_SDCARD_H_

/************************************
�������ܣ����ٷ�������
���ݲ�������
����ֵ��Ӧ��
***************************************/
unsigned char sd_write_zhi_low(unsigned char a[])
{
	unsigned char i,temp;
	SPI_CS =1;
	spi_write_char_low(0xff);
	SPI_CS =0;
	for(i=0; i<6; i++)
		spi_write_char_low(a[i]);
	i =0;
	do
	{
	 	temp =spi_read_char_low();
		i++;
	}
	while((temp==0xff)&&(i<100));
	return (temp);
}

/************************************
�������ܣ����ٷ���ָ��
���ݲ�������
����ֵ��Ӧ��
***************************************/
unsigned char sd_write_zhi_high(unsigned char a[])
{
	unsigned char i,temp;
	SPI_CS =1;
	spi_write_char_high(0xff);
	SPI_CS =0;
	for(i=0; i<6; i++)
		spi_write_char_high(a[i]);
	i =0;
	do
	{
	 	temp =spi_read_char_high();
		i++;
	}
	while((temp==0xff)&&(i<100));
	return (temp);
}



/************************************
�������ܣ���λSD��
���ݲ�������
����ֵ��0:�ɹ�;1:ʧ��
***************************************/
unsigned char sd_res(void)
{
	unsigned char temp ,i;
	unsigned char zhiling[] ={0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
	SPI_CS =1;
	for(i=0; i<0x0f; i++)
	{
		spi_write_char_low(0xff);
	}
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_low(zhiling);
		i++;
		if(i >=100)
		{
			SPI_CS =1;
			return (0x01);
		}
	}
	while(temp!=0x01);
	SPI_CS =1;
	spi_write_char_low(0xff);
	return (0);
}								


/************************************
�������ܣ���ʼ��SD��
���ݲ�������
����ֵ��0:�ɹ�;1:ʧ��
**************************************/
unsigned char sd_init(void)
{
	unsigned char i,temp;
	unsigned char zhiling[] ={0x41, 0x00, 0x00, 0x00, 0x00, 0xff};
	SPI_CS =1;
	for(i=0; i<=9; i++)
		spi_write_char_low(0xff);
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_low(zhiling);
		i++;
		if(i >=200)
		{
			SPI_CS =1;
			return (0x02);
		}
	}
	while(temp !=0X00);
	SPI_CS =1;
	spi_write_char_low(0xff);
	return (0);
}			   			 ////MMC���汾
/*
unsigned char sd_init(void)
{
	unsigned char i,temp;
	unsigned char zhiling[] ={0x77, 0x00, 0x00, 0x00, 0x00, 0xff};
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_low(zhiling);
		i++;
		if(i >=300)
		{
			SPI_CS =1;
			return (0x02);
		}
	}
	while(temp !=0X01);
	SPI_CS =1;
	spi_write_char_low(0xff);

	zhiling[0] =0x69;
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_low(zhiling);
		i++;
		if(i >=300)
		{
			SPI_CS =1;
			return (0x03);		 ///
		}
	}
	while(temp !=0X00);
	SPI_CS =1;
	spi_write_char_low(0xff);
	return (0);				
}						*///�����ð汾

/************************************
�������ܣ���SD��ĳ��ַд��512�ֽ�����
���ݲ�����add:��ַ   a[]����д������
����ֵ��0:�ɹ�;1:ʧ��
***************************************/
unsigned char sd_write512(unsigned long add, unsigned char a[])
{
	unsigned char temp;
	unsigned int i;
	unsigned char zhiling[] ={0x58, 0x00, 0x00, 0x00, 0x00, 0xff}; 
	sd_init();		   //��ʱ���ܻ���Ҫÿ�ζ�д�����г�ʼ��
	add <<=9;		   //addr = addr * 512	�����ַ��������ַ��תΪ�ֽڵ�ַ �������������SD�����������Ϊ4G��
	zhiling[1]=((add&0xff000000)>>24); 	
 	zhiling[2]=((add&0x00ff0000)>>16);
 	zhiling[3]=((add&0x0000ff00)>>8);
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_high(zhiling);
		i++;
		if(i ==100)
		{
			SPI_CS =1;
			return (temp);
		}
	}
	while(temp !=0);
	for(i=0; i<100; i++)
		spi_read_char_high();			//ԭ���Ƕ������ڸĳ���д
	spi_write_char_high(0xfe);
	for(i=0; i<512; i++)
		spi_write_char_high(a[i]);
	spi_write_char_high(0xff);
	spi_write_char_high(0xff);
	temp =spi_read_char_high();
	if(temp&0x1f !=0x05)	
	{
		SPI_CS =1;
		return (0x03);
	}
	while(spi_read_char_high()!=0xff);
	SPI_CS =1;
	spi_write_char_high(0xff);
	return (0);
}

/************************************
�������ܣ���SD��ĳ��ַ��ȡ512�ֽ�����
���ݲ�����add:��ַ   a[]����д������
����ֵ��0:�ɹ�;1:ʧ��
***************************************/
unsigned char sd_read512(unsigned long add, unsigned char a[])
{
	unsigned int i;
	unsigned char temp;
	unsigned char zhiling[] ={0x51, 0x00, 0x00, 0x00, 0x00, 0xff};
	sd_init(); 				 //��ʱ���ܻ���Ҫÿ�ζ�д�����г�ʼ��
	add <<=9;
	zhiling[1]=((add&0xff000000)>>24); 	
 	zhiling[2]=((add&0x00ff0000)>>16);
 	zhiling[3]=((add&0x0000ff00)>>8);
	SPI_CS =0;
	i =0;
	do
	{
		temp =sd_write_zhi_high(zhiling);
		i++;
		if(i ==100)
		{
			return (0x04);
		}
	}
	while(temp!=0);
	while(spi_read_char_high()!=0xfe);
	for(i=0; i<512; i++)
		a[i] =spi_read_char_high();
	spi_read_char_high();
	spi_read_char_high();
	SPI_CS =1;
	spi_write_char_high(0xff);
	return (0);
}


#endif