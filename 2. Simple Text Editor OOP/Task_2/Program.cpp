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

	void read_lines(ifstream& file, char* string, int string_length) {

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
		cout << string;
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


		/*text.add_text(command);
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
		cout << "\n\nSAVE TO FILE\n\n";
		cin >> command;
		text.save_to_file(command);*/
		

		cin >> input;
		text.load_from_file(input);
		
		text.print_text();
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