//******************************** DeviceLog ***********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : DeviceLog.c
// Summary : Store and update device information using a linked list and a 
//           binary file.
// Note    : None
// Author  : Surya Santhosh
// Date    : 15/July/2024
//******************************************************************************

//******************************* Include Files ********************************
#include "devicelog.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************
static bool devicelogAddToList(NODE **ppstHead, DEVICE_INFO stDeviceInfo);
static bool devicelogGetDeviceInfo(NODE **ppstHead);
static bool devicelogFileUpdate(NODE **ppstHead, FILE **pstFile);
static bool devicelogGetNextUID(uint16 *punUID);
static bool devicelogIsDeviceIDExist(NODE *pstHead, uint8 ucDeviceID);
static bool devicelogGetDeviceDetails(DEVICE_INFO *pstDeviceInfo);

//**************************.devicelogReadFromFile.*****************************
// Purpose : Read device information from the binary file and store it in a 
//           linked list.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogReadFromFile(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    int8 cSize = sizeof(DEVICE_INFO);
    int8 cCount = 1;
    int8 *cFileName = "task.bin";
    int8 *cMode = "rb";
    DEVICE_INFO stDeviceInfo;

    if ((NULL != ppstHead) && (NULL != ppstFile))
    {
        if (true == fileOperationOpen(ppstFile, cFileName, cMode))
        {
            while (true == fileOperationFread((int8 *)&stDeviceInfo, cSize, 
                                              cCount, *ppstFile))
            {
                if (true != devicelogAddToList(ppstHead, stDeviceInfo))
                {
                    printf("\nNo data exists.\n");
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

//************************.devicelogAddToList.**********************************
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
    NODE* pstNewNode = (NODE*)malloc(sizeof(NODE));

    if (NULL != ppstHead)
    {
        if (pstNewNode != NULL)
        {
            pstNewNode->stDeviceInfo = stDeviceInfo;
            pstNewNode->pstNext = *ppstHead;
            *ppstHead = pstNewNode;

            blResult = true;
        }
    }

    return blResult;
}

//************************.devicelogGetDeviceDetails.***************************
// Purpose : Get device information from user and store it in a linked list.
// Inputs  : pstDeviceInfo - Structure containing device information.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogGetDeviceDetails(DEVICE_INFO *pstDeviceInfo)
{
    int8 *pState[] = {STATE_DISABLED, STATE_NOT_CONNECTED, STATE_RUNNING};
    uint8 ucStateInput = 0;
    bool blResult = false;

    if (NULL != pstDeviceInfo)
    {
        printf("Enter VentorID : ");
        scanf("%hu", &pstDeviceInfo->unVentorID);
        printf("Enter Name : ");
        scanf("%s", pstDeviceInfo->ucName);
        printf("Enter State(0: Disabled, 1: Not Connected, 2: Running): ");
        scanf("%hhd", &ucStateInput);
        if (ucStateInput > 2)
        {
            printf("Invalid state input. Setting to Disabled.\n");
            ucStateInput = 0;
        }
        strcpy(pstDeviceInfo->ucState, pState[ucStateInput]);
        blResult = true;
    }

    return blResult;
}

//************************.devicelogIsDeviceIDExist.***************************
// Purpose : Get device information from user and store it in a linked list.
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

    while (pstCurrent != NULL)
    {
        if (pstCurrent->stDeviceInfo.unDeviceID == ucDeviceID)
        {
            blResult = true;
        }
        pstCurrent = pstCurrent->pstNext;
    }
    return blResult;
}

//************************.devicelogGetDeviceInfo.******************************
// Purpose : Write the linked list data to the binary file.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogGetDeviceInfo(NODE **ppstHead)
{
    bool blResult = false;
    uint8 ucNewDeviceID = 0;
    uint8 ucNumberofDevices = 0;
    uint8 ucIndex = 0;
    DEVICE_INFO stDeviceInfo;

    if (NULL != ppstHead)
    {
        printf("\nNumber of devices to enter : ");
        scanf("%hhd", &ucNumberofDevices);

        for (ucIndex; ucIndex < ucNumberofDevices; ucIndex++)
        {
            if (true == devicelogGetNextUID(&stDeviceInfo.unUID))
            {
                printf("\nDevice details\n");
                printf("\nEnter DeviceID : ");
                scanf("%hhu", &ucNewDeviceID);

                if (true == devicelogIsDeviceIDExist(*ppstHead, ucNewDeviceID))
                {
                    printf("\nAlready exist.\n");

                    blResult = true;
                    continue;
                }
            }

            stDeviceInfo.unDeviceID = ucNewDeviceID;

            if (true == devicelogGetDeviceDetails(&stDeviceInfo))
            {
                if (true == devicelogAddToList(ppstHead, stDeviceInfo))
                {
                    blResult = true;
                }
            }
        }
    }

    return blResult;
}

//**************************.devicelogFileUpdate.*******************************
// Purpose : Write the linked list data to the binary file.
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
    int8 *cFileName = "task.bin";
    int8 *cMode = "wb";
    int8 cSize = sizeof(DEVICE_INFO);
    int8 cCount = 1;

    if (true == fileOperationOpen(ppstFile, cFileName, cMode))
    {
        if ((NULL != *ppstHead) && (NULL != *ppstFile))
        {
            while (pstcurrent != NULL)
            {
                if (true == fileOperationWrite(cSize, cCount, *ppstFile,
                                           (int8 *)&(pstcurrent->stDeviceInfo)))
                {
                    pstcurrent = pstcurrent->pstNext;
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

//****************************.devicelogAddNew.*********************************
// Purpose : Add new device information to the linked list and update the binary
//           file.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           pstFile  - Pointer to the binary file to update the data.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogAddNew(NODE **ppstHead, FILE **pstFile)
{
    bool blResult = false;

    if ((NULL != ppstHead) && (NULL != pstFile))
    {
        if (true == devicelogGetDeviceInfo(ppstHead) && 
            true == devicelogFileUpdate(ppstHead,pstFile))
        {
            blResult = true;
        }
    }

    return blResult;
}

//************************.devicelogSearchFromList.*****************************
// Purpose : Search for a device in the linked list using the Device ID.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogSearchFromList(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    uint8 ucNumberofDevices = 0;
    uint8 ucIndex = 0;
    uint8 ucdataFound = 0; 
    uint16 unSearchDeviceID = 0;

    if ((NULL != ppstHead) && (NULL != ppstFile))
    {
        printf("\nEnter the number of Devices to search : ");
        scanf("%hhd",&ucNumberofDevices);

        for (ucIndex; ucIndex < ucNumberofDevices; ucIndex++)
        {
            NODE *pstCurrent = *ppstHead;
            ucdataFound = 0;

            printf("\nEnter the DeviceID : ");
            scanf("%hu", &unSearchDeviceID);

            while (pstCurrent != NULL)
            {
                if (pstCurrent->stDeviceInfo.unDeviceID == unSearchDeviceID)
                {
                    printf("\n***Device List*\n\n");
                    printf("UID : %hu | DeviceID : %hu | VentorID : %hu "
                           "| Name : %s | State : %s\n", 
                           pstCurrent->stDeviceInfo.unUID, 
                           pstCurrent->stDeviceInfo.unDeviceID, 
                           pstCurrent->stDeviceInfo.unVentorID, 
                           pstCurrent->stDeviceInfo.ucName, 
                           pstCurrent->stDeviceInfo.ucState);

                    blResult = true;
                    ucdataFound = 1; 
                    break;
                }

                pstCurrent = pstCurrent->pstNext;
            }
            if (0 == ucdataFound)
            {
                printf("\nDevice not found.\n");
            }
        }
    }

    return blResult;
}

//************************.devicelogDeleteFromList.*****************************
// Purpose : Delete a device from the linked list using the Device ID.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogDeleteFromList(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    uint8 ucNumberofDevices = 0;
    uint8 ucIndex = 0;
    uint16 unDeleteDeviceID = 0;
    uint8 ucdataFound = 0; 

    if (NULL != ppstHead && NULL != ppstFile)
    {
        printf("\nEnter the number of Devices to delete : ");
        scanf("%hhd",&ucNumberofDevices);

        for (ucIndex; ucIndex < ucNumberofDevices; ucIndex++)
        {
            NODE *pstCurrent = *ppstHead; 
            NODE *pstPrevious = NULL;
            ucdataFound = 0; 

            printf("\nEnter the DeviceID : ");
            scanf("%hu",&unDeleteDeviceID);

            while (NULL != pstCurrent)
            {
                if (pstCurrent->stDeviceInfo.unDeviceID == unDeleteDeviceID)
                {
                    ucdataFound = 1; 

                    if (NULL == pstPrevious)
                    {
                        *ppstHead = pstCurrent->pstNext;
                    }   
                    else
                    {
                        pstPrevious->pstNext = pstCurrent->pstNext;
                    }

                    printf("\nDevice ID : %hu deleted successfully.", 
                           unDeleteDeviceID);

                    break;
                }

                pstPrevious = pstCurrent;
                pstCurrent = pstCurrent->pstNext;
            }

            if (0 == ucdataFound)
            {
                printf("\nDevice not found.");
                
                blResult = true;
            }
            else if(true == devicelogFileUpdate(ppstHead,ppstFile))
            {
                blResult = true;
            }
            else
            {
                printf("\nThe file doenot exists.");
            }
        }
    }

    return blResult;
}

//************************.devicelogPrintAllDevices.****************************
// Purpose : Display all device datas stored in the binary file.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogPrintAllDevices(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    uint8 ucdataFound = 0;
    int8 *cFileName = "task.bin";
    int8 *cMode = "rb";
    DEVICE_INFO stDeviceInfo;

    if (true == fileOperationOpen(ppstFile, cFileName, cMode))
    {
        if (*ppstFile != NULL)
        {
            printf("\n Device List \n");

            while (1 == fread(&stDeviceInfo, sizeof(DEVICE_INFO), 1, *ppstFile))
            {
                printf("UID : %hu | DeviceID : %hu | VentorID : %hu "
                    "| Name : %s | State : %s\n", stDeviceInfo.unUID, 
                    stDeviceInfo.unDeviceID, stDeviceInfo.unVentorID, 
                    stDeviceInfo.ucName, stDeviceInfo.ucState);

                ucdataFound = 1;
            }

            fileOperationClose(ppstFile);

            if (1 == ucdataFound)
            {
                blResult = true;
            } 
        }
    }

    return blResult;
}

//***************************.devicelogFreeList.********************************
// Purpose : Free all nodes in the linked list.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogFreeList(NODE **ppstHead)
{
    bool blResult = false;
    NODE *pstCurrent = *ppstHead;
    NODE *pstTemp = NULL;

    if (NULL != ppstHead)
    {
        while (NULL != pstCurrent)
        {
            pstTemp = pstCurrent->pstNext;
            free(pstCurrent);
            pstCurrent = pstTemp;
        }

        *ppstHead = NULL;
        blResult = true;
    }
    return blResult;
}

//*************************.devicelogGetNextUID.********************************
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
    // File storing the last used UID.
    const char *cFileName = "uid.txt"; 
    const char *cModeRead = "rb";
    const char *cModeWrite = "wb";
    int8 cSize = sizeof(uint16);
    int8 cCount = 1;

    if (punUID == NULL)
    {
        return false;
    }

    if (true == fileOperationOpen(&pstUIDFile, (int8 *)cFileName, 
                                  (int8 *)cModeRead))
    {
        if (true == fileOperationFread((int8 *)punUID, cSize, cCount, 
                                       pstUIDFile))
        {
            // Increment UID if successfully read
            (*punUID)++;
        }
        else
        {
            // If read fails, start from UID = 1.
            *punUID = 1;
        }

        fileOperationClose(&pstUIDFile);
    }
    else
    {
        // If file doesn't exist, start from UID = 1.
        *punUID = 1;
    }

    if (true == fileOperationOpen(&pstUIDFile, (int8 *)cFileName, 
                                  (int8 *)cModeWrite))
    {
        if (true == fileOperationWrite((int8 *)punUID, cSize, cCount, 
                                       pstUIDFile))
        {
            blResult = true;
        }

        fileOperationClose(&pstUIDFile);
    }

    return blResult;
}

//*****************************.devicelogManager.*******************************
// Purpose : Generate the next UID.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           ppstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogManager(NODE **ppstHead, FILE **ppstFile)
{
    bool blResult = false;
    uint8 ucIndex = 0;
    uint8 ucOperation = 0;
    DEVICE_MANAGEMENT stFunctionTable[] = 
    {
        {"Add New Devices", devicelogAddNew},
        {"Search for Devices", devicelogSearchFromList},
        {"Delete devices", devicelogDeleteFromList},
        {"Display all Devices", devicelogPrintAllDevices}
    };

    if ((NULL != ppstHead) && (NULL != ppstFile))
    {
        printf("\n***Device Managment Menu*\n\n");
        for (ucIndex = 0; ucIndex < TOTAL_OPERATIONS; ucIndex++)
        {
            printf("%d : %s\n" , ucIndex, stFunctionTable[ucIndex].cMenu);
        }

        printf("\nEnter your choice : ");
        scanf("%hhd", &ucOperation);

        if (TOTAL_OPERATIONS <= ucOperation)
        {
            printf("\nInvalid option.\n");
            while(getchar() != '\n');

            blResult = true;
        }
        else if (THIRD_OPERATION == ucOperation)
        {
            if (true != devicelogPrintAllDevices(ppstHead, ppstFile))
            {
                printf("\nBin file is empty.\n");

                blResult = true;
            }
        }
        else
        {
            stFunctionTable[ucOperation].pFunction(ppstHead, ppstFile);

            blResult = true;
        }
    }

    return blResult;
}

//EOF

