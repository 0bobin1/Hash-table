#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<conio.h>
#include<string.h>
#define HASH_LEN 50 //��ϣ��ĳ���
#define M 47 //�����
#define NAME_NUM 30 //�༶����

typedef struct
{
	char* name;
	double score;//����
	int ascii_sum; //ASCII��
}Stu;
typedef struct //��ϣ��
{
	char* name;
	int ascii_sum;
	double score;
	int s; //���ҳ���
}HASH;
Stu NameList[HASH_LEN];
HASH HashList[HASH_LEN];
//�������ṹ�����飩��ʼ��
void creat(Stu s[], int n, char a[], double score)
{
	NameList[n].name = &a[0];
	NameList[n].score = score;
}
void InitNameList()
{
	char* f;
	int r, s0, i;
	creat(NameList, 0, "zhangsan", 60.0);
	creat(NameList, 1, "lisi", 54.0);
	creat(NameList, 2, "wangwu", 77.0);
	creat(NameList, 3, "zhaoliu", 78.0);
	creat(NameList, 4, "libai", 95.0);
	creat(NameList, 5, "baijvyi", 94.0);
	creat(NameList, 6, "taoyuanming", 92.0);
	creat(NameList, 7, "dufu", 94.0);
	creat(NameList, 8, "liuzongyuan", 89.0);
	creat(NameList, 9, "hanyu", 88.0);
	creat(NameList, 10, "wangwei", 89.0);
	creat(NameList, 11, "menghaoran", 85.0);
	creat(NameList, 12, "lihe", 84.0);
	creat(NameList, 13, "liuyvxi", 86.0);
	creat(NameList, 14, "dumu", 87.0);
	creat(NameList, 15, "lishangyin", 82.0);
	creat(NameList, 16, "gaoshi", 78.0);
	creat(NameList, 17, "luyou", 76.0);
	creat(NameList, 18, "yangwanli", 78.5);
	creat(NameList, 19, "fanchengda", 80.0);
	creat(NameList, 20, "xielingyun", 90.0);
	creat(NameList, 21, "xiehuilian", 90.5);
	creat(NameList, 22, "censhen", 91.0);
	creat(NameList, 23, "xinqiji", 92.5);
	creat(NameList, 24, "huangtingjian", 93.0);
	creat(NameList, 25, "suxun", 90.5);
	creat(NameList, 26, "sushi", 85.5);
	creat(NameList, 27, "suzhe", 80.5);
	creat(NameList, 28, "liqingzhao", 88.5);
	creat(NameList, 29, "liuyong", 90.0);

	for (i = 0; i < NAME_NUM; i++)
	{
		s0 = 0;
		f = NameList[i].name;
		for (r = 0; *(f + r) != '\0'; r++)
			//���ַ����ĸ����ַ�����Ӧ��ASCII����ӣ����õ�������Ϊ��ϣ��Ĺؼ���
			s0 = *(f + r) + s0;
		NameList[i].ascii_sum = s0;
	}
}
//������ϣ��
void CreateHashList()
{
	int i;
	for (i = 0; i < HASH_LEN; i++)
	{
		HashList[i].name = "";
		HashList[i].ascii_sum = 0;
		HashList[i].s = 0;
		HashList[i].score = 0.0;
	}
	for (i = 0; i < HASH_LEN; i++)
	{
		int sum = 0;
		int adr = (NameList[i].ascii_sum) % M; //��ϣ����
		int d = adr;
		if (HashList[adr].s == 0) //�������ͻ
		{
			HashList[adr].ascii_sum = NameList[i].ascii_sum;
			HashList[adr].name = NameList[i].name;
			HashList[adr].score = NameList[i].score;
			HashList[adr].s = 1;
		}
		else //��ͻ
		{
			do
			{
				d = (d + NameList[i].ascii_sum % 10 + 1) % M; //α���̽����ɢ�з������ͻ
				sum = sum + 1; //���Ҵ�����1
			} while (HashList[d].ascii_sum != 0);
			HashList[d].ascii_sum = NameList[i].ascii_sum;
			HashList[d].name = NameList[i].name;
			HashList[d].score = NameList[i].score;
			HashList[d].s = sum + 1;
		}
	}
}
//����
void FindList()
{
	char name[20] = { 0 };
	int s0 = 0, r, sum = 1, adr, d;
	printf("\n������������ƴ��:");
	scanf("%s", name);
	for (r = 0; r < 20; r++) //���������ƴ������Ӧ������(�ؼ���)
		s0 += name[r];
	adr = s0 % M; //ʹ�ù�ϣ����
	d = adr;
	if (HashList[adr].ascii_sum == s0) //��3����������ж�
		printf("\n����:%s λ��:%d ����:%0.1f �ؼ���:%d ���ҳ���Ϊ: 1\n", HashList[d].name,d , HashList[d].score,s0);
	else if (HashList[adr].ascii_sum == 0)
		printf("�޴˼�¼!\n");
	else
	{
		int g = 0;
		do
		{
			d = (d + s0 % 10 + 1) % M; //α���̽����ɢ�з������ͻ
			sum = sum + 1;
			if (HashList[d].ascii_sum == 0)
			{
				printf("�޴˼�¼! \n");
				g = 1;
			}
			if (HashList[d].ascii_sum == s0)
			{
				printf("\n����:%s λ��:%d �ؼ���:%d ���ҳ���Ϊ:%d\n", HashList[d].name,d, s0, sum);
				g = 1;
			}
		} while (g == 0);
	}
}
// ��ʾ��ϣ��
void Display()
{
	int i;
	float average = 0;
	printf("\n\n��ַ\t����\t   ���ҳ���\tH(key)\t�ؼ���\n");
	for (i = 0; i < 50; i++)
	{
		printf("%-5d ", i);//��ַ
		printf("%-15s ", HashList[i].name);//����

		printf("%d ", HashList[i].s);//���ҳ���
		printf("\t%d ", HashList[i].ascii_sum % M);//H(key)
		printf("\t%d ", HashList[i].ascii_sum);//�ؼ���
		printf("\n");
	}
	for (i = 0; i < HASH_LEN; i++)
		average += HashList[i].s;
	average /= NAME_NUM;
	printf("\n\nƽ�����ҳ��ȣ�ASL(%d)=%f \n\n", NAME_NUM, average);
}

void menu()
{
	printf("*************��ϣ��Ľ����Ͳ���*************\n");
	printf("\t\t1. ��ʾ��ϣ�� \n");
	printf("\t\t2. ���� \n");
	printf("\t\t0. �˳� \n");
	//printf("\t\t\n");
}

void main()
{
	int ch1;
	int flag = 1;
	InitNameList();
	CreateHashList();
	while (flag)
	{
		menu();
		printf("������ѡ��:");
		fflush(stdin);
		scanf("%d", &ch1);
		switch (ch1)
		{
		case 1:Display(); break;
		case 2:FindList(); break;
		default:flag = 0; break;
		}
	}
}