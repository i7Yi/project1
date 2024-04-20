#pragma once
#include "common.h"
struct Reservation {
    int roomHouse;
    char date[20];
    char HouseSource[20];
    char TenantName[10];
    char IntermediaryName[10];
    char time[20];
    char evaluation[20];
    struct Reservation* next;
};
void interface_reservation(struct Reservation *head);
void printReserve(struct Reservation* reserve);
void saveListToFile(struct Reservation* head, const char* filename);
struct Reservation* loadListFromFile(struct Reservation* head,FILE* file);
void modifyReserve(struct Reservation* head, int roomHouse);
struct Reservation* addReserve(struct Reservation* head);
void searchByRoomHouse(struct Reservation* head, int roomHouse);
void freeList(struct Reservation* head);
void printList(struct Reservation* head);