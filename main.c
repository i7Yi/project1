#include "common.h"
#include "account.h"
#include "house_info.h"

int main()
{
	while (1)
	{
		printf("\t\033[31m===========================================\n");
		printf("\t|\t   欢迎使用租房管理系统!       \t|\n");
		printf("\t===========================================\n");
		printf("\t\033[36m1.登录    2.注册    3.退出系统\n");
		int choice;
		printf("\t\033[37m");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			enter();
			break;
		case 2:
			sign_in();
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("\t无效指令!按任意键继续");
			getchar();
			getchar();
		}
	}
	
}









