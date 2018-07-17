#include <stdio.h>
#include "library.h"
#include <windows.h>


int main() {

    HINSTANCE hLib = LoadLibrary("Lib/libList.dll");
    if(hLib == 0)
    {
        return 0;
    }
    CreateIntList CreateIntList = GetProcAddress(hLib,"CreateIntList");
    if(CreateIntList == 0)
    {
        return 0;
    }
    IntList_AddItem IntList_AddItem = GetProcAddress(hLib,"IntList_AddItem");
    if(IntList_AddItem == 0)
    {
        return 0;
    }
    IntList_GetNum IntList_GetNum = GetProcAddress(hLib,"IntList_GetNum");
    if(IntList_GetNum == 0)
    {
        return 0;
    }
    IntList* List = CreateIntList();
    IntList_AddItem(List,13);
    printf("%d\n",IntList_GetNum(List,0));

    //IntList* List = CreateIntList();
    //IntList_AddItem(List,14);
    //printf("%d\n",IntList_GetNum(List,0));

    printf("Hello, World!\n");
    return 0;
}