/************************************
文件功能：自定义函数
					请将自定义函数保存到本文件，自定义全局变量保存到此文件，保持整个工程简洁清晰。
库要求：主函数中已定义：
		#include <reg52.h>
应用函数：

修改历史：
		   	 ‘修改人’   ‘修改内容’  ‘修改时间’

最后修改时间：

常见错误解释：
	*** WARNING L16: UNCALLED SEGMENT, IGNORED FOR OVERLAY PROCESS	：库里的函数有没有调用过的，一般可以忽略此警告
	123.C(7): error C202: 'riht1602': undefined identifier	 ：参数名称拼写错误，更正拼写错误即可
	123.C(14): error C214: illegal pointer conversion    ：要求参数是字符串，而你给的是字符
常用函数变量声明：
		static：静态变量，第二次调用应用上次调用后的值，不再重新开辟内存空间设定初值。
***************************************/

/************************************
设置需要载入的库
***************************************/
#include "atime_pwmpca.h"
#include "atime_serial.h"
#include  <INTRINS.H>


/************************************
全局变量组
***************************************/
void gq_init();
void gq_calculate();
void delay_nms(unsigned int k);
void Multiple_read_BH1750(void);
void Single_Write_BH1750(unsigned char REG_Address);

#define	  SlaveAddress   0x46 
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

sbit SCL =P3^4;        //串行时钟总线SCL位
sbit SDA =P3^5; 		   //串行数据总线SDA位

unsigned char body_set = 0; 		//状态存储：是否是人体靠近引发的灯光亮起，0代表不是，1代表是因为人体靠近引发的灯光亮起
																//0x01;0x02;0x04确定灯的点亮原因													
unsigned char body_status = 0; 	//状态存储：人体感应模块状态
unsigned char wlw_status	= 0;	//状态存储：物联网模块状态
unsigned int	gq_int_status= 0;	//光强度存储
float	gq_status			= 0;				//光强度存储
unsigned char gq_data[8];

float	pwm_status = 0.0;						//当前状态pwm输出占空比
unsigned char led_status 	= 0;	//当前led状态设置


unsigned char ge,shi,bai,qian,wan;            //显示变量	

/************************************
函数功能：I/O初始化
传递参数：空
返回值：空	
注意：空
***************************************/
void io_init()
{
		led0 = 1;
		led1 = 1;
		led2 = 1;
		led_gnd=0;
		pwm_init( pwm_on, 0, 0xf5);
		pwm_set(0, 0.0);
		serial_int(enable, baud14400, disable);
		gq_init(); 
}


/************************************
函数功能：光强传感器获取当前光强数据
传递参数：空
返回值：空	
注意：空
***************************************/
void get_gq_data()
{
		//读取光强传感器数据，并更新gq_status
		Single_Write_BH1750(0x01);   // power on
    Single_Write_BH1750(0x10);   // H- resolution mode
		delay_nms(180);              //延时180ms
		Multiple_read_BH1750();      //连续读出数据，存储在BUF中
		gq_calculate();
}


/************************************
函数功能：物联网模块获取物联网控制数据
传递参数：空
返回值：空	
注意：空
***************************************/
void get_wlw_status()
{
		//读取光强传感器数据，并更新wlw_status
}


/************************************
函数功能：人体感应模块获取当前人体位置数据
传递参数：空
返回值：空	
注意：空
***************************************/
void get_body_status()
{
		//读取光强传感器数据，并更新body_state
}


/************************************
函数功能：根据当前光强控制pwm输出状态
传递参数：空
返回值：空	
注意：空
***************************************/
void set_pwm_status()
{
		//根据body_status，设置pwm_status
		static float i=50.0;
		if(i<10.0)
				i = 91.0;
		i = i-1.0;
		pwm_set(0, i);
		
}


/************************************
函数功能：
传递参数：空
返回值：空	
注意：空
***************************************/
void set_led_status()
{
		//根据光强数据body_status/wlw_status，设置led_status
		
}


/************************************
函数功能：
传递参数：空
返回值：空	
注意：空
***************************************/
void set_led_output()
{
		//根据led_status设置led输出
		led0 = 1;
		led1 = 0;
		led2 = 1;
		led_gnd=0;
}



/************************************
函数功能：延时函数
传递参数：空
返回值：空	
注意：空
***************************************/
void Delay180ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 8;
	j = 145;
	k = 99;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay5ms()
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 54;
	j = 198;
	do
	{
		while (--j);
	} while (--i);
}

void Delay5us()
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 10;
	while (--i);
}

void delay_nms(unsigned int k)	
{						
	unsigned char i, j;
	for(;k>0;k--)
	{
			_nop_();
			i = 11;
			j = 190;
			do
			{
					while (--j);
			} 
			while (--i);					
			}
}


/**************************************
起始信号
**************************************/
void BH1750_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}


/**************************************
停止信号
**************************************/
void BH1750_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}


/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void BH1750_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}


/**************************************
接收应答信号
**************************************/
bit BH1750_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时

    return CY;
}


/**************************************
向IIC总线发送一个字节数据
**************************************/
void BH1750_SendByte(unsigned char dat)
{
    unsigned char i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    BH1750_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
unsigned char BH1750_RecvByte()
{
    unsigned char i;
    unsigned char dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    return dat;
}


/**************************************
从IIC总线写入一个字节数据
**************************************/
void Single_Write_BH1750(unsigned char REG_Address)
{
    BH1750_Start();                  //起始信号
    BH1750_SendByte(SlaveAddress);   //发送设备地址+写信号
    BH1750_SendByte(REG_Address);    //内部寄存器地址，
  //  BH1750_SendByte(REG_data);       //内部寄存器数据，
    BH1750_Stop();                   //发送停止信号
}

//*********************************************************
//
//连续读出BH1750内部数据
//
//*********************************************************
void Multiple_read_BH1750(void)
{   
		unsigned char i;	
    BH1750_Start();                          //起始信号
    BH1750_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	
		for (i=0; i<3; i++)                      //连续读取2个地址数据，存储中BUF
    {
        gq_data[i] = BH1750_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 3)
        {

           BH1750_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {		
          BH1750_SendACK(0);                //回应ACK
       }
   }

    BH1750_Stop();                          //停止信号
    Delay5ms();
}

/************************************
函数功能：
传递参数：空
返回值：空	
注意：空
***************************************/
void gq_calculate(void)
{
		int data_gq;
	
		data_gq=gq_data[0];
    data_gq=(data_gq<<8)+gq_data[1];//合成数据，即光照数据
    
		gq_int_status = data_gq; 
    gq_status=(float)data_gq/1.2;
}


/************************************
函数功能：
传递参数：空
返回值：空	
注意：空
***************************************/
void gq_init()
{
    Single_Write_BH1750(0x01);  
}


/************************************
函数功能：
传递参数：空
返回值：空	
注意：空
***************************************/
void conversion(unsigned int temp_data)  //  数据转换出 个，十，百，千，万
{  

    wan=temp_data/10000+0x30;
    temp_data=temp_data%10000;   //取余运算
		qian=temp_data/1000+0x30;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100+0x30;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10+0x30;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data+0x30; 	

}

/************************************
函数功能：
传递参数：空
返回值：空	
注意：空
***************************************/
/************************************
函数功能：
传递参数：空
返回值：空	
注意：空
***************************************/
