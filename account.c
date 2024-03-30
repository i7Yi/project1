#include "account.h"
#include "house_info.h"
void enter()		//登录界面
{
	printf("\t\033[31m=================================\n");
	printf("\t|\t      登录:\t\t|\n");
	printf("\t=================================\n");
	FILE* fp;

	printf("\t\033[36m1.管理员    2.中介    3.租客\n");
	char userName[10];
	char passWorld[10];
	char userName1[10];
	char passWorld1[10];
	int choice;
	printf("\t\033[37m");
	scanf("%d", &choice);
	int flag = 0;
	switch (choice)
	{
	case 1: {        //管理员，注册用户和删除
		char adm[10];
		printf("\t输入权限码\n");
		printf("\t");
		scanf("%s", adm);
		if (strcmp(adm, "12"))   //权限码：12
		{
			printf("\t权限码错误\n");
			printf("\t1.返回菜单\t2.退出\n");
			printf("\t");
			int judge;
			scanf("%d", &judge);
			fflush(stdin);
			switch (judge)
			{
			case 1: {
				system("cls");
				enter();
				break;
			}
			case 2: {
				exit(0);
			}
			}
			enter();
		}
	label_1:
		system("cls");
		printf("\t\033[31m=================================\n");
		printf("\t|\t 管理员登陆成功！:\t|\n");
		printf("\t=================================\n");
		printf("\t\033[36m1.注册\n\t---------------------------------\n");
		printf("\t2.修改\n\t---------------------------------\n");
		printf("\t3.信息管理\n\t---------------------------------\n");
		printf("\t4.退出登录\n\t---------------------------------\n");
		int j;
		printf("\033[37m\t");
		scanf("%d", &j);
		fflush(stdin);
		switch (j)
		{
		case 1: {//注册
			sign_in(userName, passWorld);
			goto label_1;
			break;
		}
		case 2: {//修改
			int flag1;
			do
			{
				if (Delete() == 1)
				{
					flag1 = 0;
					printf("\t是否继续删除：1.是  2.否\n");
					printf("\t");
					scanf("%d", &flag1);
				}
				else
				{
					goto label_1;
				}
				
			} while (flag1 == 1);
			system("cls");
			break;
		case 3: {//信息管理
			struct House houses[MAX_NUM];
			interface_house_info(houses);
		}
		case 4: {//退出登录
			system("cls");
			enter();
			break;
		}
		}
		default: {
			break;
		}
		}
		break;
	}
	case 2: {     //中介登录
		printf("\t登录\n");
		printf("\t用户名:");
		fflush(stdin);
		printf("\t");
		gets(userName);
		printf("\t密码:");
		printf("\t");
		gets(passWorld);
		if ((fp = fopen("enter.txt", "rt")) == NULL)
		{
			exit(0);
		}
		while (!feof(fp))
		{
			fscanf(fp, "%s %s", userName1, passWorld1);
			// encryption(passWorld);//加密
			if (!strcmp(userName, userName1) && !strcmp(passWorld, passWorld1))
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			printf("\t输入用户名密码不匹配或者错误\n");
			enter();
		}
		printf("\t成功\n");
		break;
	}
	case 3: {
		printf("\t登录\n");
		printf("\t用户名:");
		printf("\t");
		gets(userName);
		printf("\t密码:");
		printf("\t");
		gets(passWorld);
	}
	default: {
		printf("\t输入选择不符合格式\n");
		break;
	}
	}
	return;
}

void sign_in(char userName[], char passWorld[]) // 注册
{
	FILE* fp;
	int flag = 0;
	char userName1[10];
	char passWorld1[10];
	fflush(stdin);
	while (1)
	{
		fflush(stdin);
		printf("\t注册(用户名密码最多9位)\n");
		printf("\t用户名:");
		scanf("%s", userName);
		fflush(stdin);

		if ((fp = fopen("enter.txt", "rt")) == NULL)
		{
			printf("无法打开文件 enter.txt\n");
			return;
		}

		while (fscanf(fp, "%s %s", userName1, passWorld1) == 2)
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
			char c;
			scanf("%c",&c);
			if ((fp = fopen("enter.txt", "at")) == NULL)
			{
				printf("无法打开文件 enter.txt\n");
				return;
			}
			printf("\t注册成功！按任意键继续");
			scanf("%c", &c);
			// encryption(passWorld); // 加密
			fprintf(fp, "%s %s\n", userName, passWorld);
			fclose(fp); // 关闭文件
			break;
		}
	}
}

int Delete() {//删除
	FILE* fp;
	int n = 0;
	AC ac[1000];

	fp = fopen("enter.txt", "rt");
	if (fp == NULL) {
		printf("\t打开文件失败\n");
		exit(1);
	}

	// 读取用户信息
	while (fscanf(fp, "%s %s", ac[n].userName1, ac[n].passWorld1) == 2) {
		n++;
	}
	fclose(fp);

	if (n > 0) {
		// 显示用户列表
		printf("\t%-8s\t\t%-8s\n", "用户名", "密码");
		for (int i = 0; i < n; i++) {
			printf("\t%-8s\t%-8s\n", ac[i].userName1, ac[i].passWorld1);
		}

		printf("\t输入你要删除的用户名\n");
		printf("\t用户名: ");
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
			}
			n--;

			// 将更新后的用户信息写回文件
			fp = fopen("enter.txt", "wt");
			if (fp == NULL) {
				printf("\t打开文件失败\n");
				exit(1);
			}
			for (int k = 0; k < n; k++) {
				fprintf(fp, "%s %s\n", ac[k].userName1, ac[k].passWorld1);
			}
			fclose(fp);
			printf("\t删除成功！\n");
			return 1;
		}
		else {
			printf("\t未找到要删除的用户名,按任意键继续\n");
			getchar(); // 读取上一个 scanf() 中剩余的换行符
			getchar(); // 等待用户按下任意键继续
		}
	}
	else {
		printf("\t账号信息为空，按任意键继续\n");
		getchar(); // 读取上一个 scanf() 中剩余的换行符
		getchar(); // 等待用户按下任意键继续
		return 0;
	}
}


