//******************************* common ***************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//****************************************************************************** 
// 
// Summary : Typedefs are included.
// Note    : None
// 
//******************************************************************************
#ifndef COMMON_H
#define COMMON_H 

//**************************** Include Files ***********************************
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>

//**************************** Global Types ************************************
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef unsigned long uint32;
typedef char int8;
typedef signed short int16;

//************************* Global Constants ***********************************
#define MAX_CHAR_SIZE         (20)
#define TOTAL_OPERATIONS      (4)
#define TOTAL_STATE           (3)
#define UID_INITIAL_VALUE     (1)
#define READ_COUNT            (1)
#define WRITE_COUNT           (1)
#define NULL_CHARACTER        ('\0')
#define NEWLINE_CHARACTER     ('\n')
#define STATE_DISABLED        ("DISABLED")
#define STATE_NOT_CONNECTED   ("NOT_CONNECTED")
#define STATE_RUNNING         ("RUNNING")
#define WRITE_MODE            ("wb")
#define READ_MODE             ("rb")
#define APPEND_MODE           ("ab")
#define BIN_FILENAME          ("task.bin")
#define UID_FILENAME          ("UID.txt")

//************************* Global Variables *********************************** 

//************************* Forward Declarations *******************************  

//************************ Inline Method Implementations *********************** 

#endif 

// COMMON_H 
// EOF