#ifndef __BSTCAR_H__
#define __BSTCAR_H__
/************BST-V51智能小车头文件*************/
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
//定义小车驱动模块输入IO口 
sbit LeftF=P1^0;  //左轮前进 //
sbit LeftB=P1^1;  //左轮后退 //
				  //0为真	 //
sbit RightF=P1^2; //右轮前进 //
sbit RightB=P1^3; //右轮后退 //

//定义按键
//sbit K4=P3^7;
//sbit K3=P3^6;

//蜂鸣器驱动口定义
//sbit FM=P2^3;

//循迹LED指示灯定义
//sbit Left_1_led=P1^6;	 //左循迹红外传感器       
//sbit Right_1_led=P1^7;	 //右循迹红外传感器  

//避障LED指示灯定义  
//sbit Left_2_led=P3^4;	 //左避障红外传感器  
//sbit Right_2_led=P3^5;	 //右避障红外传感器  


#define Left_moto_go      {LeftF=0,LeftB=1;}   //左电机向前走
#define Left_moto_back    {LeftF=1,LeftB=0;}   //左边电机向后转
#define Left_moto_Stop    {LeftF=1,LeftB=1;}   //左边电机停转                     
#define Right_moto_go     {RightF=0,RightB=1;} //右边电机向前走
#define Right_moto_back   {RightF=1,RightB=0;} //右边电机向后走
#define Right_moto_Stop   {RightF=1,RightB=1;} //右边电机停转  



#endif
