#pragma once
#include "common.h"

struct House {
    int roomNumber; // 房间号变量--房源的唯一ID
    char location[50];
    int floor;
    char orientation[20];
    char layout[20];
    char decoration[20];//装修等级用A,B,C表示，便于后续排序
    int price;
    float area;
    int score;
    char time_period[20];
    int cnt;//租房次数
    int rent_time;//租房总时长
};
void displayHouseInfo(struct House house);
void modifyHouseInfo(struct House* house);
void saveHouseInfo(struct House house[], int count, FILE* fp);
void loadHouseInfo(struct House house[], int* count, FILE* fp);
void interface_house_info(struct House houses[MAX_NUM],struct Agency agencys[MAX_NUM]);
void sortByFloor(struct House house[], int count);
void sortByDecoration(struct House house[], int count);
void sortByPrice(struct House house[], int count);
void sortByArea(struct House house[], int count);
void modifyRentInfo(struct House* house);
void saveRentInfo(struct House house[], int count, FILE* file);
void loadRentInfo(struct House house[], int* count, FILE* file);
void statistic_house(struct House house[], int count);
void loadAgencyInfo(struct Agency agency[], int* count, FILE* file);
void saveAgencyInfo(struct Agency agency[], int count, FILE* file);
void statistic_agency(struct Agency agency[], int count);
void Houselayout(struct House* listings, int numListings, char* layout);
void Housedecoration(struct House* listings, int numListings, char* decorationType);
void Houserating(struct House* listings, int numListings, int minRating);
void Houseorientation(struct House* listings, int numListings, char* orientation);
void Housearea(struct House* listings, int num_listings, int min_area);
void Houseprice(struct House* listings, int num_listings, int min_price);
void searchHousesByTimePeriod(struct House houses[], int numHouses, const char* inputTimePeriod);
void searchHousesByLocation(struct House houses[], int numHouses, const char* keyword);
void searchHousesByPriceAndArea(struct House houses[], int numHouses, int minPrice, int maxPrice, float minArea, float maxArea);
void searchHousesByAreaAndScore(struct House houses[], int numHouses, float minArea, float maxArea, int minScore);
void searchHousesByPriceAndScore(struct House houses[], int numHouses, int minPrice, int maxPrice, int minScore);