#include<stdio.h>
#include<windows.h>
void goto_xy(int x, int y)	//��λ���λ�õ�ָ������
{
	HANDLE hOut;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);	//��ȡ��׼������ 
	COORD pos={x,y};			//����ṹ�� 
	SetConsoleCursorPosition(hOut,pos);	//��λ���λ�� 
}
void exchange(char *a,char *b)
{
	char t;
	t=*a,*a=*b,*b=t;
}
int main()
{
	system("color 02");	//ȫ�ֺڵ����� 
	system("mode con cols=40 lines=19");
	int b[40]={0};
	char a[20][40];
	int i,j,k,s;
	int std1,std2,std3;
	for(i=0;i<20;i++)
		for(j=0;j<40;j++)
			a[i][j]=' ';	//a��ʼ�� 
	while(1)
	{
	//	system("cls");
		goto_xy(0,0);
		for(i=rand()%40;b[i]!=0;i=rand()%40);	//ȷ�����������b[i]Ϊ0 
		b[i]=rand()%4+4;		//��b[i]�����ֵ����Χ��4~7����ʾ���λ�õ��ַ������� 
		for(j=18;j>-1;j--)
			for(k=0;k<40;k++)
				if(a[j][k]!=' ')
					exchange(&a[j][k],&a[j+1][k]);		//�ý�����ʽ���� 
		for(j=0;j<40;j++)
			if(b[j])			//����b[]��a[][]�ĵ�һ�и�ֵ 
			{
				s=rand()%3;	//�����s=0�������֣�1��д��ĸ��2Сд��ĸ 
				if(s==0)
					a[0][j]=rand()%10+48;
				else if(s==1)
					a[0][j]=rand()%26+65;
				else
					a[0][j]=rand()%26+97;	//�����ֵ��Сд��ĸ������ 
			}
		for(j=0;j<40;j++)
			a[19][j]=' ';		//���һ��Ӧ���ǿյģ���Ȼ��û�û� 
		for(j=0;j<19;j++)			//��ӡ 
		{
			for(k=0;k<40;k++)
				putchar(a[j][k]);
			putchar(10);
		}
		for(j=0;j<40;j++)
			if(b[j])
				b[j]--;		//b[]ֵ����1�����������ַ����� 
		Sleep(50);
	}
	return 0;
}
