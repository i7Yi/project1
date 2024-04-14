#pragma once
#include "common.h"
typedef struct {//存用户和密码
	char userName1[10];
	char passWorld1[10];
	struct AC* next;
}AC;
void sign_in();
int Delete();
void modify();
void enter_user();
void loadAccount(AC acc[], int* count, FILE* fp);
void saveAccount(AC acc[], int* count, FILE* fp);