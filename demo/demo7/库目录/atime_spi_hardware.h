/************************************
�⹦�ܣ�Ӳ��SPI�ӿڿ� BETA
��Ҫ�󣺳����Ѿ����룺
		#include "STC12C5A60S2.H"
Ӧ�ú�����
		 unsigned char spi_hardware_init( enum spi_enable a, enum spi_first b, unsigned char t, enum spi_first d)
		 void spi_send_char( unsigned char temp)
		 unsigned char spi_wr_char(unsigned char temp)
		 void spi_main(enum spi_enable a) 
		 void spi_interrupt(void) interrupt 9   ##SPI�жϷ����� 
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-04-26
���ߣ� ATIME	��Ȩ����
ʵ������
			#include "STC12C5A60S2.H" 	
			#include "atime_lcd1602.h"
			#include "atime_spi_hardware.h"
			
			
								  
			void main()
			{
				unsigned char temp =0xaa;
				int_lcd1602(rightmove, cursornotdisplay);
				spi_hardware_init( spi_enable, spi_high, 3, spi_low);
				
				print1602("ATIME", 0, 3);
				spi_main(spi_enable);
				spi_send_char(0x01);
				spi_send_char(0x01);
				spi_send_char(0x01);
				spi_send_char(0x01);
				while(1);
			}
			�жϳ���
			char i=0x30;
			void spi_interrupt(void) interrupt 9
			{
				SPSTAT =0XC0;		//��ձ�־λ���˾�Ҫ����
				i++;
				printchar1602(i, 1, 3);
				waitms(500);
				set1602(clear1602);
			}

����������ͣ�
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д������������ǰ�漸��
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
˵�����˺�������Ӳ��SPI�����⣬��֧��STC12ϵ�д���Ӳ��SPI���ܵĵ�Ƭ������������STC12C5A60S2�ϲ��ԣ����ܱ�֤������ƽ̨�Ͽɿ���
	  ����Ŀǰ��δ����ʵ��оƬ���ԣ����ܱ�֤��ȷ�ԡ�
***************************************/


#ifndef _ATIME_SPI_HARDWARE_H_ 
#define _ATIME_SPI_HARDWARE_H_


/************************************
��ȫ�ֱ�����
***************************************/
 
enum spi_enable{ spi_enable, spi_disable}; //SPI����
enum spi_first{ spi_high, spi_low};		   //SPI�ߵ�λ����

/************************************
�������ܣ�SPI��ʼ��
���ݲ�����
		a��SPI�������ر�ѡ��
		b��SPI���ݷ���˳�����
		d��SPI����ʱ�ߵ͵�ƽ����
		t��SPI�ٶ�ѡ��1/4	��1/16��1/64��1/128	����
				��Ӧ�� 	 0  �� 1  ��  2	��  3
����ֵ��0��ʧ��
		1���ɹ�
***************************************/
unsigned char spi_hardware_init( enum spi_enable a, enum spi_first b, unsigned char t, enum spi_first d)
{
	unsigned char temp;
	temp =0x94;						//Ĭ������SS������ΪI/O��ʹ�ã�����ΪƬѡ�ź�
	if(a == spi_enable)
		temp |=0x40;
	if(b == spi_low)
		temp |=0x20;
	if(d == spi_high)
		temp |=0x08;
	if(t > 3 || t < 0)
		return (0);
	temp +=t;
	SPCTL =temp;
	return (1);		
}

/************************************
�������ܣ�SPI��������
���ݲ�����temp������������
����ֵ����
***************************************/
void spi_send_char( unsigned char temp)
{
	SPSTAT =0xC0;
	SPDAT =temp;
	while(!(SPSTAT & 0x80));
	SPSTAT =0xC0;	
}


/************************************
�������ܣ�SPIд�벢��ȡ����
���ݲ�����д��
����ֵ������������
***************************************/
unsigned char spi_wr_char(unsigned char temp)
{
	SPSTAT =0XC0;
	SPDAT =temp;
	while(!(SPSTAT & 0X80));
	temp =SPDAT;
	SPSTAT =0XC0;
	return (temp);	
}


/************************************
�������ܣ�SPI�жϿ���
���ݲ���������״̬
			spi_enable,spi_disable
����ֵ����
***************************************/
void spi_main(enum spi_enable a) 
{
	if(a == spi_enable)
	{
		EA =1;
		IE2 |=0X02;
	} 
	if(a == spi_disable)
	{
		EA =0;
		IE2 &=0XFD;
	}
}

/************************************
�������ܣ�SPI�жϺ���
���ݲ�������
����ֵ����
***************************************/
void spi_interrupt(void) interrupt 9
{
	SPSTAT =0XC0;		//��ձ�־λ���˾�Ҫ����

}									  

#endif