#pragma once
#include "common.h"
typedef struct {//存用户和密码
	char userName1[10];
	char passWorld1[10];
}AC;
void enter();
void sign_in(char userName[], char passWorld[]);
int Delete();
