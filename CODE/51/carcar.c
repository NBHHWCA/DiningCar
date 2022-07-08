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
	IE = 0;	
	while(1)//push the button to start car
	{
		if(BUTTON1 == 0)
		{
			getLED1();
			break;
		}
	}
	while(1)//start loop
	{				
		if(BUTTON2 == 0)//to detective the weight
		{
			getLED2();
			//getBuzzer();
		}
		Mode = getMode();//1-6 choose a mode
		sentMode();
		receiveMove();
		startMove();			
	}//loop end
	//one loop one move	
}
void initPins()
{
	LED1 = 0;
	LED2 = 0;//light  off first
	LEFT_BI = 0;
	LEFT_FI = 0;
	RIGHT_BI = 0;
	RIGHT_FI = 0;
	BUTTON1 = 1;
	BUTTON2 = 1;
	BUZZER = 0;
	MODE1 = 1;
	MODE2 = 1;
	MODE3 = 1;
	MODE4 = 1;
	MODE5 = 1;	
	MODE6 = 1;
	WirelessInpute = 0;// not sure!!!
	WirelessOutput = 0;
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
void sendMode()//output data
{
	if(TI == 1)//output  ready??     a reg for interpret   is interpreted
	{
		if(Flag==1) //have receive the data?
		{
			SBUF = Mode;
			Flag = 0;
			TI = 0;
		}
	}
}
void receiveMove()//inpute data
{
	if(RI==1)//oh data is coming
	{
		Move = SBUF;
		Flag = 1;
		RI = 0;
	}
}
void startMove()
{
	switch(Move)
	{
		case 0x31:carGoStraight();break;//ascii for number 1  ...
		case 0x32:carGOLeft();break;
		case 0x33:carGoRight();break;
		case 0x34:carBackStraight();break;
		case 0x35:carBackLeft();break;
		case 0x36:carBackRight();break;
		default :break;
	}
}
void carGoStraight()
{
	LEFT_BI = 0;
	LEFT_FI = 1;
	RIGHT_BI = 0;
	RIGHT_FI = 1;
}
void carGOLeft()
{
	LEFT_BI = 0;
	LEFT_FI = 0;
	RIGHT_BI = 0;
	RIGHT_FI = 1;
}
void carGoRight()
{
	LEFT_BI = 0;
	LEFT_FI = 1;
	RIGHT_BI = 0;
	RIGHT_FI = 0;
}
void carBackStraight()
{
	LEFT_BI = 1;
	LEFT_FI = 0;
	RIGHT_BI = 1;
	RIGHT_FI = 0;
}
void carBackLeft()
{
	LEFT_BI = 0;
	LEFT_FI = 0;
	RIGHT_BI = 1;
	RIGHT_FI = 0;
}
void carBackRight()
{
	LEFT_BI = 1;
	LEFT_FI = 0;
	RIGHT_BI = 0;
	RIGHT_FI = 0;
}
void getLED1()
{
	LED1 = 1;
}
void getLED2()
{
	LED2 = 1;
}
void getBuzzer()
{
	BUZZER = 1;
}
unsigned char getMode()
{
	unsigned char Mode = 0x21 ;//!
	if(isError())//only for debug
	{
		getBuzzer();
	}
	if(MODE1 == 0)
	{
		Mode = 0x41 ;//A
	}
	else if(MODE2 == 0)
	{
		Mode = 0x42 ;//B
	}
	else if(MODE3 == 0)
	{
		Mode = 0x43 ;//C
	}
	else if(MODE4 == 0)
	{
		Mode = 0x44 ;//D
	}
	else if(MODE5 == 0)
	{
		Mode = 0x45 ;//E
	}
	else if(MODE6 == 0)
	{
		Mode = 0x46 ;//F
	}
	return Mode;
}
bool isError()//only for debug
{
	if(MODE1+MODE2+MODE3+MODE4+MODE5+MODE6 < 5) return True;
	return False;	
}
void getWirelessInput()//wireless part
{
	
}
void getWirelessOutput()
{
	
}
void getDelay(int TIME_BY_S)//copy from stc-isp   danwei:s
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	while(TIME_BY_S--)
	{
		do
		{
			do
			{
				while (--k);
			} while (--j);
		} while (--i);
	}
}


