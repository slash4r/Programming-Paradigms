#include <iostream>
#include <fstream>

using namespace std;

const int COMMAND_LENGTH = 32;
const int INPUT_LENGTH = 256;

class Line {
public:
	Line() {
		text = new char[line_capacity];
		text[0] = '\0';
	};

	Line(const Line& other) {
		line_length = other.line_length;
		line_capacity = other.line_capacity;
		text = new char[line_capacity + 1];
		strcpy_s(text, line_capacity + 1, other.text);
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

	void append_text(char* string, int string_lenght) {
		// copy string to text
		copy(string, string + string_lenght, text + line_length);
		line_length += string_lenght; // error here maybe. lines_length is not updated
		text[line_length] = '\0';
		cout << "Text added: " << string << endl;
	};

	void insert_text(int index, char* string, int string_length) {
		int buffer_size = line_length - index;
		char* buffer = new char[buffer_size + 1]; // +1 for '\0'!!!

		// shift the text to the right
		for (size_t i = 0; i < buffer_size; i++)
		{
			buffer[i] = text[index + i];
			//text[index + i] = string[i]; // is it correct?
		}
		buffer[buffer_size] = '\0';
		text[index] = '\0';
		strcat_s(text, line_capacity, string);
		strcat_s(text, line_capacity, buffer);

		this->line_length += string_length;
		text[line_length] = '\0';
		cout << "Text inserted!\n";

		delete[] buffer;
	};

	void insert_replace(int index, char* string, int string_length) {
		copy(string, string + string_length, text + index);
		cout << "Text inserted and replaced!\n";

		//text[index + string_length] = '\0';
		if (index + string_length > line_length) {
			line_length = index + string_length;
			text[line_length] = '\0';
		}
	};

	void delete_text(int index, int delete_length) {
		for (size_t i = index; i < line_length - index - delete_length; i++)
		{
			text[i] = text[i + delete_length];
		}
		line_length -= delete_length;
		text[line_length] = '\0';
		cout << "Text deleted!\n";
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

class Text {
public:
	Text()
	{
		lines = new Line[lines_capacity];
		current_line = lines[0];
	};

	Text(const Text& other) {
		lines_count = other.lines_count;
		lines_capacity = other.lines_capacity;
		lines = new Line[lines_capacity];
		for (size_t i = 0; i < lines_count; i++)
		{
			lines[i] = Line(other.lines[i]);
		}
		current_line = Line(other.current_line);
	};

	void add_text(char* string) {
		int string_length = strlen(string);
		int current_line_length = current_line.get_length();
		int current_line_capacity = current_line.get_capacity();

		while (string_length + current_line_length > current_line_capacity)
		{
			this->current_line.ensure_capacity();
			current_line_capacity = current_line.get_capacity();
		}
		cout << "Adding text to the current line...\n";
		this->current_line.append_text(string, string_length);

		// update the core text array
		this->lines[lines_count - 1] = current_line;
	};

	void new_line() {

		if (lines_count == lines_capacity)
		{
			this->lines_capacity *= 2;
			Line* lines_buffer = new Line[lines_capacity];
			// copy lines to lines_buffer
			copy(lines, lines + lines_count, lines_buffer);
			delete[] lines;  // implement destructor for Line class in the future!!!
			this->lines = lines_buffer;

			cout << "Lines capacity increased to " << lines_capacity << endl;
		}

		this->current_line = lines[lines_count];
		this->lines_count++;
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
		cin.ignore();

		if (line < 0 || line >= lines_count || index < 0)
		{
			cout << "Invalid line number!\n";
			return;
		}

		Line& current_line = this->lines[line];
		int current_line_length = current_line.get_length();
		int string_length = strlen(string);

		while (current_line_length + string_length > current_line.get_capacity())
		{
			current_line.ensure_capacity();
		}
		cout << "Inserting text to the line...\n";

		current_line.insert_text(index, string, string_length);
	};

	void delete_from_text(int line, int index, int delete_length) {
		if (line < 0 || line >= lines_count)
		{
			cout << "Invalid line number!\n";
			return;
		};


		Line& current_line = this->lines[line];
		int current_line_length = current_line.get_length();

		if (index < 0 || index >= current_line_length || delete_length <= 0 || delete_length > current_line_length - index) {
			cout << "Invalid index or delete length!\n";
			return;
		}
		cout << "Deleting text from the line...\n";
		current_line.delete_text(index, delete_length);
	}

	void copy_text(int line, int index, int symbols) {
		if (line < 0 || line >= lines_count || symbols <= 0)
		{
			cout << "Invalid input!\n";
			return;
		}
		Line& current_line = this->lines[line];
		int current_line_length = current_line.get_length();
		char* current_text = current_line.get_text();

		if (index >= current_line_length || index < 0)
		{
			cout << "Invalid index!\n";
			return;
		}

		if (index + symbols > current_line_length)
		{
			cout << "Symbols to copy exceed the line length!\n";
			return;
		}
		cout << "Copying text...\n";
		delete[] this->text_clipboard;
		this->text_clipboard = new char[symbols + 1];

		for (size_t i = index; i < index + symbols; i++) {

			this->text_clipboard[i - index] = current_text[i];
		}
		this->text_clipboard[symbols] = '\0';
		cout << "Text copied to the clipboard!\n";
		cout << "Clipboard is: " << text_clipboard << endl;
	};

	void paste_text(int line, int index) {
		if (line < 0 || line >= lines_count)
		{
			cout << "Invalid input!\n";
			return;
		}
		Line& current_line = this->lines[line];
		int current_line_length = current_line.get_length();
		char* current_text = current_line.get_text();

		if (index >= current_line_length || index < 0)
		{
			cout << "Invalid index!\n";
			return;
		}

		if (text_clipboard == nullptr || text_clipboard == NULL)
		{
			cout << "Clipboard is empty!\n";
			return;
		}
		cout << "Pasting text...\n";
		int clipboard_length = strlen(text_clipboard);
		int new_line_length = current_line_length + clipboard_length;

		while (new_line_length > current_line.get_capacity())
		{
			current_line.ensure_capacity();
		}
		current_line.insert_text(index, text_clipboard, clipboard_length);
	};

	void cut_text(int line, int index, int symbols) {
		copy_text(line, index, symbols);
		delete_from_text(line, index, symbols);
	};

	void insert_replace(char* string) {
		int line;
		int index;
		cout << "Enter the line number and the index: ";
		cin >> line >> index;
		cin.ignore();

		if (line < 0 || line >= lines_count || index < 0)
		{
			cout << "Invalid line number!\n";
			return;
		}

		Line& current_line = this->lines[line];
		int current_line_length = current_line.get_length();
		int string_length = strlen(string);

		while (index + string_length >= current_line.get_capacity())
		{
			current_line.ensure_capacity();
		}
		cout << "Replacing text into the line...\n";
		current_line.insert_replace(index, string, string_length); // current line is not updated
	};

private:
	int lines_count = 1;
	int lines_capacity = 16;
	Line current_line;
	Line* lines = nullptr;
	char* text_clipboard = nullptr;
};

class BufferText {
public:
	BufferText() {
		for (size_t i = 0; i < 3; i++)
		{
			this->buffers[i] = Text();
		}
		this->current_text = Text();
		this->counter = 0;
		this->undo_steps = 0;
	};

	void update_buffer(Text& text)
	{
		if (counter == 0)
		{
			this->buffers[counter] = Text(current_text);
			cout << "Buffer 1 updated!\n";

			this->undo_steps = 0;
		}
		else if (counter == 1)
		{
			this->buffers[counter] = Text(current_text);
			cout << "Buffer 2 updated!\n";

			this->undo_steps = 0;

		}
		else if (counter == 2)
		{
			this->buffers[counter] = Text(current_text);
			cout << "Buffer 3 updated!\n";

			this->undo_steps = 0;
		}

		this->current_text = Text(text); // error here
		this->counter++;
		this->counter %= 3;
	};

	void undo(Text& text) {
		if (undo_steps == 0)
		{
			this->next_redo = current_text;
		}
		if (undo_steps == 3)
		{
			cout << "Nothing to undo!\n";
			return;
		}
		else if (counter == 0)
		{
			text = buffers[2];
			this->counter = 2;
		}
		else if (counter == 1)
		{
			text = buffers[counter - 1];
			this->counter = 0;
		}
		else if (counter == 2)
		{
			text = buffers[counter - 1];
			this->counter = 1;
		}
		undo_steps++;
	};

	void redo(Text& text) {
		if (undo_steps == 0)
		{
			cout << "Nothing to redo!\n";
			return;
		}
		if (undo_steps == 1)
		{
			text = next_redo;
			this->undo_steps--;
			this->counter = (counter + 1) % 3;
		}
		else if (counter == 0)
		{
			text = buffers[counter + 1];
			this->counter = 1;
			this->undo_steps--;
		}
		else if (counter == 1)
		{
			text = buffers[counter + 1];
			this->counter = 2;
			this->undo_steps--;
		}
		else if (counter == 2)
		{
			text = buffers[counter + 1];
			this->counter = 0;
			this->undo_steps--;
		}

	};

private:
	int counter;
	int undo_steps;
	Text buffers[3];
	Text current_text;
	Text next_redo;
};

void print_help();
void parse_command(char*, Text&, BufferText&);
char* get_input();
void exit();

int main() {
	char command[COMMAND_LENGTH];
	Text text;
	BufferText buffer;

	cout << "Welcome to the console - based text editor!\n";
	cout << "Type 'help' to see the list of commands.\n\n";

	while (true)
	{
		cout << ">> ";
		char* command = get_input();
		parse_command(command, text, buffer);
	}
	return 0;
}

void parse_command(char* command, Text& text, BufferText& buffer) {
	if (!strcmp(command, "help"))
	{
		print_help();
	}
	else if (!strcmp(command, "exit"))
	{
		cout << "Thank you for using the text editor!\n";
		exit();
	}
	else if (!strcmp(command, "add"))
	{
		cout << "Enter the text to add: ";
		char* input = get_input();
		text.add_text(input);
		buffer.update_buffer(text);
	}
	else if (!strcmp(command, "print"))
	{
		text.print_text();
	}
	else if (!strcmp(command, "new"))
	{
		text.new_line();
		buffer.update_buffer(text);
	}
	else if (!strcmp(command, "save"))
	{
		cout << "Enter the filename: ";
		char* filename = get_input();
		text.save_to_file(filename);
	}
	else if (!strcmp(command, "load"))
	{
		cout << "Enter the filename: ";
		char* filename = get_input();
		text.load_from_file(filename);
		buffer.update_buffer(text);
	}
	else if (!strcmp(command, "search"))
	{
		cout << "Enter the substring: ";
		char* substring = get_input();
		text.substring_search(substring);
	}
	else if (!strcmp(command, "insert"))
	{
		cout << "Enter the text to insert: ";
		char* string = get_input();
		text.insert_into_text(string);
		buffer.update_buffer(text);
	}
	else if (!strcmp(command, "delete"))
	{
		int line;
		int index;
		int delete_length;
		cout << "Enter the line number, the index and the delete length: ";
		cin >> line >> index >> delete_length;
		cin.ignore();
		text.delete_from_text(line, index, delete_length);
		buffer.update_buffer(text);
	}
	else if (!strcmp(command, "copy"))
	{
		int line;
		int index;
		int symbols;
		cout << "Enter the line number, the index and the symbols: ";
		cin >> line >> index >> symbols;
		cin.ignore();
		text.copy_text(line, index, symbols);
	}
	else if (!strcmp(command, "paste"))
	{
		int line;
		int index;
		cout << "Enter the line number and the index: ";
		cin >> line >> index;
		cin.ignore();
		text.paste_text(line, index);
		buffer.update_buffer(text);
	}
	else if (!strcmp(command, "cut"))
	{
		int line;
		int index;
		int symbols;
		cout << "Enter the line number, the index and the symbols: ";
		cin >> line >> index >> symbols;
		cin.ignore();
		text.cut_text(line, index, symbols);
		buffer.update_buffer(text);
	}
	else if (!strcmp(command, "replace"))
	{
		cout << "Enter the text to insert and replace: ";
		char* string = get_input();
		text.insert_replace(string);
		buffer.update_buffer(text);
	}
	else if (!strcmp(command, "clear"))
	{
		system("cls");
	}
	else if (!strcmp(command, "undo"))
	{
		buffer.undo(text);
	}
	else if (!strcmp(command, "redo"))
	{
		buffer.redo(text);
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
	while (fgets(string, INPUT_LENGTH, stdin) != NULL)
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
	cout << "help    - print this help message\n";
	cout << "exit    - exit the program\n\n";

	cout << "add     - a new string to the text editor\n";
	cout << "print   - print the text\n";
	cout << "new     - create a new line\n";
	cout << "save    - save the text to the file\n";
	cout << "load    - load the text from the file\n";
	cout << "search  - search for the substring in the text\n";
	cout << "insert  - insert the text into the line\n";
	cout << "delete  - delete the text from the line\n";
	cout << "copy    - copy the text to the clipboard\n";
	cout << "paste   - paste the text from the clipboard\n";
	cout << "cut     - cut the text to the clipboard\n";
	cout << "replace - insert and replace the text\n\n";

	cout << "clear   - clear the console\n";
	cout << "undo    - undo the last action\n";
	cout << "redo    - redo the last action\n";
	cout << endl;
}

void exit() {
	cout << "Exiting the program...\n";
	// clear all the memory

	exit(0);
}

// insert_replace error