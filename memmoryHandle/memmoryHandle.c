//****************************** memmoryHandle *********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
// File    : memmoryHandle.c
// Summary : Wraper function for memmory handle such as malloc, free.
// Note    : None
// Author  : Surya Santhosh
// Date    : 28/July/2024
//******************************************************************************

//************************ Include Files ***************************************
#include "memmoryHandle.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************

//************************.memmoryHandleAllocation.*****************************
// Purpose : Allocate dynamic memory using malloc.
// Inputs  : pstNewNode    - Pointer to the node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool memmoryHandleAllocation(NODE **pstNewNode)
{
    bool blResult = false;

    if (NULL != pstNewNode)
    {
        *pstNewNode = malloc(sizeof(NODE));

        blResult = true;
    }
    else
    {
        printf("Memmory Allocation failed.\n");
    }

    return blResult;
}

//***********************.memmoryHandleDeallocation.****************************
// Purpose : Deallocation of dynamic memmory .
// Inputs  : pstNewNode - Pointer to the node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool memmoryHandleDeallocation(NODE **pstNewNode)
{
    bool blResult = false;

    if (NULL != pstNewNode)
    {
        free(*pstNewNode);
        
        *pstNewNode = NULL;
        blResult = true;
    }

    return blResult;
}
    