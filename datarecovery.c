#include "datarecovery.h"
void data_backup(struct House houses[MAX_NUM], struct Reservation* head,AC accs[])
{
    int count = 0;
    FILE* fp;
    //house_info
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
        printf("\t\033[36mhouse_info备份成功！\n");
    }
    else
    {
        printf("\t\033[31mError!系统将在3秒内终止！\n");
        Sleep(3000);
        exit(0);
    }
    //reservation
    fp = fopen("reservation_info.txt", "r");
    if (fp != NULL) {
        head = loadListFromFile(head, fp);
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
        saveListToFile(head, "Recovery/Reservation_info_r.txt");
        fclose(fp);
        printf("\t\033[36mreservation备份成功！\n");
    }
    else
    {
        printf("\t\033[31mError!系统将在3秒内终止！\n");
        Sleep(3000);
        exit(0);
    }
    //account
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
        printf("\t\033[36mAccount备份成功！\n");
    }
    else
    {
        printf("\t\033[31mError!系统将在3秒内终止！\n");
        Sleep(3000);
        exit(0);
    }
    //code
    char code1[20];
    fp = fopen("code.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%s", code1);
        fclose(fp);
    }
    else
    {
        printf("\t源文件不存在！Code备份失败 按任意键继续");
        getchar();
        return;
    }
    fp = fopen("Recovery/code_r.txt", "w");
    if (fp != NULL)
    {
        fprintf(fp, "%s", code1);
        fclose(fp);
        printf("\t\033[36mCode备份成功！按任意键继续\n");
        getchar();
        getchar();
    }
    else
    {
        printf("\t\033[31mError!系统将在3秒内终止！\n");
        Sleep(3000);
        exit(0);
    }
}

void recovery(struct House houses[MAX_NUM], struct Reservation **head,AC accs[])
{
    int count = 0;
    FILE* fp;
    //house_info
    fp = fopen("Recovery/house_info_r.txt", "r");
    if (fp != NULL) {
        loadHouseInfo(houses, &count, fp);
        fclose(fp);
    }
    else
    {
        printf("\t\033[31mhouse_info备份文件不存在！恢复失败按任意键继续");
        return;
    }
    fp = fopen("house_info.txt", "w");
    if (fp != NULL)
    {
        saveHouseInfo(houses, count, fp);
        fclose(fp);
        printf("\033[36mhouse_info恢复成功！\n");
    }
    else
    {
        printf("\t\033[31mError!系统将在3秒内终止！\n");
        Sleep(3000);
        exit(0);
    }
    //reservation
    fp = fopen("Recovery/Reservation_info_r.txt", "r");
    if (fp != NULL) {
        head = loadListFromFile(head, fp);
        fclose(fp);
    }
    else
    {
        printf("\t源文件不存在！reservation恢复失败 按任意键继续");
        getchar();
        return;
    }
    fp = fopen("reservation_info.txt", "w");
    if (fp != NULL)
    {
        saveListToFile(head, "reservation_info.txt");
        fclose(fp);
        printf("\t\033[36mreservation恢复成功！\n");
    }
    else
    {
        printf("\t\033[31mError!系统将在3秒内终止！\n");
        Sleep(3000);
        exit(0);
    }
    //Account
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
        printf("\033[36mAccount恢复成功！\n");
    }
    else
    {
        printf("\t\033[31mError!系统将在3秒内终止！\n");
        Sleep(3000);
        exit(0);
    }
    //Code
    char code1[20];
    fp = fopen("Recovery/code_r.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%s", code1);
        fclose(fp);
    }
    else
    {
        printf("\t源文件不存在！Code恢复失败 按任意键继续");
        getchar();
        return;
    }
    fp = fopen("code.txt", "w");
    if (fp != NULL)
    {
        fprintf(fp, "%s", code1);
        fclose(fp);
        printf("\t\033[36mCode恢复成功！按任意键继续\n");
        getchar();
        getchar();
    }
    else
    {
        printf("\t\033[31mError!系统将在3秒内终止！\n");
        printf("\033[37m");
        Sleep(3000);
        exit(0);
    }
}
