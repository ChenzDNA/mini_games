#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>

#define L 20

void goto_xy(int x, int y)	//��λ���λ�õ�ָ������
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//��ȡ��׼������ 
	COORD pos={x,y};			//����ṹ�� 
	SetConsoleCursorPosition(hOut,pos);	//��λ���λ�� 
}

void wa(int y,int x,char a[L][L],int b[L][L],int *ming,char *temp,int *shan)		//�ڿ���ǰѡ���ĸ���
{
	int i;
	if(a[y][x]=='F' || *temp=='F')		//�����ӾͲ��ڿ�
		return;
	if(b[y][x]==-1)			//���׾�����ֵ����
	{
		*ming=0;
		return;
	}
	else if(b[y][x]>0)		//�����־�ֻ�ڿ���һ�� 
	{
		a[y][x]=48+b[y][x];
		*shan=1;
		return;
	}
	else if(b[y][x]==0 || a[y][x]=='#')		//�ǿյؾ��ڿ���Χ�ĸ���
	{
		a[y][x]=' ';
		b[y][x]=-2;
		*temp=a[y][x];
		if(y!=19 && b[y+1][x]!=-1)
			wa(y+1,x,a,b,ming,temp,shan);
		if(x!=19 && b[y][x+1]!=-1)
			wa(y,x+1,a,b,ming,temp,shan);
		if(y!=19 && x!=19 && b[y+1][x+1]!=-1)
			wa(y+1,x+1,a,b,ming,temp,shan);
		if(y!=0 && x!=0 && b[y-1][x-1]!=-1)
			wa(y-1,x-1,a,b,ming,temp,shan);
		if(y!=0 && b[y-1][x]!=-1)
			wa(y-1,x,a,b,ming,temp,shan);
		if(x!=0 && b[y][x-1]!=-1)
			wa(y,x-1,a,b,ming,temp,shan);
		if(y!=0 && x!=19 && b[y-1][x+1]!=-1)
			wa(y-1,x+1,a,b,ming,temp,shan);
		if(y!=19 && x!=0 && b[y+1][x-1]!=-1)
			wa(y+1,x-1,a,b,ming,temp,shan);
	}
}

void biao(int y,int x,char a[L][L],int *flag,int *n,char *temp)		//��ǣ����죩
{
	if(!*n && (a[y][x]!='F' || *temp!='F'))		//������˾�û����ˣ���֤����=������
		return;
	if(a[y][x]=='F' || *temp=='F')		//��������ͻ�����
	{
		a[y][x]='#';
		*temp='#';
		*flag-=1;
		*n+=1;
		return;
	}
	a[y][x]='F';		//����
	*flag+=1;
	*n-=1;
	*temp='F';
}

int xianzhi(int x)		//���ƹ���˶���Χ
{
	if(x==L)
		return 0;
	else if(x==-1)
		return 19;
	return x;
}

void dilei(int n,int b[L][L])		//�����
{
	int i,j,x,y;
	while(n)	//������ɵ���
	{
		x=rand()%L;
		y=rand()%L;
		if(b[y][x]==0)
		{
			b[y][x]=-1;
			n-=1;
		}	
	}
	for(i=0;i<L;i++)	//����������Χ�ĸ��ӣ�ÿ��bֵ+1
		for(j=0;j<L;j++)
		{
			if(b[i][j]==-1)
			{
				if(i!=19 && b[i+1][j]!=-1)
					b[i+1][j]+=1;
				if(j!=19 && b[i][j+1]!=-1)
					b[i][j+1]+=1;
				if(i!=19 && j!=19 && b[i+1][j+1]!=-1)
					b[i+1][j+1]+=1;
				if(i!=0 && j!=0 && b[i-1][j-1]!=-1)
					b[i-1][j-1]+=1;
				if(i!=0 && b[i-1][j]!=-1)
					b[i-1][j]+=1;
				if(j!=0 && b[i][j-1]!=-1)
					b[i][j-1]+=1;
				if(i!=0 && j!=19 && b[i-1][j+1]!=-1)
					b[i-1][j+1]+=1;
				if(i!=19 && j!=0 && b[i+1][j-1]!=-1)
					b[i+1][j-1]+=1;
			}
		}
	
}

void ditu(int *y,int *x,char a[L][L],int *flag,int *n)			 //��ӡ��ͼ
{
	int i,j;
	for(i=0;i<23;i++)	//��ӡ��ͼ
		{
			if(i==0)
				printf("  X  0   2   4   6   8  10  12  14  16  18\n");
			else if(i==1)
				printf(" Y     1   3   5   7   9  11  13  15  17  19\n");
			else if(i==2)
				printf("\n");
			else
			{	
				printf("%2d  ",i-3);
				for(j=0;j<L;j++)
					printf(" %c",a[i-3][j]);
				printf(" ");
			}
		}
		printf("\n\n\t�ѱ����:%d\t������:%d\n\n\t������� x:%d\ty:%d",*flag,*n,*x,*y);
	return;
}

