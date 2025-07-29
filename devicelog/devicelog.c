//******************************* DeviceLog ************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : DeviceLog.c
// Summary : Store and update device information using a linked list and 
//           binary file.
// Note    : None
// Author  : Surya Santhosh
// Date    : 15/July/2024
//******************************************************************************

//***************************** Include Files **********************************
#include "devicelog.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************
static bool devicelogReadFromFile(NODE **ppstHead, FILE **ppstFile);
static bool devicelogGetDeviceInfo(NODE **ppstHead);
static bool devicelogAddNew(NODE **ppstHead, FILE **ppstFile);
static bool devicelogSearchFromList(NODE **ppstHead, FILE **ppstFile);
static bool devicelogDeleteFromList(NODE **ppstHead, FILE **ppstFile);
static bool devicelogPrintAllDevices(NODE **ppstHead, FILE **ppstFile);
static bool devicelogFreeList(NODE **ppstHead);
static bool devicelogHandleUserOptions(NODE **ppstHead, FILE **ppstFile);
static bool devicelogAddToList(NODE **ppstHead, DEVICE_INFO stDeviceInfo);
static bool devicelogGetDeviceInfo(NODE **ppstHead);
static bool devicelogFileUpdate(NODE **ppstHead, FILE **pstFile);
static bool devicelogGetNextUID(uint16 *punUID);
static bool devicelogIsDeviceIDExist(NODE *pstHead, uint8 ucDeviceID);
static bool devicelogGetDeviceFromUser(DEVICE_INFO *pstDeviceInfo);

//**************************.devicelogReadFromFile.*****************************
// Purpose : Read device information from the binary file and store it in a 
//           linked list.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogManager(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;

    if (true == devicelogReadFromFile(ppstHead, ppstFile))
    {
        if (true == devicelogHandleUserOptions(ppstHead, ppstFile))
        {
            blResult = true;
        }
    }

    if (true != devicelogFreeList(ppstHead))
    {
        printf("Failed to free device list.");
    }

    return blResult;
}

//**************************.devicelogReadFromFile.*****************************
// Purpose : Read device information from the binary file and store it in a 
//           linked list.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogReadFromFile(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    uint8 cSize = sizeof(DEVICE_INFO);
    DEVICE_INFO stDeviceInfo;
    struct stat stFile;

    if ((NULL != ppstHead) && (NULL != ppstFile))
    {
        if (0 == stat(BIN_FILENAME, &stFile))
        {
            if (true == fileOperationOpen(ppstFile, BIN_FILENAME, READ_MODE))
            {
                while (true == fileOperationFread(&stDeviceInfo, cSize, 
                                                  ppstFile))
                {
                    if (true != devicelogAddToList(ppstHead, stDeviceInfo))
                    {
                        printf("\nFailed to add device to list.\n");
                    }
                }

                if (true == fileOperationClose(ppstFile))
                {
                    blResult = true;
                }
            }
        }
        else
        {
            if (true == fileOperationOpen(ppstFile, BIN_FILENAME, WRITE_MODE))
            {
                if (true == fileOperationClose(ppstFile))
                {
                    blResult = true;
                }
            }
        }
    }

    return blResult;
}

//**************************.devicelogAddToList.********************************
// Purpose : Add a device record to the linked list.
// Inputs  : ppstHead      - Pointer to the head node of the linked list.
//           stDeviceInfo  - Structure containing device information.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogAddToList(NODE **ppstHead, DEVICE_INFO stDeviceInfo)
{
    bool blResult = false;
    NODE* pstNewNode = NULL;

    if (NULL != ppstHead)
    {
        if (true == memmoryHandleAllocation(&pstNewNode))
        {
            if (pstNewNode != NULL)
            {
                pstNewNode->stDeviceInfo = stDeviceInfo;
                pstNewNode->pstNext = *ppstHead;
                *ppstHead = pstNewNode;

                blResult = true;
            }
        }
    }

    return blResult;
}

