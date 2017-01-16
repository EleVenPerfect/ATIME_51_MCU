/************************************
�⹦�ܣ�IICͨѶ��
��Ҫ�󣺳����Ѿ����룺
		#include "STC12C5A60S2.H"
Ӧ�ú�����
		iic_write_char(unsigned char outside_address, unsigned char inside_address, unsigned char a)
		iic_read_char(unsigned char outside_address, unsigned char inside_address)
		iic_read_current_char(unsigned char outside_address)
		iic_read(unsigned char outside_address, unsigned char inside_address, unsigned int n, unsigned char a[])
�޸���ʷ��
		   	 ���޸��ˡ�   	���޸����ݡ�  	 		���޸�ʱ�䡯
			  ATIME		 ����iic_read����	 		2014-02-09
			  ATIME		 �޸ĺ���					2014-05-01
			  			 iic_read(��
			  			 �޸ĺ�����STC12ϵ�еļ�����
����޸�ʱ�䣺2014-02-08
���ߣ� ATIME	��Ȩ����
ʵ������
***************************************************************
				24C08����ʵ�������洢������0-Zʱ��ֱ������eepROM���ݷ����塮0����
				#include <reg52.h>
				#include "atime_iic.h"
				#include "atime_lcd1602.h"
				
				void main()
				{
					unsigned char i =0x05;
					int_lcd1602(rightmove, cursornotdisplay);
					i =iic_read_char(0xa0,2);
					if(i <0x30)
						i =0x30;
					else 
						if(i >0x5a)
							i =0x30;
					while(1)
					{
						printchar1602(i, 1, 6);
						waitms(1000);
						i++;
						iic_write_char(0xa0,2,i);
					}
				}
************************************************************
				PCF8591����ʵ����ADת������ʾ��ת������char���
				ע������PCF8591�ڲ�ת��ʱ�򣬵�ǰ��ȡ��������֮ǰͨ��ADת���Ľ����
				�������⣺��һ�������Ǵ�λ�ģ���һλ����ż����͵���λ������ֵͬ��
				#include <reg52.h>
				#include "atime_lcd1602.h"
				#include "atime_iic.h"
				
				
				
				void main()
				{
					unsigned char a[5],b[15];
					a[4] =0x00;
					int_lcd1602(rightmove, cursornotdisplay);
					while(1)
					{
						iic_read(0x90,0x44,4,a) ;
				
						bcd_trans_char(a,b,4);
						print1602(b,2,1);
						waitms(500);
					}
				} 
************************************************************
����������ͣ�
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д������������ǰ�漸��
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
ע���������Ķ�д�����м������ʱ
	�ڲ���ַΪ00H~FFH
    PCF8591������6M���������У�����IICʱ�������⵼�¶�ȡ������ң���������δ����ԭ��
***************************************/


#ifndef _ATIME_IIC_H_ 
#define _ATIME_IIC_H_


/************************************
��ȫ�ֱ�����
***************************************/

sbit SCL =P1^7;            //����ʱ������SCLλ
sbit SDA =P1^6; 		   //������������SDAλ

/************************************
�������ܣ���ʱ��Լn ����us
���ݲ�����n ʱ��
����ֵ����	
ע�⣺�˺������ܾ�ȷ��ʱ
***************************************/
void wait_iicbus()
{
	int i;
	for(i=0; i<10; i++)
	{
		;
	}	
	
}


/************************************
�������ܣ�IIC��ʼ��־
���ݲ�������
����ֵ����
***************************************/
void iic_start(void)
{
	SDA =1;
	wait_iicbus();
	SCL =1;
	wait_iicbus();
	SDA =0;
	wait_iicbus();
	SCL =0;
	wait_iicbus();
}


/************************************
�������ܣ�IIC��ֹ��־
���ݲ�������
����ֵ����
***************************************/
void iic_stop(void)
{
	SDA =0;
	wait_iicbus();
	SCL =1;
	wait_iicbus();
	SDA =1;
	wait_iicbus();
	SCL =1;
	wait_iicbus();
}


/************************************
�������ܣ�IICӦ��ʶ��
���ݲ�������
����ֵ��0����ȷ���䣻 1��������
***************************************/
bit iic_ask_judge(void)
{
	bit ask;
	SCL =0;
	wait_iicbus();
	SDA =1;
	wait_iicbus();
	SCL =1;
	wait_iicbus();
	ask =SDA;
	SCL =0;
	wait_iicbus();
	return (ask);
}



/************************************
�������ܣ��յ����ݵ�IICӦ��
���ݲ�������
����ֵ����
***************************************/
void iic_ask_receive(void)
{
	unsigned char i;
	SDA =0;
	wait_iicbus();
	SCL =1;
	for(i=0; i<1; i++);
	SCL =0;
	wait_iicbus();
	SDA =1;
	wait_iicbus();
}