void danandu(char nandu)			//��ӡ�Ѷ�
{
	if(nandu=='1')
		printf("\t\t����\n");
	else if(nandu=='2')
		printf("\t\t�����Կ�\n");
	else if(nandu=='3')
		printf("\t\t����\n");
	else
		printf("\t\t���nb\n");
}

int main()
{
	system("title ����ɨ��");
	system("mode con cols=45 lines=32");
	char r='r';
	while(r=='r' || r=='R')
	{
		char a[L][L],dong,temp,nandu='0';
		int b[L][L]={0},i,j,ming=1,y=0,x=0,flag=0,shan=1,n=0,dan1=0,dan2=0,dan3=0,zdan=0,check=0;
		system("cls");
		printf("\n\n    WASD���ƹ���ƶ�\n    E���ڿ�������ڵĸ���\n    F���������\n\n    ѡ���Ѷȣ�\n\n\t1.����\n\n\t2.�����Կ�\n\n\t3.����\n\n\t4.���nb\n\n\t(��������1~4)\n");
		while(nandu<49 || nandu>52)		//�����Ѷȣ�����1~4��
			nandu=getch();
		if(nandu=='1')		//�����Ѷȵ�������
			n=10;
		else if(nandu=='2')
			n=20;
		else if(nandu=='3')
			n=30;
		else
			n=50;
		zdan=n;		//zdan�ں��������ж�ʤ������
		dilei(n,b);		//����
		for(i=0;i<L;i++)
			for(j=0;j<L;j++)
				a[i][j]='#';		//��ʼ����ͼ
		system("cls");
		while(ming)			//����ֵ��Ϊ0ʱһֱѭ��
		{
			//system("cls");
			goto_xy(0,0);
			danandu(nandu);
			ditu(&y,&x,a,&flag,&n);
			if(kbhit())		//����
			{
				dong=getch();
				switch (dong)
				{
					case 'W':
					case 'w': a[y][x]=temp; y=xianzhi(y-1); shan=1; break;
					case 'S':
					case 's': a[y][x]=temp; y=xianzhi(y+1); shan=1; break;
					case 'A':
					case 'a': a[y][x]=temp; x=xianzhi(x-1); shan=1; break;
					case 'D':
					case 'd': a[y][x]=temp; x=xianzhi(x+1); shan=1; break;		//WASD�ƶ���� 
					case 'E':
					case 'e': wa(y,x,a,b,&ming,&temp,&shan); break;		//e������
					case 'F':
					case 'f': biao(y,x,a,&flag,&n,&temp); break;		//f������
				}
			}
				
			if(shan)		//�������
			{
				shan=0;
				temp=a[y][x];
				a[y][x]=' ';
			}
			else
			{
				a[y][x]=temp;
				shan=1;
			}
			
			dan3=dan1=zdan;		//�ж�ʤ������
			dan2=0;
			for(i=0;i<L;i++)
				for(j=0;j<L;j++)
				{
					if(a[i][j]=='F' || a[i][j]=='#')
					{
						dan1-=1;
						if(b[i][j]==-1)
							dan2+=1;
					}
					if(a[i][j]=='F' && b[i][j]==-1)
						dan3-=1;
				}
			if(dan1==0 && dan2==zdan)		//���е��׶����ҳ�����һ�������ϲ��죩 ����Ϸʤ�� 
			{
				check=1;
				break;
			}
			if(!dan3)		//�����е����ϲ���������Ϸʤ��
			{
				check=1;
				break;
			}
			else if(flag==zdan)
				printf("\n\n\tĳ��λ�ñ���д���");
			Sleep(500);
		}
		
		if(!ming) 			//����ֵΪ0��ʧ��
		{
			system("cls");
			goto_xy(0,0);
			danandu(nandu);
			for(i=0;i<L;i++)
				for(j=0;j<L;j++)
					if(a[i][j]!='F' && b[i][j]==-1)
						a[i][j]='x';		//ʧ��ʱ��ʾ���е���
			ditu(&y,&x,a,&flag,&n);
			printf("\n\n\tYOU LOSE!\n\tR�����¿�ʼ");
			r=getch();
		}
		if(check)			//��Ϸʤ��
		{
			system("cls");
			putchar(10);
			danandu(nandu);
			printf("\n\n\n\n\tYOU WIN!\n\n\tR�����¿�ʼ");
			r=getch();
		}
	}
	return 0;
} 
