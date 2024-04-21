#include "rent_info.h"

void interface_rent(struct RentalInformation* head)
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
            head = addRental(head);
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
    printf("租房编号: %d\n", rental->roomHouse);
    printf("租客姓名: %s\n", rental->TenantName);
    printf("中介姓名: %s\n", rental->IntermediaryName);
    printf("合同签订日期·: %s\n", rental->ContractDate);
    printf("出租开始日期: %s\n", rental->Rentaldate);
    printf("预计出租时长: %s\n", rental->EstimatedRentalDuration);
    printf("\n");
}

// 打印整个链表
void printList2(struct RentalInformation* head) {
    struct RentalInformation* current = head;
    if (current == NULL) {
        printf("文件中无租房信息\n");
        return;
    }

    printf("租房信息:\n");
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
    while (current != NULL) {
        fprintf(file, "%d %s %s %s %s %s\n", current->roomHouse, current->TenantName, current->IntermediaryName, current->ContractDate, current->Rentaldate, current->EstimatedRentalDuration);
        current = current->next;
    }

    fclose(file);
}

// 添加租房信息
struct RentalInformation* addRental(struct RentalInformation* head) {
    struct RentalInformation* newRental = (struct RentalInformation*)malloc(sizeof(struct RentalInformation));
    if (newRental == NULL) {
        printf("保存信息失败。\n");
        return head;
    }

    printf("请输入房屋编号: ");
    scanf("%d", &newRental->roomHouse);
    printf("请输入租客姓名: ");
    scanf("%s", newRental->TenantName);
    printf("请输入中介姓名: ");
    scanf("%s", newRental->IntermediaryName);
    printf("请输入合同签订日期·: ");
    scanf("%s", newRental->ContractDate);
    printf("请输入租房开始时间: ");
    scanf("%s", newRental->Rentaldate);
    printf("请输入预计租房时间: ");
    scanf("%s", newRental->EstimatedRentalDuration);

    newRental->next = head;
    return newRental;
}

// 修改租房信息
void modifyRental(struct RentalInformation* head, int roomHouse) {
    struct RentalInformation* current = head;
    while (current != NULL) {
        if (current->roomHouse == roomHouse) {
            printf("请输入新的租客姓名: ");
            scanf("%s", current->TenantName);
            printf("请输入新的中介姓名: ");
            scanf("%s", current->IntermediaryName);
            printf("请输入新的合同签订日期: ");
            scanf("%s", current->ContractDate);
            printf("请输入新的租房开始日期: ");
            scanf("%s", current->Rentaldate);
            printf("请输入新的预计租房时间: ");
            scanf("%s", current->EstimatedRentalDuration);
            printf("租房信息更新成功.\n");
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
            printf("租房信息:\n");
            printRental(current);
            return;
        }
        current = current->next;
    }
    printf("未找到房屋信息.\n");
}
void freeList2(struct RentalInformation* head) {
    struct RentalInformation* current = head;
    while (current != NULL) {
        struct RentalInformation* temp = current;
        current = current->next;
        free(temp);
    }
}
