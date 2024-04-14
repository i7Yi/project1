#include "house_info.h"

int houseCount = 0;
void interface_house_info(struct House houses[MAX_NUM])
{
    FILE* fp;
    fp = fopen("house_info.txt", "r");
    if (fp != NULL) {
        loadHouseInfo(houses, &houseCount, fp);
        fclose(fp);
    }
    else {
        printf("\t\033[31m无法打开文件 house_info.txt，正在创建新文件...\n");
        fp = fopen("house_info.txt", "w");
        if (fp != NULL) {
            printf("\t新文件 house_info.txt 创建成功！\n");
            fclose(fp);
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
        printf("\t\033[36m查询\n\t---------------------------------\n");
        printf("\t排序\n\t---------------------------------\n");
        printf("\t录入\n\t---------------------------------\n");
        printf("\t保存\n\t---------------------------------\n");
        printf("\t返回\n\t---------------------------------\n");
        printf("\033[37m\t");
        scanf("%s", command);
        getchar();
        if (strcmp(command, "查询") == 0) {
            printf("\t\033[31m当前房源数量:%d\n", houseCount);
            printf("\t请输入要查询的房屋索引: ");
            int index;
            printf("\033[37m");
            scanf("%d", &index);
            getchar();
            if (index >= 0 && index < houseCount) {
                displayHouseInfo(houses[index]);
            }
            else {
                printf("\t无效的房屋索引！\n");
            }
        }
        else if (strcmp(command, "排序") == 0)
        {
            while (1)
            {
                printf("\t\033[31m=================================\n");
                printf("\t|\t    请输入指令:\t\t|\n");
                printf("\t=================================\n");
                printf("\t\033[36m楼层\n\t---------------------------------\n");
                printf("\t装修\n\t---------------------------------\n");
                printf("\t价格\n\t---------------------------------\n");
                printf("\t面积\n\t---------------------------------\n");
                printf("\t返回\n\t---------------------------------\n");
                printf("\033[37m\t");
                char command_second[20];
                scanf("%s", command_second);
                if (strcmp(command_second, "楼层") == 0)
                {
                    sortByFloor(houses, houseCount);
                    break;
                }
                else if (strcmp(command_second, "装修") == 0)
                {
                    sortByDecoration(houses, houseCount);
                    break;
                }
                else if (strcmp(command_second, "价格") == 0)
                {
                    sortByPrice(houses, houseCount);
                    break;
                }
                else if (strcmp(command_second, "面积") == 0)
                {
                    sortByArea(houses, houseCount);
                    break;
                }
                else if (strcmp(command_second, "返回") == 0)
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
        else if (strcmp(command, "录入") == 0) {
            if (houseCount < MAX_NUM) {
                modifyHouseInfo(&houses[houseCount]);
                printf("\t房源信息已添加！\n");
                houseCount++;
                continue;
            }
            else {
                printf("\t已达到房屋数量上限，无法添加更多房源信息！\n");
            }
        }
        else if (strcmp(command, "保存") == 0) {
            fp = fopen("house_info.txt", "w");

            if (fp != NULL) {
                saveHouseInfo(houses, houseCount, fp);
                fclose(fp);
                printf("房源信息已保存！\n");
            }
            else {
                printf("无法打开文件 house_info.txt\n");
            }
        }
        else if (strcmp(command, "返回") == 0) {
            break;
        }
        else {
            printf("无效的指令，请重新输入！\n");
        }
    }
}
void displayHouseInfo(struct House house) {
    printf("\t\033[36m房间号: %d\n", house.roomNumber);
    printf("\t房子的位置: %s\n", house.location);
    printf("\t楼层: %d\n", house.floor);
    printf("\t朝向: %s\n", house.orientation);
    printf("\t房型: %s\n", house.type);
    printf("\t装修: %s\n", house.decoration);
    printf("\t价格: %.2f\n", house.price);
    printf("\t面积: %.2f\n", house.area);
}

void modifyHouseInfo(struct House* house) {
    printf("\t\033[36m请输入房间号: ");
    scanf("%d", &(house->roomNumber));
    printf("\t请输入房子的位置: ");
    scanf("%s", house->location);
    printf("\t请输入楼层: ");
    scanf("%d", &(house->floor));
    printf("\t请输入朝向: ");
    scanf("%s", house->orientation);
    printf("\t请输入房型: ");
    scanf("%s", house->type);
    printf("\t请输入装修: ");
    scanf("%s", house->decoration);
    printf("\t请输入价格: ");
    scanf("%f", &(house->price));
    printf("\t请输入面积: ");
    scanf("%f", &(house->area));
}

void saveHouseInfo(struct House house[], int count, FILE* fp) {
    int i;
    for (i = 0; i < count-1; i++) {
        fprintf(fp, "%d\n", house[i].roomNumber);
        fprintf(fp, "%s\n", house[i].location);
        fprintf(fp, "%d\n", house[i].floor);
        fprintf(fp, "%s\n", house[i].orientation);
        fprintf(fp, "%s\n", house[i].type);
        fprintf(fp, "%s\n", house[i].decoration);
        fprintf(fp, "%.2f\n", house[i].price);
        fprintf(fp, "%.2f\n", house[i].area);
    }
    fprintf(fp, "%d\n", house[i].roomNumber);
    fprintf(fp, "%s\n", house[i].location);
    fprintf(fp, "%d\n", house[i].floor);
    fprintf(fp, "%s\n", house[i].orientation);
    fprintf(fp, "%s\n", house[i].type);
    fprintf(fp, "%s\n", house[i].decoration);
    fprintf(fp, "%.2f\n", house[i].price);
    fprintf(fp, "%.2f", house[i].area);
}

void loadHouseInfo(struct House house[], int* count, FILE* fp) {
    *count = 0;
    // 检查文件是否为空
    fseek(fp, 0, SEEK_END);  // 将文件指针移动到文件末尾
    long fileSize = ftell(fp);  // 获取文件大小
    if (fileSize == 0) {
        printf("文件为空，按任意键继续");
        getchar();
        return;  // 文件为空，直接返回
    }
    rewind(fp);  // 将文件指针重新移动到文件开头

    while (!feof(fp) && *count < MAX_NUM) {
        fscanf(fp, "%d", &(house[*count].roomNumber));
        fscanf(fp, "%s", house[*count].location);
        fscanf(fp, "%d", &(house[*count].floor));
        fscanf(fp, "%s", house[*count].orientation);
        fscanf(fp, "%s", house[*count].type);
        fscanf(fp, "%s", house[*count].decoration);
        fscanf(fp, "%f", &(house[*count].price));
        fscanf(fp, "%f", &(house[*count].area));
        (*count)++;

    }
}
void sortByFloor(struct House house[], int count) {
    struct House temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (house[j].floor > house[j + 1].floor) {
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

