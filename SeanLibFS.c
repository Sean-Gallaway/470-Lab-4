#include "SeanLibFS.h"

FileEntry table[MAX_FILES];
int fileCount = 0;

/**
* Prints out the last file that has been the target of fileOpen.
*/
void printCurrent(int ind) {
    if (ind != -1) {
        printf("\nCurrent file: %s\n", table[ind].filename);
    }
}

/**
* Creates a file and stores a record of it inside of the file table.
*
* param filename: the name of the file to create.
*/
int fileCreate (const char* filename) {
    // Create the entry for the file
    for (int a = 0; a < MAX_FILES; a++) {
        if (strcmp(table[a].filename, filename) == 0) {
            printf("[ERROR]: File %s already exists.\n", filename);
            return -1;
        }
    }

    // create the file on the disk
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("[ERROR]: Could not create file: %s", filename);
        return -1;
    }
    fclose(file);

    // add to file table
    strcpy(table[fileCount].filename, filename);
    table[fileCount].size = 0;
    table[fileCount].isOpen = 0;
    fileCount++;
    return 0;
}

/**
* Opens a file and records it into the file table.
*
* param filename: the name of the file to open.
*/
int fileOpen (const char* filename) {
    // search for the file
    for (int a = 0; a < fileCount; a++) {
        if (strcmp(table[a].filename, filename) == 0) {
            // check if the file is already open
            if (table[a].isOpen) {
                printf("[ERROR]: '%s' is already open,\n", filename);
                return -1;
            }
            table[a].isOpen = 1;
            printf("File '%s' opened successfully.\n", filename);
            return a;
        }
    }
    // file was not found
    printf("[ERROR]: File '%s' not found.\n", filename);
    return -1;
}

/**
* Writes to a currently open file.
*
* param ind: the index of the file in the file table.
* param content: the data to put inside of the file.
*/
int fileWrite (int ind, const char* content) {
    if (ind == -1) {
        printf("[ERROR]: There is not a file open.");
        return -1;
    }
    // only write if the file is already open
    if (!table[ind].isOpen) {
        printf("[ERROR]: '%s' is not open.\n", table[ind].filename);
        return -1;
    }

    // open the file
    int size = strlen(content);
    FILE *file = fopen(table[ind].filename, "w");
    if (!file) {
        printf("[ERROR]: Unable to open file '%s' for writing.\n", table[ind].filename);
    }

    // write to the file
    fwrite(content, 1, size, file);
    fclose(file);
    table[ind].size = size;
    printf("Data written to file '%s' successfully.\n", table[ind].filename);
    return 0;
}

/**
* Reads a file and prints it into the terminal.
*
* param ind: the index of the file in the file table.
*/
void fileRead (int ind) {
    // check if there was a file open
    if (ind == -1) {
        printf("[ERROR]: There is not a file open.");
    }

    // open the file
    FILE *file = fopen(table[ind].filename, "rb");
    if (!file) {
        printf("[ERROR]: Unable to open file '%s' for reading.\n",table[ind].filename);
    }

    // read the file
    char line[1024];
    while ( fgets(line, sizeof(line), file) ) {
        printf("%s", line);
    }
    fclose(file);
}

/**
* Close a file in the file table
*
* param filename: the name of the file to close.
*/
int fileClose (const char* filename) {
    // search for the file
    for (int a = 0; a < fileCount; a++) {
        if (strcmp(table[a].filename, filename) == 0) {
            // check if the file is already open
            if (!table[a].isOpen) {
                printf("[ERROR]: '%s' is already closed,\n", filename);
                return -1;
            }
            table[a].isOpen = 0;
            printf("File '%s' closed successfully.\n", filename);
            return a;
        }
    }
    // file was not found
    printf("[ERROR]: File '%s' not found.\n", filename);
    return -1;
}

int fileDelete (const char* filename) {
    for (int a = 0; a < MAX_FILES; a++) {
        if (strcmp(table[a].filename, filename) == 0) {
            if (table[a].isOpen == 1) {
                printf("[ERROR]: %s is still open, close it first.\n", filename);
                return -1;
            }
            memset(&table[a], 0, sizeof(FileEntry));
            if (remove(filename) == 0) {
                printf("%s removed.", filename);
            }
            return 0;
        }
    }
    printf("File %s not found.", filename);
    return -1;
}
