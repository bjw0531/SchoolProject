﻿#include "preprocess.h"
#include "functions.h"



int main()
{
    

    Asciitxt();
    printf("※ Maximize This Window First ※\n");
    customPause("\n▶ Press Any Key To Start");
    system("cls");

    for (int i = 0; i < 5; i++) CCinit(&Crypto[i], names[i], prices[i], i + 1);

    printf("\n");
    for (int i = 0; i < 5; i++) CCprint(&Crypto[i], i * 13, 1);

    gotoxy(0, 3);
    printf("(1) 구매\n(2) 판매");

}	