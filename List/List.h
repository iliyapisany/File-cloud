//
// Created by ipisa on 7/13/2018.
//

#ifndef SERVER_LIST_H
#define SERVER_LIST_H

#include <malloc.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf BaseErrorProcessing;

#define LiST_LIB_DYNAMIC_BLOCK_SIZE 0
#define LIST_LIB_DEFAULT_BLOCK_SIZE 512
#define __LIST_LIB_DEFAULT_TRY_CREATING_BLOCK_COUNT 6


typedef struct{unsigned int ElementSize;unsigned int ElementCount; unsigned int BlockSize; void* DataEntryPoint;} List;

List* CreateList(unsigned int ElementSize, unsigned int BlockSize);
char AddElement(List* List,void* Element);
void* GetElement(List* List, unsigned int ElementNum);


void _CreateConstSizeBlock(List* List);
//void* _CreateVarSizeBlock(List* List, unsigned int ElementCount, unsigned int ElementSize);

char _CheckFreeSpace(List* List);


void _BaseSignalProcessing(int Signal);

void* _GetPage(List* List, unsigned int ElementNum);

#endif //SERVER_LIST_H
