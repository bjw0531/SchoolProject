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

struct _CrypCur // 가상화폐 구조체
{
    char name[50];
    double price;
    double updown;
    int idx;
} Crypto[CRYPTOCNT];

char names[CRYPTOCNT][50] = { "DOGE", "USDT", "XRP", "ETH", "BTC" };
double prices[CRYPTOCNT] = { 5,50,200,1500,25000 };
ll wallet[CRYPTOCNT] = { 0, };
double lastpercent[CRYPTOCNT] = { 0, };
double mycash = 10000000;
