//****************************** fileoperation *********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
// File    : fileoperation.c
// Summary : Wraper function for file operation such as fopen, fclose, fread, 
//           fwrite, fseek.
// Note    : None
// Author  : Surya Santhosh
// Date    : 15/July/2024
//******************************************************************************

//************************ Include Files ***************************************
#include "fileOperation.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************

//***************************.fileOperationOpen.********************************
// Purpose : To open the file.
// Inputs  : pstFile - Pointer to the binary file.
//         : pcFileName -  Name of the file to be opened.
//         : pcMode - Mode of opeation.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationOpen(FILE **ppstFile, char *pcFileName, char *pcMode)
{
    bool blResult = false;

    *ppstFile = fopen(pcFileName, pcMode);

    if (NULL == *ppstFile)
    {
        printf("Unable to open file.\n");
    }
    else
    {
        blResult = true;
    }

    return blResult;
}

//***************************.fileoperationClose.*******************************
// Purpose : To close file.
// Inputs  : ppstFile - Pointer to the binary file 
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationClose(FILE **ppstFile)
{
    bool blResult = false;

    if (NULL != *ppstFile)
    {
        if (0 != fclose(*ppstFile))
        {
            printf("Unable to closing file.\n");
        }
        else
        {
            *ppstFile = NULL;

            blResult = true;
        }
    }

    return blResult;
}

//*************************.fileoperationFseek.*********************************
// Purpose : To move the file pointer to specific location.
// Inputs  : ppstFile - Pointer to the binary file.
//         : cOffset - It is the number of bytes to offset from the position.
//         : cPosition - The position the offset started.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationFseek(FILE **ppstFile, uint8 cOffset, uint8 cPosition)
{
    bool blResult = false;

    if (NULL != ppstFile)
    {
        if (0 != fseek(*ppstFile, cOffset, cPosition))
        {
            printf("Fseek failed.\n");
        }
        else
        {
            blResult = true;
        }
    }

    return blResult;
}

//*************************.fileoperationFread.*********************************
// Purpose : To read the data from the binary file.
// Inputs  : ppstFile - Pointer to the binary file 
//         : pBuffer  - Structure containing device information.
//         : cSize - The size in bytes of each element to be read.
//         : cCount - The number of elements to read.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationFread(void *pBuffer, uint8 cSize, FILE **ppstFile)
{
    bool blResult = false;
    uint16 ucReadCount = 0;

    if (NULL != ppstFile && NULL != pBuffer)
    {
        ucReadCount = fread(pBuffer, cSize, WRITE_COUNT, *ppstFile);

        if (WRITE_COUNT == ucReadCount)
        {
            blResult = true;
        }
    }

    return blResult;
}

//**********************.fileoperationWrite.************************************
// Purpose : To write data from the linked list to binary file.
// Inputs  : pstFile - Pointer to the binary file 
//         : pBuffer  - Structure containing device information.
//         : cSize - The size in bytes of each element to be read.
//         : cCount - The number of elements to read.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationWrite(uint8 cSize, FILE *pstFile, void *pBuffer)
{
    bool blResult = false;
    uint16 ucWriteCount = 0;

    if (NULL != pstFile && NULL != pBuffer)
    {
        ucWriteCount = fwrite(pBuffer, cSize, WRITE_COUNT, pstFile);

        if (WRITE_COUNT == ucWriteCount)
        {
            blResult = true;
        }
        else
        {
            printf("Fwrite failed.\n");
        }
    }

    return blResult;
}

//*******************.fileOperationReadwithFseek********************************
// Purpose : To open binary file with read mode and reset the file pointer.
// Inputs  : pstFile - Pointer to the binary file.
//         : pcFileName -  Name of the file to be opened.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool fileOperationReadwithFseek(FILE **ppstFile, char *pcFileName)
{
    bool blResult = false;

    if (true == fileOperationOpen(ppstFile, pcFileName, READ_MODE))
    {
        if (true == fileOperationFseek(ppstFile, 0, SEEK_SET))
        {
            blResult = true;
        }
    }

    return blResult;
}


//EOF