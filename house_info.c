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
        printf("\t\033[36minquire\n\t---------------------------------\n");
        printf("\tenter\n\t---------------------------------\n");
        printf("\tsave\n\t---------------------------------\n");
        printf("\texit\n\t---------------------------------\n");
        printf("\033[37m\t");
        scanf("%s", command);
        getchar();
        if (strcmp(command, "inquire") == 0) {
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
        else if (strcmp(command, "enter") == 0) {
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
        else if (strcmp(command, "save") == 0) {
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
        else if (strcmp(command, "exit") == 0) {
            break;
        }
        else {
            printf("无效的指令，请重新输入！\n");
        }
    }
}
void displayHouseInfo(struct House house) {
    printf("房子的位置: %s\n", house.location);
    printf("楼层: %d\n", house.floor);
    printf("朝向: %s\n", house.orientation);
    printf("房型: %s\n", house.type);
    printf("装修: %s\n", house.decoration);
    printf("价格: %.2f\n", house.price);
}

void modifyHouseInfo(struct House* house) {
    printf("\t请输入新的房子的位置: ");
    scanf("%s", house->location);
    printf("\t请输入新的楼层: ");
    scanf("%d", &(house->floor));
    printf("\t请输入新的朝向: ");
    scanf("%s", house->orientation);
    printf("\t请输入新的房型: ");
    scanf("%s", house->type);
    printf("\t请输入新的装修: ");
    scanf("%s", house->decoration);
    printf("\t请输入新的价格: ");
    scanf("%f", &(house->price));
}

void saveHouseInfo(struct House house[], int count, FILE* fp) {
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", house[i].location);
        fprintf(fp, "%d\n", house[i].floor);
        fprintf(fp, "%s\n", house[i].orientation);
        fprintf(fp, "%s\n", house[i].type);
        fprintf(fp, "%s\n", house[i].decoration);
        fprintf(fp, "%.2f\n", house[i].price);
    }
}

void loadHouseInfo(struct House house[], int* count, FILE* fp) {
    *count = 0;
    // 检查文件是否为空
    fseek(fp, 0, SEEK_END);  // 将文件指针移动到文件末尾
    long fileSize = ftell(fp);  // 获取文件大小
    if (fileSize == 0) {
        printf("");
        return;  // 文件为空，直接返回
    }
    rewind(fp);  // 将文件指针重新移动到文件开头

    while (!feof(fp) && *count < MAX_NUM) {
        fscanf(fp, "%s", house[*count].location);
        fscanf(fp, "%d", &(house[*count].floor));
        fscanf(fp, "%s", house[*count].orientation);
        fscanf(fp, "%s", house[*count].type);
        fscanf(fp, "%s", house[*count].decoration);
        fscanf(fp, "%f", &(house[*count].price));
        (*count)++;
    }
}