//************************.devicelogGetDeviceFromUser.**************************
// Purpose : Collect device information from user.
// Inputs  : pstDeviceInfo - Structure containing device information.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogGetDeviceFromUser(DEVICE_INFO *pstDeviceInfo)
{
    int8 *pState[] = {STATE_DISABLED, STATE_NOT_CONNECTED, STATE_RUNNING};
    uint8 ucStateInput = 0;
    uint8 ucFlagVentorID = 0;
    uint8 ucFlagState = 0;
    bool blResult = false;

    if (NULL != pstDeviceInfo)
    {
        printf("Enter VendorID : ");

        ucFlagVentorID = scanf("%hhu", &pstDeviceInfo->unVendorID);

        while (NEWLINE_CHARACTER != getchar());

        if (0 == ucFlagVentorID)
        {
            printf("\n\tInvalid VentorID.\n");
        }
        else
        {
            printf("Enter Name : ");
            fgets(pstDeviceInfo->ucName, MAX_CHAR_SIZE, stdin);

            // Remove trailing newline with null character.
            if (pstDeviceInfo->ucName[strlen(pstDeviceInfo->ucName)-1] == 
                NEWLINE_CHARACTER)
            {
                pstDeviceInfo->ucName[strlen(pstDeviceInfo->ucName)-1] = 
                NULL_CHARACTER;
            }

            printf("Enter State(0: Disabled, 1: Not Connected, 2: Running): ");

            ucFlagState = scanf("%hhd", &ucStateInput);

            while (NEWLINE_CHARACTER != getchar());

            if ((0 == ucFlagState ) || (TOTAL_STATE <= ucStateInput))
            {
                printf("\n\tInvalid state input.\n");
            }
            else
            {
                strcpy(pstDeviceInfo->ucState, pState[ucStateInput]);

                blResult = true;
            }
        }
    }

    return blResult;
}

//**********************.devicelogIsDeviceIDExist.******************************
// Purpose : Check whether DeviceID is exists in a linked list.
// Inputs  : pstHead - Pointer to the head node of the linked list.
//         : ucDeviceID - Device ID.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogIsDeviceIDExist(NODE *pstHead, uint8 ucDeviceID)
{
    NODE *pstCurrent = pstHead;
    bool blResult = false;

    while (NULL != pstCurrent)
    {
        if (pstCurrent->stDeviceInfo.unDeviceID == ucDeviceID)
        {
            blResult = true;
        }

        pstCurrent = pstCurrent->pstNext;
    }

    return blResult;
}

//***********************.devicelogGetDeviceInfo.*******************************
// Purpose : collect deviceinformation from user and added to linked list.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogGetDeviceInfo(NODE **ppstHead)
{
    bool blResult = false;
    uint8 ucNewDeviceID = 0;
    uint8 ucNumberofDevices = 0;
    uint8 ucIndex = 0;
    uint8 ucFlag = 0;
    DEVICE_INFO stDeviceInfo;

    if (NULL != ppstHead)
    {
        printf("\nNumber of devices to enter : ");
        scanf("%hhu", &ucNumberofDevices);

        for (ucIndex = 0; ucIndex < ucNumberofDevices; ucIndex++)
        {
            if (true == devicelogGetNextUID(&stDeviceInfo.unUID))
            {
                printf("\nDevice details\n");
                printf("\nEnter DeviceID : ");

                ucFlag = scanf("%hhu", &ucNewDeviceID);

                while (NEWLINE_CHARACTER != getchar());

                if (0 == ucFlag)
                {
                    printf("\n\tInvalid DeviceID.\n");

                    blResult = true;
                }
                else if (true == devicelogIsDeviceIDExist(*ppstHead, 
                                                          ucNewDeviceID))
                {
                    printf("\n\tAlready exist.\n");

                    blResult = true;
                }
                else
                {
                    stDeviceInfo.unDeviceID = ucNewDeviceID;

                    if ((true == devicelogGetDeviceFromUser(&stDeviceInfo)) && 
                        (true == devicelogAddToList(ppstHead, stDeviceInfo)))
                    {
                        blResult = true;
                    }
                }
            }
        }
    }

    return blResult;
}

//***************************.devicelogFileUpdate.******************************
// Purpose : Update binary file using data from the linked list.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file to update the data.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogFileUpdate(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    NODE *pstcurrent = *ppstHead;
    int8 cSize = sizeof(DEVICE_INFO);

    if ((NULL != ppstHead) && (NULL != ppstFile))
    {
        if (true == fileOperationAppendandWrite(ppstFile, BIN_FILENAME))
        {
            while (pstcurrent != NULL)
            {
                if (true == fileOperationFseek(ppstFile, 0, SEEK_END))
                {
                    if (true == fileOperationWrite(cSize, *ppstFile, 
                                                   pstcurrent))
                    {
                        pstcurrent = pstcurrent->pstNext;
                    }
                }
            }

            if (true == fileOperationClose(ppstFile))
            {
                blResult = true;
            }
        }
    }

    return blResult;
}

//**************************.devicelogAddNew.***********************************
// Purpose : Add new device information to the linked list and update the binary
//           file.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           pstFile  - Pointer to the binary file to update the data.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogAddNew(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;

    if ((NULL != ppstHead) && (NULL != ppstFile))
    {
        if (true == devicelogGetDeviceInfo(ppstHead) && 
            true == devicelogFileUpdate(ppstHead,ppstFile))
        {
            blResult = true;
        }
    }

    return blResult;
}

