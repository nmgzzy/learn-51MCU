#include<reg52.h>  

sbit LeftF=P1^0;  //左轮前进 //
sbit LeftB=P1^1;  //左轮后退 //
				  //0为真	 //
sbit RightF=P1^2; //右轮前进 //
sbit RightB=P1^3; //右轮后退 //

void delay(unsigned int xms)				
{
	unsigned int i,j;
	for(i=xms;i>0;i--)		      //i=xms即延时约xms毫秒
		for(j=112;j>0;j--);
}

void run(void)	//前进
{
    LeftF=0;
	LeftB=1;
	RightF=0;
	RightB=1;
}

void back(void)			  //后退函数
{
    LeftF=1;
	LeftB=0; 
	RightB=0;
	RightF=1;
}

void right(void)		 //右转函数
{
    LeftF=0;
	LeftB=1;
	RightB=1;
	RightF=1;
}

void left(void)			  //左转函数
{
    LeftF=1;
	LeftB=1; 
	RightB=1;
	RightF=0;
}

void stop(void)			  //停止函数
{
    LeftF=1;
	LeftB=1;
	RightB=1;
	RightF=1;
}


void spin_right(void)	  //向右打转函数
{
    LeftF=0;
	LeftB=1;
	RightB=0;
	RightF=1;
}

void spin_left(void)	  //向左打转函数
{
    LeftF=1;
	LeftB=0; 
	RightB=1;
	RightF=0;
}



void main(void)
{
    delay(2000); //延时2s后启动
    back();		 
	delay(1000); //后退1s
	stop();		 
	delay(500);	 //停止0.5s
	run();		 
	delay(1000); //前进1s
	stop();
	delay(500);	 //停止0.5s
	left();
	delay(1000); //向左转1s
	right();
	delay(1000); //向右转1s
	spin_right();
    delay(2000); //向左旋转2s
	spin_left();
	delay(2000); //向右旋转2s
	stop();		 //停车
	while(1);  //死循环	复位键重新跑程序
}











