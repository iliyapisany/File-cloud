//
// Created by ipisa on 7/13/2018.
//

#include "List.h"

List* CreateList(unsigned int ElementSize, unsigned int BlockSize)
{
    List* Result = malloc(sizeof(List));

    Result->DataEntryPoint = 0;
    Result->BlockSize = BlockSize;
    Result->ElementCount = 0;
    Result->ElementSize = ElementSize;

    return Result;
}

char AddElement(List* List, void* Element)
{
    // Try to found memory to add element
    for(unsigned int i = 0; i <= __LIST_LIB_DEFAULT_TRY_CREATING_BLOCK_COUNT; ++i)
    {
        if(i == __LIST_LIB_DEFAULT_TRY_CREATING_BLOCK_COUNT)
        {
            return 0;
        }
        if(_CheckFreeSpace(List))
        {
            break;
        }
        else
        {
            _CreateConstSizeBlock(List);
        }
    }


    // Get memory pointer to a element slot in list
    void* pElementToAdd = *((char*)_GetPage(List->ElementCount, List->ElementCount) + List->ElementCount % List->BlockSize);
    if(pElementToAdd == 0)
    {
        return 0;
    }
    /*unsigned int BlockNum = (List->ElementCount / List->BlockSize) + 1;
    void* pBlockToAdd = List->DataEntryPoint;
    for(unsigned int i = 0; i < BlockNum && *(void**)pBlockToAdd != 0;++i)
    {
        pBlockToAdd = *(void**)pBlockToAdd;
    }

    void* pElementToAdd = *(((char*)pElementToAdd) + 4 + List->ElementCount % List->BlockSize);*/



    // processing signal, when added element link isn't valid
    __p_sig_fn_t LastFunc = signal(SIGSEGV, _AddElementSignal);
    if(setjmp(AddElementJMP) == 0)
    {
        // Copy element data to slot in list
        for(unsigned int i = 0; i < List->ElementSize; ++i)
        {
            *((char*)pElementToAdd + i) = *((char*)Element + i);
        }
    }
    else
    {
        signal(SIGSEGV, LastFunc);
        return 0;
    }
    signal(SIGSEGV, LastFunc);
    return 1;
}

void* GetElement(List* List, unsigned int Num)
{
    if(Num >= List->ElementCount)
        return 0;

    __p_sig_fn_t pLastFn = signal(SIGSEGV, _BaseSignalProcessing);

    void* Result = 0;

    if(setjmp(BaseErrorProcessing) == 0)
    {
        Result = *((void**)_GetPage(List,Num) + Num % List->BlockSize);
    }
    else
    {
        signal(SIGSEGV, pLastFn);
        return 0;
    }

    signal(SIGSEGV, pLastFn);
    return Result;
}

void* _GetPage(List* List, unsigned int ElementNum)
{
    if(List->ElementCount == 0 || List->DataEntryPoint == 0)
    {
        return 0;
    }
    void* Result = List->DataEntryPoint;


    // Processing error in segmentation list
    __p_sig_fn_t pLastFn = signal(SIGSEGV, _GetPageSignal);
    if(setjmp(BaseErrorProcessing) == 0) {
        for (unsigned int i = 0; i < List->ElementCount / List->BlockSize; ++i) {
            Result = *((void **) Result);
        }
    }
    else
    {
        signal(SIGSEGV, pLastFn);
        return 0;
    }
    signal(SIGSEGV, pLastFn);



    return Result + sizeof(void*);
}

char _CheckFreeSpace(List* List)
{
    __p_sig_fn_t pLastFn = signal(SIGSEGV,_BaseSignalProcessing);
    char Result = 0;
    if(setjmp(BaseErrorProcessing) == 0)
    {
        if(List->ElementCount % List->BlockSize == 0)
        {
            if(_GetPage(List, List->ElementCount) - sizeof(void*) == 0)
            {
                Result = 1;
            }
        }
        else
        {
            Result = 1;
        }
    }

    signal(SIGSEGV, pLastFn);
    return Result;
}

void* _CreateConstSizeBlock(List* List)
{
    void* Result = 0;
}

void _AddElementSignal(int signal)
{

}