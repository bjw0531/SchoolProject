#pragma once
#include "preprocess.h"


void gotoxy(int x, int y) // �ܼ� ���콺 Ŀ�� �̵� �Լ�
{
    COORD Pos = { x * 2, y };   // ���ڸ� COORD �ڷ������� ����, x�� ��ǥ�� 2�踦 ���ؾ� 1:1 �����̱� ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); // WinCon.h�� ���ǵ� �Լ��� Ŀ�� ��ġ�� ����, GetStdHandle�� ���â�� �ڵ��� ������
}

void ColorPrint(double num)
{
    char tmp[100] = { 0, };
    if (num > 0)  printf("\033[38;2;242;61;61m+ ");  // ���������� ���� ����, +���
    if (num < 0)  printf("\033[38;2;38;145;204m- ");   // �Ķ������� ���� ����, -���
    printf("%.1lf%%", fabs(num));
    printf("\033[0m");
}

void WalletPrint(ll wallet[], int x, int y) // ���� �������
{
    int cnt = 0;
    gotoxy(x + cnt * 13, y-2);
    printf("���� : $%.2lf", mycash);  // ���� �� ���

    for (int i = 0; i < CRYPTOCNT; i++)
    {
        if (wallet[i] > 0)  // wallet[i] = i��° ����ȭ�� ����
        {
            gotoxy(x + cnt * 13, y);
            printf("�̸� : %s\n", Crypto[i].name);    // i��° ����ȭ�� �̸�
            gotoxy(x + cnt * 13, y + 1);
            printf("���� : %lld\n", wallet[i]);       // i��° ���� ���
            gotoxy(x + cnt++ * 13, y + 2);
            printf("�Ѿ� : $%.2lf", wallet[i] * Crypto[i].price); // ���� * ���簳��
        }
    }
}

void VaryPrice()
{
    for (int i = 0; i < CRYPTOCNT; i++) // ��� ����ȭ�� ���ؼ�
    {
        srand(time(NULL) + i);    // ����ð�+i�� rand �õ� �ʱ�ȭ
        double randomChange = double(rand() % 70 + 1) / 1000;   // 0.001-0.07 : 0.1���ο��� 7���α���
        Crypto[i].updown = randomChange * 100;  // i��° ����ȭ���� ����� ����
        if (rand() % 100 > 46)  // 0~46 ���� �϶�, 47~99���� ���
        {
            Crypto[i].price += randomChange * Crypto[i].price;  // {randomChange}% ��ŭ ���
        }
        else 
        {
            Crypto[i].price -= randomChange * Crypto[i].price;  // {randomChange}% ��ŭ �϶�
            Crypto[i].updown *= -1;
        }
    }
    
}


void CCprint(struct _CrypCur* CC, int x, int y) // CC ��� �Լ�
{
    gotoxy(x, y);
    printf("�̸� : %s", CC->name);    // �̸� ���
    gotoxy(x, y + 1);
    printf("���� : $%.2lf", CC->price);   // ���� ���
    gotoxy(x, y + 2);
    printf("����� : ");   // ����� ���
    ColorPrint(CC->updown);
}

void CCinit(struct _CrypCur* CC, const char name[], double price, int idx) // CC �ʱ�ȭ �Լ�
{
    CC->idx = idx;
    strcpy(CC->name, name);
    CC->price = price;
    CC->updown = 0;
}

void Asciitxt()
{
    printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
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
    printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}

void customPause(const char* message) // ����� ���� pause
{
    printf("%s", message);
    _getch(); 
}

void InitScreen() // �ʱ� ���� ȭ��
{
    Asciitxt();
    printf("�� Maximize This Window First ��\n");
    customPause("\n�� Press Any Key To Start");
    system("cls");
}

void InitVars() // CC ���� �ʱ�ȭ
{
    for (int i = 0; i < CRYPTOCNT; i++) CCinit(&Crypto[i], names[i], prices[i], i + 1);
}

void PrtCCInfo(int x, int y) // CC ���
{
    gotoxy(x, y);
    for (int i = 0; i < CRYPTOCNT; i++) CCprint(&Crypto[i], i * 13, y);
    gotoxy((CRYPTOCNT - 1) * 13, y + 4);

    WalletPrint(wallet, x, y + 20);
}

void CursorView() // Ŀ�� ������
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };    // CONSOLE_CURSOR_INFO �ڷ���
    cursorInfo.dwSize = 1; // Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = FALSE; // Ŀ�� Visible TRUE(����) FALSE(����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // Handle�� Cursor������ ���� ������ ����
}

void ApplyTransaction(int mode, int idx, int cnt)
{
    int type = 0;
    if (mode == 1)      type = -1;  // �����̸� -1
    else if (mode == 2) type = 1;   // �Ǹ��̸� 1

    mycash += Crypto[idx].price * cnt * type;   // ������ ���� ������ ���� ������
    
    type *= -1; // �����̸� 1, �Ǹ��̸� -1�� ��
    wallet[idx] += cnt * type;

}   

void StartTransaction(int ccprintpos, int printpos)
{
    int CCmode, CCidx, CCcnt;
select1:
    system("cls");
    PrtCCInfo(0, ccprintpos);
    gotoxy(0, printpos);
    printf("(1) ����\n(2) �Ǹ�\n(ESC) ���ư���");

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
    printf("(ESC) ���ư���\n");

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
        printf("����: ");
        scanf("%d", &CCcnt); 
        if (CCmode == 1 && Crypto[CCidx].price * CCcnt > mycash)    // ���� �ŷ��̰� ������ ����� ���� ���� ���
        {
            gotoxy(0, printpos+1);
            printf("�ܾ��� �����մϴ�.\n");
            Sleep(1000);
            system("cls");
            continue;
        }
        if (CCmode == 2 && wallet[CCidx] < CCcnt)   // �Ǹ� �ŷ��̰� ������ ����� ����ȭ�� ���� ���
        {
            gotoxy(0, printpos + 1);
            printf("����ȭ�� �����մϴ�.\n");
            Sleep(1000);
            system("cls");
            continue;
        }

        if (CCmode == 1)         printf("���Ű� �Ϸ�Ǿ����ϴ�.");
        else if (CCmode == 2)    printf("�ǸŰ� �Ϸ�Ǿ����ϴ�.");

        Sleep(1000);
        break;
    }
    ApplyTransaction(CCmode, CCidx, CCcnt);

    system("cls");
}

