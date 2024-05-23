#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int COMMAND_LENGTH = 32; 
const int LINE_LENGTH = 256;    

char **text;                // Array of pointers to hold lines of text
int text_lines_count = 0;   // Current number of 'inputs' in the text editor
int text_capacity = 16;     // Number of possible 'inputs'


void print_help() {
    printf("The list of commands:\n");
    printf("help           - Show this help information\n");
    printf("exit           - Exit the text editor\n");
    printf("add_line       - Add a new line to the text editor\n");
    printf("print_text     - Display all text in console\n");
    printf("save_to_file   - Save the text to a file\n");
    printf("load_from_file - Load the text from a file\n");
}

void add_line(char* line) {
    if (text_lines_count >= text_capacity) {
        // resizing the array
        text_capacity *= 2;
        char** new_text = (char**)realloc(text, text_capacity * sizeof(char*));
        if (new_text == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        text = new_text;
        free(new_text);
    }
    /*for (int i = 0; i < strlen(line); i++) {
		printf("%c\n", line[i]);
	}
    printf("%p", text);*/

    // new memory for the new line
    text[text_lines_count] = (char*)malloc((strlen(line) + 1) * sizeof(char));
    if (text[text_lines_count] == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}

    strcpy_s(text[text_lines_count], strlen(line) + 1, line);
    printf("Line added successfully!\n");
    text_lines_count++;
    return;
}

void print_lines() {
    if (text_lines_count == 0) {
        printf("*emptiness*\n");
        return;
    }
    for (int i = 0; i < text_lines_count; i++) {
        printf("%s", text[i]);
    }
}

void save_to_file(char* filename) {
    errno_t err;
    FILE* file;
    err = fopen_s(&file, filename, "w");
    if (err == 0) {
        printf("The file was opened\n");
	}
	else {
		printf("The file was not opened\n");
		return;
    }
    for (int i = 0; i < text_lines_count; i++) {
        fprintf(file, "%s", text[i]);
    }
    fclose(file);
    printf("Text saved to the file successfully!\n");
}

void load_from_file(char* filename) {
    FILE* file;
    errno_t err;
    err = fopen_s(&file, filename, "r");
    if (err == 0) {
        printf("The file was opened\n");
    }
    else {
        printf("The file was not opened\n");
        return;
    }
    char line[LINE_LENGTH];
    while (fgets(line, LINE_LENGTH, file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
    printf("Text loaded from the file successfully!\n");
}

void parse_command(char *command) {
    // string comparison   true == 0
    if (strcmp(command, "help") == 0) {
        print_help();
    }
    else if (strcmp(command, "exit") == 0) {
        printf("Exiting the text editor...\n");
        for (int i = 0; i < text_lines_count; i++) {
            free(text[i]);
        }
        free(text);
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
    else if (strcmp(command, "print_text") == 0) {
        print_lines();
    }
    else if (strcmp(command, "save_to_file") == 0) {
    char filename[LINE_LENGTH];
		printf("Enter the filename: ");
		if (fgets(filename, LINE_LENGTH, stdin) != NULL) {
			filename[strcspn(filename, "\n")] = 0;
            strcat_s(filename, ".txt");
			save_to_file(filename);
		}
	}
    else if (strcmp(command, "load_from_file") == 0) {
        char filename[LINE_LENGTH];
        printf("Enter the filename: ");
        if (fgets(filename, LINE_LENGTH, stdin) != NULL) {
            filename[strcspn(filename, "\n")] = 0;
            strcat_s(filename, ".txt");
            load_from_file(filename);
        }
    }
    else {
        printf("The command is not implemented\n");
    }
}


int main() {
    char command[COMMAND_LENGTH];
    text = (char**)malloc(text_capacity * sizeof(char*));
    if (text == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

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
