 /*******************************************************************************
*  ����:                  �������������ʾ�¶�                                  *
*																			    *
*********************************************************************************
*  1.ͨ���������˽� DLASS18b20�Ļ���ԭ���ʹ�� ,��Ⲣ����18B20��������ı�д	*
*  2.�˽�����I2C���߽ӿڵĹ���ԭ��һ���̷����� 								*
*    ����18B20 �۲�����ܵ�ʵ���¶���ʾ
*    �����߽�JP10(P0��) �� J12 ����	��������Ͽ��Կ��¶���ʾ					*
* 																				*
* ע�⣺18B20����ֻ����12Tģʽ�¹��� 6Tģʽ�Լ��޸���Ӧʱ��                     *
* ��ѧԱ�������������̣���DLASS18b20��C�����еĲ���                       	    *
********************************************************************************/
#include <reg52.H>

extern GetTemp();									   //���������ⲿ����
extern unsigned int  idata Temperature;	              // ���������ⲿ����
void delay(unsigned int i);

//else IO
sbit    LS138A=P2^2;       //�ܽŶ���
sbit    LS138B=P2^3;
sbit    LS138C=P2^4; 


//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
unsigned char code Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40}; 
unsigned long  LedOut[5],LedNumVal;


void system_Ini()
{
    TMOD|= 0x11;
    TH1 = 0xD8;    //10
    TL1 = 0xF0;	
	IE = 0x8A;	
    TR1  = 1;

}

main()
{ unsigned char i; 
  system_Ini();
    while(1)
   {	
	  GetTemp();

   	  /********���½���18b20�������͵�LED�������ʾ*************/
       LedNumVal=Temperature;      //��ʵ���¶��͵�LedNumVal������
	  LedOut[0]=Disp_Tab[LedNumVal%10000/1000];
      LedOut[1]=Disp_Tab[LedNumVal%1000/100];
      LedOut[2]=Disp_Tab[LedNumVal%100/10];	 //ʮλ
      LedOut[3]=Disp_Tab[LedNumVal%10];    //��λ
  	  
    for(i=0; i<4; i++) 
	  {		
		 P0 = LedOut[i] ;
	  			 	 	  	
		switch(i)					  
         {	    	  //138����
			case 0:LS138A=0; LS138B=0; LS138C=0; break;         
            case 1:LS138A=1; LS138B=0; LS138C=0; break;             	
            case 2:LS138A=0; LS138B=1; LS138C=0; break; 
            case 3:LS138A=1; LS138B=1; LS138C=0; break; 
         }
		 
		delay(100);
	  }

	  P0 = 0;  
  
    }
}

 //��ʱ����
void delay(unsigned int i)
{
    char j;
    for(i; i > 0; i--)
        for(j = 200; j > 0; j--);
}



