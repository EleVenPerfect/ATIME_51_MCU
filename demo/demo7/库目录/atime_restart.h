/************************************
�⹦�ܣ���������λ
��Ҫ�����������Ѷ��壺
		#include ��STC12C5A60S2��
Ӧ�ú�����
		 void rstart(void)
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  				      �޸�ʱ�䡯
				��			��								��
������ʱ��:2014-04-27
���ߣ� ATIME	��Ȩ����
ʵ������
	#include "STC12C5A60S2.H"
	#include "atime_restart.h"

	void waitms(unsigned int n)
	{
		int i;
		while(n--)
		{
			for( i=0; i<580; i++);
		}
	}

	void main()
	{
		P0 =0XF0;
		waitms(500);
		P0 =0x0f;
		waitms(500);
		restart();
		while(1);
	}

����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(13): warning C182: pointer to different objects  :�������������תΪchar���������
	ATIME_DS1302.H(30): error C231: 'P0': redefinition  :  �ظ������˱���  ��������������������#define���д��������������漴��
***************************************/

#ifndef _ATIME_RESTART_H_ 
#define _ATIME_RESTART_H_


/**************************************
�������ܣ���������λ
���ݲ�������
����ֵ����
***************************************/
void restart(void)
{
	IAP_CONTR =0X60;
}

#endif	