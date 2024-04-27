#include "house_info.h"
#include "agency_info.h"

int judge = 0;
int judge_all = 0;
int houseCount = 0;
int agencyCount = 0;
void interface_house_info(struct House houses[MAX_NUM],struct Agency agencys[MAX_NUM])
{
    FILE* file = fopen("house_info.txt", "r");
    FILE* file_agency = fopen("Agency_info.txt", "r");
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
    if (file_agency != NULL) {
        loadAgencyInfo(agencys, &agencyCount, file_agency);
        fclose(file_agency);
    }
    else {
        printf("生成失败\n");
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
            while (1)
            {
                judge = 0;
                judge_all = 0;
                system("cls");
                printf("\t\033[31m=================================\n");
                printf("\t|\t    请输入指令:\t\t|\n");
                printf("\t=================================\n");
                printf("\t\033[36m1.查询所有\n\t---------------------------------\n");
                printf("\t2.房间号查询\n\t---------------------------------\n");
                printf("\t3.按户型查询\n\t---------------------------------\n");
                printf("\t4.按朝向查询\n\t---------------------------------\n");
                printf("\t5.按指定评分查询\n\t---------------------------------\n");
                printf("\t6.按面积查询\n\t---------------------------------\n");
                printf("\t7.按指定价格查询\n\t---------------------------------\n");
                printf("\t8.空闲\n\t---------------------------------\n");
                printf("\t9.地区\n\t---------------------------------\n");
                printf("\t10.面积和价格\n\t---------------------------------\n");
                printf("\t11.面积和评分\n\t---------------------------------\n");
                printf("\t12.价格和评分\n\t---------------------------------\n");
                printf("\t13.返回\n\t---------------------------------\n");
                printf("\033[37m\t");
                printf("\t\033[36m当前房源数量:%d\n", houseCount);
                
                printf("\t\033[37m");
                int command_second;
                int input_num;
                char input_ch[20];
                scanf("%d", &command_second);
                switch (command_second)
                {
                case 1:
                    judge_all = 1;
                    for (int i = 0; i < houseCount; i++)
                    {
                        displayHouseInfo(houses[i]);
                        judge = 1;
                    }
                    printf("\t按任意键继续");
                    getchar();
                    getchar();
                    break;
                case 2:
                    printf("\t请输入要查询的房间号: ");
                    int number;
                    scanf("%d", &number);
                    int index = -1;
                    for (int i = 0; i < houseCount; i++)
                    {
                        if (houses[i].roomNumber == number) index = i;
                    }
                    if (index != -1) displayHouseInfo(houses[index]);
                    else
                    {
                        printf("\t\033[36m该房间不存在\n");
                        Sleep(1000);
                        break;
                    }
                case 3:
                    printf("请输入户型：");
                    scanf("%s", &input_ch);
                    Houselayout(houses, houseCount, input_ch);
                    printf("\t按任意键继续");
                    getchar();
                    getchar();
                    break;
                case 4:
                    printf("请输入朝向：");
                    scanf("%s", input_ch);
                    Houseorientation(houses, houseCount, input_ch);
                    printf("\t按任意键继续");
                    getchar();
                    getchar();
                    break;
                case 5:
                    printf("请输入最低评分要求：");
                    scanf("%d", &input_num);
                    Houserating(houses, houseCount,input_num);
                    printf("\t按任意键继续");
                    getchar();
                    getchar();
                    break;
                case 6:
                    printf("请输入最低面积：");
                    scanf("%d", &input_num);
                    Housearea(houses, houseCount, input_num);
                    printf("\t按任意键继续");
                    getchar();
                    getchar();
                    break;
                case 7:
                    printf("请输入最低价格：");
                    scanf("%d", &input_num);
                    Houseprice(houses, houseCount,input_num);
                    printf("\t按任意键继续");
                    getchar();
                    getchar();
                    break;
                case 8:
                    printf("输入空闲时间段:\n");
                    char period[20];
                    scanf("%s", period);
                    searchHousesByTimePeriod(houses, houseCount, period);
                    break;
                case 9:
                    printf("请输入地区关键字:\n");
                    char region[20];
                    scanf("%s", region);
                    searchHousesByLocation(houses, houseCount, region);
                    break;
                case 10:
                    printf("输入面积下限:\n");
                    float a, b;
                    scanf("%f", &a);
                    printf("输入面积上限:\n");
                    scanf("%f", &b);
                    printf("输入价格下限:\n");
                    int c, d;
                    scanf("%d", &c);
                    printf("输入价格上限:\n");
                    scanf("%d", &d);
                    searchHousesByPriceAndArea(houses, houseCount, c, d, a, b);
                    break;
                case 11:
                    printf("输入面积下限:\n");
                    scanf("%f", &a);
                    printf("输入面积上限:\n");
                    scanf("%f", &b);
                    printf("输入最低评分:\n");
                    scanf("%d", &c);
                    searchHousesByAreaAndScore(houses, houseCount, a, b, c);
                    break;
                case 12:
                    printf("输入价格下限:\n");
                    scanf("%d", &c);
                    printf("输入价格上限:\n");
                    scanf("%d", &d);
                    printf("输入最低评分:\n");
                    scanf("%d", &a);
                    searchHousesByPriceAndScore(houses, houseCount, c, d, a);
                    break;
                case 13:
                    system("cls");
                    return;
                    break;
                default:
                    printf("\t\033[31m无效指令！请重新输入！");
                    Sleep(300);
                }
                if (judge == 0)
                {
                    printf("\t未查询到符合条件的房屋信息\n");
                    Sleep(1000);
                }
            }   
        }
        else if (strcmp(command, "3") == 0) {//录入
            system("cls");
            while (1)
            {
                printf("\t\033[31m=================================\n");
                printf("\t|\t    请输入指令:\t\t|\n");
                printf("\t=================================\n");
                printf("\t\033[36m1.房源信息录入\n\t---------------------------------\n");
                printf("\t2.返回\n\t---------------------------------\n");
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
                        saveHouseInfo(houses, &houseCount, file);
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
                        break;
                }
                else
                {
                    printf("\t无效指令请重新输入！\n");
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
            system("cls");
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
    printf("\t请输入出租次数: ");
    scanf("%d", &(house->cnt));
    printf("\t请输入出租总时长: ");
    scanf("%d", &(house->rent_time));
}


void saveHouseInfo(struct House house[], int count, FILE* file) {
    int i;
    for (i = 0; i < count-1; i++) {
        fprintf(file, "%d\n", house[i].roomNumber);
        fprintf(file, "%s\n", house[i].location);
        fprintf(file, "%d\n", house[i].floor);
        fprintf(file, "%s\n", house[i].orientation);
        fprintf(file, "%s\n", house[i].layout);
        fprintf(file, "%s\n", house[i].decoration);
        fprintf(file, "%d\n", house[i].price);
        fprintf(file, "%.2f\n", house[i].area);
        fprintf(file, "%d\n", house[i].score);
        fprintf(file, "%s\n", house[i].time_period);
        fprintf(file, "%d\n", house[i].cnt);
        fprintf(file, "%d\n", house[i].rent_time);
    }
    fprintf(file, "%d\n", house[i].roomNumber);
    fprintf(file, "%s\n", house[i].location);
    fprintf(file, "%d\n", house[i].floor);
    fprintf(file, "%s\n", house[i].orientation);
    fprintf(file, "%s\n", house[i].layout);
    fprintf(file, "%s\n", house[i].decoration);
    fprintf(file, "%d\n", house[i].price);
    fprintf(file, "%.2f\n", house[i].area);
    fprintf(file, "%d\n", house[i].score);
    fprintf(file, "%s\n", house[i].time_period);
    fprintf(file, "%d\n", house[i].cnt);
    fprintf(file, "%d", house[i].rent_time);
}


void loadHouseInfo(struct House house[], int* count, FILE* file) {
    *count = 0;

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
        fscanf(file, "%d", &house[*count].cnt);
        fscanf(file, "%d", &house[*count].rent_time);
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
        printf("\t\033[36m房间号:%d\n", house[i].roomNumber);
        if (a != 0)
        {
            printf("\t总出租时间:%d\n", house[i].rent_time);
            printf("\t总出租次数:%d\n", house[i].cnt);
            printf("\t平均出租时间(月/次):%.1f\n", average);
        }
        else
        {
            printf("\t无出租次数\n");
        }
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
void saveAgencyInfo(struct Agency agency[], int count, FILE* file)
{
    int i;
    for (i = 0; i < count - 1; i++) {
        fprintf(file, "%s\n", agency[i].name);
        fprintf(file, "%d\n", agency[i].reservation_cnt);
        fprintf(file, "%d\n", agency[i].rent_cnt);
    }
    fprintf(file, "%s\n", agency[i].name);
    fprintf(file, "%d\n", agency[i].reservation_cnt);
    fprintf(file, "%d", agency[i].rent_cnt);
    fclose(file);
}
void statistic_agency(struct Agency agency[], int count) {

    for (int i = 0; i < count; i++) {
        if (agency[i].reservation_cnt == 0) {
            continue;
        }
        printf("\t\033[36m中介的姓名: %s\n", agency[i].name);
        printf("\t中介的预约次数: %d\n", agency[i].reservation_cnt);
        printf("\t中介的成功租房次数: %d\n", agency[i].rent_cnt);
        double rate = (double)agency[i].rent_cnt / agency[i].reservation_cnt;
        printf("\t中介的出租率: %.2f%%\n\n", rate*100);
    }

    printf("\t按任意键继续\n\033[37m");
    getchar();
    getchar();
    system("cls");
}
/**************************************/
//韬志
// 
//户型查找
void Houselayout(struct House* listings, int numListings, char* layout) {
    printf("\033[36m符合 %s 户型要求的房屋信息如下:\n", layout);
    for (int i = 0; i < numListings; ++i) {
        if (strcmp(listings[i].layout, layout) == 0) {
            printf("\033[37m房间号: %d\n房子的位置: %s\n楼层: %d\n朝向: %s\n房型: %s\n价格: %d\n面积: %.2f\n评分: %d\n空闲时间段: %s开始\n\n",
                listings[i].roomNumber, listings[i].location, listings[i].floor, listings[i].orientation, listings[i].layout, listings[i].price,
                listings[i].area, listings[i].score, listings[i].time_period);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}
//装修查找
void Housedecoration(struct House* listings, int numListings, char* decorationType) {
    printf("\033[36m装修类型为 %s 的房屋信息如下:\n", decorationType);

    for (int i = 0; i < numListings; ++i) {
        if (strcmp(listings[i].decoration, decorationType) == 0) {
            printf("\033[37m房间号: %d\n房子的位置: %s\n楼层: %d\n朝向: %s\n房型: %s\n价格: %d\n面积: %.2f\n评分: %d\n空闲时间段: %s开始\n\n",
                listings[i].roomNumber, listings[i].location, listings[i].floor, listings[i].orientation, listings[i].layout, listings[i].price,
                listings[i].area, listings[i].score, listings[i].time_period);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}
//评分查找
void Houserating(struct House* listings, int numListings, int minRating) {
    printf("\033[36m评分高于 %d 的房屋信息如下:\n", minRating);
    for (int i = 0; i < numListings; ++i) {
        if (listings[i].score > minRating) {
            printf("\033[37m房间号: %d\n房子的位置: %s\n楼层: %d\n朝向: %s\n房型: %s\n价格: %d\n面积: %.2f\n评分: %d\n空闲时间段: %s开始\n\n",
                listings[i].roomNumber, listings[i].location, listings[i].floor, listings[i].orientation, listings[i].layout, listings[i].price,
                listings[i].area, listings[i].score, listings[i].time_period);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}
//朝向查找
void Houseorientation(struct House* listings, int numListings, char* orientation) {
    printf("\033[36m朝向为 %s 的房屋信息如下:\n", orientation);
    int found = 0;
    for (int i = 0; i < numListings; ++i) {
        if (strcmp(listings[i].orientation, orientation) == 0) {
            printf("\033[37m房间号: %d\n房子的位置: %s\n楼层: %d\n朝向: %s\n房型: %s\n价格: %d\n面积: %.2f\n评分: %d\n空闲时间段: %s开始\n\n",
                listings[i].roomNumber, listings[i].location, listings[i].floor, listings[i].orientation, listings[i].layout, listings[i].price,
                listings[i].area, listings[i].score, listings[i].time_period);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}
//面积查找
void Housearea(struct House* listings, int num_listings, int min_area) {
    printf("\033[36m大于等于 %d 面积的房源id：\n", min_area);
    for (int i = 0; i < num_listings; ++i) {
        if (listings[i].area >= min_area) {
            printf("\033[37m房间号: %d\n房子的位置: %s\n楼层: %d\n朝向: %s\n房型: %s\n价格: %d\n面积: %.2f\n评分: %d\n空闲时间段: %s开始\n\n",
                listings[i].roomNumber, listings[i].location, listings[i].floor, listings[i].orientation, listings[i].layout, listings[i].price,
                listings[i].area, listings[i].score, listings[i].time_period);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}
//价格查找
void Houseprice(struct House* listings, int num_listings, int min_price) {
    printf("\033[36m大于等于 %d 价格的房源id：\n", min_price);
    for (int i = 0; i < num_listings; ++i) {
        if (listings[i].price >= min_price) {
            printf("\033[37m房间号: %d\n房子的位置: %s\n楼层: %d\n朝向: %s\n房型: %s\n价格: %d\n面积: %.2f\n评分: %d\n空闲时间段: %s开始\n\n",
                listings[i].roomNumber, listings[i].location, listings[i].floor, listings[i].orientation, listings[i].layout, listings[i].price,
                listings[i].area, listings[i].score, listings[i].time_period);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}

/****************************************************************/
//智富
// 
//按空闲查找
void searchHousesByTimePeriod(struct House houses[], int numHouses, const char* inputTimePeriod) {
    for (int i = 0; i < numHouses; i++) {
        struct House house = houses[i];

        if (strcmp(house.time_period, inputTimePeriod) > 0) {
            displayHouseInfo(house);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}
//地区查找
void searchHousesByLocation(struct House houses[], int numHouses, const char* keyword) {
    for (int i = 0; i < numHouses; i++) {
        struct House house = houses[i];

        if (strstr(house.location, keyword) != NULL) {
            displayHouseInfo(house);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}
//面积&价格
void searchHousesByPriceAndArea(struct House houses[], int numHouses, int minPrice, int maxPrice, float minArea, float maxArea) {
    for (int i = 0; i < numHouses; i++) {
        struct House house = houses[i];

        if (house.price >= minPrice && house.price <= maxPrice &&
            house.area >= minArea && house.area <= maxArea) {
            displayHouseInfo(house);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}
//面积&评分
void searchHousesByAreaAndScore(struct House houses[], int numHouses, float minArea, float maxArea, int minScore) {
    for (int i = 0; i < numHouses; i++) {
        struct House house = houses[i];
        if (house.area >= minArea && house.area <= maxArea &&
            house.score >= minScore) {
            displayHouseInfo(house);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}
//价格和评分
void searchHousesByPriceAndScore(struct House houses[], int numHouses, int minPrice, int maxPrice, int minScore) {
    for (int i = 0; i < numHouses; i++) {
        struct House house = houses[i];

        if (house.price >= minPrice && house.price <= maxPrice &&
            house.score >= minScore) {
            displayHouseInfo(house);
            judge = 1;
        }
    }
    if (judge != 0)
    {
        printf("\t按任意键继续");
        getchar();
        getchar();
    }
}