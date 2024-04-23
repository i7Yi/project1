#pragma once
#include "common.h"
struct RentalInformation {
    int roomHouse;
    char TenantName[20];
    char IntermediaryName[20];
    char ContractDate[20];
    char Rentaldate[20];
    int EstimatedRentalDuration;
    struct RentalInformation* next;
};

void interface_rent(struct RentalInformation* head,struct House houses_rent[MAX_NUM],struct Agency agencys_rent[MAX_NUM]);
void printRental(struct RentalInformation* rental);
void printList2(struct RentalInformation* head);
struct RentalInformation* loadListFromFile2(struct RentalInformation* head, FILE* file);
void saveListToFile2(struct RentalInformation* head, const char* filename);
struct RentalInformation* addRental(struct RentalInformation* head, struct House houses[MAX_NUM], struct Agency agencys[MAX_NUM]);
void modifyRental(struct RentalInformation* head, int roomHouse);
void searchByRoomHouse2(struct RentalInformation* head, int roomHouse);
void freeList2(struct RentalInformation* head);
