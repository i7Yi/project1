#include "house_info.h"
#include "agency_info.h"

int houseCount = 0;
int agencyCount = 0;
void interface_house_info(struct House houses[MAX_NUM],struct Agency agencys[MAX_NUM])
{
    FILE* file = fopen("house_info.txt", "r");
    FILE* file_rent = fopen("Rent_info.txt", "r");
    FILE* file_agency = fopen("Agency_info.txt", "r");
    for (int i = 0; i < MAX_NUM; i++) houses[i].cnt = 0, houses[i].rent_time = 0;
    for (int i = 0; i < MAX_NUM; i++) agencys[i].rent_cnt = 0, agencys[i].reservation_cnt = 0;
    if (file != NULL) {
        loadHouseInfo(houses, &houseCount, file);
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
            return ;
        }
    }

    char command[20];

    while (1) {
        printf("\t\033[31m=================================\n");
        printf("\t|\t    请输入指令:\t\t|\n");
        printf("\t=================================\n");
        printf("\t\033[36m1.查询\n\t---------------------------------\n");
        printf("\t2.排序\n\t---------------------------------\n");
        printf("\t3.录入\n\t---------------------------------\n");
        printf("\t4.统计\n\t---------------------------------\n");
        printf("\t5.返回\n\t---------------------------------\n");
        printf("\033[37m\t");
        scanf("%s", command);
        getchar();
        if (strcmp(command, "1") == 0) {
            system("cls");
            printf("\t\033[36m当前房源数量:%d\n", houseCount);
            printf("\t请输入要查询的房间号: ");
            printf("\033[37m");
            int number;
            scanf("%d", &number);
            int index = -1;
            for (int i = 0; i < houseCount; i++)
            {
                if (houses[i].roomNumber == number) index = i;
            }
            if (index != -1) displayHouseInfo(houses[index]);
            else printf("\t\033[36m该房间不存在\n");
        }
        else if (strcmp(command, "3") == 0) {//录入
            system("cls");
            while (1)
            {
                printf("\t\033[31m=================================\n");
                printf("\t|\t    请输入指令:\t\t|\n");
                printf("\t=================================\n");
                printf("\t\033[36m1.房源信息录入\n\t---------------------------------\n");
                printf("\t2.租房信息录入\n\t---------------------------------\n");
                printf("\t3.返回\n\t---------------------------------\n");
                printf("\033[37m\t");
                char command_second[20];
                scanf("%s", command_second);
                if (strcmp(command_second, "1") == 0)
                {
                    if (houseCount < MAX_NUM) {
                        modifyHouseInfo(&houses[houseCount]);
                        houseCount++;
                    }
                    else {
                        printf("已达到房屋数量上限，无法添加更多房源信息！\n");
                    }

                    file = fopen("house_info.txt", "w");
                    if (file != NULL) {
                        saveHouseInfo(houses, houseCount, file);
                        printf("房源信息已保存！\n");
                        fclose(file);
                    }
                    else {
                        printf("无法打开文件 House.txt 进行保存！\n");
                    }
                    break;
                }
                else if (strcmp(command_second, "2") == 0)
                {
                    /*录入的过程同时会增加房屋的租房次数和中介的租房次数*******/

                    int number;
                    printf("请输入房间号:\n");
                    scanf("%d", &number);
                    int index = -1;
                    for (int i = 0; i < houseCount; i++)
                    {
                        if (number == houses[i].roomNumber) index = i;
                    }
                    if (index != -1)
                    {
                        printf("请输入中介姓名:");
                        char t[20];
                        scanf("%s", t);
                        int index_a = -1;
                        for (int j = 0; j < agencyCount; j++)
                        {
                            if (strcmp(agencys[j].name, t) == 0) index_a = j;
                        }
                        if (index_a == -1)
                        {
                            strcpy(agencys[agencyCount].name, t);
                            agencys[agencyCount].rent_cnt++;
                        }
                        else
                        {
                            agencys[index_a].rent_cnt++;
                        }
                        agencyCount++;

                        file_agency = fopen("Agency_info.txt", "w");

                        saveAgencyInfo(agencys, agencyCount, file_agency);
                        fclose(file_agency);

                        file_rent = fopen("Rent_info.txt", "w");
                        modifyRentInfo(&houses[index]);
                        saveRentInfo(houses, houseCount, file_rent);
                        fclose(file_rent);
                        printf("租房信息已保存!\n");
                        break;
                    }
                    else
                    {
                        printf("\t无效指令请重新输入！\n");
                    }
                }
            }
        }
        else if (strcmp(command, "2") == 0)
        {
            system("cls");
            while (1)
            {
                printf("\t\033[31m=================================\n");
                printf("\t|\t    请输入指令:\t\t|\n");
                printf("\t=================================\n");
                printf("\t\033[36m1.楼层\n\t---------------------------------\n");
                printf("\t2.装修\n\t---------------------------------\n");
                printf("\t3.价格\n\t---------------------------------\n");
                printf("\t4.面积\n\t---------------------------------\n");
                printf("\t5.返回\n\t---------------------------------\n");
                printf("\033[37m\t");
                char command_second[20];
                scanf("%s", command_second);
                if (strcmp(command_second, "1") == 0)
                {
                    sortByFloor(houses, houseCount);
                    break;
                }
                else if (strcmp(command_second, "2") == 0)
                {
                    sortByDecoration(houses, houseCount);
                    break;
                }
                else if (strcmp(command_second, "3") == 0)
                {
                    sortByPrice(houses, houseCount);
                    break;
                }
                else if (strcmp(command_second, "4") == 0)
                {
                    sortByArea(houses, houseCount);
                    break;
                }
                else if (strcmp(command_second, "5") == 0)
                {
                    break;
                }
                else
                {
                    printf("\t无效指令请重新输入！\n");
                }
            }

            for (int i = 0; i < houseCount; i++)
            {
                displayHouseInfo(houses[i]);
            }
        }
        else if (strcmp(command, "4") == 0)
        {
            char commmand_sta[20];
            while (1)
            {
                printf("\t\033[31m=================================\n");
                printf("\t|\t    请输入指令:\t\t|\n");
                printf("\t=================================\n");
                printf("\t\033[36m1.中介出租率\n\t---------------------------------\n");
                printf("\t2.房屋平均出租时间\n\t---------------------------------\n");
                printf("\t3.返回\n\t---------------------------------\n");
                printf("\033[37m\t");
                char command_sta[20];
                scanf("%s", command_sta);
                if (strcmp(command_sta, "1") == 0)
                {
                    statistic_agency(agencys, agencyCount);
                    break;
                }
                else if (strcmp(command_sta, "2") == 0)
                {
                    statistic_house(houses, houseCount);
                    break;
                }
                else if (strcmp(command_sta, "3") == 0)
                {
                    break;
                }
                else
                {
                    printf("\t无效指令请重新输入！\n");
                    Sleep(300);
                }
            }
        }
        else if (strcmp(command, "5") == 0)
        {
            return;
            break;
        }
        else
        {
            printf("\t无效指令请重新输入！\n");
            Sleep(300);
        }
    }
}
void displayHouseInfo(struct House house) {
    printf("\t\033[36m房间号: %d\n", house.roomNumber);
    printf("\t房子的位置: %s\n", house.location);
    printf("\t楼层: %d\n", house.floor);
    printf("\t朝向: %s\n", house.orientation);
    printf("\t房型: %s\n", house.layout);
    printf("\t装修: %s\n", house.decoration);
    printf("\t价格: %d\n", house.price);
    printf("\t面积: %.2f\n", house.area);
    printf("\t评分: %d\n", house.score);
    printf("\t空闲时间段: %s开始\n", house.time_period);
    printf("\033[37m\n\n");
}


