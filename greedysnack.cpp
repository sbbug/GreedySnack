//̰������Ϸ
//��δ�ӡ�Թ�ʳ����̰���ߣ����������
//����Ϸ���д��Ż���


#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <cmath>
using namespace std;

#define maxLen  30//̰�����ܳԵ������ʳ��

int foodLocation[2]={0};
int snack[maxLen][2];
int len=2;//̰���ߵ�ǰ����
char order;//�Ӽ���������Ϣ
char snDir;//̰���ߵĵ�ǰ�˶�����
int score=0;//ȫ�ֱ���Ĭ�ϳ�ʼֵ��0��
bool life=true;

void drawWall();
void drawFood();
void drawSnack();
void drawCircle(int,int,int);//��ɫ������int���͡�
void drawScore();
void eatFood();
void goDirection(char);
bool judge();//�ж��Ƿ�ײ��ǽ
void win();
void gameOver();
void knockSelf();
double countDis(int ,int,int,int);//��������Բ�ľ��롣



void main()
{
	initgraph(800,700);
	
     //��ʼ����ͷλ�á�	
	snack[0][0]=300;
    snack[0][1]=300;
	
	//ǽ�е������ʼ��
	
	drawScore();
    drawWall();//��ǽ
	drawSnack();//��̰���ߵĳ�ʼλ��
	drawFood();//�������ʳ��

	while(!kbhit())
	{    
		
		snDir='a';//̰���ߵĳ�ʼ�˶�����
		goDirection(snDir);
		gameOver();//�ж��Ƿ�ײǽ
		if(life==0)
			break;
		Sleep(500);
	}

	
	while(1)
	{
	   while(kbhit())
	   {
		order=getch();//��ȡ��ǰ����
		goDirection(order);
		Sleep(500);
		if(life==0)
			break;
	   }
  
       if(life==0)
		   break;
	   while(!kbhit())
	   {
		goDirection(order);
		Sleep(500);
		if(life==0)
		break;
	   }
	 }
   	getch();
	closegraph();
}



//////////////////////////
void drawFood()
{
	 int i;
	 bool flag=false;

     srand((unsigned)time(0));
//�滮ʳ��λ��
	 while(!flag)
	 {
	    foodLocation[0]=rand()%480+150;foodLocation[1]=rand()%500+130;
		double dis;
		
        for(i=0;i<len;i++)
		{       
		  
		   dis=countDis(snack[i][0],snack[i][1],foodLocation[0],foodLocation[1]);
		   if(dis>100)//��ֹʳ����̰������������
		   {
			   flag=true;
		   }
	   }

	 }
	 drawCircle(foodLocation[0],foodLocation[1],0x114499);
}
///////////////////////////////////
void drawCircle(int x,int y,int color)
{
	setfillcolor(color);
	solidcircle(x,y,10);
}
//////////////////////////////////
void drawScore()
{
	char author[]="Producer: ���ΰ GAMENAME: GREEDY SNACK DATE: 2015/5/3 ";
	char o[]="GAME BEGIN!";
    char f[]="SCORE : ";
	char g[]="Game Intructions: W->UP, A->LEFT, S->DOWN, D->RIGHT, SPACEKEY->STOP ";
	outtextxy(20,10,author);
    outtextxy(20,30,o);
	outtextxy(20,50,f);
	outtextxy(20,70,g);

    sprintf(f,"%d",score);//���������ַ�������ʽ���
    outtextxy(60,50,f);
}
///////////////////////////////////
void drawSnack()//����̰���ߵĻ���
{
	   int i;

	   
       for(i=0;i<len;i++)//�Ȼ�һ����ֹ��̰����
	   {
		 drawCircle(snack[i][0],snack[i][1],0x881345);
	   }
        
       knockSelf();//�ж���ͷ�Ƿ�����������
	   for(i=len-1;i>=0;i--)//����֮��������λ��Ϊ��һ��̰���߻滭��׼��
	   {
		snack[i+1][0]=snack[i][0];
		snack[i+1][1]=snack[i][1];
	   }
       drawCircle(snack[len][0],snack[len][1],BLACK);
}
//////////////////////////////
void goDirection(char c)
{
           
	       if(snDir=='w'&&c=='s')
			   snDir='w';
		   else if(snDir=='s'&&c=='w')
			   snDir='s';
		   else if(snDir=='a'&&c=='d')
			   snDir='a';
		   else if(snDir=='d'&&c=='a')
			   snDir='d';
		   else if(1)
			   snDir=c;
		  if(c==' ')
		  {
			  while(!kbhit());
		  }
             
			switch(snDir)
			{
			case 'w':
				snack[0][1]-=20;break;//�����˶�
			case 's':
				snack[0][1]+=20;break;//�����˶�
			case 'a':
				snack[0][0]-=20;break;//�����˶�
			case 'd':
				snack[0][0]+=20;break;//�����˶�
			default:
				;
			}
			
	    eatFood();
	    drawSnack();
		drawScore();
		win();
		gameOver();
}

