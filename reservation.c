#include "reservation.h"

void interface_reservation(struct Reservation *head)
{//信息管理子界面
    FILE* file = fopen("reservation_info.txt", "r");
    char filename[] = "reservation_info.txt";
    head = loadListFromFile(head,file);
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
            printf("\t\033[31m输入要查找的租房编号: ");
            int roomHouse;
            printf("\033[37m");
            scanf("%d", &roomHouse);
            searchByRoomHouse(head, roomHouse);
        }
        else if (strcmp(command, "3") == 0) {
            head = addReserve(head);
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

    printf("预约信息:\n");
    while (current != NULL) {
        printReserve(current);
        current = current->next;
    }
}

// 展示房间信息
void printReserve(struct Reservation* reserve) {
    printf("租房编号: %d\n", reserve->roomHouse);
    printf("看房时间: %s\n", reserve->date);
    printf("租客姓名: %s\n", reserve->TenantName);
    printf("中介姓名: %s\n", reserve->IntermediaryName);
    printf("看房时间: %s\n", reserve->time);
    printf("租客反馈: %s\n", reserve->evaluation);
    printf("\n");
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
struct Reservation* loadListFromFile(struct Reservation *head,FILE *file) {
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
            printf("请输入新的看房日期: ");
            scanf("%s", current->date);
            printf("请输入新的租客姓名: ");
            scanf("%s", current->TenantName);
            printf("请输入新的中介姓名: ");
            scanf("%s", current->IntermediaryName);
            printf("请输入新的看房时长: ");
            scanf("%s", current->time);
            printf("请输入新的看房反馈: ");
            scanf("%s", current->evaluation);
            printf("预约信息更新成功.\n");
            return;
        }
        current = current->next;
    }
    printf("\t房间不存在！\n");
}

// 添加预约信息
struct Reservation* addReserve(struct Reservation* head) {
    struct Reservation* newReserve = (struct Reservation*)malloc(sizeof(struct Reservation));
    if (newReserve == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    printf("请输入房屋编号: ");
    scanf("%d", &newReserve->roomHouse);
    printf("请输入看房日期: ");
    scanf("%s", newReserve->date);
    printf("请输入租客姓名: ");
    scanf("%s", newReserve->TenantName);
    printf("请输入中介姓名: ");
    scanf("%s", newReserve->IntermediaryName);
    printf("请输入看房时长: ");
    scanf("%s", newReserve->time);
    printf("请输入看房反馈: ");
    scanf("%s", newReserve->evaluation);

    newReserve->next = head;
    return newReserve;
}

// 根据房间号搜索预约信息
void searchByRoomHouse(struct Reservation* head, int roomHouse) {
    struct Reservation* current = head;
    while (current != NULL) {
        if (current->roomHouse == roomHouse) {
            printf("预约信息:\n");
            printReserve(current);
            return;
        }
        current = current->next;
    }
    printf("未找到房屋信息.\n");
}
void freeList(struct Reservation* head) {
    struct Reservation* current = head;
    while (current != NULL) {
        struct Reservation* temp = current;
        current = current->next;
        free(temp);
    }
}