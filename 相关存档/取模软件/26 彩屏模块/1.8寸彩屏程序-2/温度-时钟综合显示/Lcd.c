/**********************************************************
*                   									  *
*				   ������������							  *
*														  *
**********************************************************/

#include <reg52.h>
#include "Lcd.h"
#include "char.h"
#include "chinese.h"

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

  �ַ���ʾ�Ӻ���

**********************************************************/
void LCD_ShowChar(uchar x,uchar y,uint For_color,uint Bk_color, char ch)
{       
   uchar temp;
   uchar pos,t;
   uchar  CHAR_W,CHAR_H;
   
   CHAR_W = 8;         //8*16
   CHAR_H = 16;

   if(x>(LCD_SIZE_X-CHAR_W)||y>(LCD_SIZE_Y-CHAR_H))
   return;
   
   LCD_SetRamAddr(x, x+CHAR_W-1, y,y+CHAR_H-1);	  //������ʾ������
   ch = ch-32;                       //����ASCII����˳��ĵ���Ӧ��ĸ�ı���

   for(pos=0;pos<CHAR_H;pos++)  
   {
      temp= Font8x16[ch][pos];
      
      for(t=0;t<CHAR_W;t++)
      {                 
	    if(temp&0x80)
	     {WriteDAT(For_color>>8); WriteDAT(For_color); } //textcolor  //������ɫ
    
	 else 
		{WriteDAT(Bk_color>>8);	 WriteDAT(Bk_color) ;  	}
	
		
        temp<<=1; 
	
      }
	  
   }
}  

/**********************************************************
 ��ʾ�ַ����Ӻ���

 x,y:�������  
 *p:�ַ�����ʼ��ַ

**********************************************************/
void LCD_ShowString(uchar x,uchar y,uint For_color,uint Bk_color,char *p)
{         
   while(*p!='\0')
   {       
     LCD_ShowChar(x,y,For_color,Bk_color,*p);
     x+=8;	  //����Ŀ��
     p++;
   }
}


/**********************************************************

  д�����Ӻ���

**********************************************************/
void ChineseChar(uint x,uint y,int size,uint For_color,uint Bk_color ,char c)
{
   int e=0,i,j;
   int  ed;
   
   uint  ncols;
   uint  nrows;
   uint  nbytes;

   uchar *pfont;
   uchar *pchar;
   uchar *fonttable[]={(uchar *)hz12,(uchar *)hz16,(uchar *)hz24};		//��������׵�ַ����fortable������
   
   pfont=(uchar *)fonttable[size];

   if(size==0)
   {
     ncols =12-1;
     nrows =12-1;
     nbytes =24;	 //(12*12)/8
   }
   else
   if(size==1)
   {
     ncols =16-1;
     nrows =16-1;
     nbytes =32;  //(16*16)/8
   }
   else
   if(size==2)
   {
     ncols =24-1;
     nrows =24-1;
     nbytes =72;   //(24*24)/8
   }
   
   pchar=pfont + (nbytes*(c-1));

   LCD_SetRamAddr(x, x+nrows, y,y+ncols);  //������ʾ������
   
   for(i=0;i<nbytes;i++)
   {
     ed=*pchar++;
	 if(size==0)
	 {
       if(i%2==0)
       e=8;
       else
       e=4;
	 }
	 else
	 e=8;
     
     for(j=0;j<e;j++)
     if((ed>>j)&0x01)
     {
       WriteDAT(For_color>>8);  //textcolor	������ɫ
	   WriteDAT(For_color);
	 }
     else
     {
       WriteDAT(Bk_color>>8);  //backcolor ������ɫ
	   WriteDAT(Bk_color);
	 }
  }
}

/*********************************************************/
