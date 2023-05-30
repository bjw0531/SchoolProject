#pragma once
#include "preprocess.h"

void VaryPrice() // ������ �Լ�
{
    // ������ ���

    for (int i = 0; i < CRYPTOCNT; i++)
    {
        float randomChange = float(((rand() % 40) + 10)) / 1000;
        // 50%�� Ȯ���� ��� �Ǵ� �϶�    
        Crypto[i].price = Crypto[i].price * (1 + randomChange);
        if (rand() % 2 == 0) {
            Crypto[i].price += randomChange * Crypto[i].price;  // �ۼ�Ʈ ���� ����
        }
        else {
            Crypto[i].price -= randomChange * Crypto[i].price;  // �ۼ�Ʈ ���� ����
        }
    }
    
}

void gotoxy(int x, int y) // �ܼ� ���콺 Ŀ�� �̵� �Լ�
{
    COORD Pos = { x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CCprint(struct _CrypCur* CC, int x, int y) // CC ��� �Լ�
{
    gotoxy(x, y);
    printf("�̸� : %s", CC->name);
    gotoxy(x, y + 1);
    printf("���� : $%.2lf", CC->price);
}

void CCinit(struct _CrypCur* CC, const char name[], double price, int idx) // CC �ʱ�ȭ �Լ�
{
    CC->idx = idx;
    strcpy(CC->name, name);
    CC->price = price;
}

void PrtScrHead() 
{
    for (int i = DASHCNT; i--;)  printf("��");
    printf("Virtual CryptoCurrency Market");
    for (int i = DASHCNT; i--;)  printf("��");
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
    getch(); 
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
    printf("�ܰ� : $%.2lf", mycash);
}

void CursorView() // Ŀ�� ������
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
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
    printf("(1) ����\n(2) �Ǹ�");

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
        printf("����: ");
        scanf("%d", &CCcnt);
        if (Crypto[CCidx].price * CCcnt > mycash)
        {
            gotoxy(0, printpos+1);
            printf("�ܾ��� �����մϴ�.\n");
            Sleep(1000);
            system("cls");
            continue;
        }

        if (CCmode == 1)         printf("���Ű� �Ϸ�Ǿ����ϴ�.");
        else if (CCmode == 2)    printf("�ǸŰ� �Ϸ�Ǿ����ϴ�.");

        Sleep(1000);
        break;
    }
    system("cls");
}