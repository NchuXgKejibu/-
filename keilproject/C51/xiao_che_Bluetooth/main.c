#include <reg52.h>
#include "serial.h"
#include "PWM.h"
/******************************************
			ȫ�ֱ���
*******************************************/
unsigned char MainFlag=0;						//ѡ�����е�ģʽ����

unsigned char Serial_flag=0;					//���ڱ���
char Serial_dat=0;

int main(void)
{	

	Serial_Init();			//���ڳ�ʼ��
	PWM_Init();				//PWM��ʼ��  
	while(1) 
	{		
	
		if(Serial_flag)
		{
			switch(Serial_dat)
			{
				case 'A':
						{
							MOTORSpeed+=10;
							if(MOTORSpeed>=100)
								MOTORSpeed=100;
						}
						break;
				case 'B':
						{
							MOTORSpeed-=10;
							if(MOTORSpeed<=-100)
								MOTORSpeed=-100;
						};
						break;
				case 'C':
						{
							MOTOR(0);
							ServoControl(90);
						}
						break;
				case 'D':
						MOTORSpeed=100;
						break;
				case 'a':				//��ǰ
						{
							ServoControl(90);
						}
						break;
				case 'e':				//���
						{
							MOTOR(-MOTORSpeed);
							ServoControl(90);
						}
						break;
				case 'c':				//��ȫ��
						{
							ServoControl(0);	
						}
						break;
				case 'g':				//��ȫ��
						{
							ServoControl(180);
						}
						break;
				case 'b':				//��ǰ
						{
							ServoControl(45);
						}
						break;
				case 'h':				//��ǰ
						{
							ServoControl(135);
						}
						break;
				case 'd':				//���
						{
							ServoControl(45);
						}
						break;
				case 'f':				//�Һ�
						{
							ServoControl(135);
						}
						break;

				
			}
			//SBUF=Serial_dat;
			Serial_flag=0;
		}
		MOTOR(MOTORSpeed);	
	}     	  
	
}

/**********************************************
				�жϺ���
***********************************************/
void Serial_Receive(void) interrupt	4
{
		if(RI)
		{
			RI=0;
			Serial_dat=SBUF;
			Serial_flag=1;
		}
}

void Servo_interrupt(void) interrupt 1
{
	TH0=0xff;			//80us
	TL0=0x9c;							
	ServoCount++;
	if(ServoAngle<90)
	{
		if(ServoCount<(90-ServoAngle)*15)	
			Servo0=1;
		else
		{
			Servoflag++;
			Servo0=0;
			Servo0=1;	
			Servo0=0;
			if(Servoflag>2500)
				TR0=0;
		}
	}
	else
	{
		if(ServoCount<(ServoAngle-90)*20)
			Servo1=1;
		else
		{
			Servoflag++;
			Servo1=0;
			Servo1=1;	
			Servo1=0;
			if(Servoflag>2500)
				TR0=0;  
		}	
	}

}


void PWM_interrupt(void) interrupt 5
{
	TF2=0;
	MOTORCount++;
	MOTORCount=MOTORCount>100?1:MOTORCount;
	if(MOTORSpeed>=0)
	{
		if(MOTORCount<MOTORSpeed)
			PWM0=1;
		else
			PWM0=0;	
	}
	else
	{
		if(MOTORCount>(100+MOTORSpeed))
			PWM1=1;
		else
			PWM1=0;
	}
}

 