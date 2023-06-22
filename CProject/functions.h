#pragma once
#include "preprocess.h"


void gotoxy(int x, int y) // 콘솔 마우스 커서 이동 함수
{
    COORD Pos = { x * 2, y };   // 인자를 COORD 자료형으로 변경, x의 좌표는 2배를 취해야 1:1 비율이기 때문
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); // WinCon.h에 정의된 함수로 커서 위치를 변경, GetStdHandle로 출력창의 핸들을 가져옴
}

void ColorPrint(double num)
{
    char tmp[100] = { 0, };
    if (num > 0)  printf("\033[38;2;242;61;61m+ ");  // 빨간색으로 색을 변경, +출력
    if (num < 0)  printf("\033[38;2;38;145;204m- ");   // 파란색으로 색을 변경, -출력
    printf("%.1lf%%", fabs(num));
    printf("\033[0m");
}

void WalletPrint(ll wallet[], int x, int y) // 지갑 상태출력
{
    int cnt = 0;
    gotoxy(x + cnt * 13, y - 2);
    printf("현금 : $%.2lf", mycash);  // 현재 돈 출력

    for (int i = 0; i < CRYPTOCNT; i++)
    {
        if (wallet[i] > 0)  // wallet[i] = i번째 가상화폐 갯수
        {
            gotoxy(x + cnt * 13, y);
            printf("이름 : %s\n", Crypto[i].name);    // i번째 가상화폐 이름
            gotoxy(x + cnt * 13, y + 1);
            printf("갯수 : %lld\n", wallet[i]);       // i번째 갯수 출력
            gotoxy(x + cnt++ * 13, y + 2);
            printf("총액 : $%.2lf", wallet[i] * Crypto[i].price); // 가격 * 현재개수
        }
    }
}

void VaryPrice()
{
    for (int i = 0; i < CRYPTOCNT; i++) // 모든 가상화폐에 대해서
    {
        srand(time(NULL) + i);    // 현재시간+i로 rand 시드 초기화
        double randomChange = double(rand() % 70 + 1) / 1000;   // 0.001-0.07 : 0.1프로에서 7프로까지
        Crypto[i].updown = randomChange * 100;  // i번째 가상화폐의 등락폭 저장
        if (rand() % 100 > 46)  // 0~46 까지 하락, 47~99까지 상승
        {
            Crypto[i].price += randomChange * Crypto[i].price;  // {randomChange}% 만큼 상승
        }
        else
        {
            Crypto[i].price -= randomChange * Crypto[i].price;  // {randomChange}% 만큼 하락
            Crypto[i].updown *= -1;
        }
    }

}


void CCprint(struct _CrypCur* CC, int x, int y) // CC 출력 함수
{
    gotoxy(x, y);
    printf("이름 : %s", CC->name);    // 이름 출력
    gotoxy(x, y + 1);
    printf("가격 : $%.2lf", CC->price);   // 가격 출력
    gotoxy(x, y + 2);
    printf("등락폭 : ");   // 등락폭 출력
    ColorPrint(CC->updown);
}

void CCinit(struct _CrypCur* CC, const char name[], double price, int idx) // CC 초기화 함수
{
    CC->idx = idx;
    strcpy(CC->name, name);
    CC->price = price;
    CC->updown = 0;
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
    _getch();
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

    WalletPrint(wallet, x, y + 20);
}

void CursorView() // 커서 가리기
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };    // CONSOLE_CURSOR_INFO 자료형
    cursorInfo.dwSize = 1; // 커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; // 커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // Handle의 Cursor정보를 위의 정보로 변경
}

void ApplyTransaction(ll mode, ll idx, ll cnt)
{
    int type = 0;
    if (mode == 1)      type = -1;  // 구매이면 -1
    else if (mode == 2) type = 1;   // 판매이면 1

    mycash += Crypto[idx].price * cnt * type;   // 지갑에 돈을 넣을지 뺄지 결정함

    type *= -1; // 구매이면 1, 판매이면 -1이 됨
    wallet[idx] += cnt * type;
}

void StartTransaction(int ccprintpos, int printpos)
{
    ll CCmode, CCidx, CCcnt;
select1:
    system("cls");  // 화면 clear
    PrtCCInfo(0, ccprintpos);   // CC 정보 출력
    gotoxy(0, printpos);
    printf("(1) 구매\n(2) 판매\n(ESC) 돌아가기");

    while (1)
    {
        CCmode = _getch() - '0';    // getch()로 값을 받고 '0'을 뺌으로 정수 변환
        if (CCmode == VK_ESCAPE - '0')  // ESC와 값이 같을 경우
        {
            system("cls");  // 화면 clear
            return; // 함수 종료
        }
        if (1 > CCmode || CCmode > 2)   continue;   // 1~2가 아닐시엔 무한루프
        break;  // 1~2일시엔 무한루프 종료
    }

select2:
    system("cls");  // 화면 clear
    PrtCCInfo(0, ccprintpos);   // CC 정보 출력
    gotoxy(0, printpos);
    for (int i = 0; i < CRYPTOCNT; i++) printf("(%d) %s\n", i + 1, Crypto[i].name); // CRYPTOCNT 상수까지 돌면서 i번째 이름 출력
    printf("(ESC) 돌아가기\n");

    while (1)
    {
        CCidx = _getch() - '0' - 1; // getch()로 정수 변환하고 1빼기(1 -> 0, 5 -> 4) 인덱스를 0부터 사용하는 컴퓨터와 맞추기 위함
        if (CCidx == VK_ESCAPE - '0' - 1)   goto select1;   // ESC일 경우엔 select1으로
        if (0 > CCidx || CCidx > CRYPTOCNT - 1)  continue;  // 0~CRYPTOCNT-1 이 아닐경우 무한루프
        break;  // 맞는경우 종료
    }

select3:
    system("cls");  // 화면 clear
    while (1)
    {
        PrtCCInfo(0, ccprintpos);   // CC 정보 출력
        gotoxy(0, printpos);
        printf("갯수: ");
        scanf("%lld", &CCcnt);
        if (CCmode == 1 && Crypto[CCidx].price * CCcnt > mycash)    // 구매 거래이고 지갑에 충분한 돈이 없을 경우
        {
            gotoxy(0, printpos + 1);
            printf("잔액이 부족합니다.\n");
            Sleep(1000);    // 1초 대기
            system("cls");  // 화면 clear
            continue;
        }
        if (CCmode == 2 && wallet[CCidx] < CCcnt)   // 판매 거래이고 지갑에 충분한 가상화폐가 없을 경우
        {
            gotoxy(0, printpos + 1);
            printf("가상화폐가 부족합니다.\n");
            Sleep(1000);    // 1초 대기
            system("cls");  // 화면 clear
            continue;
        }

        if (CCmode == 1)         printf("구매가 완료되었습니다.");    // 구매일경우
        else if (CCmode == 2)    printf("판매가 완료되었습니다.");    // 판매일경우

        Sleep(1000);    // 1초대기
        break;          // while 탈출
    }
    ApplyTransaction(CCmode, CCidx, CCcnt); // 거래 적용 함수 호출

    system("cls");  // 화면 clear
}
