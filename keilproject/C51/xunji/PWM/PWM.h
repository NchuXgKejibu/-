#ifndef _PWM_H
#define _PWM_H
#include <STC12C5A60S2.h>


extern char MOTORSpeed,Angle,Angle1,AngleFlag,AngleFlag1,speed;
extern unsigned int MOTORCount,ServoCount,ServoAngle,Servoflag;

sbit PWM0	=	P0^4;			//PWM�������
sbit PWM1	=	P0^5;
sbit Servo0	=	P0^2;			//���
sbit Servo1	=	P0^3;

void PWM_Init(void);					//PWM��ʼ��
void MOTOR(char Sp);					//�������
void ServoControl(unsigned char angle);	//����Ƕȿ���
void delay_ms(unsigned int time);		//��ʱ



#endif