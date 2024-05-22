#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int COMMAND_LENGTH = 32; 
const int LINE_LENGTH = 256;    

char **text;                // Array of pointers to hold lines of text
int text_lines_count = 0;   // Current number of lines in the text editor
int text_capacity = 16;     // Number of 'inputs'


void print_help() {
    printf("The list of commands:\n");
    printf("help     - Show this help information\n");
    printf("exit     - Exit the text editor\n");
    printf("add_line - Add a new line to the text editor\n");
}

void add_line(char* line) {
    if (text_lines_count >= text_capacity) {
        printf("Error! Maximum number of lines is reached");
        //resize the array later
        return;
    }
    for (int i = 0; i < strlen(line); i++) {
		printf("%c\n", line[i]);
	}
    // new memory for the new line
    printf("%p", text);
    text[text_lines_count] = (char*)malloc((strlen(line) + 1) * sizeof(char));

    strcpy_s(text[text_lines_count], strlen(line) + 1, line);
    printf("Line added successfully!\n");
    text_lines_count++;
    return;
}

void print_lines() {
    if (text_lines_count == 0) {
        return;
    }
    for (int i = 0; i < text_lines_count; i++) {
        for (int j = 0; j < strlen(text[i]); j++) {
            printf("%d: %c", i + 1, text[i][j]);
            printf("\n");
        }
    }
}

void parse_command(char *command) {
    // string comparison   true == 0
    if (strcmp(command, "help") == 0) {
        print_help();
    }
    else if (strcmp(command, "exit") == 0) {
        printf("Exiting the text editor...\n");
        exit(0);
    }
    else if (strcmp(command, "add_line") == 0) {
		char line[LINE_LENGTH];
		printf("Enter the line to add: ");
		if (fgets(line, LINE_LENGTH, stdin) != NULL) {
			line[strcspn(line, "\n")] = 0;
			add_line(line);
		}
	}
	
    else {
        printf("The command is not implemented\n");
    }
}


int main() {
    char command[COMMAND_LENGTH];
    text = (char**)malloc(text_capacity * sizeof(char*));
    printf("Welcome to the console-based text editor!\n");
    printf("Type \"help\" to see all commands.\n");

    while (true) {
        printf(">> ");
        if (fgets(command, COMMAND_LENGTH, stdin) != NULL) {
            
            // Remove the newline character at the end
            command[strcspn(command, "\n")] = 0;

            print_lines();
            parse_command(command);
        }
    }
    return 0;
}
