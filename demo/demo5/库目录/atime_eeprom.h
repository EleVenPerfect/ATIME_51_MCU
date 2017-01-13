/************************************
�⹦�ܣ�12��Ƭ��EEPROM��
��Ҫ�����������Ѷ��壺
		#include "STC15F2K60S2.H" 
Ӧ�ú�����	
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  	���޸�ʱ�䡯
			   ��			��				��
����޸�ʱ�䣺2014-04-29
���ߣ� ATIME	��Ȩ����
ʵ������
		#include "STC15F2K60S2.H" 
		#include "atime_eeprom.h"
		#include "atime_lcd1602.h"
		
		void main()
		{
				unsigned char i, j;
				int_lcd1602(rightmove, cursornotdisplay);
				i =eeprom_write( 0x00, 0x00, 0xff);
				j =eeprom_read( 0x00, 0x00);
				printint1602( i, 0, 1);
				printint1602( j, 1, 1);
				while(1);
		}


����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
***************************************/


#ifndef _ATIME_EEPROM_H_ 
#define _ATIME_EEPROM_H_


/************************************
��ȫ�ֱ�����
***************************************/
#define EEPROM_RW_FAIL	  0X00		//EEPROM��������
#define EEPROM_RW_SUCCESS 0X01		//EEPROM�����ɹ�

/************************************
�������ܣ�д��EEPROM����
���ݲ�����
����ֵ��EEPROM_RW_FAIL	 ��ʧ�ܣ�
		EEPROM_RW_SUCCESS���ɹ���	
***************************************/
unsigned char eeprom_write( unsigned char addh, unsigned char addl, unsigned char temp)
{
	IAP_CONTR =0X80;
	IAP_ADDRL =addl;
	IAP_ADDRH =addh;
	IAP_DATA =temp;
	IAP_CMD =0X02;
	IAP_TRIG =0X5A;
	IAP_TRIG =0X5A;
	if((bit)((IAP_CONTR&0x10)>>4) ==1)	  //�ж��Ƿ�ɹ�д��
	{
		IAP_CONTR =0X80;
		return (EEPROM_RW_FAIL);
	}
	return (EEPROM_RW_SUCCESS);
}

/************************************
�������ܣ���ȡEEPROM����
���ݲ�����
����ֵ��	
***************************************/
unsigned char eeprom_read( unsigned char addh, unsigned char addl)
{
	unsigned char temp;
	IAP_CONTR =0X80;
	IAP_ADDRL =addl;
	IAP_ADDRH =addh;
	IAP_CMD =0X01;
	IAP_TRIG =0X5A;
	IAP_TRIG =0X5A;
	if((bit)((IAP_CONTR&0x10)>>4) ==1)	  //�ж��Ƿ�ɹ���ȡ�ɹ�
	{
		IAP_CONTR =0X80;
		return (EEPROM_RW_FAIL);						  //����ֵΪ0�����Ƕ�ȡʧ��
	}
	temp =IAP_DATA;
	return (temp);
}




#endif