#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

//吃的东西的符号 
#define TABEMONO "★"
//身体符号 
#define BODY "●"
//空符号 
#define EMPTY "  "
//x轴移动步长 
#define STEPX 2
//y轴移动步长 
#define STEPY 1
//窗口高度 
#define HEIGHT 20
//窗口宽度 
#define WIDTH 40
//x轴初始位置 
#define STARTX 10
//y轴初始位置 
#define STARTY 5

//蛇身结构体，在移动的时候就知道双向链表的好处了 
typedef struct Node
{
	struct Node *pre;
	int x;
	int y;
	char ch[2];
	struct Node *next;
}Body;
//食物结构体
typedef struct FOOD
{
	int x;
	int y;
	char ch[2];
}Food;

//分数 
int score=0;
//蛇尾节点 
Body *tail;

//设置光标到指定的位置 
void goTo(int x,int y)
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos={x,y};
	SetConsoleCursorPosition(hOut,pos);
}

//限制x轴位置在指定区域内 
int limitX(int x)
{
	if(x==WIDTH)
		return 0;
	else if(x==-STEPX)
		return WIDTH-STEPX;
	return x;
}

//限制y轴位置在指定区域内
int limitY(int y)
{
	if(y==HEIGHT+STEPY-1)
		return 0;
	else if(y==-STEPY)
		return HEIGHT;
	return y;
}

//清除整条蛇占用的空间
void kill(Body *&snake)
{
	Body *p;
	for(p=snake,snake=snake->next;snake!=NULL;snake=snake->next)
	{
		free(p);
		p=snake;
	}
	free(p);
} 

//新建食物
void newFood(Food *&food)
{
	int x,y;
	do
	{
		x=(rand()%(WIDTH/2))*2;	//保证x为偶数 
		y=rand()%HEIGHT;
	}while(x==food->x && y==food->y);
	food->x=x;
	food->y=y;
} 

//蛇长身体，在坐标为x,y的地方生成新的尾部，并连接到身体 
void grow(Body *snake,int x,int y)
{
	Body *p;
	p=(Body *)malloc(sizeof(Body));
	p->x=x,p->y=y;
	strcpy(p->ch,EMPTY);	//尾节点是空的，用来覆盖之走过的身体 
	tail->next=p;	//尾节点的next指向新的尾节点 
	p->pre=tail;
	strcpy(tail->ch,BODY);
	tail=p;		//tail指向新的尾节点 
	tail->next=NULL;
}

//初始化各种东西，n是一开始蛇身的数量 
void init(Body *&snake,int n,char *direction,int *life,Food *&food)
{
	if(snake!=NULL)
		kill(snake);
	if(food==NULL)
	{
		food=(Food *)malloc(sizeof(Food));
	}
	Body *body;
	int x=STARTX,y=STARTY;
	int i;
	snake=(Body *)malloc(sizeof(Body));
	tail=snake;	//tail是全局变量，永远指向尾节点 
	snake->x=x;
	snake->y=y;
	strcpy(snake->ch,EMPTY);	//蛇从虚无中诞生（？） 
	snake->next=NULL;
	snake->pre=NULL;
	score=0;	//score是全局变量，任何函数都能改变它的值 
	for(i=0;i<n;i++)
	{
		y+=STEPY;
		grow(snake,x,y);
	} 
	*direction='w';
	*life=1;
	strcpy(food->ch,TABEMONO);
	newFood(food);
} 

//显示蛇和食物 
void display(Body *snake,Food *food)
{
	int i;
	Body *p;
	for(p=snake;p!=NULL;p=p->next)
	{
		goTo(p->x,p->y);
		printf("%s",p->ch);
	}
	goTo(food->x,food->y);
	printf("%s",food->ch);
	goTo(0,HEIGHT);
	printf("\t分数：%d",score);
} 

//蛇移动
int move(Body *&snake,Food *&food,char direction)
{
	Body *pre,*con;
	int check=0;
	int tailX,tailY;
	tailX=tail->x;	//tail->x/y会被修改掉，存起来 
	tailY=tail->y;	//当吃到食物时用这个坐标生成身体 
	for(con=tail,pre=tail->pre;pre!=NULL;pre=pre->pre,con=con->pre)
	{	//复制后面节点的坐标到前节点（双向链表的好处） 
		con->x=pre->x;
		con->y=pre->y;
	}
	switch(direction)
	{	//根据方向移动头的坐标（上个循环中头的坐标已经赋值给了脖子(?)了） 
		case 'w':snake->y=limitY(snake->y-STEPY);break;
		case 'a':snake->x=limitX(snake->x-STEPX);break;
		case 's':snake->y=limitY(snake->y+STEPY);break;
		case 'd':snake->x=limitX(snake->x+STEPX);break;
	}
	for(con=snake->next;con!=NULL;con=con->next)
	{
		if(con->x==snake->x && con->y==snake->y)	//吃到身体就结束 
			return 0;
	}
	if(snake->x==food->x && snake->y==food->y)
	{
		score+=1;
		newFood(food);
		grow(snake,tailX,tailY);
	}	
	return 1;
} 

int main()
{
	//随机数种子，每次打开程序，食物位置都不一样 
	srand((unsigned)time(NULL));
	system("mode con cols=40 lines=21");
	Body *snake=NULL;
	Food *food=NULL;
	char direction,input,again;
	int life=1,flag=1;
	int bestScore=0;
	int n=3;
	while(flag)
	{
		system("cls");
		init(snake,n,&direction,&life,food);
		while(life)
		{
			display(snake,food);
			if(kbhit())
			{
				input=getch();
				switch(input)
				{
					case 'w': case 'W': if(direction!='s') direction='w'; break;
					case 's': case 'S': if(direction!='w') direction='s'; break;
					case 'a': case 'A': if(direction!='d') direction='a'; break;
					case 'd': case 'D': if(direction!='a') direction='d'; break;
				}
			}
			life=move(snake,food,direction);
			Sleep(200);
		}
		bestScore=bestScore>score?bestScore:score;
		goTo(WIDTH/2,HEIGHT/2);
		printf("吃到了自己的身体！\n"); 
		system("pause");
		system("cls");
		printf("\n\t你的分数：%d\t最高分：%d\n",score,bestScore);
		printf("按'R'再来一次");
		again=getch();
		if(again!='R' && again!='r')
			flag=0;
	}
	kill(snake);
	return 0;
}