/************************************
�������ܣ��յ����ݵ�IIC��Ӧ��
���ݲ�������
����ֵ����
***************************************/
void iic_ask_not_receive(void)
{
	unsigned char i;
	SDA =1;
	wait_iicbus();
	SCL =1;
	for(i =0; i<1; i++);
	SCL =0;
	wait_iicbus();
	SDA =0;
	wait_iicbus();
}




/************************************
�������ܣ�IIC ����һ���ַ�����ָ��
���ݲ�����a������������
����ֵ����
***************************************/
void iic_writeachar(unsigned char a)
{
	unsigned char i;

	SCL =0;
	for(i =0; i<=7; i++)
	{
		SDA =(bit)(a&0x80);
		wait_iicbus();
		SCL =1;
		wait_iicbus();
		SCL =0;
		wait_iicbus();
		a =a<<1;
	}
}



/************************************
�������ܣ���IIC��ȡһ���ַ����ݻ�ָ��
���ݲ�������
����ֵ����ȡ�����ݻ�ָ��
***************************************/
unsigned char iic_readachar(void)
{
	unsigned char i, a;

	SCL =0;
	wait_iicbus();
	for(i=0; i<=7; i++)
	{
		SCL =1;
		wait_iicbus();
		a =a<<1;
		a |=(unsigned char)SDA;
		SCL =0;
		wait_iicbus();	
	}
	return (a);
}


/************************************
�������ܣ���ָ��IICоƬ��ָ��оƬ�ڵ�ַ��������
���ݲ�����
		  outside_address��Ƭѡ��ַ
		  inside_address ��Ƭ�ڵ�ַ
		  a				 ������������
����ֵ��0:�ɹ�  1:ʧ��
***************************************/
bit iic_write_char(unsigned char outside_address, unsigned char inside_address, unsigned char a)
{
	bit ok =1;
	iic_start();
	iic_writeachar(outside_address&0xfe);
	if(iic_ask_judge()==0)
	{
		iic_writeachar(inside_address);
		if(iic_ask_judge()==0)
		{
			iic_writeachar(a);
			if(iic_ask_judge()==0)
			{
				iic_stop();
				ok =0;
			}
		}
	}
	return (ok);	
}



/************************************
�������ܣ���ָ��оƬָ����ַ��ȡһ�ֽ�����
���ݲ�����
		  outside_address��Ƭѡ��ַ
		  inside_address ��Ƭ�ڵ�ַ
����ֵ��a����ȡ������
ע���������ֵ���ǡ�E�����ȡ���̴���
***************************************/
unsigned char iic_read_char(unsigned char outside_address, unsigned char inside_address)
{
	unsigned char a =0x45;

	iic_start();
	iic_writeachar(outside_address&0xfe);
	if(iic_ask_judge()==0)
	{
		iic_writeachar(inside_address);
		if(iic_ask_judge()==0)
		{
			iic_start();
			iic_writeachar(outside_address|0x01);
			if(iic_ask_judge()==0)
			{
				a =iic_readachar();
				iic_stop();
			}
		}
	}
	return (a);			
}


/************************************
�������ܣ���ȡָ��оƬ��ǰ��ַһ�ֽ�����
���ݲ�����outside_address��Ƭѡ��ַ
����ֵ��a����ȡ������
ע����ַ����������Ϊ�������ֽڵĵ�ַ�� 1Ҳ����˵����ϴζ�/д
�Ĳ�����ַΪN ���������ĵ�ַ�ӵ�ַN+1��ʼ
***************************************/
unsigned char iic_read_current_char(unsigned char outside_address)
{
	unsigned char a;
	iic_start();
	iic_writeachar(outside_address|0x01);
    if(iic_ask_judge()==0)
	{
		a =iic_readachar();
    	iic_stop();
	}
	return (a);	
}


/************************************
�������ܣ���ȡn������
���ݲ�����
		  outside_address��Ƭѡ��ַ
		  inside_address ��Ƭ�ڵ�ַ
		  n��	��ȡ���ֽ���
		  a[]����ȡ����������
����ֵ��������a��������
ע��������֧��������ȡ��оƬ��Ҫ֪����Ҫ�յ���������
***************************************/
void iic_read(unsigned char outside_address, unsigned char inside_address, unsigned int n, unsigned char a[])
{
	unsigned char temp;
	unsigned int i =0;
	SCL =0;
	iic_stop();
	iic_start();
	iic_writeachar(outside_address&0xfe);		   //αд����������ַָ��Ŀ��λ��
	if(iic_ask_judge()==0)
	{
		iic_writeachar(inside_address);
		if(iic_ask_judge()==0)
		{											
			iic_start();
			iic_writeachar(outside_address|0x01);  //дҪ��ȡ�ĵ�ַ 
			if(iic_ask_judge()==0)
			{
				i =0;
				while(i <n-1)
				{
					temp =iic_readachar();
					a[i++] =temp;
				    iic_ask_receive();			  //�յ���������Ӧ��
				}
				temp =iic_readachar();			  //���һ�ζ�ȡ����ҪӦ��
				a[i++] =temp;
				iic_ask_not_receive();
			}
			iic_stop();
		}	
	}		
}




#endif