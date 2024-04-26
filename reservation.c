#include "reservation.h"

int houseCount_reserve = 0;
int agencyCount_reserve = 0;
void interface_reservation(struct Reservation* head, struct Agency agencys[MAX_NUM], struct House houses[MAX_NUM])
{//信息管理子界面
    FILE* file = fopen("reservation_info.txt", "a+");
    char filename[] = "reservation_info.txt";
    if (file == NULL) {
        printf("reservation_info.txt不存在，正在创建新文件...\n");
        file = fopen("reservation_info.txt", "w");
        if (file != NULL) {
            printf("新文件 reservation_info.txt 创建成功！\n");
            fclose(file);
        }
        else {
            printf("无法创建新文件 reservation_info.txt\n");
            Sleep(2000);
            exit(0);
        }
    }
    head = loadListFromFile(head, file);
    char command[20];

    while (1) {
        printf("\t\033[31m=================================\n");
        printf("\t|\t    请输入指令:\t\t|\n");
        printf("\t=================================\n");
        printf("\t\033[36m1.查询所有预约信息\n\t---------------------------------\n");
        printf("\t\033[36m2.查询指定预约信息\n\t---------------------------------\n");
        printf("\t3.录入\n\t---------------------------------\n");
        printf("\t4.保存\n\t---------------------------------\n");
        printf("\t5.修改\n\t---------------------------------\n");
        printf("\t6.返回\n\t---------------------------------\n");
        printf("\033[37m\t");
        scanf("%s", command);
        if (strcmp(command, "1") == 0)
        {
            printList(head);
        }
        else if (strcmp(command, "2") == 0) {
            printf("\t\033[31m输入要查找的房屋编号: ");
            int roomHouse;
            printf("\033[37m");
            scanf("%d", &roomHouse);
            searchByRoomHouse(head, roomHouse);
        }
        else if (strcmp(command, "3") == 0) {
            head = addReserve(head, agencys, houses);
            if (head == NULL)
            {
                continue;
            }
        }
        else if (strcmp(command, "4") == 0) {
            saveListToFile(head, "reservation_info.txt");
            printf("预约信息保存成功.\n");
        }
        else if (strcmp(command, "5") == 0) {
            int roomHouse;
            printf("输入要修改的租房编号: ");
            scanf("%d", &roomHouse);
            modifyReserve(head, roomHouse);
        }
        else if (strcmp(command, "6") == 0)
        {
            freeList(head);
            break;
        }
        else {
            printf("\t\033[31m无效的指令，请重新输入！\n");
        }
    }
}

void interface_reservation_user(struct Reservation* head, const char name[], struct Agency agencys[MAX_NUM], struct House houses[MAX_NUM])
{//信息管理子界面
    FILE* file = fopen("reservation_info.txt", "r");
    char filename[] = "reservation_info.txt";
    head = loadListFromFile(head, file);
    if (file == NULL) {
        printf("reservation_info.txt不存在，正在创建新文件...\n");
        file = fopen("reservation_info.txt", "w");
        if (file != NULL) {
            printf("新文件 reservation_info.txt 创建成功！\n");
            fclose(file);
        }
        else {
            printf("无法创建新文件 reservation_info.txt\n");
            Sleep(2000);
            exit(0);
        }
    }
    char command[20];

    while (1) {
        system("cls");
        printf("\t\033[31m=================================\n");
        printf("\t|\t    请输入指令:\t\t|\n");
        printf("\t=================================\n");
        printf("\t\033[36m1.查询个人预约信息\n\t---------------------------------\n");
        printf("\t\033[36m2.查询指定预约信息\n\t---------------------------------\n");
        printf("\t3.录入\n\t---------------------------------\n");
        printf("\t4.保存\n\t---------------------------------\n");
        printf("\t5.修改\n\t---------------------------------\n");
        printf("\t6.返回\n\t---------------------------------\n");
        printf("\033[37m\t");
        scanf("%s", command);
        if (strcmp(command, "1") == 0)
        {
            system("cls");
            FILE* file = fopen("reservation_info.txt", "r");
            loadListFromFile(head, file);
            printList_user(head, name);
            printf("\t按任意键继续！");
            getchar();
            getchar();
        }
        else if (strcmp(command, "2") == 0) {
            printf("\t\033[31m输入要查找的租房编号: ");
            int roomHouse;
            printf("\033[37m");
            scanf("%d", &roomHouse);
            system("cls");
            searchByRoomHouse(head, roomHouse);
        }
        else if (strcmp(command, "3") == 0) {
            head = addReserve(head, agencys, houses);
            if (head == NULL)
            {
                continue;
            }
        }
        else if (strcmp(command, "4") == 0) {
            saveListToFile(head, "reservation_info.txt");
            printf("预约信息保存成功.\n");
            Sleep(1000);
        }
        else if (strcmp(command, "5") == 0) {
            int roomHouse;
            printf("输入要修改的租房编号: ");
            scanf("%d", &roomHouse);
            modifyReserve(head, roomHouse);
        }
        else if (strcmp(command, "6") == 0)
        {
            freeList(head);
            break;
        }
        else {
            printf("\t\033[31m无效的指令，请重新输入！\n");
        }
    }
}
// 打印整个链表
void printList(struct Reservation* head) {
    struct Reservation* current = head;
    if (current == NULL) {
        printf("文件中无预约信息\n");
        return;
    }
    system("cls");
    printf("\t\033[31m预约信息:\n");
    printf("\033[36m");
    while (current != NULL) {
        printReserve(current);
        current = current->next;
    }
    printf("\n\t按任意键返回！\n");
    getchar();
    getchar();
    system("cls");
}
//租客打印
void printList_user(struct Reservation* head, const char name[]) {
    struct Reservation* current = head;
    if (current == NULL) {
        printf("文件中无预约信息\n");
        return;
    }

    printf("\t预约信息:\n");
    while (current != NULL) {
        printReserve_user(current, name);
        current = current->next;
    }
}

