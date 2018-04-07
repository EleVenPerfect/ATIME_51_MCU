/************************************
设置需要载入的库
***************************************/
#include  <INTRINS.H>
#ifndef _GUANGQIANG_H_
#define _GUANGQIANG_H_
#define	  SlaveAddress   0x46 
void gq_init();
void gq_calculate();
void delay_nms(unsigned int k);
void Multiple_read_BH1750(void);
void Single_Write_BH1750(unsigned char REG_Address);
/***********************************************************************************************************/
//GY-30 光强模块程序
//晶振：11。0592
//接线：模块SCL接 P2.3  SDA 接P2.4
//串口波特率9600
/***********************************************************************************************************/
sbit SCL =P2^4;        //串行时钟总线SCL位
sbit SDA =P2^3; 		   //串行数据总线SDA位
												

float	gq_status;				//光强度存储
unsigned char gq_data[8];
unsigned int 	gq_int_status;


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
		printf("GQ=%d\n",gq_int_status);
		printf("GQ=%f\n",gq_status);
}



/************************************
函数功能：延时函数
传递参数：空
返回值：空	
注意：空
***************************************/
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
		printf("GQ Inint OK!\n");
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
#endif