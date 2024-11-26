#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // for isdigit() function && iswcntrl() function

#define INIT_STR_SIZE 0x1000000 // 4mb
#define MAX_STR_SIZE 0x10000 //
#define ARRMAX 0x100 // 0x10000 * 0x100 == 4mb

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef struct _StrStruct {
	char* Str; // 문자열이 저장될 공간
	uint8 Type; // 0 == String, 1 == Integer
} StrStruct;



char IsValidInitStr(char* InitStr); // validator.c
char IsValidStrArr(StrStruct** StrArr); // validator.c

char ParseStr(char* InitStr, StrStruct** StrArr); // parser.c

char Add(StrStruct* Str1, StrStruct* Str2, StrStruct* Target); // operations.c
char Subtract(StrStruct* Str1, StrStruct* Str2, StrStruct* Target); // operations.c
char Multiply(StrStruct* Str1, StrStruct* MulNum, StrStruct* Target); // operations.c
char Divide(StrStruct* Str1, StrStruct* Str2, StrStruct* Target); // operations.c

void Erase(StrStruct** StrArr, int Index); // calculate.c
char Calc(StrStruct** StrArr); // calculate.c