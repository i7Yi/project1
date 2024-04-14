#include "common.h"
#include "account.h"
#include "house_info.h"

int main()
{
	label_0:
	printf("\t\033[31m===========================================\n");
	printf("\t|\t   欢迎使用租房管理系统!       \t|\n");
	printf("\t===========================================\n");
	printf("\t\033[36m1.登录    2.注册\n");
	int choice;
	printf("\t\033[37m");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		enter();
		goto label_0;
		break;
	case 2:
		sign_in();
		goto label_0;
		break;
	default:
		printf("\t无效指令!按任意键继续");
		getchar();
		getchar();
		goto label_0;
	}
}









