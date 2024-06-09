#include <iostream>
#include <string.h>
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
	}

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
		line_length += string_lenght;
		text[line_length] = '\0';
		cout << "Text inserted: " << string << endl;
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
		Line* lines = new Line[lines_capacity];
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
	}

	private:
	int lines_count = 0;
	int lines_capacity = 16;
	Line current_line;
};


void print_help();
void exit();

int main() {
	// for testing purposes
	char command[] = "asdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegf";
	char input[INPUT_LENGTH];
	Text text;

	cout << "Welcome to the console - based text editor!\n";
	cout << "Type 'help' to see the list of commands.\n\n";

	while (true)
	{
		cout << ">> ";
		// change it later!!
		cin >> input; // input buffer ??? (cin)
		text.add_text(command);
		
	}

	return 0;
}

void print_help() {
	cout << "The list of commands:\n\n";
	cout << "help - print this help message\n";
	cout << "exit - exit the program\n\n";
	cout << "add  - a new string to the text editor\n";
}

void exit() {
	cout << "Exiting the program...\n";
	exit(0);
}