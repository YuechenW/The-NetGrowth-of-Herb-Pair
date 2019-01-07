#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include"source.h"

int main(int argc, char const * argv[])
{
	int selct_i = 0;
	int c = 0, lines = 0;
	char tmp[10];
	int sleptime;

	//欢迎界面
	system("title The NetGrowth of Herb Pair");
	system("mode con cols=74 lines=30");
	system("color 0B");
	system("date /T");
	system("TIME /T");
	printf("╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪╪\n");
	printf("╔═══╧╧╧╧╧╧        Welcome to the NetGrowth of Herb Pair        ╧╧╧╧╧╧═══╗\n");
	printf("║ This NetGrowth is based on 'A complete collection of Chinese medicine'║\n");
	printf("╚═══════════════════════════════════════════════════════════════════════╝\n\n");
	printf("                                           version: 2.019      by:王悦晨\n");
	system("PAUSE");
	system("CLS");
	system("color 0A");

	//读取原文件 舍去不需要数据 生成一个新文件
	FILE * f_y = fopen("A complete collection of Chinese medicine.txt", "r");
	FILE * f_z = fopen("tmp.txt", "a");
	if (f_y)
	{
		char buf[100];
		char meanls[][100] = { "　　二、辛凉解表\n","　　第二章 温里类\n","　　第三章 清热类\n","　　一、清热泄火\n","　　二、清退虚热\n","　　三、清热凉血\n","　　第四章 泻下类\n","　　一、攻下\n","　　二、润肠\n","　　三、逐水\n","　　第五章 除湿类\n","　　一、化湿\n","　　二、利湿\n","　　三、祛风湿\n","　　第六章 止咳类\n","　　第七章 消散类\n","　　一、化痰\n","　　第十四章 其它\n","　　一、开窍\n","　　二、截疟\n","　　三、涌吐\n","　　四、驱虫\n","　　五、外用\n" };
		fseek(f_y, 2125L, SEEK_SET);//用fgets和fputs试出的跳过位置
		while (fgets(buf, 100, f_y) != NULL)
		{
			int jishu = 1;
			for (int i = 0; i < (sizeof(meanls) / sizeof(meanls[0])); i++)
			{
				if (strcmp(meanls[i], buf) == 0)
					jishu = 0;
			}
			if (jishu == 1)
				fputs(buf, f_z);
		}
	}

	fclose(f_y);
	fclose(f_z);

	//获取文件行数
	FILE * f_p = fopen("tmp.txt", "r");
	if (f_p)
	{
		while ((c = fgetc(f_p)) != EOF)
			if (c == '\n')
				lines++;
		lines = lines + 1;
		printf("已获取到该文件的总药对数为%d(不含重复)\n", lines);
		Sleep(2000);
		fclose(f_p);
	}
	int number = lines;
	type *aTyp;
	aTyp = malloc(sizeof(type)*number);
	char (*selected)[20];
	selected = malloc(sizeof(char)*number * 20);

	//做循环将文件中的值录入数组
	FILE * fp = fopen("tmp.txt", "r");
	if (fp)
	{
		for (int i = 0; i < number; i++)
		{
			int jishu = 0;//处理开头的中文空白
			for (int j = 0; j < i; j++)
			{
				fscanf(fp, "%*[^\n]%*c");
				jishu = 1;
			}
			if (jishu == 0)
				fseek(fp, 4L, SEEK_CUR);
			else if (jishu == 1)
				fseek(fp, 6L, SEEK_CUR);
			fscanf(fp, "%s %s", aTyp[i].first, aTyp[i].second);
			aTyp[i].num = 1;
			for (int k = 0; k < i; k++)
			{
				if (((strcmp(aTyp[i].first, aTyp[k].first) == 0) && (strcmp(aTyp[i].second, aTyp[k].second) == 0)) || ((strcmp(aTyp[i].first, aTyp[k].second) == 0) && (strcmp(aTyp[i].second, aTyp[k].first) == 0)))
				{
					aTyp[k].num += 1;
					aTyp[i].num = 0;
				}
			}
		}
	}
	fclose(fp);

	//清除文件内容
	FILE * f_f = fopen("tmp.txt", "w");
	fclose(f_f);

	//打印数组
	printf("请输入每一行的显示时间：(ms)(推荐200)");
	scanf("%d", &sleptime);
	printf("药对如下：\n\n");
	int m = 1;
	for (int i = 0; i < number; i++)
	{
		if (aTyp[i].num == 0)
			continue;
		printf("第%3d个药对：\n", m);
		printf("%-8s %-8s 关联度 %d\n", aTyp[i].first, aTyp[i].second, aTyp[i].num);
		m++;
		Sleep(sleptime);
	}

	//按关联度输出数据
	int selt = 0;
	while (1)
	{
		printf("\n请问您想看关联度为多少的药对？(0跳过)\n");
		scanf("%d", &selt);
		if (selt == 0)
			break;
		else
			for (int i = 0; i < number; i++)
			{
				if (aTyp[i].num == selt)
				{
					printf("%-8s %-8s 关联度 %d\n", aTyp[i].first, aTyp[i].second, aTyp[i].num);
					Sleep(sleptime);
				}
			}
	}

	//获取关系头
	re:printf("\n请输入要构造的中药：");
	scanf("%s", tmp);

	//输出界面
	system("CLS");
	system("color 0D");
	printf("请闭上眼睛默数到第三秒见证神奇的一刻：\n");
	Sleep(3000);
	system("color 7C");
	Sleep(150);
	system("color 0C");
	Sleep(150);
	system("color 7C");
	Sleep(150);
	system("color 0C");
	Sleep(150);
	system("color 7C");
	printf("\nBling~\n\n草药链如下：\n");
	printf("%s", tmp);
	strcpy(selected[selct_i], tmp);
	selct_i++;

	//查找关系头
	int max_i = -1, max_num = 0;
	for (int i = 0; i < number; i++)
	{
		if (strcmp(tmp, aTyp[i].first) == 0 || strcmp(tmp, aTyp[i].second) == 0)
		{
			if (max_num < aTyp[i].num)
			{
				max_num = aTyp[i].num;
				max_i = i;
			}
		}
	}
	if (strcmp(tmp, aTyp[max_i].first) == 0)
		strcpy(tmp, aTyp[max_i].second);
	else
		strcpy(tmp, aTyp[max_i].first);
	if (max_i == -1)
	{
		printf("未在草药中找到，");
		printf("请重新输入。");
		goto re;
	}
	else
	{
		printf(" -> %s (关联度%d)", tmp, aTyp[max_i].num);
		strcpy(selected[selct_i], tmp);
		selct_i++;
	}

	//测试已选择数组
		//printf("%s %s",selected[0],selected[1]);

	//开始循环连接下一项
	while (max_num != 0)
	{
		max_i = -1, max_num = 0;
		for (int i = 0; i < number; i++)
		{

			if (strcmp(tmp, aTyp[i].first) == 0 || strcmp(tmp, aTyp[i].second) == 0)
			{
				if (max_num < aTyp[i].num)
				{

					if (strcmp(tmp, aTyp[i].first) == 0)
					{
						int jishu = 1;
						for (int j = 0; j < selct_i; j++)
						{
							if (strcmp(aTyp[i].second, selected[j]) == 0)
								jishu = 0;
						}
						if (jishu == 1)
						{
							max_num = aTyp[i].num;
							max_i = i;
							strcpy(tmp, aTyp[max_i].second);
						}
					}
					else if (strcmp(tmp, aTyp[i].second) == 0)
					{
						int jishu = 1;
						for (int j = 0; j < selct_i; j++)
						{
							if (strcmp(aTyp[i].first, selected[j]) == 0)
								jishu = 0;
						}
						if (jishu == 1)
						{
							max_num = aTyp[i].num;
							max_i = i;
							strcpy(tmp, aTyp[max_i].first);
						}
					}
				}
			}
		}
		if (max_num != 0)
		{
			printf(" -> %s (关联度%d)", tmp, aTyp[max_i].num);
			strcpy(selected[selct_i], tmp);
			selct_i++;
		}

		//测试已选择数组
				//printf("%s %s %s",selected[0],selected[1],selected[2]);
	}
	free(aTyp);
	free(selected);

	return 0;
}
