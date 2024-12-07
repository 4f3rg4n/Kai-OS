#include "../include/shell.h"

void shell(){
    char command[100] = {0};
    do {
        _start:
        printf("\n$ ");
        gets(command); // get user command

        // if user press just enter
        if(command[0] == '\0')
            goto _start;

        if(!strcmp(command, "time")) {
            timer_print();
            goto _start;
        }

        printf("\nyou write: ");
        printf(command);
        puts("\n");
    } while (strcmp(command, "exit"));
    
    printf("bye!");
}
