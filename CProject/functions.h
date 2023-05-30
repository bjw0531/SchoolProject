#pragma once
#include "preprocess.h"

void VaryPrice() // 스레드 함수
{
    // 이현웅 담당

    for (int i = 0; i < CRYPTOCNT; i++)
    {
        float randomChange = float(((rand() % 40) + 10)) / 1000;
        // 50%의 확률로 상승 또는 하락    
        Crypto[i].price = Crypto[i].price * (1 + randomChange);
        if (rand() % 2 == 0) {
            Crypto[i].price += randomChange * Crypto[i].price;  // 퍼센트 값을 증감
        }
        else {
            Crypto[i].price -= randomChange * Crypto[i].price;  // 퍼센트 값을 증감
        }
    }
    
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
    for (int i = DASHCNT; i--;)  printf("─");
    printf("Virtual CryptoCurrency Market");
    for (int i = DASHCNT; i--;)  printf("─");
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

void customPause(const char* message) // 사용자 지정 pause
{
    printf("%s", message);
    getch(); 
}

void InitScreen() // 초기 시작 화면
{
    Asciitxt();
    printf("※ Maximize This Window First ※\n");
    customPause("\n▶ Press Any Key To Start");
    system("cls");
}

void InitVars() // CC 정보 초기화
{
    for (int i = 0; i < CRYPTOCNT; i++) CCinit(&Crypto[i], names[i], prices[i], i + 1);
}

void PrtCCInfo(int x, int y) // CC 출력
{
    gotoxy(x, y);
    for (int i = 0; i < CRYPTOCNT; i++) CCprint(&Crypto[i], i * 13, y);
    gotoxy((CRYPTOCNT - 1) * 13, y + 4);
    printf("잔고 : $%.2lf", mycash);
}

void CursorView() // 커서 가리기
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void ApplyTransaction(int mode, int idx, int cnt)
{

}

void StartTransaction(int ccprintpos, int printpos)
{
    int CCmode, CCidx, CCcnt;
select1:
    system("cls");
    PrtCCInfo(0, ccprintpos);
    gotoxy(0, printpos);
    printf("(1) 구매\n(2) 판매");

    while (1)
    {
        CCmode = _getch() - '0';
        if (CCmode == VK_ESCAPE - '0')
        {
            system("cls");
            return;
        }
        if (1 > CCmode || CCmode > 2)   continue;
        break;
    }

select2:
    system("cls");
    PrtCCInfo(0, ccprintpos);
    gotoxy(0, printpos);
    for (int i = 0; i < CRYPTOCNT; i++) printf("(%d) %s\n", i + 1, Crypto[i].name);

    while (1)
    {
        CCidx = _getch() - '0' - 1;
        if (CCidx == VK_ESCAPE - '0' - 1)   goto select1;
        if (0 > CCidx || CCidx > 4)  continue;
        break;
    }

select3:
    system("cls");
    while (1)
    {
        PrtCCInfo(0, ccprintpos);
        gotoxy(0, printpos);
        printf("갯수: ");
        scanf("%d", &CCcnt);
        if (Crypto[CCidx].price * CCcnt > mycash)
        {
            gotoxy(0, printpos+1);
            printf("잔액이 부족합니다.\n");
            Sleep(1000);
            system("cls");
            continue;
        }

        if (CCmode == 1)         printf("구매가 완료되었습니다.");
        else if (CCmode == 2)    printf("판매가 완료되었습니다.");

        Sleep(1000);
        break;
    }
    system("cls");
}