#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int COMMAND_LENGTH = 100;

void print_help() {
    printf("The list of commands:\n");
    printf("help     - Show this help information\n");
    printf("exit     - Exit the text editor\n");
}

void parse_command(char* command) {
    // string comparison     true == 0
    if (strcmp(command, "help") == 0) {
        print_help();
    }
    else if (strcmp(command, "exit") == 0) {
        printf("Exiting the text editor...\n");
        exit(0);
    }
    else {
        printf("The command is not implemented\n");
    }
}

int main() {
    char command[COMMAND_LENGTH];

    printf("Welcome to the console-based text editor!\n");
    printf("Type \"help\" to see all commands.\n");

    while (true) {
        printf(">> ");
        if (fgets(command, COMMAND_LENGTH, stdin) != NULL) {
            
            // Remove the newline character at the end
            command[strcspn(command, "\n")] = 0;

            parse_command(command);
        }
    }

    return 0;
}
