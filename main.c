//******************************** main ****************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : main.c
// Summary : Store and update device information using a linked list and a 
//           binary file.
// Note    : None
// Author  : Surya Santhosh
// Day     : 14/July/2025
//******************************************************************************

//**************************** Include Files ***********************************
#include "commonHeader.h"
#include "devicelog.h"
#include "fileOperation.h"
#include "memmoryHandle.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************

//*****************************.mainFunction.***********************************
// Purpose : Store and access device information using a linked list and 
//           binary file.Supports add, search, delete, and display operations.
// Inputs  : none
// Outputs : none
// Return  : 0
// Notes   : None
//******************************************************************************
int main()
{
    NODE *pstHead = NULL;
    FILE *pstFile = NULL;

    if (true != devicelogManager(&pstHead, &pstFile))
    {
        printf("Device Manger failed.");
    }

    return 0;
}

// EOF