#include"serial.h"

/**********************************************
			串口函数
***********************************************/

void Serial_Init(void)
{
	 TMOD|=0x20;			//设置定时器1工作方式2,自动重载
	 SCON=0x50;			//设置串口方式1,使能REN
	 TH1=0xfd;			//装载初值,波特率9600
	 TL1=0xfd;
	 EA=1;				//开总中断
	 ES=1;				//开串口中断
	 PS=1;				//中断级别
	 TR1=1;				//开启时器1
}
/**********************************************
			
***********************************************/
void Serial_Send(unsigned char dat)
{
	ES=0;					//关串口中断
	SBUF=dat;				//送入数据
	while(!TI);				//等待数据发送完成
	TI=0;					//标志位清除
	ES=1;					//开串口中断
}
/**********************************************
			
***********************************************/

/***************************************************
void Serial_Receive(void) interrupt	4
{
		if(RI)
		{
			RI=0;
			Serial_dat=SBUF;
			Serial_flag=1;
		}
}

***************************************************/

