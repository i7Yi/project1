#include "common.h"
//!!!!!
struct House {
    int roomNumber;
    char location[50];
    int floor;
    char orientation[20];
    char type[20];
    char decoration[20];
    float price;
    float area;
};
void displayHouseInfo(struct House house);
void modifyHouseInfo(struct House* house);
void saveHouseInfo(struct House house[], int count, FILE* fp);
void loadHouseInfo(struct House house[], int* count, FILE* fp);
void interface_house_info(struct House houses[MAX_NUM]);
void sortByFloor(struct House house[], int count);
void sortByDecoration(struct House house[], int count);
void sortByPrice(struct House house[], int count);
void sortByArea(struct House house[], int count);

