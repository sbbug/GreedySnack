//贪吃蛇游戏
//如何打印吃过食物后的贪吃蛇，如何清屏。
//此游戏还有待优化，


#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <cmath>
using namespace std;

#define maxLen  30//贪吃蛇能吃到的最多食物

int foodLocation[2]={0};
int snack[maxLen][2];
int len=2;//贪吃蛇当前长度
char order;//从键盘输入信息
char snDir;//贪吃蛇的当前运动方向
int score=0;//全局变量默认初始值是0；
bool life=true;

void drawWall();
void drawFood();
void drawSnack();
void drawCircle(int,int,int);//颜色参数是int类型。
void drawScore();
void eatFood();
void goDirection(char);
bool judge();//判断是否撞到墙
void win();
void gameOver();
void knockSelf();
double countDis(int ,int,int,int);//计算两个圆心距离。



void main()
{
	initgraph(800,700);
	
     //初始化蛇头位置。	
	snack[0][0]=300;
    snack[0][1]=300;
	
	//墙中的坐标初始化
	
	drawScore();
    drawWall();//画墙
	drawSnack();//画贪吃蛇的初始位置
	drawFood();//随机生成食物

	while(!kbhit())
	{    
		
		snDir='a';//贪吃蛇的初始运动方向
		goDirection(snDir);
		gameOver();//判断是否撞墙
		if(life==0)
			break;
		Sleep(500);
	}

	
	while(1)
	{
	   while(kbhit())
	   {
		order=getch();//获取当前方向
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
//规划食物位置
	 while(!flag)
	 {
	    foodLocation[0]=rand()%480+150;foodLocation[1]=rand()%500+130;
		double dis;
		
        for(i=0;i<len;i++)
		{       
		  
		   dis=countDis(snack[i][0],snack[i][1],foodLocation[0],foodLocation[1]);
		   if(dis>100)//防止食物在贪吃蛇身上生成
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
	char author[]="Producer: 孙宏伟 GAMENAME: GREEDY SNACK DATE: 2015/5/3 ";
	char o[]="GAME BEGIN!";
    char f[]="SCORE : ";
	char g[]="Game Intructions: W->UP, A->LEFT, S->DOWN, D->RIGHT, SPACEKEY->STOP ";
	outtextxy(20,10,author);
    outtextxy(20,30,o);
	outtextxy(20,50,f);
	outtextxy(20,70,g);

    sprintf(f,"%d",score);//将数字以字符串的形式输出
    outtextxy(60,50,f);
}
///////////////////////////////////
void drawSnack()//动的贪吃蛇的绘制
{
	   int i;

	   
       for(i=0;i<len;i++)//先画一个静止的贪吃蛇
	   {
		 drawCircle(snack[i][0],snack[i][1],0x881345);
	   }
        
       knockSelf();//判断蛇头是否画在了蛇身上
	   for(i=len-1;i>=0;i--)//画好之后将数组移位，为下一次贪吃蛇绘画做准备
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
				snack[0][1]-=20;break;//向上运动
			case 's':
				snack[0][1]+=20;break;//向下运动
			case 'a':
				snack[0][0]-=20;break;//向左运动
			case 'd':
				snack[0][0]+=20;break;//向右运动
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
	if(dist>0&&dist<20)//当蛇头坐标与食物坐标相同时
	{
		score++;
		len++;
        drawCircle(foodLocation[0],foodLocation[1],BLACK);//当食物坐标与舌头相同时，画黑圆覆盖它。
		drawFood();
	}

}
///////////////////////////////
//判断是否碰墙
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
			settextstyle(50,50,_T("黑体"));
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
			 settextstyle(10,15,_T("黑体"));
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
此次做游戏总结：
1，做游戏之前没有认真规划。
2，对于一些细节掌握不够好，还需要耐心钻研。
3，思考问题时太单一。

今后做游戏时应该：
1，做之前先要需求分析，游戏要实现哪些功能。
2，尽量做出草稿文档，画出游戏流程图，其次，做之前要对游戏中一些小的不确定的细节，通过小程序进行测试。
3，多练习用类实现，
*/