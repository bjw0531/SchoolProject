#include "preprocess.h"
#include "functions.h"

int age = 0;
int main()
{
    CursorView();
    InitScreen();
    InitVars();

    clock_t start = clock();

    while (1)
    {
        CursorView();
        clock_t now = clock();
        int currentage = int(now - start) / CLOCKS_PER_SEC / 2;
        if (age != currentage)
        {
            age = currentage;
            system("cls");
            VaryPrice();
        }

        PrtCCInfo(0, 1);
        gotoxy(0, 5);

        if (GetAsyncKeyState(VK_RETURN) < 0)    StartTransaction(1, 5);
        else                                    printf("동작하려면 엔터를 누르세요.");
    }
}	
