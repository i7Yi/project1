#pragma once
#include "common.h"
#include "account.h"
#include "house_info.h"
#include "reservation.h"
void data_backup(struct House house[], struct Reservation reservations[],AC acc[]);
void recovery(struct House house[],struct Reservation reservations[],AC acc[]);