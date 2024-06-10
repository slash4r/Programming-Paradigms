#include <iostream>
#include <fstream>

using namespace std;

const int COMMAND_LENGTH = 32;
const int INPUT_LENGTH = 256;

class Line {
public:
	Line() {
		text = new char[line_capacity];
	};

	int get_length() {
		return line_length;
	};
	int get_capacity() {
		return line_capacity;
	};
	char* get_text() {
		return text;
	};


	void ensure_capacity() {
		line_capacity *= 2;
		char* text_buffer = new char[line_capacity];
		// copy text to text_buffer
		copy(text, text + line_length, text_buffer);
		delete[] text;
		text = text_buffer;
		
		cout << "Capacity increased to " << line_capacity << endl;
	};

	void insert_text(char* string, int string_lenght) {
		// copy string to text
		copy(string, string + string_lenght, text + line_length);
		line_length += string_lenght; // error here maybe. lines_length is not updated
		text[line_length] = '\0';
		cout << "Text inserted: " << string << endl;
	};

	void print_text() {
		// blank line
		if (line_length == 0)
		{
			return;
		}
		cout << text;
	};
private:
	int line_length = 0;
	int line_capacity = 128;
	char* text = nullptr;
};

class Text
{
public:
	Text()
	{
		lines = new Line[lines_capacity];
		current_line = lines[0];
	};

	void add_text(char* string) {
		int string_length = strlen(string);
		int current_line_length = current_line.get_length();
		int current_line_capacity = current_line.get_capacity();

		while (string_length + current_line_length > current_line_capacity)
		{
			current_line.ensure_capacity();
			current_line_capacity = current_line.get_capacity();
		}
		cout << "Adding text to the current line...\n";
		current_line.insert_text(string, string_length);

		// update the core text array
		lines[lines_count - 1] = current_line;
	};

	void new_line() {
		
		if (lines_count == lines_capacity)
		{
			lines_capacity *= 2;
			Line* lines_buffer = new Line[lines_capacity];
			// copy lines to lines_buffer
			copy(lines, lines + lines_count, lines_buffer);
			delete[] lines;  // implement destructor for Line class in the future!!!
			lines = lines_buffer;

			cout << "Lines capacity increased to " << lines_capacity << endl;
		}

		current_line = lines[lines_count];
		lines_count++;
		cout << "New line created!\n";
	};

	void print_text() {
		cout << "Printing the text...\n";

		for (size_t i = 0; i < lines_count; i++)
		{
			Line printing_line = lines[i];
			cout << "\t";
			printing_line.print_text();
			cout << "\n";
		}
	};

	void save_to_file(char* filename) {
		const int name_length = strlen(filename);
		strcat_s(filename, name_length + 5, ".txt");
		cout << "Saving the text to the file: " << filename << endl;

		ofstream file; // create and write to file
		file.open(filename);

		if (!file.is_open())
		{
			cout << "Failed to open the file: " << filename << endl;
			return;
		}
		
		for (size_t i = 0; i < lines_count; i++)
		{
			Line saving_line = lines[i];
			char* saving_text = saving_line.get_text();

			file << "\t";
			file << saving_text;
			file << "\n";
		}

		cout << "Text saved to the file: " << filename << endl;
		file.close();
	};

	void load_from_file(char* filename) {
		const int name_length = strlen(filename);
		strcat_s(filename, name_length + 5, ".txt");
		cout << "Loading the text from the file: " << filename << endl;

		ifstream file; // read from file
		file.open(filename);

		if (!file.is_open())
		{
			cout << "Failed to open the file: " << filename << endl;
			return;
		}
		int size = 32;
		char* string = new char[size];
		char c;
		int counter = 0;

		// read the file char by char
		while (file.get(c))
		{
			if (counter == size - 1)
			{
				int new_size = size * 2;
				char* new_string = new char[new_size];
				strcpy_s(new_string, new_size, string);
				delete[] string;

				size = new_size;
				string = new_string;
			}
			if (c == '\n')
			{
				string[counter] = '\0';
				add_text(string);
				new_line();
				counter = 0;
			}
			else if (c == '\t')
			{
				continue;
			}
			else
			{
				string[counter] = c;
				counter++;
			}
		}

		// if the last line without '\n'
		if (counter > 0) {
			string[counter] = '\0';
			add_text(string);
		}

		//cout << string;
		delete[] string;
		file.close();
	};

