#pragma once
#include "common.h"
#include "house_info.h"
#include "UI.h"
typedef struct {//存用户和密码
	char userName1[10];
	char passWorld1[10];
	char name[20];
	char phone[12];
	struct AC* next;
}AC;
void sign_in();
int Delete();
void modify_reset();
void enter_zj(char name[]);
void enter_zk(char name[]);
void loadAccount(AC acc[], int* count, FILE* fp);
void saveAccount(AC acc[], int count, FILE* fp);
void display_info(FILE* fp, int* n, AC ac[1000]);
void code();
void modify_code(int *judge);