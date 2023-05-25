#pragma once
#include "preprocess.h"

void PriceThread() // 스레드 함수
{
    // 이현웅 담당
}

void gotoxy(int x, int y) // 콘솔 마우스 커서 이동 함수
{
    COORD Pos = { x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CCprint(struct _CrypCur* CC, int x, int y) // CC 출력 함수
{
    gotoxy(x, y);
    printf("이름 : %s", CC->name);
    gotoxy(x, y + 1);
    printf("가격 : $%.2lf", CC->price);
}

void CCinit(struct _CrypCur* CC, const char name[], double price, int idx) // CC 초기화 함수
{
    CC->idx = idx;
    strcpy(CC->name, name);
    CC->price = price;
}

void PrtScrHead()
{
    for (int i = STARCNT; i--;)  printf("─");
    printf("Virtual CryptoCurrency Market");
    for (int i = STARCNT; i--;)  printf("─");
}

void Asciitxt()
{
    printf("┌─────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("        _      _               _                                          \n");
    printf(" /\\   /(_)_ __| |_ _   _  __ _| |                                         \n");
    printf(" \\ \\ / / | '__| __| | | |/ _` | |                                         \n");
    printf("  \\ V /| | |  | |_| |_| | (_| | |                                         \n");
    printf("   \\_/ |_|_|   \\__|\\__,_|\\__,_|_|                                         \n");
    printf("                                                                           \n");
    printf("    ___                 _          ___                                     \n");
    printf("   / __\\ __ _   _ _ __ | |_ ___   / __\\   _ _ __ _ __ ___ _ __   ___ _   _ \n");
    printf("  / / | '__| | | | '_ \\| __/ _ \\ / / | | | | '__| '__/ _ \\ '_ \\ / __| | | |\n");
    printf(" / /__| |  | |_| | |_) | || (_) / /__| |_| | |  | | |  __/ | | | (__| |_| |\n");
    printf(" \\____/_|   \\__, | .__/ \\__\\___/\\____/\\__,_|_|  |_|  \\___|_| |_|\\___|\\__, |\n");
    printf("            |___/|_|                                                 |___/ \n");
    printf("                    _        _                                             \n");
    printf("   /\\/\\   __ _ _ __| | _____| |_                                           \n");
    printf("  /    \\ / _` | '__| |/ / _ \\ __|                                          \n");
    printf(" / /\\/\\ \\ (_| | |  |   <  __/ |_                                           \n");
    printf(" \\/    \\/\\__,_|_|  |_|\\_\\___|\\__|                                          \n");                                                                      
    printf("└─────────────────────────────────────────────────────────────────────────────────┘\n");
}

void customPause(const char* message) {
    printf("%s", message);
    getch(); // 사용자 입력 대기
}