#include "account.h"

AC* head = NULL;
void sign_in() // 注册
{
	FILE* fp;
	int flag = 0;
	char userName[10];
	char passWorld[10];
	char name1[20];
	char phone1[12];
	char userName1[10];//储存txt文件账户信息用于比对
	char passWorld1[10];
	while (1)
	{
		printf("\t注册(用户名密码最多9位)\n");
		if ((fp = fopen("enter.txt", "a+")) == NULL)
		{
			printf("\tERROR!\n");
			exit(0);
		}
		printf("\t用户名:");
		scanf("%s", userName);
		getchar();
		while (fscanf(fp, "%s %s %s %s", userName1, passWorld1,name1,phone1) == 4)
		{
			if (!strcmp(userName, userName1))
			{
				printf("\t用户名重复\n");
				flag = 1;
				break;
			}
		}



		if (flag == 1)
		{
			printf("\t");
			printf("1.换个名字 2.返回菜单\n");
			printf("\t");
			int judge;
			scanf("%d", &judge);

			switch (judge)
			{
			case 1:
				flag = 0;
				getchar();
				continue;
				break;
			case 2:
				system("cls");
				enter();
				return;
			}
		}
		else
		{
			printf("\t密码:");
			scanf("%s", passWorld);
			printf("\t姓名:");
			scanf("%s", name1);
			printf("\t电话:");
			scanf("%s", phone1);
			getchar();
			fp = fopen("enter.txt", "a+");
			if (fp == NULL)
			{
				printf("无法打开文件 enter.txt\n");
				return;
			}
			printf("\t注册成功！按任意键继续");
			// 检查文件是否为空
			fseek(fp, 0, SEEK_END);  // 将文件指针移动到文件末尾
			long fileSize = ftell(fp);  // 获取文件大小
			if (fileSize != 0) {
				fprintf(fp,"\n");
			}
			rewind(fp);  // 将文件指针重新移动到文件开头
			fprintf(fp, "%s %s %s %s", userName, passWorld,name1,phone1);
			fclose(fp); // 关闭文件
			getchar();
			break;
		}
	}
}

//void sign_in_user() // 租客注册
//{
//	FILE* fp;
//	int flag = 0;
//	char userName[10];
//	char passWorld[10];
//	char userName1[10];
//	char passWorld1[10];
//	while (1)
//	{
//		printf("\t注册(用户名密码最多9位)\n");
//		printf("\t用户名:");
//		scanf("%s", userName);
//
//		if ((fp = fopen("enter.txt", "rt")) == NULL)
//		{
//			printf("无法打开文件 enter.txt\n");
//			return;
//		}
//
//		while (fscanf(fp, "%s %s", userName1, passWorld1) == 2)
//		{
//			if (!strcmp(userName, userName1))
//			{
//				printf("\t用户名重复\n");
//				flag = 1;
//				break;
//			}
//		}
//
//
//
//		if (flag == 1)
//		{
//			printf("\t");
//			printf("1.换个名字 2.返回菜单\n");
//			printf("\t");
//			int judge;
//			scanf("%d", &judge);
//
//			switch (judge)
//			{
//			case 1:
//				flag = 0;
//				continue;
//				break;
//			case 2:
//				system("cls");
//				enter();
//				return;
//			}
//		}
//		else
//		{
//			printf("\t密码:");
//			scanf("%s", passWorld);
//			getchar();
//			if ((fp = fopen("enter.txt", "at")) == NULL)
//			{
//				printf("无法打开文件 enter.txt\n");
//				return;
//			}
//			printf("\t注册成功！按任意键继续");
//			getchar();
//			fprintf(fp, "%s %s\n", userName, passWorld);
//			fclose(fp); // 关闭文件
//			break;
//		}
//	}
//}
void display_info(FILE** fp, int* n,AC ac[1000]) {
	*fp = fopen("enter.txt", "rt");
	if (*fp == NULL) {
		printf("\t\033[36m打开文件失败 如有备份请尝试恢复！\n");
		Sleep(2000);
		exit(1);
	}

	while (fscanf(*fp, "%s %s %s %s", ac[*n].userName1, ac[*n].passWorld1, ac[*n].name, ac[*n].phone) == 4) {
		(*n)++;
	}

	fclose(*fp);

	if (*n > 0) {
		// 显示用户列表
		printf("\033[36m\t%-8s\t\t%-8s\t\t%-8s\t\t%-8s\n", "用户名", "密码", "姓名", "电话");
		for (int i = 0; i < *n; i++) {
			printf("\t%-8s\t%-8s\t%-8s\t\t%-8s\n", ac[i].userName1, ac[i].passWorld1, ac[i].name, ac[i].phone);
		}
	}
}