///////////////////////////////
void eatFood()
{

	double dist;
	dist=countDis(snack[0][0],snack[0][1],foodLocation[0],foodLocation[1]);
	if(dist>0&&dist<20)//����ͷ������ʳ��������ͬʱ
	{
		score++;
		len++;
        drawCircle(foodLocation[0],foodLocation[1],BLACK);//��ʳ����������ͷ��ͬʱ������Բ��������
		drawFood();
	}

}
///////////////////////////////
//�ж��Ƿ���ǽ
bool judge()
{
     bool temp=true;

	 if(snack[0][0]<120)
	 {
		 temp=false;
		 life=false;
	 }
     else if(snack[0][1]<120)
	 {
		 temp=false;
		 life=false;
	 }
	 else if(snack[0][0]>660)
	 {
		 temp=false;
		 life=false;
	 }
	 else if(snack[0][1]>660)
	 {
		 temp=false;
		 life=false;
	 }
	
		return temp;
}

/////////////////////////////
void drawWall()
{
	int a1,a2;
	int b1,b2;
	for(b1=90;b1<=690;b1+=600)
	{
		for(b2=90;b2<=690;b2++)
		{
			putpixel(b1,b2,YELLOW);
			putpixel(b2,b1,YELLOW);
		}
		for(b2=110;b2<=670;b2++)
		{
			b1=b1==690?b1-40:b1;
			
			putpixel(b1+20,b2,YELLOW);
			putpixel(b2,b1+20,YELLOW);
		}
	}
	for(a1=100;a1<=680;a1+=580)
	{
		for(a2=100;a2<=680;a2+=20)
		{
			drawCircle(a1,a2,0x114466);
			drawCircle(a2,a1,0x114466);
		}
	}
	
	 
}
void win()
{
	if(len>maxLen+1)
		{
		    //status=false;
			cleardevice();
			char w[]="You Win Game!";
	        outtextxy(300,300,w);
		}
}

void gameOver()
{
	
       if(!judge())
		{
		    life=false;
			cleardevice();
			settextstyle(50,50,_T("����"));
			char m[]="Game Over!";
			outtextxy(100,300,m);
			
		}
}
void knockSelf()
{
	int i;
     for(i=1;i<len;i++)
	 {
		 if(countDis(snack[0][0],snack[0][1],snack[i][0],snack[i][1])<20)
		 {
			 life=false;
			 cleardevice();
			 char s[]="you knock yourself!";
			 settextstyle(10,15,_T("����"));
			 outtextxy(300,300,s);
		 }
	 }
}

double countDis(int x1,int y1,int x2, int y2)
{
	double distance;
	double temp1,temp2;
	temp1=fabs(x1-x2);
	temp2=fabs(y1-y2);
	distance=sqrt(temp1*temp1+temp2*temp2);
	return distance;
}
//////////////////////////////////////
/*
�˴�����Ϸ�ܽ᣺
1������Ϸ֮ǰû������滮��
2������һЩϸ�����ղ����ã�����Ҫ�������С�
3��˼������ʱ̫��һ��

�������ϷʱӦ�ã�
1����֮ǰ��Ҫ�����������ϷҪʵ����Щ���ܡ�
2�����������ݸ��ĵ���������Ϸ����ͼ����Σ���֮ǰҪ����Ϸ��һЩС�Ĳ�ȷ����ϸ�ڣ�ͨ��С������в��ԡ�
3������ϰ����ʵ�֣�
*/