#include"PWM.h"
#include<reg52.h>

char MOTORSpeed=0;
unsigned int MOTORCount=0,ServoCount=0,ServoAngle=90,Servoflag=0;

void PWM_Init()
{
	TMOD|=0x01;			//���ö�ʱ��0������ʽ1,��ʱ��1������ʽ1
	
	T2MOD|=0x00;		//���ö�ʱ��2������ʽ16λ�Զ�����
	T2CON|=0X00;
	
	TH0=0xff;			//80us
	TL0=0x9c;			
	
	RCAP2H=0xff;		//��ʱ��2�Զ�������ֵ
	RCAP2L=0xec;

	
	PT0=1;				//T0���жϼ���
	
	EA=1;				//�����ж�
	
	ET0=1;				//����T0�ж�
	ET2=1;				//����T2�ж�

	PWM0=0;				//����������
	PWM1=0;
	
	Servo0=0;			//ת����
	Servo1=0;

	TR0=0;				//�رն�ʱ��0
	TR2=1;				//������ʱ��2
}

void MOTOR(char Speed)
{
	MOTORSpeed=Speed;
	if(Speed>=0)
	{
		PWM1=0;	
	}
	else
	{
		PWM0=0;
	}	
}

void ServoControl(unsigned char angle)
{
	ServoAngle=angle;
	if(angle==90)
	{
		Servo0=0;
		Servo1=0;
		ServoCount=0;
		Servoflag=0;
		TR0=0;							//�رն�ʱ��0
	}
	else if (angle>90)
	{
		Servo0=0;
		ServoCount=0;
		Servoflag=0;
		TR0=1;							//������ʱ��0
	}
	else
	{
		Servo1=0;
		ServoCount=0;
		Servoflag=0;
		TR0=1;							//������ʱ��0	
	}		
}


void delay_ms(unsigned int time)
{
	int icd,jcd;
	for(icd=0;icd<time;icd++)
		for(jcd=0;jcd<110;jcd++);
}
/***************************************************
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

***************************************************/
/***************************************************
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

***************************************************/

