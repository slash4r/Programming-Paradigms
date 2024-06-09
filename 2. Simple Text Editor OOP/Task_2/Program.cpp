#include <iostream>

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

	void save_to_file() {
		cout << "Saving the text to the file...\n";
	};

	private:
	int lines_count = 1;
	int lines_capacity = 16;
	Line current_line;
	Line* lines = nullptr;
};


void print_help();
void exit();

int main() {
	// for testing purposes
	char command[] = "FIRST****asdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegf";
	char input[INPUT_LENGTH];
	Text text;

	cout << "Welcome to the console - based text editor!\n";
	cout << "Type 'help' to see the list of commands.\n\n";

	while (true)
	{
		cout << ">> ";
		// change it later!!
		//cin >> command; // input buffer ??? (cin)
		text.add_text(command);
		text.new_line();
		char command2[] = "SECOND////asdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegf";
		text.add_text(command2);
		text.new_line();
		char command3[] = "THIRD////asdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegf";
		text.add_text(command3);
		text.new_line();
		text.new_line();
		char command4[] = "FOURTH////asdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegfasdfsggsdgdfsgdfshsdjshdjhgsdfjsdgfjhsdgfshdjgfdshjgfsdhfgsdjgfsdhjgfsdhjfjsdgfufeyugfwyuegfwegf";
		text.add_text(command4);
		text.print_text();
		cin >> input;
		
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
	// clear all the memory

	exit(0);
}