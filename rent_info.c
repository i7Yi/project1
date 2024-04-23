#include "rent_info.h"
#include "house_info.h"
#include "agency_info.h"

int houseCount_rent = 0;
int agencyCount_rent = 0;
void interface_rent(struct RentalInformation* head, struct House houses_rent[MAX_NUM], struct Agency agencys_rent[MAX_NUM])
{//租房子界面
    FILE* file = fopen("rent_info.txt", "a+");
    char filename[] = "rent_info.txt";
    if (file == NULL) {
        printf("rent_info.txt不存在，正在创建新文件...\n");
        file = fopen("rent_info.txt", "w");
        if (file != NULL) {
            printf("新文件 rent_info.txt 创建成功！\n");
            fclose(file);
        }
        else {
            printf("无法创建新文件 rent_info.txt\n");
            Sleep(2000);
            exit(0);
        }
    }
    head = loadListFromFile2(head, file);
    char command[20];

    while (1) {
        printf("\t\033[31m=================================\n");
        printf("\t|\t    请输入指令:\t\t|\n");
        printf("\t=================================\n");
        printf("\t\033[36m1.查询所有租房信息\n\t---------------------------------\n");
        printf("\t\033[36m2.查询指定租房信息\n\t---------------------------------\n");
        printf("\t3.录入\n\t---------------------------------\n");
        printf("\t4.保存\n\t---------------------------------\n");
        printf("\t5.修改\n\t---------------------------------\n");
        printf("\t6.返回\n\t---------------------------------\n");
        printf("\033[37m\t");
        scanf("%s", command);
        if (strcmp(command, "1") == 0)
        {
            printList2(head);
        }
        else if (strcmp(command, "2") == 0) {
            printf("\t\033[31m输入要查找的租房编号: ");
            int roomHouse;
            printf("\033[37m");
            scanf("%d", &roomHouse);
            searchByRoomHouse2(head, roomHouse);
        }
        else if (strcmp(command, "3") == 0) {
            system("cls");
            head = addRental(head, houses_rent, agencys_rent);
        }
        else if (strcmp(command, "4") == 0) {
            saveListToFile2(head, "rent_info.txt");
            printf("租房信息保存成功.\n");
        }
        else if (strcmp(command, "5") == 0) {
            int roomHouse;
            printf("输入要修改的租房编号: ");
            scanf("%d", &roomHouse);
            modifyRental(head, roomHouse);
        }
        else if (strcmp(command, "6") == 0)
        {
            freeList2(head);
            break;
        }
        else {
            printf("\t\033[31m无效的指令，请重新输入！\n");
        }
    }
}
// 打印单个预约信息
void printRental(struct RentalInformation* rental) {
    printf("\t\033[36m房屋编号: %d\n", rental->roomHouse);
    printf("\t租客姓名: %s\n", rental->TenantName);
    printf("\t中介姓名: %s\n", rental->IntermediaryName);
    printf("\t合同签订日期·: %s\n", rental->ContractDate);
    printf("\t出租开始日期: %s\n", rental->Rentaldate);
    printf("\t预计出租时长: %s\n", rental->EstimatedRentalDuration);
    printf("\033[37m\n");
}

// 打印整个链表
void printList2(struct RentalInformation* head) {
    struct RentalInformation* current = head;
    printf("\033[36m");
    if (current == NULL) {
        printf("\t文件中无租房信息\n");
        return;
    }

    printf("\t租房信息:\n");
    while (current != NULL) {
        printRental(current);
        current = current->next;
    }
}
struct RentalInformation* loadListFromFile2(struct RentalInformation* head, FILE* file) {
    struct RentalInformation temp;
    while (fscanf(file, "%d %19s %19s %19s %19s %19s", &temp.roomHouse, temp.TenantName, temp.IntermediaryName, temp.ContractDate, temp.Rentaldate, temp.EstimatedRentalDuration) == 6) {
        struct RentalInformation* newRental = (struct RentalInformation*)malloc(sizeof(struct RentalInformation));
        if (newRental == NULL) {
            printf("内存分配失败\n");
            fclose(file);
            return NULL;
        }
        *newRental = temp;
        newRental->next = head;
        head = newRental;
    }

    fclose(file);
    return head;
}

// 保存链表到文件
void saveListToFile2(struct RentalInformation* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件%s.\n", filename);
        return;
    }

    struct RentalInformation* current = head;
    while (current->next != NULL) {
        fprintf(file, "%d %s %s %s %s %s\n", current->roomHouse, current->TenantName, current->IntermediaryName, current->ContractDate, current->Rentaldate, current->EstimatedRentalDuration);
        current = current->next;
    }
    fprintf(file, "%d %s %s %s %s %s", current->roomHouse, current->TenantName, current->IntermediaryName, current->ContractDate, current->Rentaldate, current->EstimatedRentalDuration);
    fclose(file);
}

