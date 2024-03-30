#include "common.h"
#define MAX_NUM 100
//!!!!!
struct House {
    char location[50];
    int floor;
    char orientation[20];
    char type[20];
    char decoration[20];
    float price;
};
void displayHouseInfo(struct House house);
void modifyHouseInfo(struct House* house);
void saveHouseInfo(struct House house[], int count, FILE* fp);
void loadHouseInfo(struct House house[], int* count, FILE* fp);
void interface_house_info(struct House houses[MAX_NUM]);
