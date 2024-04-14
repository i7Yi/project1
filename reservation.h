#pragma once
#include "common.h"
struct Reservation {
    int roomNumber;
    char tenantID[30];//租客ID
    struct Date appointmentTime;
};
void interface_reservation(struct Reservation reservations[MAX_NUM]);
void displayReservationInfo(struct Reservation reservation);
void saveReservationInfo(struct Reservation reservations[], int count, FILE* file);
void loadReservationInfo(struct Reservation reservations[], int* count, FILE* file);