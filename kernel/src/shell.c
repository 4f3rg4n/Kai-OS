#include "../include/shell.h"

void shell(){
    char command[100] = {0};
    do {
        _start:
        puts("\n$ ");
        int size = gets(command); // get user command
        command[size] = 0;

        // if user press just enter
        if(command[0] == '\0')
            goto _start;

        if(!strcmp(command, "time")) {
            int tmp;
            puts("hours: ");
            geti(&tmp);
            clock->hours = tmp;
            puts("minutes: ");
            geti(&tmp);
            clock->minutes = tmp;
            puts("seconds: ");
            geti(&tmp);
            clock->seconds = tmp;
            goto _start;
        }

        if(!strcmp(command, "delay")) {
            puts("0");
            timer_delay(18);
            puts("1");
            timer_delay(18);
            puts("2");
            timer_delay(18);
            puts("3");
            goto _start;
        }

        if(!strcmp(command, "shell")) {
            shell();
            goto _start;
        }

        puts("\n$ you write: ");
        puts(command);
        puts("\n");
    } while (strcmp(command, "exit"));
    
    puts("bye!");
}
