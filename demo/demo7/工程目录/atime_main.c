#include "STC12C5A60S2.H"		 //�����滻REG52.H������ʹ�����ͷ�ļ�
#include "atime_project.c"


void main()
{
		io_init();
	
		while(1)
		{
				get_gq_data();						//ͨ��I2C���߶�ȡ��ǰ��ǿ
				get_wlw_status();					//��ȡ������ģ�����鿪��״̬
				get_body_status();				//��ȡ�����Ӧģ��״̬	
			
				set_pwm_status();					//���ݹ�ǿ���������������
				set_led_status();					//����ledӦ���״̬
				set_led_output();					//����led���
			
				conversion(gq_int_status);
				send_char(wan);
				send_char(qian);
				send_char(bai);
				send_char(shi);
				send_char(ge);
				send_char('\n');
				delay_nms(200); 
		}
}