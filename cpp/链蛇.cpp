#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

//�ԵĶ����ķ��� 
#define TABEMONO "��"
//������� 
#define BODY "��"
//�շ��� 
#define EMPTY "  "
//x���ƶ����� 
#define STEPX 2
//y���ƶ����� 
#define STEPY 1
//���ڸ߶� 
#define HEIGHT 20
//���ڿ�� 
#define WIDTH 40
//x���ʼλ�� 
#define STARTX 10
//y���ʼλ�� 
#define STARTY 5

//����ṹ�壬���ƶ���ʱ���֪��˫������ĺô��� 
typedef struct Node
{
	struct Node *pre;
	int x;
	int y;
	char ch[2];
	struct Node *next;
}Body;
//ʳ��ṹ��
typedef struct FOOD
{
	int x;
	int y;
	char ch[2];
}Food;

//���� 
int score=0;
//��β�ڵ� 
Body *tail;

//���ù�굽ָ����λ�� 
void goTo(int x,int y)
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos={x,y};
	SetConsoleCursorPosition(hOut,pos);
}

//����x��λ����ָ�������� 
int limitX(int x)
{
	if(x==WIDTH)
		return 0;
	else if(x==-STEPX)
		return WIDTH-STEPX;
	return x;
}

//����y��λ����ָ��������
int limitY(int y)
{
	if(y==HEIGHT+STEPY-1)
		return 0;
	else if(y==-STEPY)
		return HEIGHT;
	return y;
}

//���������ռ�õĿռ�
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

//�½�ʳ��
void newFood(Food *&food)
{
	int x,y;
	do
	{
		x=(rand()%(WIDTH/2))*2;	//��֤xΪż�� 
		y=rand()%HEIGHT;
	}while(x==food->x && y==food->y);
	food->x=x;
	food->y=y;
} 

//�߳����壬������Ϊx,y�ĵط������µ�β���������ӵ����� 
void grow(Body *snake,int x,int y)
{
	Body *p;
	p=(Body *)malloc(sizeof(Body));
	p->x=x,p->y=y;
	strcpy(p->ch,EMPTY);	//β�ڵ��ǿյģ���������֮�߹������� 
	tail->next=p;	//β�ڵ��nextָ���µ�β�ڵ� 
	p->pre=tail;
	strcpy(tail->ch,BODY);
	tail=p;		//tailָ���µ�β�ڵ� 
	tail->next=NULL;
}

//��ʼ�����ֶ�����n��һ��ʼ��������� 
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
	tail=snake;	//tail��ȫ�ֱ�������Զָ��β�ڵ� 
	snake->x=x;
	snake->y=y;
	strcpy(snake->ch,EMPTY);	//�ߴ������е��������� 
	snake->next=NULL;
	snake->pre=NULL;
	score=0;	//score��ȫ�ֱ������κκ������ܸı�����ֵ 
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

//��ʾ�ߺ�ʳ�� 
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
	printf("\t������%d",score);
} 

//���ƶ�
int move(Body *&snake,Food *&food,char direction)
{
	Body *pre,*con;
	int check=0;
	int tailX,tailY;
	tailX=tail->x;	//tail->x/y�ᱻ�޸ĵ��������� 
	tailY=tail->y;	//���Ե�ʳ��ʱ����������������� 
	for(con=tail,pre=tail->pre;pre!=NULL;pre=pre->pre,con=con->pre)
	{	//���ƺ���ڵ�����굽ǰ�ڵ㣨˫������ĺô��� 
		con->x=pre->x;
		con->y=pre->y;
	}
	switch(direction)
	{	//���ݷ����ƶ�ͷ�����꣨�ϸ�ѭ����ͷ�������Ѿ���ֵ���˲���(?)�ˣ� 
		case 'w':snake->y=limitY(snake->y-STEPY);break;
		case 'a':snake->x=limitX(snake->x-STEPX);break;
		case 's':snake->y=limitY(snake->y+STEPY);break;
		case 'd':snake->x=limitX(snake->x+STEPX);break;
	}
	for(con=snake->next;con!=NULL;con=con->next)
	{
		if(con->x==snake->x && con->y==snake->y)	//�Ե�����ͽ��� 
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
	//��������ӣ�ÿ�δ򿪳���ʳ��λ�ö���һ�� 
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
		printf("�Ե����Լ������壡\n"); 
		system("pause");
		system("cls");
		printf("\n\t��ķ�����%d\t��߷֣�%d\n",score,bestScore);
		printf("��'R'����һ��");
		again=getch();
		if(again!='R' && again!='r')
			flag=0;
	}
	kill(snake);
	return 0;
}
