#include "UI.h"
#include "house_info.h"
#include "reservation.h"
#include "datarecovery.h"
#include "account.h"
#include "agency_info.h"
#include "rent_info.h"

struct House houses[MAX_NUM];
struct Agency agencys[MAX_NUM];

void enter()		//登录界面
{
	for (int i = 0; i < MAX_NUM; i++) houses[i].cnt = 0, houses[i].rent_time = 0;
	for (int i = 0; i < MAX_NUM; i++) agencys[i].rent_cnt = 0, agencys[i].reservation_cnt = 0;
	printf("\t\033[31m=================================\n");
	printf("\t|\t      登录:\t\t|\n");
	printf("\t=================================\n");
	printf("\t\033[36m1.管理员    2.中介    3.租客    4.返回主界面\n");
	int choice;
	printf("\t\033[37m");
	scanf("%d", &choice);
	int flag = 0;
	switch (choice)
	{
	case 1: {        //管理员，注册用户和删除
		code();
	label_1:
		system("cls");
		printf("\t\033[31m=================================\n");
		printf("\t|\t 管理员登陆成功！:\t|\n");
		printf("\t=================================\n");
		printf("\t\033[36m1.注册\n\t---------------------------------\n");
		printf("\t2.修改\n\t---------------------------------\n");
		printf("\t3.信息管理\n\t---------------------------------\n");
		printf("\t4.数据备份\n\t---------------------------------\n");
		printf("\t5.退出登录\n\t---------------------------------\n");
		int j;
		printf("\033[37m\t");
		scanf("%d", &j);
		fflush(stdin);
		switch (j)
		{
		case 1: {//注册
			sign_in();
			goto label_1;
			break;
		}
		case 2: {//修改
			system("cls");
			printf("\t\033[31m=================================\n");
			printf("\t|\t 管理员登陆成功！:\t|\n");
			printf("\t=================================\n");
			printf("\t\033[36m1.删除用户\n\t---------------------------------\n");
			printf("\t2.重置用户密码\n\t---------------------------------\n");
			printf("\t3.修改权限码\n\t---------------------------------\n");
			printf("\t4.返回\n\t---------------------------------\n");
			printf("\033[37m\t");
			int j_modify_menu;
			while (1)
			{
				scanf("%d", &j_modify_menu);
				if (j_modify_menu == 1)
				{
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
				}
				else if (j_modify_menu == 2)
				{
					modify_reset();
					goto label_1;
				}
				else if (j_modify_menu == 3)
				{
					int judge_modify_code = 0;
					modify_code(&judge_modify_code);
					if (judge_modify_code == 1)
					{
						goto label_1;
					}
					else
					{
						enter();
					}
				}
				else if (j_modify_menu == 4)
				{
					goto label_1;
				}
				else
				{
					printf("\t\033[31m无效指令！请重新输入:\n");
					printf("\t\033[37m");
				}
			}
		case 3: {//信息管理
			interface_info();
			int j_info;
			while (1)
			{
				scanf("%d", &j_info);
				if (j_info == 1)
				{
					interface_house_info(houses, agencys);
					goto label_1;
					break;
				}
				else if (j_info == 2)
				{
					struct Reservation* head = NULL;
					interface_reservation(head, agencys, houses);
					goto label_1;
					break;
				}
				else if (j_info == 3)
				{
					goto label_1;
					break;
				}
				else
				{
					printf("\t\033[31m无效指令！请重新输入:\n");
					printf("\t\033[37m");
				}
			}
		}
		case 4: {//数据备份
			struct House houses_data[MAX_NUM];
			struct Reservation* head = NULL;
			struct RentalInformation* head2 = NULL;
			AC accs[MAX_NUM];
			system("cls");
			printf("\t\033[31m=================================\n");
			printf("\t|\t 管理员登陆成功！ \t|\n");
			printf("\t=================================\n");
			printf("\t\033[36m1.数据备份\n\t---------------------------------\n");
			printf("\t2.数据恢复\n\t---------------------------------\n");
			printf("\t3.返回\n\t---------------------------------\n");
			printf("\033[37m\t");
			int j_modify_data;
			while (1)
			{
				scanf("%d", &j_modify_data);
				if (j_modify_data == 1)
				{
					data_backup(houses_data, head, accs, head2, agencys);
					break;
				}
				else if (j_modify_data == 2)
				{
					recovery(houses_data, head, accs, head2, agencys);
					break;
				}
				else if (j_modify_data == 3)
				{
					goto label_1;
					break;
				}
				else
				{
					printf("\t\033[31m无效指令！请重新输入:\n");
					printf("\t\033[37m");
				}
			}
		}
		case 5: {//退出登录
			system("cls");
			enter();
			break;
		}
		}
		default: {
			printf("\t无效指令!按任意键继续\n");
			getchar();
			getchar();
			goto label_1;
			break;
		}
		}
		break;
	}
	case 2: {  //中介登录
		code();
		char zj_name[20];
		char uid[20];
		enter_zj(zj_name, uid);
	label_5:
		system("cls");
		printf("\t\033[31m=================================\n");
		printf("\t|\t 中介\"%s\"登陆成功！   | \n", zj_name);
		printf("\t=================================\n");
		printf("\t\033[36m1.信息查询\n\t---------------------------------\n");
		printf("\t2.租房\n\t---------------------------------\n");
		printf("\t3.修改密码\n\t---------------------------------\n");
		printf("\t4.退出登录\n\t---------------------------------\n");
		int j;
		printf("\033[37m\t");
		scanf("%d", &j);
		fflush(stdin);
		switch (j)
		{
		case 1: {//信息查询
			interface_info();
			int j_info;
			scanf("%d", &j_info);
			switch (j_info)
			{
			case 1: {//房源信息
				interface_house_info(houses, agencys);
				goto label_5;
				break;
			}
			case 2: {//预约信息
				struct Reservation* head = NULL;
				interface_reservation(head, agencys, houses);
				goto label_5;
				break;
			}
			case 3: {//返回
				goto label_5;
				break;
			}
			}

		}
		case 2: {//租房
			system("cls");
			struct RentalInformation* head2 = NULL;
			interface_rent(head2, houses, agencys);
			goto label_5;
			break;
		}
		case 3: {//修改密码
			int judge_modify_password = 0;
			modify_password(&judge_modify_password, uid);
			if (judge_modify_password == 1)
			{
				goto label_6;
			}
			else
			{
				enter();
			}
		}
		case 4: {
			system("cls");
			enter();
			break;
		}
		default: {
			printf("\t无效指令!按任意键继续\n");
			getchar();
			getchar();
			goto label_5;
		}
		}
		break;
		break;
	}
	case 3: { //租客
		char zk_name[20];
		char uid[20];
		enter_zk(zk_name, uid);
	label_6:
		system("cls");
		printf("\t\033[31m=================================\n");
		printf("\t|\t 租客\"%s\"登陆成功！ \t|\n", zk_name);
		printf("\t=================================\n");
		printf("\t\033[36m1.信息查询\n\t---------------------------------\n");
		printf("\t2.修改密码\n\t---------------------------------\n");
		printf("\t3.退出登录\n\t---------------------------------\n");
		int j;
		printf("\033[37m\t");
		scanf("%d", &j);
		fflush(stdin);
		switch (j)
		{
		case 1: {//信息查询
			interface_info();
			int j_info;
			scanf("%d", &j_info);
			switch (j_info)
			{
			case 1: {//房源信息
				struct House houses[MAX_NUM];
				struct Agency agencys[MAX_NUM];
				interface_house_info(houses, agencys, houses);
				goto label_6;
				break;
			}
			case 2: {//预约信息
				struct Reservation* head = NULL;
				interface_reservation_user(head, zk_name, agencys, houses);
				goto label_6;
				break;
			}
			case 3: {
				goto label_6;
				break;
			}
			}

		}
		case 2:
		{
			int judge_modify_password = 0;
			modify_password(&judge_modify_password, uid);
			if (judge_modify_password == 1)
			{
				goto label_6;
			}
			else
			{
				enter();
			}
		}
		case 3: {
			system("cls");
			enter();
			break;
		}
		default: {
			printf("\t无效指令!按任意键继续\n");
			getchar();
			getchar();
			goto label_6;
		}
		}
		break;
		break;
	}
	case 4:
		system("cls");
		return;
		break;
	default:
	{
		printf("\t无效操作！按任意键继续");
		getchar();
		getchar();
		system("cls");
		enter();
	}
	}
}

void interface_info()
{
	system("cls");
	printf("\t\033[31m=================================\n");
	printf("\t|\t    登陆成功\t\t|\n");
	printf("\t=================================\n");
	printf("\t\033[36m1.房屋信息\n\t---------------------------------\n");
	printf("\t2.预约信息\n\t---------------------------------\n");
	printf("\t3.返回\n\t---------------------------------\n");
	printf("\033[37m\t");
}