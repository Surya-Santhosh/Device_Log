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

//**************************.devicelogReadFromFile.*****************************
// Purpose : Read device information from the binary file and store it in a 
//           linked list.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           pstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogReadFromFile(NODE **ppstHead, FILE **pstFile)
{
    bool blResult = false;

    DEVICE_INFO stDeviceInfo;

    if ((NULL != ppstHead) && (NULL != pstFile))
    {
        while(0 != fread(&stDeviceInfo, sizeof(DEVICE_INFO), 1, *pstFile))
        {
            if (true != devicelogAddToList(ppstHead, stDeviceInfo))
            {
                printf("\nNo data exists.\n");
            }
        }

        blResult = true;
    }

    return blResult;
}

//************************.devicelogAddToList.**********************************
// Purpose : Add a device record to the linked list.
// Inputs  : ppstHead      - Pointer to the head node of the linked list.
//           stDeviceInfo  - Structure containing device information..
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogAddToList(NODE **ppstHead, DEVICE_INFO stDeviceInfo)
{
    bool blResult = false;

    if (NULL != ppstHead)
    {
        NODE* pstNewNode = (NODE*)malloc(sizeof(NODE));

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

//*************************.devicelogGetDeviceInfo.*****************************
// Purpose : Get device information from user and store it in a linked list.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogGetDeviceInfo(NODE **ppstHead)
{
    //char is used for string operations.
    char *pState[] = {"DISABLED", "NOT_CONNECTED", "RUNNING"};

    bool blResult = false;
    uint8 ucStateInput = 0;
    uint8 ucdataFound = 0;
    uint8 ucNewDeviceID = 0;
    uint8 ucNumberofDevices = 0;
    uint8 ucIndex = 0;

    DEVICE_INFO stDeviceInfo;

    if (NULL != ppstHead)
    {
        printf("\nNumber of devices to enter : ");
        scanf("%hhd",&ucNumberofDevices);

        for (ucIndex = 0; ucIndex < ucNumberofDevices; ucIndex++)
        {
            if (true == devicelogGetNextUID(&stDeviceInfo.unUID))
            {
                printf("\nDevice details\n");
                printf("\nEnter DeviceID : ");
                scanf("%hhu", &ucNewDeviceID);

                NODE *pstCurrent = *ppstHead;

                while (NULL != pstCurrent)
                {
                    if (pstCurrent->stDeviceInfo.unDeviceID == ucNewDeviceID)
                    {
                        ucdataFound = 1;
                    }

                    pstCurrent = pstCurrent->pstNext;
                }

                if (1 == ucdataFound)
                {
                    printf("\nAlready exist.\n");

                    blResult = true;
                }
                else
                {
                    stDeviceInfo.unDeviceID = ucNewDeviceID;
                    printf("Enter VentorID : ");
                    scanf("%hu", &stDeviceInfo.unVentorID);
                    printf("Enter Name : ");
                    scanf("%s", stDeviceInfo.ucName);
                    printf("Enter State(0: Disabled, 1: Not Connected,"
                           "2: Running): ");
                    scanf("%hhd", &ucStateInput);
                    strcpy(stDeviceInfo.ucState, pState[ucStateInput]);

                    if (true == devicelogAddToList(ppstHead, stDeviceInfo))
                    {
                        blResult = true;
                    }
                }
            }
        }
    }

    return blResult;
}

//**************************.devicelogFileUpdate.*******************************
// Purpose : Write the linked list data to the binary file.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           pstFile  - Pointer to the binary file to update the data.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
static bool devicelogFileUpdate(NODE **ppstHead, FILE **pstFile)
{
    bool blResult = false;

    *pstFile = fopen("./task.bin", "wb");

    if ((NULL != *ppstHead) && (NULL != *pstFile))
    {
        NODE *pstcurrent = *ppstHead;

        while (pstcurrent != NULL)
        {
            fwrite(&pstcurrent->stDeviceInfo, sizeof(DEVICE_INFO), 1, *pstFile);

            pstcurrent = pstcurrent->pstNext;
        }

        fclose(*pstFile);

        blResult = true;
    }

    return blResult;
}

//***********************.devicelogAddNewtotheList.*****************************
// Purpose : Add new device information to the linked list and update the binary
//           file.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           pstFile  - Pointer to the binary file to update the data.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogAddNewtotheList(NODE **ppstHead, FILE **pstFile)
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
//           pstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogSearchFromList(NODE **ppstHead, FILE **pstFile)
{
    bool blResult = false;
    uint8 ucNumberofDevices = 0;
    uint8 ucIndex = 0;

    if (NULL != ppstHead && NULL != pstFile)
    {
        printf("\nEnter the number of Devices to search : ");
        scanf("%hhd",&ucNumberofDevices);

        for (ucIndex = 0; ucIndex < ucNumberofDevices; ucIndex++)
        {
            uint16 unSearchDeviceID = 0;

            printf("\nEnter the DeviceID : ");
            scanf("%hu", &unSearchDeviceID);

            NODE *pstCurrent = *ppstHead;

            while (pstCurrent != NULL)
            {
                if (pstCurrent->stDeviceInfo.unDeviceID == unSearchDeviceID)
                {
                    printf("\n****Device List****\n\n");
                    printf("UID : %hu | DeviceID : %hu | VentorID : %hu "
                           "| Name : %s | State : %s\n", 
                           pstCurrent->stDeviceInfo.unUID, 
                           pstCurrent->stDeviceInfo.unDeviceID, 
                           pstCurrent->stDeviceInfo.unVentorID, 
                           pstCurrent->stDeviceInfo.ucName, 
                           pstCurrent->stDeviceInfo.ucState);

                    blResult = true;
                    break;
                }

                pstCurrent = pstCurrent->pstNext;
            }
        }
    }

    return blResult;
}

//************************.devicelogDeleteFromList.*****************************
// Purpose : Delete a device from the linked list using the Device ID.
// Inputs  : ppstHead - Pointer to the head node of the linked list.
//           pstFile  - Pointer to the binary file.
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogDeleteFromList(NODE **ppstHead, FILE **pstFile)
{
    bool blResult = false;
    uint8 ucNumberofDevices = 0;
    uint8 ucIndex = 0;

    if (NULL != ppstHead && NULL != pstFile)
    {
        printf("\nEnter the number of Devices to delete : ");
        scanf("%hhd",&ucNumberofDevices);

        for (ucIndex = 0; ucIndex < ucNumberofDevices; ucIndex++)
        {
            uint16 unDeleteDeviceID = 0;
            uint8 ucFlag = 0;

            printf("\nEnter the DeviceID : ");
            scanf("%hd",&unDeleteDeviceID);

            NODE *pstCurrent = *ppstHead;
            NODE *pstPrevious = NULL;

            while (NULL != pstCurrent)
            {
                if (pstCurrent->stDeviceInfo.unDeviceID == unDeleteDeviceID)
                {
                    ucFlag = 1;

                    if (NULL == pstPrevious)
                    {
                        *ppstHead = pstCurrent->pstNext;
                    }   
                    else
                    {
                        pstPrevious->pstNext = pstCurrent->pstNext;
                    }

                    printf("\nDevice ID : %hd deleted successfully.", 
                           unDeleteDeviceID);

                    break;
                }

                pstPrevious = pstCurrent;
                pstCurrent = pstCurrent->pstNext;
            }

            if (ucFlag == 0)
            {
                printf("\nDevice not found.");

                blResult = true;
            }
            else if(true == devicelogFileUpdate(ppstHead,pstFile))
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
// Inputs  : pstFile - Pointer to the binary file 
// Outputs : None
// Return  : blResult
// Notes   : None
//******************************************************************************
bool devicelogPrintAllDevices(FILE **pstFile)
{
    bool blResult = false;
    DEVICE_INFO stDeviceInfo;

    *pstFile = fopen("./task.bin", "rb");

    if (*pstFile != NULL)
    {
        uint8 ucdataFound = 0;

        printf("\n ****Device List**** \n\n");

        while (1 == fread(&stDeviceInfo, sizeof(DEVICE_INFO), 1, *pstFile))
        {
            printf("UID : %hu | DeviceID : %hu | VentorID : %hu "
                   "| Name : %s | State : %s\n", stDeviceInfo.unUID, 
                   stDeviceInfo.unDeviceID, stDeviceInfo.unVentorID, 
                   stDeviceInfo.ucName, stDeviceInfo.ucState);

            ucdataFound = 1;
        }

        fclose(*pstFile);

        if (1 == ucdataFound)
        {
            blResult = true;
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

    if (NULL != ppstHead)
    {
        NODE *pstCurrent = *ppstHead;
        NODE *pstTemp = NULL;

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

    if (NULL != punUID)
    {
        FILE *pstUIDFile = fopen("./uid.txt", "rb");

        if (NULL != pstUIDFile)
        {
            if (1 == fread(punUID, sizeof(uint16), 1, pstUIDFile))
            {
                (*punUID)++;
            }
            else
            {
                *punUID = 1; 
            }

            fclose(pstUIDFile);
        }
        else
        {
            *punUID = 1; 
        }

        pstUIDFile = fopen("./uid.txt", "wb");

        if (NULL != pstUIDFile)
        {
            if (1 == fwrite(punUID, sizeof(uint16), 1, pstUIDFile))
            {
                blResult = true;
            }

            fclose(pstUIDFile);
        }
    }

    return blResult;
}

//EOF