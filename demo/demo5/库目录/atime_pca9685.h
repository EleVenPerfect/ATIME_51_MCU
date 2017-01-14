/************************************
�⹦�ܣ�PCA9685
��Ҫ�����������Ѷ��壺
		#include <reg52.h>
Ӧ�ú�����
			key4_4( )
�޸���ʷ��
		   	 ���޸��ˡ�   ���޸����ݡ�  ���޸�ʱ�䡯
				��			��			��
����޸�ʱ�䣺2014-01-29
���ߣ� ATIME	��Ȩ����
ʵ������

����������ͣ�
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	������ĺ�����û�е��ù��ģ�һ����Ժ��Դ˾���
	123.C(7): error C202: 'riht1602': undefined identifier	 ����������ƴд���󣬸���ƴд���󼴿�
	123.C(14): error C214: illegal pointer conversion    ��Ҫ��������ַ���������������ַ�
***************************************/


#ifndef _ATIME_PCA9685_H_ 
#define _ATIME_PCA9685_H_

#include "atime_iic.h"

/************************************
��ȫ�ֱ�����
***************************************/

#define PCA9685_ADDR 		0x80			//����PCA9685Ӳ����ַ
#define PCA9685_MODE1 		0x00
#define PCA9685_PRESCALE	0xfe
#define LED0_ON_L 			0x6
#define LED0_ON_H 			0x7
#define LED0_OFF_L 			0x8
#define LED0_OFF_H 			0x9
/************************************
�������ܣ�д���ݵ�ָ����ַ
���ݲ�����transdata������
		  addr	   ��ָ����ַ
����ֵ����	
***************************************/
void pca9685_write( unsigned char addr, unsigned char transdata)
{
	iic_write_char( PCA9685_ADDR, addr, transdata);
}



/************************************
�������ܣ���ָ����ַ����
���ݲ�����
		  addr	   ��ָ����ַ
����ֵ��transdata������
***************************************/
unsigned char pca9685_read( unsigned char addr)
{
	unsigned char transdata;
	transdata = iic_read_char( PCA9685_ADDR, addr);
	return transdata;
}



/************************************
�������ܣ���λ
���ݲ�������
����ֵ����	
***************************************/
void pca9685_reset()
{
	pca9685_write( PCA9685_MODE1, 0x0);
}


/************************************
�������ܣ�����Ƶ��
���ݲ�����freq��Ƶ��
����ֵ����	
***************************************/
void pca9685_setfreq(float freq)
{
	unsigned char lastmode,newmode,prescale;
	float prescaleval;
	freq *= 0.92;  // Correct for overshoot in the frequency setting
	prescaleval = 6103.515;
	prescaleval /= freq;
    prescaleval -= 1;
    prescale = (unsigned char)(prescaleval + 0.5);	

	lastmode = pca9685_read(PCA9685_MODE1);
	newmode = (lastmode&0x7F)|0x10; // sleep
	pca9685_write( PCA9685_MODE1, newmode);
	pca9685_write( PCA9685_PRESCALE, prescale);
	pca9685_write( PCA9685_MODE1, lastmode);
	for( newmode=0; newmode<200; newmode++);   //��ʱ
	pca9685_write( PCA9685_MODE1,lastmode|0xa1);
}

/************************************
�������ܣ�����ռ�ձ�
���ݲ�����
����ֵ����	
***************************************/
void pca9685_setpwm(unsigned char num, unsigned int on, unsigned int off) 
{
    pca9685_write(LED0_ON_L+4*num,on);
    pca9685_write(LED0_ON_H+4*num,on>>8);
    pca9685_write(LED0_OFF_L+4*num,off);
    pca9685_write(LED0_OFF_H+4*num,off>>8);
}

#endif