//***********************.devicelogSearchFromList.******************************
// Purpose : Search for a device in the linked list using the Device ID.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogSearchFromList(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    uint8 ucNumberofDevices = 0;
    uint8 ucIndex = 0;
    uint8 ucdataFound = 0; 
    uint8 unSearchDeviceID = 0;
    uint8 ucFlag = 0;
    NODE *pstCurrent = NULL;

    if ((NULL != ppstHead) && (NULL != ppstFile))
    {
        printf("\nEnter the number of Devices to search : ");
        scanf("%hhd", &ucNumberofDevices);

        for (ucIndex = 0; ucIndex < ucNumberofDevices; ucIndex++)
        {
            pstCurrent = *ppstHead;
            ucdataFound = 0;

            printf("\nEnter DeviceID : ");
            ucFlag = scanf("%hhu", &unSearchDeviceID);

            while ('\n' != getchar());
        
            if (0 == ucFlag)
            {
                printf("\n\tInvalid DeviceID.\n");

                blResult = true;

                continue;
            }

            while (pstCurrent != NULL)
            {
                if (pstCurrent->stDeviceInfo.unDeviceID == unSearchDeviceID)
                {
                    printf("\n******Device List******\n\n");
                    printf("UID : %hu | DeviceID : %hu | VendorID : %hu "
                           "| Name : %s | State : %s\n", 
                           pstCurrent->stDeviceInfo.unUID, 
                           pstCurrent->stDeviceInfo.unDeviceID, 
                           pstCurrent->stDeviceInfo.unVendorID, 
                           pstCurrent->stDeviceInfo.ucName, 
                           pstCurrent->stDeviceInfo.ucState);

                    blResult = true;
                    ucdataFound++; 

                    break;
                }

                pstCurrent = pstCurrent->pstNext;
            }

            if (0 == ucdataFound)
            {
                printf("\n\tDevice not found.\n");
            }
        }
    }

    return blResult;
}

//***********************.devicelogDeleteFromList.******************************
// Purpose : Delete a device from the linked list using the Device ID.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogDeleteFromList(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    uint8 ucNumberofDevices = 0;
    uint8 ucIndex = 0;
    uint8 unDeleteDeviceID = 0;
    uint8 ucdataFound = 0; 
    uint8 ucFlag = 0;
    NODE *pstCurrent = NULL;
    NODE *pstPrevious = NULL;

    if (NULL != ppstHead && NULL != ppstFile)
    {
        printf("\nEnter the number of Devices to delete : ");
        scanf("%hhd", &ucNumberofDevices);

        for (ucIndex = 0; ucIndex < ucNumberofDevices; ucIndex++)
        {
            pstCurrent = *ppstHead; 
            pstPrevious = NULL;
            ucdataFound = 0; 

            printf("\nEnter DeviceID : ");
            ucFlag = scanf("%hhu", &unDeleteDeviceID);

            while (NEWLINE_CHARACTER != getchar());
        
            if (0 == ucFlag)
            {
                printf("\n\tInvalid DeviceID.\n");

                blResult = true;
                
                continue;
            }

            while (NULL != pstCurrent)
            {
                if (pstCurrent->stDeviceInfo.unDeviceID == unDeleteDeviceID)
                {
                    ucdataFound++; 

                    if (NULL == pstPrevious)
                    {
                        *ppstHead = pstCurrent->pstNext;

                        if (true != memmoryHandleDeallocation(&pstCurrent))
                        {
                            printf("Memmory Deallocation failed.\n");
                        }
                    }   
                    else
                    {
                        pstPrevious->pstNext = pstCurrent->pstNext;

                        if (true != memmoryHandleDeallocation(&pstCurrent))
                        {
                            printf("Memmory Deallocation failed.\n");
                        }
                    }

                    printf("\n\tDevice ID : %hu deleted successfully.\n", 
                           unDeleteDeviceID);

                    break;
                }

                pstPrevious = pstCurrent;
                pstCurrent = pstCurrent->pstNext;
            }

            if (0 == ucdataFound)
            {
                printf("\n\tDevice not found.\n");
                
                blResult = true;
            }
            else if(true == devicelogFileUpdate(ppstHead,ppstFile))
            {
                blResult = true;
            }
            else
            {
                printf("\nFile doenot exists.");
            }
        }
    }

    return blResult;
}

