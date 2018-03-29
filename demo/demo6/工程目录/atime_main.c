#include "STC12C5A60S2.H"		 //�����滻REG52.H������ʹ�����ͷ�ļ�
#include "atime_pwmpca.h"
#include "atime_iic.h"

sbit led0 = P1^0;
sbit led1 = P1^1;
sbit led2 = P1^2;
sbit led_gnd = P1^3;

sbit wlw_high = P1^4;
sbit wlw_k0 = P1^5;
sbit wlw_k1 = P1^6;
sbit wlw_k2 = P1^7;

sbit body0 = P3^0;
sbit body1 = P3^1;

unsigned char body_set = 0;//״̬�洢���Ƿ������忿�������ĵƹ�����0�����ǣ�1��������Ϊ���忿�������ĵƹ�����

void main()
{
		P1 = 0XFF;
		P1M1 = 0x00;
		P1M0 = 0x17;//����P1�˿����״̬
		P3 = 0xff;//����P3�˿����״̬
		pwm_init( pwm_on, 0, 0x02);
		pwm_set(0, 100.0);

		while(1)
		{
				//ͨ��I2C���߶�ȡ��ǰ��ǿ
				//��ȡ������ģ�����鿪��״̬
				//��ȡ�����Ӧģ��״̬	
				//���ݹ�ǿ���������������
				if( body_set==1 )//�������Ϊ���忿�������ĵƹ�����
				{
						//�������Ӧģ��仯ʱ��Ҫ�������õƹ�״̬
						//��������ģ�鷢��ָ��ʱ��Ҫ�������õƹ�״̬
				}
				else
				{
						//��������ģ�鷢��ָ��ʱ��Ҫ�������õƹ�״̬
				}					
		}
}