//****************************** fileoperation *********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : fileoperation.c
// Summary : Store and update device information using a linked list and a 
//           binary file.
// Note    : None
// Author  : Surya Santhosh
// Date    : 15/July/2024
//******************************************************************************

//******************************* Include Files ********************************
#include "fileoperation.h"
#include "devicelog.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************
static bool fileoperationFseek(FILE **ppstFile);

//****************************.fileoperationRead.*******************************
// Purpose : To open the file.
// Inputs  : pstFile - Pointer to the binary file.
//         : cFileName -  Name of the file to be opened.
//         : cMode - Mode of opeation.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileoperationOpen(FILE **ppstFile, int8 *cFileName, int8 *cMode)
{
    bool blResult = false;

    *ppstFile = fopen(cFileName, cMode);

    if (NULL != ppstFile)
    {
        printf("Unable to open file.");
    }
    else
    {
        blResult = true;
    }

    return blResult;
}

//****************************.fileoperationClose.******************************
// Purpose : To close file.
// Inputs  : pstFile - Pointer to the binary file 
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileoperationClose(FILE **ppstFile)
{
    bool blResult = false;

    if (NULL != ppstFile)
    {
        if (0 != fclose(*ppstFile))
        {
            printf("Unable to closing file.");
        }
        else
        {
            blResult = true;
        }
    }

    return blResult;
}

//****************************.fileoperationFseek.******************************
// Purpose : To move the file pointer to specific location.
// Inputs  : pstFile - Pointer to the binary file 
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileoperationFseek(FILE **ppstFile)
{
    bool blResult = false;

    if (NULL != ppstFile)
    {
        if (0 != fseek(*ppstFile, 0, SEEK_SET))
        {
            printf("Fseek failed.");
        }
        else
        {
            blResult = true;
        }
    }

    return blResult;
}

//****************************.fileoperationFread.******************************
// Purpose : To read the data from the binary file.
// Inputs  : pstFile - Pointer to the binary file 
//         : stDeviceInfo  - Structure containing device information.
//         : pstCurrent - Pointer to the node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileoperationFread(DEVICE_INFO *stDeviceInfo, FILE **ppstFile)
{
    bool blResult = false;

    if (NULL != ppstFile)
    {
        while (0 != fread(&stDeviceInfo, sizeof(DEVICE_INFO), 1, *ppstFile))
        {
           blResult = true;
        }
    }

    return blResult;
}

//****************************.fileoperationWrite.******************************
// Purpose : To write data from the linked list to binary file.
// Inputs  : pstFile - Pointer to the binary file.
//         : stDeviceInfo  - Structure containing device information.
//         : pstCurrent - Pointer to the node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileoperationWrite(NODE **pstcurrent, FILE **ppstFile)
{
    bool blResult = false;
    DEVICE_INFO stDeviceInfo;

    if (NULL != ppstFile && NULL != pstcurrent)
    {
        if (0 == fwrite(&pstcurrent, sizeof(DEVICE_INFO), 1, 
                        *ppstFile))
        {
            printf("Fwrite failed.");
        }
        else
        {
            blResult = true;
        }
    }

    return blResult;
}

//**************************.fileoperationCheckRead.****************************
// Purpose : To write data from the linked list to binary file.
// Inputs  : pstFile - Pointer to the binary file.
//         : stDeviceInfo  - Structure containing device information.
//         : pstCurrent - Pointer to the node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileoperationCheck(FILE **ppstFile, int8 *cFileName, int8 *cMode, 
                            NODE **ppstHead)
{
    bool blResult = false;

    if (true == fileoperationOpen(ppstFile, cFileName, cMode))
    {
        if (true == fileoperationFseek(ppstFile))
        {
            if (true == devicelogReadFromFile(ppstHead, ppstFile))
            {
                if (true == fileoperationClose(ppstFile))
                {
                    blResult = true;
                }
            }
        }
    }

    return blResult;
}
