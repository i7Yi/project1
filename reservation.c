#include "reservation.h"

int reservationCount = 0;
void interface_reservation(struct Reservation reservations[MAX_NUM])
{//信息管理子界面
    FILE* file = fopen("reservation_info.txt", "r");

    if (file != NULL) {
        loadReservationInfo(reservations, &reservationCount, file);
        fclose(file);
    }
    else {
        printf("无法打开文件 reservation_info.txt，正在创建新文件...\n");
        file = fopen("reservation_info.txt", "w");
        if (file != NULL) {
            printf("新文件 reservation_info.txt 创建成功！\n");
            fclose(file);
        }
        else {
            printf("无法创建新文件 reservation_info.txt\n");
            return 1;
        }
    }

    char command[20];

    while (1) {
        printf("\t\033[31m=================================\n");
        printf("\t|\t    请输入指令:\t\t|\n");
        printf("\t=================================\n");
        printf("\t\033[36m查询\n\t---------------------------------\n");
        printf("\t录入\n\t---------------------------------\n");
        printf("\t保存\n\t---------------------------------\n");
        printf("\t返回\n\t---------------------------------\n");
        printf("\033[37m\t");
        scanf("%s", command);

        if (strcmp(command, "查询") == 0) {
            printf("\t\033[31m请输入要查询的房间号: ");
            int roomNumber;
            printf("\033[37m");
            scanf("%d", &roomNumber);

            int found = 0;
            for (int i = 0; i < reservationCount; i++) {
                if (reservations[i].roomNumber == roomNumber) {
                    found = 1;
                    printf("\t\033[36m该房间已租出\n");
                    displayReservationInfo(reservations[i]);
                    break;
                }
            }

            if (!found) {
                printf("\t\033[36m该房间未租出\n");
            }
        }
        else if (strcmp(command, "录入") == 0) {
            if (reservationCount < MAX_NUM) {
                printf("\t\033[31m请输入房间号: ");
                scanf("%d", &(reservations[reservationCount].roomNumber));
                printf("\t\033[31m请输入租客ID: ");
                scanf("%s", reservations[reservationCount].tenantID);
                printf("\t\033[31m请输入预约时间（年 月 日 时）: ");
                scanf("%d %d %d %d", &(reservations[reservationCount].appointmentTime.year),
                    &(reservations[reservationCount].appointmentTime.month),
                    &(reservations[reservationCount].appointmentTime.day),
                    &(reservations[reservationCount].appointmentTime.hour));
                printf("\t\033[31m预约信息已添加！\n");
                reservationCount++;
            }
            else {
                printf("\t\033[31m已达到预约数量上限，无法添加更多预约信息！\n");
            }
        }
        else if (strcmp(command, "保存") == 0) {
            file = fopen("reservation_info.txt", "w");

            if (file != NULL) {
                saveReservationInfo(reservations, reservationCount, file);
                fclose(file);
                printf("\t\033[31m预约信息已保存！\n");
            }
            else {
                printf("\t\033[31m无法打开文件 reservation_info.txt\n");
            }

            //调试
            for (int i = 0; i < reservationCount; i++)
            {
                displayReservationInfo(reservations[i]);
            }

        }
        else if (strcmp(command, "返回") == 0) {
            break;
        }
        else {
            printf("\t\033[31m无效的指令，请重新输入！\n");
        }
    }
}
// 展示房间信息
void displayReservationInfo(struct Reservation reservation) {
    printf("\t\033[36m房间号: %d\n", reservation.roomNumber);
    printf("\t租客ID: %s\n", reservation.tenantID);
    printf("\t预约时间: %d年%d月%d日 %d时\n", reservation.appointmentTime.year, reservation.appointmentTime.month,
        reservation.appointmentTime.day, reservation.appointmentTime.hour);
    printf("\033[37m");
}

// 将录入信息保存
void saveReservationInfo(struct Reservation reservations[], int count, FILE* file) {
    int i;
    for (i = 0; i < count-1; i++) {
        fprintf(file, "%d\n", reservations[i].roomNumber);
        fprintf(file, "%s\n", reservations[i].tenantID);
        fprintf(file, "%d %d %d %d\n", reservations[i].appointmentTime.year, reservations[i].appointmentTime.month,reservations[i].appointmentTime.day, reservations[i].appointmentTime.hour);
    }
    fprintf(file, "%d\n", reservations[i].roomNumber);
    fprintf(file, "%s\n", reservations[i].tenantID);
    fprintf(file, "%d %d %d %d", reservations[i].appointmentTime.year, reservations[i].appointmentTime.month, reservations[i].appointmentTime.day, reservations[i].appointmentTime.hour);
}

// 从文件中读取信息，存入结构体数组
void loadReservationInfo(struct Reservation reservations[], int* count, FILE* file) {
    *count = 0;
    while (!feof(file) && *count < MAX_NUM) {
        fscanf(file, "%d", &(reservations[*count].roomNumber));
        fscanf(file, "%s", reservations[*count].tenantID);
        fscanf(file, "%d %d %d %d", &(reservations[*count].appointmentTime.year),
            &(reservations[*count].appointmentTime.month),
            &(reservations[*count].appointmentTime.day),
            &(reservations[*count].appointmentTime.hour));

        (*count)++;
    }
}