void modifyHouseInfo(struct House* house) {
    printf("\t请输入房间号: ");
    scanf("%d", &(house->roomNumber));
    printf("\t请输入房子的位置: ");
    scanf("%s", house->location);
    printf("\t请输入楼层: ");
    scanf("%d", &(house->floor));
    printf("\t请输入朝向: ");
    scanf("%s", house->orientation);
    printf("\t请输入房型: ");
    scanf("%s", house->layout);
    printf("\t请输入装修: ");
    scanf("%s", house->decoration);
    printf("\t请输入价格: ");
    scanf("%d", &(house->price));
    printf("\t请输入面积: ");
    scanf("%f", &(house->area));
    printf("\t请输入评分: ");
    scanf("%d", &(house->score));
    printf("\t请输入空闲时间段: ");
    scanf("%s", house->time_period);
}


void saveHouseInfo(struct House house[], int count, FILE* file) {
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", house[i].roomNumber);
        fprintf(file, "%s\n", house[i].location);
        fprintf(file, "%d\n", house[i].floor);
        fprintf(file, "%s\n", house[i].orientation);
        fprintf(file, "%s\n", house[i].layout);
        fprintf(file, "%s\n", house[i].decoration);
        fprintf(file, "%d\n", house[i].price);
        fprintf(file, "%.2f\n", house[i].area);
        fprintf(file, "%d\n", house[i].score);
        if (i == count - 1) fprintf(file, "%s", house[i].time_period);
        else fprintf(file, "%s\n", house[i].time_period);
    }
}


