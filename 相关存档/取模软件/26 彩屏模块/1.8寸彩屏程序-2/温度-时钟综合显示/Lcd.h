/**********************************************************

file:  Lcd.h
**********************************************************/


#define uchar unsigned char
#define uint unsigned int

#define  TYPE_LCD_DATA		1
#define  TYPE_LCD_COMMAND	0
#define  LCD_SIZE_X		128
#define  LCD_SIZE_Y		160
#define  DATA   P0

sbit LCD_RST  = P2^7;    //RST ���Ŷ���
sbit LCD_RD   = P3^2;	 //RD  ���Ŷ���
sbit LCD_WR   = P3^3;	 //WR  ���Ŷ���
sbit LCD_RS   = P2^5;	 //RS  ���Ŷ���
sbit LCD_CS   = P2^6;	 //CS  ���Ŷ���

extern  uint colors[];
extern  void  delay_ms(uint ms);
extern  void  LCD_Write(uchar type, uint value);
extern  void  LCD_SendData8(uchar value);
extern  void  LCD_Wirte_Data16(uint value);
extern  void  Reg_Write(uint reg,uint value);
extern  void  LCD_SetRamAddr(uint xStart, uint xEnd, uint yStart, uint yEnd);
extern  void  LCD_init(void);
extern  void  pic_play(uint xStart, uint xEnd, uint yStart, uint yEnd, const uchar *P);
extern  void  LCD_clear(uchar n);
extern  void LCD_color();
extern  void LCD_color_H();
extern  void LCD_color_V();
extern  void  LCD_ShowChar(uchar x,uchar y,uint For_color,uint Bk_color,char ch);
extern  void  LCD_ShowString(uchar x,uchar y,uint For_color,uint Bk_color,char *p);
extern  void ChineseChar(uint x,uint y,int size,uint For_color, uint Bk_color , char c);

