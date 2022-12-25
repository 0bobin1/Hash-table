#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<conio.h>
#include<string.h>
#define HASH_LEN 50 //哈希表的长度
#define M 47 //随机数
#define NAME_NUM 30 //班级人数

typedef struct
{
	char* name;
	double score;//分数
	int ascii_sum; //ASCII和
}Stu;
typedef struct //哈希表
{
	char* name;
	int ascii_sum;
	double score;
	int s; //查找长度
}HASH;
Stu NameList[HASH_LEN];
HASH HashList[HASH_LEN];
//姓名（结构体数组）初始化
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
			//将字符串的各个字符所对应的ASCII码相加，所得的整数做为哈希表的关键字
			s0 = *(f + r) + s0;
		NameList[i].ascii_sum = s0;
	}
}
//建立哈希表
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
		int adr = (NameList[i].ascii_sum) % M; //哈希函数
		int d = adr;
		if (HashList[adr].s == 0) //如果不冲突
		{
			HashList[adr].ascii_sum = NameList[i].ascii_sum;
			HashList[adr].name = NameList[i].name;
			HashList[adr].score = NameList[i].score;
			HashList[adr].s = 1;
		}
		else //冲突
		{
			do
			{
				d = (d + NameList[i].ascii_sum % 10 + 1) % M; //伪随机探测再散列法处理冲突
				sum = sum + 1; //查找次数加1
			} while (HashList[d].ascii_sum != 0);
			HashList[d].ascii_sum = NameList[i].ascii_sum;
			HashList[d].name = NameList[i].name;
			HashList[d].score = NameList[i].score;
			HashList[d].s = sum + 1;
		}
	}
}
//查找
void FindList()
{
	char name[20] = { 0 };
	int s0 = 0, r, sum = 1, adr, d;
	printf("\n请输入姓名的拼音:");
	scanf("%s", name);
	for (r = 0; r < 20; r++) //求出姓名的拼音所对应的整数(关键字)
		s0 += name[r];
	adr = s0 % M; //使用哈希函数
	d = adr;
	if (HashList[adr].ascii_sum == s0) //分3种情况进行判断
		printf("\n姓名:%s 位置:%d 分数:%0.1f 关键字:%d 查找长度为: 1\n", HashList[d].name,d , HashList[d].score,s0);
	else if (HashList[adr].ascii_sum == 0)
		printf("无此记录!\n");
	else
	{
		int g = 0;
		do
		{
			d = (d + s0 % 10 + 1) % M; //伪随机探测再散列法处理冲突
			sum = sum + 1;
			if (HashList[d].ascii_sum == 0)
			{
				printf("无此记录! \n");
				g = 1;
			}
			if (HashList[d].ascii_sum == s0)
			{
				printf("\n姓名:%s 位置:%d 关键字:%d 查找长度为:%d\n", HashList[d].name,d, s0, sum);
				g = 1;
			}
		} while (g == 0);
	}
}
// 显示哈希表
void Display()
{
	int i;
	float average = 0;
	printf("\n\n地址\t姓名\t   查找长度\tH(key)\t关键字\n");
	for (i = 0; i < 50; i++)
	{
		printf("%-5d ", i);//地址
		printf("%-15s ", HashList[i].name);//姓名

		printf("%d ", HashList[i].s);//查找长度
		printf("\t%d ", HashList[i].ascii_sum % M);//H(key)
		printf("\t%d ", HashList[i].ascii_sum);//关键字
		printf("\n");
	}
	for (i = 0; i < HASH_LEN; i++)
		average += HashList[i].s;
	average /= NAME_NUM;
	printf("\n\n平均查找长度：ASL(%d)=%f \n\n", NAME_NUM, average);
}

void menu()
{
	printf("*************哈希表的建立和查找*************\n");
	printf("\t\t1. 显示哈希表 \n");
	printf("\t\t2. 查找 \n");
	printf("\t\t0. 退出 \n");
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
		printf("请输入选项:");
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