int Delete() {//删除
	AC ac[1000];
	FILE* fp = fopen("enter.txt", "rt");
	int n = 0;
	display_info(fp, &n,ac);

	if (n > 0) {
		printf("\t输入你要删除的用户名\n");
		printf("\t用户名: ");
		printf("\033[37m");
		char ch[20];
		scanf("%s", ch);

		// 查找要删除的用户名并删除
		int i;
		for (i = 0; i < n; i++) {
			if (strcmp(ch, ac[i].userName1) == 0) {
				break;
			}
		}
		if (i < n) {
			for (int j = i; j < n - 1; j++) {
				strcpy(ac[j].userName1, ac[j + 1].userName1);
				strcpy(ac[j].passWorld1, ac[j + 1].passWorld1);
				strcpy(ac[j].name, ac[j + 1].name);
				strcpy(ac[j].phone, ac[j + 1].phone);
			}
			n--;

			// 将更新后的用户信息写回文件
			fp = fopen("enter.txt", "wt");
			if (fp == NULL) {
				printf("\t打开文件失败\n");
				exit(1);
			}
			for (int k = 0; k < n; k++) {
				fprintf(fp, "%s %s %s %s\n", ac[k].userName1, ac[k].passWorld1,ac[k].name,ac[k].phone);
			}
			fclose(fp);
			printf("\t\033[31m删除成功！按任意键继续\n");
			getchar();
			getchar();
		}
		else {
			printf("\t\033[31m未找到要删除的用户名,按任意键继续\n");
			getchar(); // 读取上一个 scanf() 中剩余的换行符
			getchar(); // 等待用户按下任意键继续
		}
	}
	else {
		printf("\t\033[31m账号信息为空，按任意键继续\n");
		getchar();

	}
}
void modify_reset()//管理员重置密码
{
	FILE* fp = fopen("enter.txt", "rt");
	AC ac[1000];
	int n = 0;
	display_info(fp, &n, ac);
	char flag[5];
	if (n > 0)
	{
label_2:
		printf("\t输入你要重置密码的用户名\n");
		printf("\033[37m\t");
		char id[20];
		scanf("%s", id);
		getchar();

		int i;
		for (i = 0; i < n; i++) {
			if (strcmp(id, ac[i].userName1) == 0) {
				break;
			}
		}
		if (i < n)
		{
			printf("\t是否重置'%s'的密码?(yes/no)\n\t", id);
			scanf("%s", &flag);
			getchar();
			if (strcmp(flag, "yes") == 0)
			{
				strcpy(ac[i].passWorld1, "888888");
				// 将更新后的用户信息写回文件
				fp = fopen("enter.txt", "wt");
				if (fp == NULL) {
					printf("\t打开文件失败\n");
					exit(1);
				}
				for (int k = 0; k < n; k++) {
					fprintf(fp, "%s %s %s %s\n", ac[k].userName1, ac[k].passWorld1,ac[k].name,ac[k].phone);
				}
				fclose(fp);
				printf("\t已将%s的密码重置为\"888888\",按任意键继续");
				getchar();
			}
			else
			{
				printf("\t1.重置其他用户密码\n\t2.返回管理员菜单");
				int j_modify;
				scanf("%d", &j_modify);
				switch (j_modify)
				{
				case 1: {
					goto label_2;
					break;
				}
				case 2: {
					return;
				}
				}
			}
		}
		else {
			printf("\t\033[31m未找到要删除的用户名,按任意键继续\n");
			getchar();
		}
	}
}

