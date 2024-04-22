#pragma once
#include "common.h"
#include "account.h"
#include "house_info.h"
#include "reservation.h"
#include "rent_info.h"
void data_backup(struct House house[], struct Reservation* head,AC accs[], struct RentalInformation* head2);
void recovery(struct House house[], struct Reservation* head,AC accs[],struct RentalInformation* head2);