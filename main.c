#include <stdio.h>
#include "List.h"
#include <windows.h>d

typedef List* CPL(unsigned char a, unsigned int b);

int main() {
    HINSTANCE hLib = LoadLibrary(TEXT("Lib/libList.dll"));
    if(hLib == 0)
    {
        printf("Error\n");
        getchar();
        return 0;
    }

    CPL* CreateList = GetProcAddress(hLib,TEXT("CreateList"));

    List* List = CreateList(0,LIST_LIB_DEFAULT_BLOCK_SIZE);
    printf("Hello, World!\n");
    return 0;
}