void enter_user()
{
	FILE* fp;
	AC ac[100];
	int n = 0;
	fp = fopen("enter.txt", "rt");
	if (fp == NULL) {
		printf("\t数据丢失，请联系管理员 按任意键继续\n");
		getchar();
		exit(1);
	}
	while (fscanf(fp, "%s %s", ac[n].userName1, ac[n].passWorld1) == 2) {
		n++;
	}
	fclose(fp);
label_3:
	printf("\t\033[36m请输入用户名\n");
	printf("\033[37m\t");
	char ch[20];
	scanf("%s", ch);
	// 查找用户名
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(ch, ac[i].userName1) == 0) {
			break;
		}
	}
	if (i < n)
	{
	label_4:
		printf("\t\033[36m请输入密码:\n");
		printf("\t\033[37m");
		scanf("%s", ch);
		if (strcmp(ch, ac[i].passWorld1) == 0)
		{
			return;
		}
		else
		{
			printf("\t密码错误！\n");
			printf("\t1.再试一次\t2.返回\n");
			printf("\t");
			int judge;
			scanf("%d", &judge);
			fflush(stdin);
			switch (judge)
			{
			case 1: {
				goto label_4;
				break;
			}
			case 2: {
				system("cls");
				enter();
				break;
			}
			}
		}
	}
	else
	{
		printf("\t\033[36m用户不存在\n");
		printf("\t按任意键继续");
		printf("\t\033[37m");
		getchar();
		getchar();
		goto label_3;
	}
}

void loadAccount(AC acc[], int* count, FILE* fp) {
	*count = 0;
	// 检查文件是否为空
	fseek(fp, 0, SEEK_END);  // 将文件指针移动到文件末尾
	long fileSize = ftell(fp);  // 获取文件大小
	if (fileSize == 0) {
		printf("文件为空，按任意键继续");
		getchar();
		return;  // 文件为空，直接返回
	}
	rewind(fp);  // 将文件指针重新移动到文件开头

	while (!feof(fp) && *count < MAX_NUM) {
		fscanf(fp, "%s", acc[*count].userName1);
		fscanf(fp, "%s", acc[*count].passWorld1);
		fscanf(fp, "%s", acc[*count].name);
		fscanf(fp, "%s", acc[*count].phone);
		(*count)++;

	}
}
void saveAccount(AC acc[], int count, FILE* fp)
{
	int i;
	for (i = 0; i < count-1; i++) {
		fprintf(fp, "%s ", acc[i].userName1);
		fprintf(fp, "%s ", acc[i].passWorld1 );
		fprintf(fp, "%s ", acc[i].name);
		fprintf(fp, "%s\n", acc[i].phone);
	}
	fprintf(fp, "%s ", acc[i].userName1);
	fprintf(fp, "%s ", acc[i].passWorld1);
	fprintf(fp, "%s ", acc[i].name);
	fprintf(fp, "%s", acc[i].phone);
}
void code()
{
	FILE* f = fopen("code.txt", "r");
	if (f == NULL)
	{
		printf("\t\033[031m权限码不存在！自动尝试恢复！");
		Sleep(1000);
		exit(0);
	}
	printf("\t\033[36m请输入权限码:");
	printf("\033[37m");
	char code[10];
	char code1[10];
	fscanf(f, "%s", code1);
	while(1)
	{
		scanf("%s", code);
		if (!strcmp(code, code1))
		{
			printf("\t\033[31m权限验证成功!\n");
			Sleep(500);
			return;
		}
		else
		{
			printf("\t\033[31m权限码错误!\n");
			printf("\t\033[36m1.再试一次\t2.返回菜单\n");
			printf("\t\033[37m");
			int judge;
			scanf("%d", &judge);
			switch (judge)
			{
			case 1: {
				printf("\t\033[36m请输入权限码:");
				break;
			}
			case 2: {
				enter();
			}
			default:
				printf("\t\033[36m无效指令，按任意键继续");
				printf("\033[37m");
				getchar();
				return;
			}
		}
	}	
}