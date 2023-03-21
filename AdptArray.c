#include <stdio.h>
#include "AdptArray.h"
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_
{
    int ArrSize;
    PElement *PElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printf_)
{
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    if (pArr == NULL)
        return NULL;
    pArr->ArrSize = 0;
    pArr->PElemArr = NULL;
    pArr->delFunc = delFunc_;
    pArr->copyFunc = copyFunc_;
    pArr->printFunc = printf_;
    return pArr;
}

Result SetAdptArrayAt(PAdptArray Arr, int idx, PElement pNewElem)
{
    if (Arr == NULL)
        return FAIL;
    if (idx >= Arr->ArrSize)
    {
        PElement *newpElemArr;
        if ((newpElemArr = (PElement *)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, Arr->PElemArr, (Arr->ArrSize) * sizeof(PElement));
        free(Arr->PElemArr);
        Arr->PElemArr = newpElemArr;
    }
    if (Arr->PElemArr[idx] != NULL)
    {
        Arr->delFunc((Arr->PElemArr)[idx]);
    }
    (Arr->PElemArr)[idx] = Arr->copyFunc(pNewElem);
    Arr->ArrSize = (idx >= Arr->ArrSize) ? (idx + 1) : Arr->ArrSize;
    return SUCCESS;
}

void DeleteAdptArray(PAdptArray Arr)
{
    int i;
    if (Arr == NULL)
        return;
    for (i = 0; i < Arr->ArrSize; ++i)
    {
        if (Arr->PElemArr[i] != NULL)
        {
            Arr->delFunc((Arr->PElemArr)[i]);
        }
    }
    free(Arr->PElemArr);
    free(Arr);
}

PElement GetAdptArrayAt(PAdptArray Arr, int index)
{
    if (Arr == NULL)
        return NULL;
    if (Arr->ArrSize <= index)
        return NULL;
    if (Arr->PElemArr[index] == NULL)
        return NULL;
    return Arr->copyFunc(Arr->PElemArr[index]);
}

int GetAdptArraySize(PAdptArray Arr)
{
    if (Arr == NULL)
        return -1;
    return Arr->ArrSize;
}

void PrintDB(PAdptArray Arr)
{
    if (Arr == NULL)
        return;
    for (int i = 0; i < Arr->ArrSize; i++)
    {
        if (Arr->PElemArr[i] != NULL)
        {
            Arr->printFunc(Arr->PElemArr[i]);
        }
    }
}
