# DeviceLog
C based menu driven project that manages device information using a linked list 
and a binary file.Supports add, search, delete, and display operations.

## Features

The executable, object, Assembly files are in **release** and debug files are in 
**debug**.

## Prerequisites

**CMake** ≥ 3.10  
**Make**  
**GCC** (for Linux build)  


## Building with Make

### 1. Linux (Release)

$ make linux

Output:  
release/main.o  
realease/main.s  
release/devicelog.o  
realease/devicelog.s   


### 2. Linux (Debug)

$ make debug

Output:  
debug/main.o  
debug/devicelog.o  


### 5. Build All

$ make all

Builds both linux.

### 6. Clean Build Artifacts

$ make clean

Removes all files from release/ and debug/ folders.

## Building with Make

### 1. Release Build
  
$ make  


## Building with CMake

## Using gcc Compiler

Output: release/DeviceLog_gcc

### 1. Release Build
  
$ cmake -B build   
  
$ cmake --build build 


