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

	//��ӭ����
	system("title The NetGrowth of Herb Pair");
	system("mode con cols=74 lines=30");
	system("color 0B");
	system("date /T");
	system("TIME /T");
	printf("�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n�n\n");
	printf("�X�T�T�T�k�k�k�k�k�k        Welcome to the NetGrowth of Herb Pair        �k�k�k�k�k�k�T�T�T�[\n");
	printf("�U This NetGrowth is based on 'A complete collection of Chinese medicine'�U\n");
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n\n");
	printf("                                           version: 2.019      by:���ó�\n");
	system("PAUSE");
	system("CLS");
	system("color 0A");

	//��ȡԭ�ļ� ��ȥ����Ҫ���� ����һ�����ļ�
	FILE * f_y = fopen("A complete collection of Chinese medicine.txt", "r");
	FILE * f_z = fopen("tmp.txt", "a");
	if (f_y)
	{
		char buf[100];
		char meanls[][100] = { "���������������\n","�����ڶ��� ������\n","���������� ������\n","����һ������й��\n","����������������\n","��������������Ѫ\n","���������� к����\n","����һ������\n","����������\n","����������ˮ\n","���������� ��ʪ��\n","����һ����ʪ\n","����������ʪ\n","�����������ʪ\n","���������� ֹ����\n","���������� ��ɢ��\n","����һ����̵\n","������ʮ���� ����\n","����һ������\n","����������ű\n","��������ӿ��\n","�����ġ�����\n","�����塢����\n" };
		fseek(f_y, 2125L, SEEK_SET);//��fgets��fputs�Գ�������λ��
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

	//��ȡ�ļ�����
	FILE * f_p = fopen("tmp.txt", "r");
	if (f_p)
	{
		while ((c = fgetc(f_p)) != EOF)
			if (c == '\n')
				lines++;
		lines = lines + 1;
		printf("�ѻ�ȡ�����ļ�����ҩ����Ϊ%d(�����ظ�)\n", lines);
		Sleep(2000);
		fclose(f_p);
	}
	int number = lines;
	type *aTyp;
	aTyp = malloc(sizeof(type)*number);
	char (*selected)[20];
	selected = malloc(sizeof(char)*number * 20);

	//��ѭ�����ļ��е�ֵ¼������
	FILE * fp = fopen("tmp.txt", "r");
	if (fp)
	{
		for (int i = 0; i < number; i++)
		{
			int jishu = 0;//����ͷ�����Ŀհ�
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

	//����ļ�����
	FILE * f_f = fopen("tmp.txt", "w");
	fclose(f_f);

	//��ӡ����
	printf("������ÿһ�е���ʾʱ�䣺(ms)(�Ƽ�200)");
	scanf("%d", &sleptime);
	printf("ҩ�����£�\n\n");
	int m = 1;
	for (int i = 0; i < number; i++)
	{
		if (aTyp[i].num == 0)
			continue;
		printf("��%3d��ҩ�ԣ�\n", m);
		printf("%-8s %-8s ������ %d\n", aTyp[i].first, aTyp[i].second, aTyp[i].num);
		m++;
		Sleep(sleptime);
	}

	//���������������
	int selt = 0;
	while (1)
	{
		printf("\n�������뿴������Ϊ���ٵ�ҩ�ԣ�(0����)\n");
		scanf("%d", &selt);
		if (selt == 0)
			break;
		else
			for (int i = 0; i < number; i++)
			{
				if (aTyp[i].num == selt)
				{
					printf("%-8s %-8s ������ %d\n", aTyp[i].first, aTyp[i].second, aTyp[i].num);
					Sleep(sleptime);
				}
			}
	}

	//��ȡ��ϵͷ
	re:printf("\n������Ҫ�������ҩ��");
	scanf("%s", tmp);

	//�������
	system("CLS");
	system("color 0D");
	printf("������۾�Ĭ�����������֤�����һ�̣�\n");
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
	printf("\nBling~\n\n��ҩ�����£�\n");
	printf("%s", tmp);
	strcpy(selected[selct_i], tmp);
	selct_i++;

	//���ҹ�ϵͷ
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
		printf("δ�ڲ�ҩ���ҵ���");
		printf("���������롣");
		goto re;
	}
	else
	{
		printf(" -> %s (������%d)", tmp, aTyp[max_i].num);
		strcpy(selected[selct_i], tmp);
		selct_i++;
	}

	//������ѡ������
		//printf("%s %s",selected[0],selected[1]);

	//��ʼѭ��������һ��
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
			printf(" -> %s (������%d)", tmp, aTyp[max_i].num);
			strcpy(selected[selct_i], tmp);
			selct_i++;
		}

		//������ѡ������
				//printf("%s %s %s",selected[0],selected[1],selected[2]);
	}
	free(aTyp);
	free(selected);

	return 0;
}
