#pragma once
#include "preprocess.h"

void PriceThread() // ������ �Լ�
{
    // ������ ���
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
    printf("���� : %.2lf", CC->price);
}

void CCinit(struct _CrypCur* CC, const char name[], double price, int idx) // CC �ʱ�ȭ �Լ�
{
    CC->idx = idx;
    strcpy(CC->name, name);
    CC->price = price;
}