void loadHouseInfo(struct House house[], int* count, FILE* file) {
    *count = 0;
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0) {
        return;
    }
    rewind(file);

    while (!feof(file) && *count < MAX_NUM) {
        fscanf(file, "%d", &(house[*count].roomNumber));
        fscanf(file, "%s", house[*count].location);
        fscanf(file, "%d", &(house[*count].floor));
        fscanf(file, "%s", house[*count].orientation);
        fscanf(file, "%s", house[*count].layout);
        fscanf(file, "%s", house[*count].decoration);
        fscanf(file, "%d", &(house[*count].price));
        fscanf(file, "%f", &(house[*count].area));
        fscanf(file, "%d", &(house[*count].score));
        fscanf(file, "%s", house[*count].time_period);
        (*count)++;
    }
}

void sortByFloor(struct House house[], int count) {
    struct House temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (house[j].floor < house[j + 1].floor) {
                temp = house[j];
                house[j] = house[j + 1];
                house[j + 1] = temp;
            }
        }
    }
}

void sortByDecoration(struct House house[], int count) {
    struct House temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(house[j].decoration, house[j + 1].decoration) > 0) {
                temp = house[j];
                house[j] = house[j + 1];
                house[j + 1] = temp;
            }
        }
    }
}

void sortByPrice(struct House house[], int count) {
    struct House temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (house[j].price > house[j + 1].price) {
                temp = house[j];
                house[j] = house[j + 1];
                house[j + 1] = temp;
            }
        }
    }
}

void sortByArea(struct House house[], int count) {
    struct House temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (house[j].area < house[j + 1].area) {
                temp = house[j];
                house[j] = house[j + 1];
                house[j + 1] = temp;
            }
        }
    }
}
void modifyRentInfo(struct House* house)
{
    printf("请输入租房时长(月)\n");
    int time;
    scanf("%d", &time);
    house->rent_time += time;
    house->cnt++;
}
void saveRentInfo(struct House house[], int count, FILE* file)
{
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d\n", house[i].roomNumber);
        int time;
        fprintf(file, "%d\n", house[i].cnt);
        if (i == count - 1) fprintf(file, "%d", house[i].rent_time);
        else fprintf(file, "%d\n", house[i].rent_time);
    }
}
void loadRentInfo(struct House house[], int* count, FILE* file)
{
    *count = 0;
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0) {
        return;
    }
    rewind(file);

    while (!feof(file) && *count < MAX_NUM)
    {
        fscanf(file, "%d", &(house[*count].roomNumber));
        fscanf(file, "%d", &house[*count].cnt);
        fscanf(file, "%d", &house[*count].rent_time);
        (*count)++;
    }
}
void statistic_house(struct House house[], int count)
{
    for (int i = 0; i < count; i++)
    {
        int a = house[i].cnt;
        int b = house[i].rent_time;
        double average = b / (a * 1.0);
        printf("房间号:%d\n", house[i].roomNumber);
        if (a != 0)
        {
            printf("总出租时间:%d\n", house[i].rent_time);
            printf("总出租次数:%d\n", house[i].cnt);
            printf("平均出租时间(月/次):%.1f\n", average);
        }
        else
        {
            printf("无出租次数\n");
        }
    }
}
void saveAgencyInfo(struct Agency agency[], int count, FILE* file)
{
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s\n", agency[i].name);
        fprintf(file, "%d\n", agency[i].reservation_cnt);
        if (i == count - 1) fprintf(file, "%d", agency[i].rent_cnt);
        else fprintf(file, "%d\n", agency[i].rent_cnt);
    }
}
void loadAgencyInfo(struct Agency agency[], int* count, FILE* file)
{
    *count = 0;
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0) {
        return;
    }
    rewind(file);

    while (!feof(file) && *count < MAX_NUM)
    {
        fscanf(file, "%s", agency[*count].name);
        fscanf(file, "%d", &agency[*count].reservation_cnt);
        fscanf(file, "%d", &agency[*count].rent_cnt);
        (*count)++;
    }
}
void statistic_agency(struct Agency agency[], int count)
{
    for (int i = 0; i < count; i++)
    {
        struct Agency t = agency[i];

        if (t.reservation_cnt == 0)
        {
            continue;
        }
        printf("中介的姓名:%s\n", t.name);
        printf("中介的预约次数:%d\n", t.reservation_cnt);
        printf("中介的成功租房次数:%d\n", t.rent_cnt);
        double a = t.rent_cnt / (1.0 * t.reservation_cnt);
        printf("中介的出租率:%.2f\n\n", a);
    }
}