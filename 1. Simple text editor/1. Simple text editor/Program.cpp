#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int COMMAND_LENGTH = 32; 
const int LINE_LENGTH = 256;    

char **text;                // Array of pointers to hold lines of text
int text_inputs_count = 0;  // Current number of 'inputs' in the text editor
int text_capacity = 16;     // Number of possible 'inputs'


void print_help() {
    printf("The list of commands:\n");
    printf("help   - Show this help information\n");
    printf("exit   - Exit the text editor\n");
    printf("add    - Add a new line to the text editor\n");
    printf("print  - Display all text in console\n");
    printf("save   - Save the text to a file\n");
    printf("load   - Load the text from a file\n");
    printf("find   - Find a substring's index in the text\n");
}

void add_text(const char* line) {
    if (text_inputs_count >= text_capacity) {
        // resizing the array
        text_capacity *= 2;
        char** new_text = (char**)realloc(text, text_capacity * sizeof(char*));
        if (new_text == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        text = new_text;    }

    // Check if this is the first line
    char* new_line;
    if (text_inputs_count == 0) {
        new_line = (char*)malloc((strlen(line) + 2 * sizeof(char))); // +2 for tab and endline
        if (new_line == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        strcpy_s(new_line, strlen(line) + 2, "\t");
        strcat_s(new_line, strlen(line) + 2, line);
        
    }

    else {
        new_line = (char*)malloc((strlen(line) + 1) * sizeof(char));
        if (new_line == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        strcpy_s(new_line, strlen(line) + 1, line);
    }

    text[text_inputs_count] = new_line;
    printf("Line added successfully!\n");
    text_inputs_count++;
}

void print_text() {
    if (text_inputs_count == 0) {
        printf("*emptiness*\n");
        return;
    }
    for (int i = 0; i < text_inputs_count; i++) {
        printf("%s", text[i]);
    }
    printf("\n");
}

void save_to_file(char* filename) {
    errno_t err;
    FILE* file;
    err = fopen_s(&file, filename, "w");
    if (err == 0) {
        printf("The file was opened.\n");
        printf("WARNING! If the file has some data in it, it will be OVERWRITTEN!\n");
	}
	else {
		printf("The file was not opened\n");
		return;
    }
    for (int i = 0; i < text_inputs_count; i++) {
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
        printf("Do you want to add text to existing one? y/n\n");
    }
    else {
        printf("The file was not opened\n");
        return;
    }

    char answer;
    answer = getchar();
    while (true) {
        if (answer == 'y') {
			break;
		}
		else if (answer == 'n') {
			for (int i = 0; i < text_inputs_count; i++) {
				free(text[i]);
			}
			text_inputs_count = 0;
			break;
		}
        else {
            printf("Please enter y or n\n");
            // clear answer
            while (getchar() != '\n') {
                continue;
            }
            answer = getchar();
            // some problem here!
        }   
    }
    

    char line[LINE_LENGTH];
    while (fgets(line, LINE_LENGTH, file) != NULL) {
        add_text(line);
        printf("%s", line);
    }
    fclose(file);

    printf("\n");
    printf("Text loaded from the file successfully!\n");
}

void find_substring(char* substring) {
	for (int i = 0; i < text_inputs_count; i++) {
		if (strstr(text[i], substring) != NULL) {
			printf("The substring is found in the line %d\n", i + 1);
		}
	}
}

void parse_command(char* command) {
    // string comparison   true == 0
    if (strcmp(command, "help") == 0) {
        print_help();
    }
    else if (strcmp(command, "exit") == 0) {
        printf("Exiting the text editor...\n");
        for (int i = 0; i < text_inputs_count; i++) {
            free(text[i]);
        }
        free(text);
        exit(0);
    }
    else if (strcmp(command, "add") == 0) {
        char line[LINE_LENGTH];
        printf("Enter the line to add: ");
        if (fgets(line, LINE_LENGTH, stdin) != NULL) {
            line[strcspn(line, "\n")] = 0;
            add_text(line);
        }
    }
    else if (strcmp(command, "print") == 0) {
        print_text();
    }
    else if (strcmp(command, "save") == 0) {
        char filename[LINE_LENGTH];
        printf("Enter the filename: ");
        if (fgets(filename, LINE_LENGTH, stdin) != NULL) {
            filename[strcspn(filename, "\n")] = 0;
            strcat_s(filename, ".txt");
            save_to_file(filename);
        }
    }
    else if (strcmp(command, "load") == 0) {
        char filename[LINE_LENGTH];
        printf("Enter the filename: ");
        if (fgets(filename, LINE_LENGTH, stdin) != NULL) {
            filename[strcspn(filename, "\n")] = 0;
            strcat_s(filename, ".txt");
            load_from_file(filename);
        }
    }

    else if (strcmp(command, "find") == 0) 
    {
        char substring[LINE_LENGTH];
        printf("Enter the substring to find: "); 
        if (fgets(substring, LINE_LENGTH, stdin) != NULL)
        {
            substring[strcspn(substring, "\n")] = 0;
            find_substring(substring);
        }       
    }
    else if (strcmp(command, "newline") == 0)
    {
        add_text("\n\t");
    }
    else {
        printf("tetstststs");
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
