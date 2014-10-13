/**********************************************************************
*                                                                     *
*           TFTҺ�����¶Ⱥ�ʱ���ۺ���ʾ����                           *
*              ��  ���пƼ�  ��                                       *
*                                                                     *
* ʵ��Ŀ�ģ�1.����TFT������������ı�д��							  *
*           2.ѧ������ȡ��ģ���Ӧ��(ȡ�ַ��ͺ�������)				  *
*			3.ѧ������������ģ��������                                *
*                                                                     *                                                                     *
*ʵ������ ��������ʾ�¶Ⱥ�ʱ��                                      *
*                                                                     *
***********************************************************************/

#include <reg52.h>
#include <intrins.h>
#include "lcd.h"


unsigned char   Tempera_Val[3] ,temp;  //�¶�
unsigned char   RTC_Val[15];          //ʱ������
unsigned int xdata TIM,TIM1;    //���ڼ����ȡ�¶Ⱥ�ʱ��
extern unsigned int  idata Temperature;	 //�¶�
extern unsigned  char xdata D[8];    //��ȡʱ�ӷŵ�D������

extern void Read_RTC(void);
extern void GetTemp (void);
extern void Set_RTC(void); //set RTC 


/**********************************************************
         ���ö�ʱ������
 **********************************************************/
void Timer_Ini()
{
    TMOD|= 0x11;
    TH1 = 0xD8;    //10
    TL1 = 0xF0;	
	IE = 0x8A;	
    TR1  = 1;
}

/**********************************************************

  ������

**********************************************************/
void main(void)
{  
    P2 = 0xff;
    P0 = 0xff;

   	Timer_Ini();	 //��ʼ��
    LCD_init();      //��ʼ��
    LCD_clear(5);    //����
  
    ChineseChar(14,10,2,colors[2],colors[7],1);	  //��
    ChineseChar(38,10,2,colors[2],colors[7],2);	  //��
    ChineseChar(62,10,2,colors[2],colors[7],3);	  //��
    ChineseChar(86,10,2,colors[2],colors[7],4);	  //��
  
    ChineseChar(24,50,1,colors[2],colors[7],10);  //��
	ChineseChar(40,50,1,colors[2],colors[7],11);  //��
    ChineseChar(80,50,1,colors[2],colors[7],12);  //��

    ChineseChar(30,80,1,colors[2],colors[7],13);  //ʵ
	ChineseChar(46,80,1,colors[2],colors[7],14);  //ʱ
	ChineseChar(62,80,1,colors[2],colors[7],14);  //ʱ
    ChineseChar(76,80,1,colors[2],colors[7],15);  //��
   
	Set_RTC();

   while(1)	
  {	  
      if( TIM1 >= 10)  //ÿ�� 10ms ��ȡds1302
	  {
	    TIM1  =  0;
		Read_RTC();  //��ȡDS1302
	  }
        GetTemp();
		//*****�¶�***********************
        Tempera_Val[0] = Temperature%100/10 + 0x30;    //Temperature;
        Tempera_Val[1] = Temperature%10 + 0x30;

		//******��***********************
		temp =   ((D[4]&0x70)>>4)*10 + (D[4]&0x0f);	  
		RTC_Val[0] = temp/10 + 0x30;     //��10λת��ASCII��
		RTC_Val[1] = temp%10 + 0x30;     //����λת��ASCII��
		
		RTC_Val[2] = '-'  ;	     //�̺���
		 //*****��***********************
		temp =   ((D[3]&0x70)>>4)*10 + (D[3]&0x0f);	  
		RTC_Val[3] =  temp/10 + 0x30;
		RTC_Val[4] =  temp%10 + 0x30;
		RTC_Val[5] = ' '  ;
		//******ʱ***********************
		temp =   ((D[2]&0x70)>>4)*10 + (D[2]&0x0f);	   
		RTC_Val[6] = temp/10 + 0x30;
		RTC_Val[7] = temp%10 + 0x30;

		RTC_Val[8] = ':'	;	  //ð��
		 //******��***********************
		temp =   ((D[1]&0x70)>>4)*10 + (D[1]&0x0f);	  
		RTC_Val[9] =  temp/10 + 0x30;
		RTC_Val[10] = temp%10 + 0x30;

		RTC_Val[11] = ':';
		 //******��***********************
	    temp =   ((D[0]&0x70)>>4)*10 + (D[0]&0x0f);		
		RTC_Val[12] = temp/10 + 0x30;
		RTC_Val[13] = temp%10 + 0x30;

	  	   
	    LCD_ShowString(60,50,colors[7],colors[2], Tempera_Val); //���ַ��͵���������ʾ
		LCD_ShowString(10,100,colors[7],colors[2], RTC_Val);     //���ַ��͵���������ʾ

  }  
}


/*************************************
 [ t1 (10ms)�ж�] �ж�
*************************************/
void T1zd(void) interrupt 3 
{
   TH1 = 0xD8;    //10
   TL1 = 0xF0;
   TIM++;
   TIM1++;
}



