#pragma once
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>
#include <conio.h>

#define STARCNT 20

typedef long long ll;

struct _CrypCur // 가상화폐 구조체
{
    char name[50];
    double price;
    int idx;
} Crypto[5];

char names[5][50] = { "Soo", "Bang", "Gun", "Soo", "Gang" };
ll prices[5] = { 100,200,300,400,5000000 };
ll wallet[5] = { 0, };