	void substring_search(char* substring) {
		cout << "Searching for the substring: " << substring << endl;
		for (size_t i = 0; i < lines_count; i++)
		{
			Line line = lines[i];
			char* text = line.get_text();
			char* match = strstr(text, substring);
			while (match != NULL || match != nullptr) {
				cout << "Found substring in line " << i << " at position " << (match - text) << endl;
				match = strstr(match + 1, substring);
			}	
		}
	};

	void insert_into_text(char* string) {
		int line;
		int index;
		cout << "Enter the line number and the index: ";
		cin >> line >> index;

		Line& current_line = lines[line];
		int current_line_length = current_line.get_length();
		int string_length = strlen(string);
		while (current_line_length + string_length > current_line.get_capacity())
		{
			current_line.ensure_capacity();
		}
		cout << "Inserting text to the line...\n";

		int buffer_size = current_line_length - index;
		char* buffer = new char[buffer_size + 1]; // +1 for '\0'!!!
		char* current_text = current_line.get_text();
		for (size_t i = 0; i < buffer_size; i++)
		{
			buffer[i] = current_text[i + index];
			current_text[i + index] = string[i]; // is it correct?
		}
		buffer[buffer_size] = '\0';

		strcat_s(current_text, current_line.get_capacity(), buffer);
		lines[line] = current_line;

		// delete buffer!!
		delete[] buffer;
	};
	private:
	int lines_count = 1;
	int lines_capacity = 16;
	Line current_line;
	Line* lines = nullptr;
};


void print_help();
void parse_command(char* command, Text& text);
char* get_input();
void exit();


int main() {
	// for testing purposes
	char command[COMMAND_LENGTH];
	char input[INPUT_LENGTH];
	Text text;

	cout << "Welcome to the console - based text editor!\n";
	cout << "Type 'help' to see the list of commands.\n\n";

	while (true)
	{
		cout << ">> ";
		char* command = get_input();
		parse_command(command, text);
	}

	return 0;
}

void parse_command(char* command, Text& text) {
	if (!strcmp(command, "help"))
	{
		print_help();
	}
	else if (!strcmp(command, "exit"))
	{
		cout << "Thank you for using the text editor!\n";
		cout << "Exiting the program...\n";
		exit();
	}
	else if (!strcmp(command, "add"))
	{
		cout << "Enter the text to add: ";
		char* input = get_input();
		text.add_text(input);
	}
	else if (strcmp(command, "print") == 0)
	{
		text.print_text();
	}
	else if (strcmp(command, "new") == 0)
	{
		text.new_line();
	}
	else if (strcmp(command, "save") == 0)
	{
		cout << "Enter the filename: ";
		char* filename = get_input();
		text.save_to_file(filename);
	}
	else if (strcmp(command, "load") == 0)
	{
		cout << "Enter the filename: ";
		char* filename = get_input();
		text.load_from_file(filename);
	}
	else if (strcmp(command, "search") == 0)
	{
		cout << "Enter the substring: ";
		char* substring = get_input();
		text.substring_search(substring);
	}
	else if (strcmp(command, "insert") == 0)
	{
		cout << "Enter the text to insert: ";
		char* string = get_input();
		text.insert_into_text(string);
	}
	else
	{
		cout << "Unknown command. Type 'help' to see the list of commands.\n";
	}
}

char* get_input() {
	char* string = new char[INPUT_LENGTH];
	// get the input from the user
	char* input = new char[1];
	input[0] = '\0';
	while(fgets(string, INPUT_LENGTH, stdin) != NULL)
	{
		int new_input_length = strlen(string) + strlen(input);

		char* new_input = new char[new_input_length + 1];
		strcpy_s(new_input, new_input_length + 1, input);
		strcat_s(new_input, new_input_length + 1, string);
		
		delete[] input;
		input = new_input;
		// infinite loop here

		if (string[strlen(string) - 1] == '\n')
		{
			break;
		}
	}
	// delete string!!!
	delete[] string;
	input[strlen(input) - 1] = '\0';
	return input;
}

void print_help() {
	cout << "The list of commands:\n\n";
	cout << "help   - print this help message\n";
	cout << "exit   - exit the program\n\n";
	cout << "add    - a new string to the text editor\n";
	cout << "print  - print the text\n";
	cout << "new    - create a new line\n";
	cout << "save   - save the text to the file\n";
	cout << "load   - load the text from the file\n";
	cout << "search - search for the substring in the text\n";
	cout << "insert - insert the text into the line\n\n";
}

void exit() {
	cout << "Exiting the program...\n";
	// clear all the memory

	exit(0);
}