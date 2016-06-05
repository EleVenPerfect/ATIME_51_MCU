#include "STC12C5A60S2.H" 
#include "atime_lcd1602.h"
#include "atime_18b20.h"
#include "atime_serial.h"
#include "atime_timer.h"
#include "atime_interrupt.c"


void main()
{
	unsigned char display_temp[8];		//��ʾ����

	jdq_1 = 1;
	jdq_2 = 1;							//Ϊ1ʱ����
	serial_int(enable, baud9600, disable); //���ڳ�ʼ��
	int_lcd1602( rightmove, cursornotdisplay); //1602��ʼ��
	int_interrupt( 0, negative_jump);		   //�ⲿ�ж�0���½��ش���
	int_interrupt( 1, negative_jump);
	main_timer(on,0);						//������ʱ��
	timer_8_int(0,240,normal);				//��ʱ������240�������������������ж�
	main_interrupt(on);						//�������ж�

	while(1)
	{
		/*��ʾ������ֵ*/
		display_temp[0] = temp_set%100/10+0x30;	 //�κ����ּ�0x30ת��Ϊ������ʾ��ASCII��
		display_temp[1] = temp_set%10+0x30;
		display_temp[2] = '\0';
		print1602( display_temp, 0,14);
		printchar1602(' ', 1, 15);


		/*��ȡ�¶ȴ�����1����ʾ������ȡ�¶�Ϊ85ʱΪ�������ݣ�����ʾ*/
		ds18b20_1_exist =int_18b20_1();	//�жϴ������Ƿ����
		if( ds18b20_1_exist ==0 )		   //Ϊ0ʱ����
		{
			temperature1 = read_temper_1();	  //��ȡ�¶�����
			if(temperature1<85.0)			  //ȥ��������һ����ʾ�Ĵ�������
			{
				translate( temperature1, display_temp);	//��float������ת��Ϊ������ʾ�����ݲ��ŵ���ʾ����
				print1602( display_temp, 0, 0);			//��ʾ
			}
		}
		else											//��������
		{
			print1602( "Check 1", 0, 1);
			waitms(500);								 //�����ʾ������
			clear1602_10(0);
		}
		/*��ȡ�¶ȴ�����2������ȡ�¶�Ϊ85ʱΪ�������ݣ�����ʾ*/
		ds18b20_2_exist =int_18b20_2();
		if( ds18b20_2_exist ==0 )
		{
			temperature2 = read_temper_2();
			if(temperature2<85.0)
			{
				translate( temperature2, display_temp);
				print1602( display_temp, 1, 0);
			}
		}
		else
		{
			print1602( "Check 2", 1, 1);
			waitms(500);
			clear1602_10(1);
		}
		waitms(300);
	}
}