// 展示房间信息
void printReserve(struct Reservation* reserve) {
    printf("\t\033[36m租房编号: %d\n", reserve->roomHouse);
    printf("\t看房时间: %s\n", reserve->date);
    printf("\t租客姓名: %s\n", reserve->TenantName);
    printf("\t中介姓名: %s\n", reserve->IntermediaryName);
    printf("\t看房时间: %s\n", reserve->time);
    printf("\t备注信息: %s\n", reserve->evaluation);
    printf("\n");
}
void printReserve_user(struct Reservation* reserve, char name[]) {
    if (strcmp(name, reserve->TenantName) == 0)
    {
        printf("\t\033[36m租房编号: %d\n", reserve->roomHouse);
        printf("\t看房时间: %s\n", reserve->date);
        printf("\t租客姓名: %s\n", reserve->TenantName);
        printf("\t中介姓名: %s\n", reserve->IntermediaryName);
        printf("\t看房时间: %s\n", reserve->time);
        printf("\t备注信息: %s\n", reserve->evaluation);
        printf("\n");
    }
}
// 将录入信息保存
void saveListToFile(struct Reservation* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件%s.\n", filename);
        return;
    }

    struct Reservation* current = head;
    while (current->next != NULL) {
        fprintf(file, "%d %s %s %s %s %s\n", current->roomHouse, current->date, current->TenantName, current->IntermediaryName, current->time, current->evaluation);
        current = current->next;
    }
    fprintf(file, "%d %s %s %s %s %s", current->roomHouse, current->date, current->TenantName, current->IntermediaryName, current->time, current->evaluation);
    fclose(file);
}
// 从文件中读取信息
struct Reservation* loadListFromFile(struct Reservation* head, FILE* file) {
    struct Reservation temp;
    while (fscanf(file, "%d %s %s %s %s %s", &temp.roomHouse, temp.date, temp.TenantName, temp.IntermediaryName, temp.time, temp.evaluation) != EOF) {
        struct Reservation* newReserve = (struct Reservation*)malloc(sizeof(struct Reservation));
        if (newReserve == NULL) {
            printf("内存分配失败\n");
            fclose(file);
            return NULL;
        }
        *newReserve = temp;
        newReserve->next = head;
        head = newReserve;
    }

    fclose(file);
    return head;
}
void modifyReserve(struct Reservation* head, int roomHouse) {
    struct Reservation* current = head;
    while (current != NULL) {
        if (current->roomHouse == roomHouse) {
            printf("\t请输入新的看房日期: ");
            scanf("%s", current->date);
            printf("\t请输入新的租客姓名: ");
            scanf("%s", current->TenantName);
            printf("\t请输入新的中介姓名: ");
            scanf("%s", current->IntermediaryName);
            printf("\t请输入新的看房时长: ");
            scanf("%s", current->time);
            printf("\t请输入新的备注信息: ");
            scanf("%s", current->evaluation);
            printf("\t预约信息更新成功.\n");
            Sleep(1000);
            return;
        }
        current = current->next;
    }
    printf("\t房间不存在！\n");
    Sleep(1000);
}

