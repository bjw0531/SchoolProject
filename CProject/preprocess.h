#pragma once
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define CRYPTOCNT 5
#define DASHCNT 20

typedef long long ll;

struct _CrypCur // ����ȭ�� ����ü
{
    char name[50];
    double price;
    int idx;
} Crypto[CRYPTOCNT];

char names[CRYPTOCNT][50] = { "Apple", "Kakao", "Samsung", "Tesla", "Microsoft" };
ll prices[CRYPTOCNT] = { 100,200,300,400,5000000 };
ll wallet[CRYPTOCNT] = { 0, };
double mycash = 10000000;
