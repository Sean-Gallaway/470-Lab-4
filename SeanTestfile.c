#include "SeanLibFS.h"
#include <ctype.h>

void displayMenu (int ind) {
    printCurrent(ind);
    printf("\nMENU\n1) Create a File\t\t2) Open a File\t\t3) Write to File\n4) Read the File\t\t5) Close a file\t\t6) Delete a file\n7) Exit\n");
}

void waitForUser () {
    printf("Press enter to continue\n");
    while (getchar() != '\n');
}

int main () {
    char filename[MAX_FILENAME];
    char introduction[] = "Hi my name is Sean Gallaway\n"
        "I am a Computer Science student that is about to graduate in December\n"
        "I hope you find my implementation fits the criteria of the assignment\n"
        "\n"
        "Hope your holidays go well!";

    int fileIndex = -1;
    int choice;

    while (1) {
        displayMenu(fileIndex);
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                printf("Name of the file to create: ");
                scanf("%s", filename);
                fileCreate(filename);
                break;
            case 2:
                printf("Name of the file to open: ");
                scanf("%s", filename);
                fileIndex = fileOpen(filename);
                break;
            case 3:
                fileWrite(fileIndex, introduction);
                break;
            case 4:
                fileRead(fileIndex);
                break;
            case 5:
                printf("Name of the file to close: ");
                scanf("%s", filename);
                fileClose(filename);
                fileIndex = -1;
                break;
            case 6:
                printf("Name of the file to delete: ");
                scanf("%s", filename);
                fileDelete(filename);
                break;
            case 7:
                printf("Goodbye\n");
                return 0;
            default:
                printf("Invalid choice, please try again\n");
                waitForUser();
                break;
        }
    }

    return 0;
}
