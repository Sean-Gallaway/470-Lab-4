#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_FILES 100
#define MAX_FILENAME 50
#define MAX_FILE_SIZE 1024

typedef struct {
    char filename [MAX_FILENAME];
    int size;
    int isOpen;
} FileEntry;

int fileCreate();
int fileOpen();
int fileWrite();
void fileRead();
int fileClose();
int fileDelete();
void printCurrent();
