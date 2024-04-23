#pragma once
#include "common.h"
#include "account.h"
#include "house_info.h"
#include "reservation.h"
#include "rent_info.h"
#include "agency_info.h"
void data_backup(struct House houses[MAX_NUM], struct Reservation* head, AC accs[], struct RentalInformation* head2,struct Agency agencys[]);
void recovery(struct House houses[MAX_NUM], struct Reservation** head, AC accs[], struct RentalInformation* head2, struct Agency agencys[]);