//*********************.devicelogPrintAllDevices.*******************************
// Purpose : Display all device datas stored in the binary file.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogPrintAllDevices(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    int8 cSize = sizeof(DEVICE_INFO);
    DEVICE_INFO stDeviceInfo;
    uint8 ucdataFound = 0;
    (void)ppstHead;

    if (NULL != ppstFile)
    {
        if (true == fileOperationReadwithFseek(ppstFile, BIN_FILENAME))
        {
            printf("\n******Device List******\n\n");

            while (true == fileOperationFread(&stDeviceInfo, cSize, ppstFile))
            {
                printf("UID : %hu | DeviceID : %hu | VendorID : %hu "
                       "| Name : %s | State : %s\n", stDeviceInfo.unUID,
                       stDeviceInfo.unDeviceID, stDeviceInfo.unVendorID,
                       stDeviceInfo.ucName, stDeviceInfo.ucState);

                ucdataFound++;
                blResult = true;
            }

            if (0 == ucdataFound)
            {
                printf("\tBin file is empty.\n");
            }

            if (true == fileOperationClose(ppstFile))
            {
                // Dummy case.
            }
        }
    }

    return blResult;
}

//***********************.devicelogFreeList.************************************
// Purpose : Free all nodes in the linked list.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogFreeList(NODE **ppstHead)
{
    bool blResult = false;
    NODE *pstCurrent = *ppstHead;
    NODE *pstTemp = NULL;

    if (NULL != ppstHead)
    {
        while (NULL != pstCurrent)
        {
            pstTemp = pstCurrent->pstNext;

            if (true == memmoryHandleDeallocation(&pstCurrent))
            {
                pstCurrent = pstTemp;
            }
        }

        *ppstHead = NULL;
        blResult = true;
    }

    return blResult;
}

//**********************.devicelogGetNextUID.***********************************
// Purpose : Generate the next UID.
// Inputs  : punUID - Pointer to store the UID.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogGetNextUID(uint16 *punUID)
{
    bool blResult = false;
    FILE *pstUIDFile = NULL;
    int8 cSize = sizeof(uint16);
    struct stat stFile;

    if (NULL != punUID)
    {
        if (0 == stat(UID_FILENAME, &stFile))
        {
            if (true == fileOperationOpen(&pstUIDFile, UID_FILENAME, READ_MODE))
            {
                if (true == fileOperationFread(punUID, cSize, &pstUIDFile))
                {
                    // Increment UID if successfully read
                    (*punUID)++;
                }
                else
                {
                    // If read fails, start from UID = 1.
                    *punUID = UID_INITIAL_VALUE;
                }

                if (true == fileOperationClose(&pstUIDFile))
                {
                    // dummy case.
                }
            }
        }
        else
        {
            if (true == fileOperationOpen(&pstUIDFile, UID_FILENAME, 
                                          WRITE_MODE))
            {
                if (true == fileOperationClose(&pstUIDFile))
                {
                    // If file doesn't exist, start from UID = 1.
                    *punUID = UID_INITIAL_VALUE;
                }
            }
        }

        if (true == fileOperationOpen(&pstUIDFile, UID_FILENAME, WRITE_MODE))
        {
            if (true == fileOperationWrite(cSize, pstUIDFile, punUID))
            {
                if (true == fileOperationClose(&pstUIDFile))
                {
                    blResult = true;
                }
            }
        }
    }

    return blResult;
}

//**********************.devicelogHandleUserOptions.****************************
// Purpose : Display Menu driven interface to manage device informations.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogHandleUserOptions(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    uint8 ucIndex = 0;
    uint8 ucOperation = 0;
    uint8 ucFlag = 0;
    DEVICE_MANAGEMENT stMenuFunctionTable[] = 
    {
        {"Add New Devices", devicelogAddNew},
        {"Search for Devices", devicelogSearchFromList},
        {"Delete devices", devicelogDeleteFromList},
        {"Display all Devices", devicelogPrintAllDevices},
        {"Exit", NULL}
    };

    if ((NULL != ppstHead) && (NULL != ppstFile))
    {
        while (true)
        {
            ucFlag = 0;

            printf("\n******Device Management Menu******\n\n");

            for (ucIndex = 0; ucIndex <= TOTAL_OPERATIONS; ucIndex++)
            {
                printf("%d : %s\n" , ucIndex, 
                       stMenuFunctionTable[ucIndex].cMenu);
            }

            printf("\nEnter your choice : ");

            ucFlag = scanf("%hhd", &ucOperation);

            while (NEWLINE_CHARACTER != getchar());

            if (0 == ucFlag)
            {
                printf("\n\tInvalid choice.\n");

                continue;
            }

            if (TOTAL_OPERATIONS < ucOperation)
            {
                printf("\n\tInvalid option.\n");

                while(NEWLINE_CHARACTER != getchar());

                continue;
            }
            else if (TOTAL_OPERATIONS == ucOperation)
            {
                printf("Exiting Device Management.......\n");

                break;
            }
            else
            {
                stMenuFunctionTable[ucOperation].pFunction(ppstHead, ppstFile);
            }
        }

        blResult = true;
    }

    return blResult;
}

//EOF