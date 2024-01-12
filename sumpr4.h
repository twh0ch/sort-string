#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <locale.h>


#define STRINGS_COUNT  10//1000
#define MAX_STRING_SIZE 20//100
#define MAX 50


char* GenerateRandomString(unsigned int max_size);

void GenerateRandomStrings(FILE* outputfile, char* str);

void ReadFile(char* filename, char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings);
void PrintStrings(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings);

void SortStrings(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int (*compareStringsFunction)(char staticStrings[][MAX_STRING_SIZE],char**dynamicStrings,int,int));

//int length(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int index, int index1,int len1,int len2,int indef);

int SortPlus(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int, int);
int SortMinus(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int, int);

int caseA_Z(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings,int,int);
int caseZ_A(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings,int,int);

