#include <reg51.c>
#include <absacc.h> //many address name to use directly
//mode choice
sbit MODE1 = P0^0;
sbit MODE2 = P0^1;
sbit MODE3 = P0^2;
sbit MODE4 = P0^3;
sbit MODE5 = P0^4;
sbit MODE6 = P0^5;
//little toy
sbit LED1 = P1^0;
sbit LED2 = P1^1;
sbit BUZZER = P1^2;
sbit BUTTON1 = P2^7;
sbit BUTTON2 = P2^4;
//the car
sbit LEFT_BI = P2^3;
sbit LEFT_FI = P2^2;
sbit RIGHT_BI = P2^1;
sbit RIGHT_FI =	P2^0;
sbit LEFT_H1 = P3^5;
sbit LEFT_H2 = P3^3;//int0
sbit RIGTH_H1 = P3^4;
sbit RIGHT_H2 = P3^2;//int1
//others
sbit SET = P3^6;//wireless part setting
sbit CS = P3^7;//wireless part sleep
sbit RST = P5^4;
sbit TXD = P3^1;
sbit RXD = P3^0;

unsigned char Mode;// sent to cam
unsigned char Move;//receive from cam
unsigned char Flag;//1 = have received data
unsigned char WirelessInpute;//this two only for wireless part
unsigned char WirelessOutput;

void main()
{
	initPins();//some pins  inital status
	initSerial();//serial attribute init
	IE = 0;	// ping bi zhong duan
	while(1)//start loop
	{				

		sendMode(0x41);//test

        
	}//loop end
	//one loop one move	
}
void sendMode(unsigned char Data)//output data
{
	if(TI == 1)//output  ready??     a reg for interpret   is interpreted
	{
		if(Flag==1) //have receive the data?
		{
			SBUF = Data;
			Flag = 0;
			TI = 0;
		}
	}
}
void receiveMove()//inpute data
{
	unsigned char Data;
	if(RI==1)//oh data is coming
	{
		Data = SBUF;
		Flag = 1;
		RI = 0;
	}
	return Data
}
void initSerial() //for  data trans
{
	TMOD=0x20; //timer  T1 work_mode 2
	TL1=250; //
	TH1=250;
	TR1=1; //timer1 start
	PCON=0x80; //SMOD=1	
	SCON=0x50; //9600bit/s 
	TI=1;
}