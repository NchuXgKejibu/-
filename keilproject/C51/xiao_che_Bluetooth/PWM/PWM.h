#ifndef _PWM_H
#define _PWM_H
#include<reg52.h>


extern char MOTORSpeed;
extern unsigned int MOTORCount,ServoCount,ServoAngle,Servoflag;

sbit PWM0	=	P0^4;			//PWM�������
sbit PWM1	=	P0^5;
sbit Servo0	=	P0^2;			//���
sbit Servo1	=	P0^3;

void PWM_Init(void);					//PWM��ʼ��
void MOTOR(char Speed);					//�������
void ServoControl(unsigned char angle);	//����Ƕȿ���
void delay_ms(unsigned int time);		//��ʱ



#endif