#include "datarecovery.h"
#include "house_info.h"
#include "reservation.h"
#include "account.h"
void data_backup(struct House houses[MAX_NUM], struct Reservation reservations[],AC accs[])
{
    int count = 0;
    FILE* fp;
label_6://house_info
    fp = fopen("house_info.txt", "r");
    if (fp != NULL) {
        loadHouseInfo(houses, &count, fp);
        fclose(fp);
    }
    else
    {
        printf("\thouse_info源文件不存在！备份失败按任意键继续");
        return;
    }
    fp = fopen("Recovery/house_info_r.txt", "w");
    if (fp != NULL)
    {
        saveHouseInfo(houses, count, fp);
        fclose(fp);
        printf("house_info备份成功！按任意键继续\n");
    }
    else
    {
        printf("\t正在创建备份...\n");
        fp = fopen("Recovery/house_info_r.txt", "w");
        if (fp != NULL) {
            printf("\t新文件 house_info_r.txt 创建成功！\n");
            fclose(fp);
            Sleep(2000);
            goto label_6;
        }
        else {
            printf("无法创建新文件 house_info_r.txt 按任意键继续\n");
            getchar();
            return;
        }
    }
label_7://reservation
    fp = fopen("reservation_info.txt", "r");
    if (fp != NULL) {
        loadReservationInfo(reservations, &count, fp);
        fclose(fp);
    }
    else
    {
        printf("\t源文件不存在！reservation备份失败 按任意键继续");
        getchar();
        return;
    }
    fp = fopen("Recovery/Reservation_info_r.txt", "w");
    if (fp != NULL)
    {
        saveReservationInfo(reservations, count, fp);
        fclose(fp);
        printf("reservation备份成功！按任意键继续\n");
    }
    else
    {
        printf("\t正在创建备份...\n");
        fp = fopen("Recovery/Reservation_info.txt", "w");
        if (fp != NULL) {
            printf("\t新文件 Reservation_info.txt 创建成功！\n");
            fclose(fp);
            Sleep(2000);
            goto label_7;
        }
        else {
            printf("无法创建新文件 Reservation_info.txt 按任意键继续\n");
            return;
        }
    }
label_8://account
    fp = fopen("enter.txt", "r");
    if (fp != NULL) {
        loadAccount(accs, &count, fp);
        fclose(fp);
    }
    else
    {
        printf("\t源文件不存在！Account备份失败 按任意键继续");
        getchar();
        return;
    }
    fp = fopen("Recovery/enter_r.txt", "w");
    if (fp != NULL)
    {
        saveAccount(accs, count, fp);
        fclose(fp);
        printf("Account备份成功！按任意键继续\n");
        getchar();
        getchar();
    }
    else
    {
        printf("\t正在创建备份...\n");
        fp = fopen("Recovery/enter_r.txt", "w");
        if (fp != NULL) {
            printf("\t新文件 enter_r.txt 创建成功！\n");
            fclose(fp);
            Sleep(2000);
            goto label_8;
        }
        else {
            printf("无法创建新文件 enter_r.txt 按任意键继续\n");
            getchar();
            return;
        }
    }
}

void recovery(struct House houses[MAX_NUM], struct Reservation reservations[],AC accs[])
{
    int count = 0;
    FILE* fp;
label_9:
    fp = fopen("Recovery/house_info_r.txt", "r");
    if (fp != NULL) {
        loadHouseInfo(houses, &count, fp);
        fclose(fp);
    }
    else
    {
        printf("\thouse_info备份文件不存在！恢复失败按任意键继续");
        return;
    }
    fp = fopen("house_info.txt", "w");
    if (fp != NULL)
    {
        saveHouseInfo(houses, count, fp);
        fclose(fp);
        printf("house_info恢复成功！\n");
    }
    else
    {
        printf("\t正在创建恢复...\n");
        fp = fopen("house_info.txt", "w");
        if (fp != NULL) {
            printf("\t新文件 house_info.txt 创建成功！\n");
            fclose(fp);
            Sleep(2000);
            goto label_9;
        }
        else {
            printf("无法创建新文件 house_info.txt 按任意键继续\n");
            getchar();
            return;
        }
    }
label_10://reservation
    fp = fopen("Recovery/Reservation_info_r.txt", "r");
    if (fp != NULL) {
        loadReservationInfo(reservations, &count, fp);
        fclose(fp);
    }
    else
    {
        printf("\t备份不存在！恢复失败按任意键继续");
        return;
    }
    fp = fopen("reservation_info.txt", "w");
    if (fp != NULL)
    {
        saveReservationInfo(reservations, count, fp);
        fclose(fp);
        printf("reservation_info恢复成功!\n");
    }
    else
    {
        printf("\t正在恢复...\n");
        fp = fopen("reservation_info.txt", "w");
        if (fp != NULL) {
            printf("\treservation_info.txt 创建成功！\n");
            fclose(fp);
            getchar();
            goto label_10;
        }
        else {
            printf("无法创建新文件 reservation_info.txt 按任意键继续\n");
            getchar();
            return;
        }
    }
label_11:
    fp = fopen("Recovery/enter_r.txt", "r");
    if (fp != NULL) {
        loadAccount(accs, &count, fp);
        fclose(fp);
    }
    else
    {
        printf("\t备份文件不存在！恢复失败 按任意键继续");
        getchar();
        return;
    }
    fp = fopen("enter.txt", "w");
    if (fp != NULL)
    {
        saveAccount(accs, count, fp);
        fclose(fp);
        printf("Account恢复成功！按任意键继续\n");
        getchar();
        getchar();
    }
    else
    {
        printf("\t正在恢复...\n");
        fp = fopen("enter.txt", "w");
        if (fp != NULL) {
            printf("\t新文件 enter.txt 创建成功！\n");
            fclose(fp);
            Sleep(2000);
            goto label_11;
        }
        else {
            printf("无法创建新文件 enter.txt 按任意键继续\n");
            getchar();
            return;
        }
    }
}