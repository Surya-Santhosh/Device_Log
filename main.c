//********************************** main **************************************
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

//******************************* Include Files ********************************
#include "common.h"
#include "devicelog.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************

//******************************.mainFunction.**********************************
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

    uint8 ucChoice = 'y';
    uint8 ucOperation = 0;

    pstFile = fopen("./task.bin", "ab");

    if (pstFile != NULL)
    {
        if (0 == fseek(pstFile, 0, SEEK_SET))
        {
            if (true == devicelogReadFromFile(&pstHead, &pstFile))
            {
                fclose(pstFile);

                Function FunctionTable[] = { devicelogAddNewtotheList, 
                                             devicelogSearchFromList, 
                                             devicelogDeleteFromList };

                while ((ucChoice == 'y') || (ucChoice == 'Y'))
                {
                    printf("\n****Device Managment Menu****\n");
                    printf("\n0 : Add New Devices"
                           "\n1 : Search for Devices"
                           "\n2 : Delete devices"
                           "\n3 : Display all Devices\n");
                    printf("\nEnter your choice : ");
                    scanf("%hhd", &ucOperation);

                    if (TOTAL_OPERATIONS < ucOperation)
                    {
                        printf("\nInvalid option.\n");
                        while(getchar() != '\n');
                        continue;
                    }
                    else if (THIRD_OPERATION == ucOperation)
                    {
                        if (true != devicelogPrintAllDevices(&pstFile))
                        {
                            printf("\nBin file is empty.\n");
                        }
                    }
                    else
                    {
                        FunctionTable[ucOperation](&pstHead, &pstFile);
                    }

                    printf("\nIf you want to continue (Y/N): ");
                    while(getchar() != '\n');
                    scanf("%c", &ucChoice);

                    printf("\x1b[H"); // Move Cursor to top-left
                    printf("\x1b[J"); // clear screen

                }
            }
        }
    }

    devicelogFreeList (&pstHead);

    return 0;
}
// EOF