// 添加预约信息
struct Reservation* addReserve(struct Reservation* head, struct Agency agencys[MAX_NUM], struct House houses[MAX_NUM]) {
    struct Reservation* newReserve = (struct Reservation*)malloc(sizeof(struct Reservation));
    if (newReserve == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }
    FILE* file = fopen("house_info.txt", "r");
    FILE* file_agency = fopen("Agency_info.txt", "r");
    if (file != NULL) {
        loadHouseInfo(houses, &houseCount_reserve, file);//load房源
        fclose(file);
    }
    else {
        printf("\t\033[31mhouse_info.txt不存在，正在创建新文件...\n");
        file = fopen("house_info.txt", "w");
        if (file != NULL) {
            printf("\t新文件 house_info.txt 创建成功！\n");
            fclose(file);
        }
        else {
            printf("无法创建新文件 house_info.txt\n");
            return;
        }
    }
    if (file_agency != NULL) {
        loadAgencyInfo(agencys, &agencyCount_reserve, file_agency);//load中介
        fclose(file_agency);
    }
    else {
        printf("\t\033[31mAgency_info.txt不存在，正在创建新文件...\n");
        file_agency = fopen("Agency_info.txt", "w");
        if (file_agency != NULL) {
            printf("\t新文件 Agency_info.txt 创建成功！\n");
            fclose(file_agency);
        }
        else {
            printf("无法创建新文件 Agency_info.txt\n");
            return;
        }
    }


    int roomSearch_num = -1;
    printf("\t请输入房屋编号: ");
    scanf("%d", &roomSearch_num);
    //获取对应索引
    int index = -1;
    for (int i = 0; i < houseCount_reserve; i++)
    {
        if (roomSearch_num == houses[i].roomNumber) index = i;
    }
    if (index != -1)
    {
        newReserve->roomHouse = roomSearch_num;
    }
    else
    {
        printf("\t房间号不存在！\n");
        Sleep(1000);
        return NULL;
    }
    //scanf("%d", &newReserve->roomHouse);
    printf("\t请输入看房日期: ");
    scanf("%s", newReserve->date);
    printf("\t请输入租客姓名: ");
    scanf("%s", newReserve->TenantName);
    printf("\t请输入中介姓名: ");
    scanf("%s", newReserve->IntermediaryName);
    printf("\t请输入看房时长: ");
    scanf("%s", newReserve->time);
    printf("\t请输入备注信息: ");
    scanf("%s", newReserve->evaluation);

    int index_a = -1;
    char t[20];
    strcpy(t, newReserve->IntermediaryName);
    for (int j = 0; j < agencyCount_reserve; j++)
    {
        if (strcmp(agencys[j].name, t) == 0) index_a = j;
    }
    if (index_a == -1)
    {
        strcpy(agencys[agencyCount_reserve].name, t);
        agencys[agencyCount_reserve].reservation_cnt++;
        agencyCount_reserve++;
    }
    else
    {
        agencys[index_a].reservation_cnt++;
    }

    file_agency = fopen("Agency_info.txt", "w");
    saveAgencyInfo(agencys, agencyCount_reserve, file_agency);
    fclose(file_agency);

    newReserve->next = head;
    printf("\t添加成功！");
    Sleep(1000);
    return newReserve;
}

// 根据房间号搜索预约信息
void searchByRoomHouse(struct Reservation* head, int roomHouse) {
    if (head != NULL)
    {
        struct Reservation* current = head;
        while (current != NULL) {
            if (current->roomHouse == roomHouse) {
                printf("\t\033[36m预约信息:\n");
                printReserve(current);
            }
            current = current->next;
        }

        printf("\n\t按任意键继续!");
        getchar();
        getchar();
        return;
        Sleep(1000);
    }
    else
    {
        printf("\t\033[31m未找到房屋信息.\n");
        Sleep(1000);
        return;
    }
}
void searchByuserName(struct Reservation* head, const char name[]) {
    struct Reservation* current = head;
    while (current != NULL) {
        if (current->TenantName == name) {
            printf("\t\033[36m预约信息:\n");
            printReserve(current);
            return;
        }
        current = current->next;
    }
    printf("\t未找到房屋信息.\n");
    system(1000);
}
void freeList(struct Reservation* head) {
    struct Reservation* current = head;
    while (current != NULL) {
        struct Reservation* temp = current;
        current = current->next;
        free(temp);
    }
}