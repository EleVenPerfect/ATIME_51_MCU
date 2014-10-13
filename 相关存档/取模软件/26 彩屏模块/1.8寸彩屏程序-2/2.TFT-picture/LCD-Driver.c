
/**********************************************************
*                   									  *
*				   ������������							  *
*														  *
**********************************************************/

#include <reg52.h>
#include <intrins.h>
#include "LCD.h"
#include "picture.h"


uint colors[]=
{
  0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xffff
};

/**********************************************************

 ��ʱ�Ӻ���

**********************************************************/
void delay_ms(uint ms)
{
  unsigned char k;

  while (ms--)
  {
    for (k = 0; k < 228; k++)
      ;
  }
}

/**********************************************************

 д8λ�����Ӻ���

**********************************************************/
void WriteDAT(uchar value)    // color data
{
	LCD_CS =  0;
	LCD_RS 	= 1;
//	LCD_WR  = 0;
	DATA 	= value;
    LCD_WR  = 0;
	LCD_WR  = 1;
   	LCD_CS =  1;
}

/**********************************************************

 д8λ�����Ӻ���

**********************************************************/
void WriteCOM(uchar value)    // color data
{
	LCD_CS  =  0;
	LCD_RS 	=  0;
//	LCD_WR  =  0;
	DATA 	=  value;
	LCD_WR  =  0;
	LCD_WR  =  1;
   	LCD_CS  =  1;
}


/**********************************************************

������ʾ�����Ӻ���

**********************************************************/
void LCD_SetRamAddr(uint xStart, uint xEnd, uint yStart, uint yEnd) 
{
	WriteCOM(0x2a);		   //��
	WriteDAT(xStart>>8);   //XS15-XS8
	WriteDAT(xStart);	   //XS7-XS0    (X start address)
	WriteDAT(xEnd>>8);	   //XE15-XE8
	WriteDAT(xEnd);		   //XE7-XE0    (X end address)

	WriteCOM(0x2b);		   //��	row address set (RASET)
	WriteDAT(yStart>>8);   //YS15-YS8
	WriteDAT(yStart);	   //YS7-YS0    (Y start address)
	WriteDAT(yEnd>>8);	   //YE15-YE8
	WriteDAT(yEnd);		   //YE7-YE0    (Y end address)

    WriteCOM(0x2c);		   //display on	��ʾ������
   
}


/**********************************************************/
void LCD_init(void)
{	 //�뿴�����ֲ������� �˽��������Ĺ���
	LCD_RST=1;
	delay_ms(100);
	LCD_RST=0;
	delay_ms(100);
	LCD_RST=1;
	delay_ms(100);
	
	WriteCOM(0x01);	    //software reset�����λ
	delay_ms(100);
	WriteCOM(0x11);	    //sleep out/power on(SLPOUT) �˳�˯��
	delay_ms(50);
	WriteCOM(0x20);		//display inversion off �ر�ȡ��
	delay_ms(50);
	WriteCOM(0x38);	    //ID mode off (IDMOFF)
	delay_ms(50);
	WriteCOM(0x13);	    //Normal display mode on (Partial mode off)
	
	WriteCOM(0x3a);	    //color mode Interface pixel format  (COLMOD)
	WriteDAT(0x05);		//16-bit/pixel , 1-times data transfer
	
	WriteCOM(0xc0);		//power control 1      (PWCTR1)
	WriteDAT(0x03);		//default value  LCM=0 set the GVDD voltage=4.65
	
	WriteCOM(0xc5);	   
	WriteDAT(0xc8);	   //VCOMH voltage set 4.300V
	
	WriteCOM(0xc6);
	WriteDAT(0x1f);	   //VCOMAC voltage set 5.550V ;
	delay_ms(10);
	
	WriteCOM(0xfe);
	WriteDAT(0x00);
	WriteDAT(0x04);
	
	WriteCOM(0x26);	   //gamma sel
	WriteDAT(0x04);
	
	
	WriteCOM(0x2a);	   //column address set (CASET)
	WriteDAT(0x00);	   //XS15-XS8
	WriteDAT(0x00);	   //XS7-XS0    (X start address)
	WriteDAT(0x00);	   //XE15-XE8
	WriteDAT(0x7f);	   //XE7-XE0    (X end address)
	
	WriteCOM(0x2b);	   //row address set (RASET)
	WriteDAT(0x00);	   //YS15-YS8
	WriteDAT(0x00);	   //YS7-YS0    (Y start address)
	WriteDAT(0x00);	   //YE15-YE8
	WriteDAT(0x9f);	   //YE7-YE0    (Y end address)
	
	WriteCOM(0x36);	   //memory data access control  (MADCTR)
	WriteDAT(0xc0);
	
	WriteCOM(0x29);	  // display on

 
}
/**********************************************************

 �����Ӻ���

**********************************************************/
void  LCD_clear(uchar n)
{
   uint num;
   
   LCD_SetRamAddr(0,127, 0,159);  //������ʾ������

   for(num=20480;num>0;num--)          //160*128=20480
   {
  	 WriteDAT(colors[n]>>8);   //��8λ
	 WriteDAT(colors[n]);	   //��8λ
   }
}


/**********************************************************

 ͼƬ��ʾ�Ӻ���

**********************************************************/
void  pic_play(uint Start_X, uint End_X,uint Start_Y,uint End_Y)
{
   uint m;

   LCD_CS = 0;
   LCD_SetRamAddr(Start_X,End_X-1,Start_Y,End_Y-1) ;   //���õ�ַ
   LCD_RS 	= 1; 


   for(m=0; m<(7128/2); m++)	
   {		
      WriteDAT(Image_pic[m*2+1]);	//��λ��ǰ
	  WriteDAT(Image_pic[m*2]);     //��λ�ں�

   }
   LCD_CS = 1;

}


