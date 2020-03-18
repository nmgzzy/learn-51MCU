#include <reg52.h>  
#include "car.h" 

uchar pwm_val_left  =0; //变量定义
uchar pwm_val_right =0;
uchar push_val_left =8; // 左电机占空比N/20
uchar push_val_right=8; // 右电机占空比N/20
bit Right_PWM_ON=0;	    //右电机PWM开关
bit Left_PWM_ON =0;		//左电机PWM开关
bit EN1 = 1;
bit EN2 = 1;
uchar flag_2s = 0;

void init()
{
	TMOD = 0X01;
	TL0 = 0X66;
	TH0 = 0XFC;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void run(void)				//前进
{
	Left_PWM_ON = 0;
	Right_PWM_ON = 0;
	if(EN1)
	{
	    LeftF=0;
		LeftB=1;
	}
	if(EN2)
	{
		RightF=0;
		RightB=1;
	}
}

void back(void)			  //后退函数
{
	Left_PWM_ON = 0;
	Right_PWM_ON = 0;
	if(EN1)
	{
	    LeftF=1;
		LeftB=0;
	}
	if(EN2)
	{
		RightF=1;
		RightB=0;
	}
}

void right(void)		 //右转函数
{
	Left_PWM_ON = 0;
	Right_PWM_ON = 1;
	if(EN1)
	{
	    LeftF=0;
		LeftB=1;
	}
	if(EN2)
	{
		RightF=0;
		RightB=1;
	}
}

void left(void)			  //左转函数
{
	Left_PWM_ON = 1;
	Right_PWM_ON = 0;
	if(EN1)
	{
	    LeftF=0;
		LeftB=1;
	}
	if(EN2)
	{
		RightF=0;
		RightB=1;
	}
}

void stop(void)			  //停止函数
{
	Left_PWM_ON = 0;
	Right_PWM_ON = 0;
    LeftF=1;
	LeftB=1;
	RightB=1;
	RightF=1;
}


/*****************************************************/
//               PWM调制电机转速                                   
void pwm_out_left_moto(void)
{  
	if(Left_PWM_ON)
	{
        if(pwm_val_left<=push_val_left)
		{
			EN1=1; 
	    }
	    else 
	    {
	        Left_moto_Stop
			EN1 = 0;
        }
        if(pwm_val_left>=20)
		{
			pwm_val_left=0;
		}
	}
	else
		EN1=1;
}

void pwm_out_right_moto(void)
{ 
	if(Right_PWM_ON)
    { 
        if(pwm_val_right<=push_val_right)	
	    {
			EN2 = 1; 				
        }
	    else 
	    {
			EN2 = 0;
	        Right_moto_Stop
        }
	    if(pwm_val_right>=20)
		{
	    	pwm_val_right=0;
		}
    }
	else
		EN2=1;
}
   
void timer0()interrupt 1
{
	static uint cnt=0;
    TH0=0XFC;	  //1Ms定时
	TL0=0X66;
	pwm_val_left++;
	pwm_val_right++;
	pwm_out_left_moto();
	pwm_out_right_moto();
	cnt++;
	if(cnt>=2000)
	{
		flag_2s++;
		cnt = 0;
	}
}

void main(void)
{
	init();	
	while(1)
	{
		switch(flag_2s)
		{
			case 1:back();break;
			case 2:run();break;
			case 3:left();break;
			case 4:right();break;
			default:stop();break;
		}
	}
}











