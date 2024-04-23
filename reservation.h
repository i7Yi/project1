#pragma once
#include "common.h"
#include "agency_info.h"
#include "house_info.h"
struct Reservation {
    int roomHouse;
    char date[20];
    char TenantName[10];
    char IntermediaryName[10];
    char time[20];
    char evaluation[20];
    struct Reservation* next;

};
void interface_reservation(struct Reservation *head, struct Agency agencys[MAX_NUM], struct House houses[MAX_NUM]);
void interface_reservation_user(struct Reservation* head,const char name[], struct Agency agencys[MAX_NUM], struct House houses[MAX_NUM]);
void printReserve(struct Reservation* reserve);
void printReserve_user(struct Reservation* reserve,char name[]);
void saveListToFile(struct Reservation* head, const char* filename);
struct Reservation* loadListFromFile(struct Reservation* head,FILE* file);
void modifyReserve(struct Reservation* head, int roomHouse);
struct Reservation* addReserve(struct Reservation* head,struct Agency agencys[MAX_NUM],struct House houses[MAX_NUM]);
void searchByRoomHouse(struct Reservation* head, int roomHouse);
void searchByuserName(struct Reservation* head, const char name[]);
void freeList(struct Reservation* head);
void printList(struct Reservation* head);
void printList_user(struct Reservation* head,const char name[]);