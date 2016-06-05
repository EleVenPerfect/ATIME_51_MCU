/************************************
�⹦�ܣ�Ӳ��PWM/PAC��
��Ҫ�󣺳����Ѿ����룺
		#include ��STC12C5A60S2��
Ӧ�ú�����
		  void pwm_init( enum pwm_switch a, unsigned char pwm , unsigned char f)
		  unsigned char pwm_set( unsigned char f, float pp)
		  void pwm_contral( enum pwm_switch a)
		  unsigned char pca_init( unsigned char a, unsigned char b, enum pwm_switch c)
		  void pca_contral( enum pwm_switch a)
		  unsigned int pca_read( unsigned char a)
		  void pca_interrupt0(void) 				//PCA0�жϷ�����
		  void pca_interrupt1(void) 				//PCA1�жϷ�����
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-04-30
���ߣ� ATIME	��Ȩ����
ʵ������
���ܣ���·PWM�����
		#include "STC12C5A60S2.H" 	
		#include "atime_pwmpac.h"
		
		void main()
		{
			P1 =0XFF;
			pwm_init( on, 1, 0x02);
			pwm_init( on, 0, 0x02);
			pwm_set(0, 37.5);
			pwm_set(1, 12.5);
			pwm_contral( on);
			while(1);	  
		}

����������ͣ�
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д������������ǰ�漸��
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
ע�⣺�⺯���ڲ��Ѿ����ж�����ΪPC0��PCA1�����жϣ���PCA0���ȼ���PCA1���ȼ��ߣ�
	  �ұ�־λ�Ѿ��Զ�������㡣
***************************************/

#ifndef _ATIME_PWMPCA_H_ 
#define _ATIME_PWMPCA_H_

/************************************
��ȫ�ֱ�����
***************************************/
sfr PCAPWM0     =   0xf2;
sfr PCAPWM1     =   0xf3;
enum pwm_switch { on, off};
/************************************
�������ܣ�PWM��ʼ������
���ݲ�����
		a	:PWM��������
		pwm :PWMͨ��ѡ��0~1��
		f	:��Ƶϵ�����ã�1~255��
����ֵ����	
ע����Ƶϵ���������PWM��Ƶ�ʵĵ��ڲ�����
			  ��ϵͳʱ�ӵ�256��Ƶ���ڷ�Ƶ������
			  ����ͨ�����Ƶ��һ�£���һ�µĻ��������һ�����õ�Ϊ׼��
***************************************/
void pwm_init( enum pwm_switch a, unsigned char pwm , unsigned char f)
{
	CCON =0X40;
	CMOD =0X84;  				//Ĭ��������T0���������Ϊ����Դ 
								//����ģʽ�����ɹ���
								//������CF�ж�
	CL =0;
	CH =0;
	AUXR |=0X80;			  	//��ʱ������
	ET0 =0;
	TMOD =TMOD|0X02;
	f =0x100-f;
	TL0 =TH0 =f;
	if(pwm == 0)
	{
		if(a == on)
		{
			CCAPM0 =0x42;
			P1M1 &=0XF7;
			P1M0 &=0XF7;
		}
		else 
			CCAPM0 =0X00;	
	}
	if(pwm == 1)
	{
		if(a == on)
		{
			CCAPM1 =0x42;
			P1M1 &=0XEF;
			P1M0 &=0XEF;
		}
		else
			CCAPM1 =0X00;	
	}		
}


/************************************
�������ܣ�����ռ�ձ�
���ݲ�����
		f: ͨ��ѡ��
		pp:ռ�ձ����ã�������0.0~100.0��
����ֵ��0:ʧ��
		1:�ɹ�	
***************************************/
unsigned char pwm_set( unsigned char f, float pp)
{
	unsigned char a;
	if(pp > 100.0 || pp < 0)
		return(0);
	a =(unsigned char)(((100-pp)*256)/100);
	if(f == 0)
	{
		CCAP0H =CCAP0L =a;		
		PCAPWM0 =0X00;
	}
	if(f == 1)
	{
		CCAP1H =CCAP1L =a;		
		PCAPWM1 =0X00;
	}
	return (1);
}

/************************************
�������ܣ�PWM�������
���ݲ���������״̬
����ֵ����	
***************************************/
void pwm_contral( enum pwm_switch a)
{
	if(a == on)
	{
		CR =1;
		TR0 =1;
	}
	else 
	{
		CR =0;
		TR0 =0;
	}
}



/************************************
�������ܣ�PCA��ʼ��
���ݲ�����
		a:PCAѡ��
		b:0�������ز�׽
		  1���½��ز�׽
		  2���������½��ز�׽
		c:�жϿ���
����ֵ��0��ʧ��
		1���ɹ�	
***************************************/
unsigned char pca_init( unsigned char a, unsigned char b, enum pwm_switch c)
{
	unsigned char temp;
	CL = 0;                     
    CH = 0;
	CCON =0X00;
	if(c == on)
	{
		CMOD =0X89;					   //Ĭ��������Ƶ��Ϊ��׼
		EA =1;
	}
	else 
	{
		CMOD =0X88;
		EA =0;
	}
	if(a == 0)
	{
		P1M1 &=0XF7;
		P1M0 &=0XF7;
		CCAP0L = 0;
   		CCAP0H = 0;
		switch(b)
		{
			case 0 :temp =0x20;break;
			case 1 :temp =0x10;break;
			case 2 :temp =0x30;break;
			default: return (0);
		}
		if(c == on)
			temp |=0x01;	
		CCAPM0 =temp;	
	}
	if(a == 1)
	{
		P1M1 &=0XEF;
		P1M0 &=0XEF;
		CCAP1L = 0;
    	CCAP1H = 0;
		switch(b)
		{
			case 0 :temp =0x20;break;
			case 1 :temp =0x10;break;
			case 2 :temp =0x30;break;
			default:return (0);
		}
		if(c == on)
			temp |=0x01;
		CCAPM1 =temp;	
	}
	return (1);
}



/************************************
�������ܣ�PCA���п���
���ݲ�����a:
			on����ʼ����
			off:ֹͣ����
����ֵ����	
***************************************/
void pca_contral( enum pwm_switch a)
{
	if(a == on)
		CR =1;
	else 
		CR =0;
}


/************************************
�������ܣ�PCA��ǰ����ֵ��ȡ
���ݲ�������
����ֵ������ֵ	
***************************************/
unsigned int pca_read( unsigned char a)
{
	if(a == 0)
		return ( CCAP0L+CCAP0H*256);
	if(a == 1)
	    return( CCAP1L+CCAP1H*256);

	return (0);
}


/****************************************************
�������ܣ�PCA�жϷ������
�����������
����ֵ����
ע�⣺�벻Ҫ�޸Ĵ˺���
****************************************************/
void pca_interrupt0(void);
void pca_interrupt1(void);
void ad_interrupt(void)	interrupt 7 
{
	CF =0;					//�������
	if(CCF0 == 1)
	{
		CCF0 =0;
		pca_interrupt0();	
	}
	if(CCF1 == 1)
	{
		CCF1 =0;
		pca_interrupt1();
	}
}

/************************************
�������ܣ�PCAͨ��0�жϷ�����
���ݲ�������
����ֵ����	
ע�⣺�벻Ҫ�޸Ĵ˺�������
***************************************/
void pca_interrupt0(void)
{

}



/************************************
�������ܣ�PCAͨ��1�жϷ�����
���ݲ�������
����ֵ����	
ע�⣺�벻Ҫ�޸Ĵ˺�������
***************************************/
void pca_interrupt1(void)
{

}





												

#endif