// 添加租房信息
struct RentalInformation* addRental(struct RentalInformation* head, struct House houses[MAX_NUM], struct Agency agencys[MAX_NUM]) {
    struct RentalInformation* newRental = (struct RentalInformation*)malloc(sizeof(struct RentalInformation));
    if (newRental == NULL) {
        printf("保存信息失败。\n");
        return head;
    }
    FILE* file = fopen("house_info.txt", "r");
    FILE* file_agency = fopen("Agency_info.txt", "r");
    if (file != NULL) {
        loadHouseInfo(houses, &houseCount_rent, file);
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
        loadAgencyInfo(agencys, &agencyCount_rent, file_agency);
        fclose(file_agency);
    }
    else {
        printf("\t\033[31mAgency_info.txt不存在，正在创建新文件...\n");
        file = fopen("Agency_info.txt", "w");
        if (file != NULL) {
            printf("\t新文件 Agency_info.txt 创建成功！\n");
            fclose(file);
        }
        else {
            printf("无法创建新文件 Agency_info.txt\n");
            return;
        }
    }
    printf("\t请输入房屋编号: ");
    scanf("%d", &newRental->roomHouse);
    printf("\t请输入租客姓名: ");
    scanf("%s", newRental->TenantName);
    printf("\t请输入中介姓名: ");
    scanf("%s", newRental->IntermediaryName);
    printf("\t请输入合同签订日期·: ");
    scanf("%s", newRental->ContractDate);
    printf("\t请输入租房开始时间: ");
    scanf("%s", newRental->Rentaldate);
    printf("\t请输入预计租房时间: ");
    scanf("%s", newRental->EstimatedRentalDuration);


    int index = -1;
    for (int i = 0; i < houseCount_rent; i++)
    {
        if (newRental->roomHouse == houses[i].roomNumber) index = i;
    }
    int index_a = -1;
    char t[20];
    strcpy(t, newRental->IntermediaryName);
    for (int j = 0; j < agencyCount_rent; j++)
    {
        if (strcmp(agencys[j].name, t) == 0) index_a = j;
    }

    //*******************************

    if (index_a == -1)
    {
        strcpy(agencys[agencyCount_rent].name, t);
        agencys[agencyCount_rent].rent_cnt++;
        agencyCount_rent++;
    }
    else
    {
        agencys[index_a].rent_cnt++;
    }
    if (index != -1)
    {
        houses[index].cnt++;
        houses[index].rent_time += (int)newRental->EstimatedRentalDuration;
    }
    //printf("%d\n", agencyCount_rent);
    file_agency = fopen("Agency_info.txt", "w");
    saveAgencyInfo(agencys, agencyCount_rent, file_agency);
    fclose(file_agency);
    newRental->next = head;
    return newRental;
}


// 修改租房信息
void modifyRental(struct RentalInformation* head, int roomHouse) {
    struct RentalInformation* current = head;
    while (current != NULL) {
        if (current->roomHouse == roomHouse) {
            printf("\t请输入新的租客姓名: ");
            scanf("%s", current->TenantName);
            printf("\t请输入新的中介姓名: ");
            scanf("%s", current->IntermediaryName);
            printf("\t请输入新的合同签订日期: ");
            scanf("%s", current->ContractDate);
            printf("\t请输入新的租房开始日期: ");
            scanf("%s", current->Rentaldate);
            printf("\t请输入新的预计租房时间: ");
            scanf("%s", current->EstimatedRentalDuration);
            printf("\t租房信息更新成功.\n");
            return;
        }
        current = current->next;
    }
    printf("Room house not found.\n");
}

// 根据房间号搜索租房信息
void searchByRoomHouse2(struct RentalInformation* head, int roomHouse) {
    struct RentalInformation* current = head;
    while (current != NULL) {
        if (current->roomHouse == roomHouse) {
            printf("\t\033[36m租房信息:\n");
            printRental(current);
            return;
        }
        current = current->next;
    }
    printf("\t\033[31m未找到房屋信息.\n");
    printf("\033[37m");
}
void freeList2(struct RentalInformation* head) {
    struct RentalInformation* current = head;
    while (current != NULL) {
        struct RentalInformation* temp = current;
        current = current->next;
        free(temp);
    }
}