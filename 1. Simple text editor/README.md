
# Simple Console-Based Text Editor

This project is a simple console-based text editor implemented in C. It demonstrates the basics of procedural and structural programming, memory management, and dynamic arrays. The text editor supports various operations such as adding text, printing text, saving to and loading from files, and finding substrings.

## Features

1. **Add Text**: Add a new line to the text editor.
2. **Print Text**: Display all text in the console.
3. **Save Text**: Save the current text to a file.
4. **Load Text**: Load text from a file.
5. **Find Substring**: Find the index of a substring in the text.
6. **Start New Line**: Start a new line in the text.
7. **Insert Text**: Insert text at a specific line and position.

## Commands

- `help`: Show help information.
- `exit`: Exit the text editor.
- `add`: Add a new line to the text editor.
- `print`: Display all text in the console.
- `save`: Save the text to a file.
- `load`: Load the text from a file.
- `find`: Find a substring's index in the text.
- `newline`: Start a new line.
- `input`: Insert text at a specific line and position.

## Usage

Upon running the program, you will be greeted with a welcome message and instructions to type `help` to see all commands. You can then use the commands to interact with the text editor.

## Examples 👀

1. **Add Text**

```sh 
>> add
Enter the line to add: Hello, text editor!
Line added successfully!
```

2. **Print Text**

```sh 
>> print
Hello, text editor!
```

3. **Save Text**

```sh 
>> save
WARNING! If the file has some data in it, it will be OVERWRITTEN!
Enter the filename: my_text
The file was opened.
Text saved to the file successfully!
```

4. **Load Text**

```sh 
>> load
Enter the filename: my_text
The file was opened
Do you want to add text to existing one? y/n
```

5. **Find Substring**

```sh 
>> find
Enter the substring to find: text
The substring "text" is found at position 7 in line 0
```

## Implementation Details 🔍

The implementation includes the following functions:

- `print_help()`: Prints the list of available commands.
- `add_text(const char* line)`: Adds a new line of text to the editor.
- `print_text()`: Prints all lines of text to the console.
- `save_to_file(char* filename)`: Saves the current text to a file.
- `load_from_file(char* filename)`: Loads text from a file.
- `find_substring(char* substring)`: Finds a substring within the text and prints its position.
- `input_text(int line_index, int pos)`: Inserts text at a specific line and position. **DOES NOT WORK ❌**
- `parse_command(char* command)`: Parses and executes the given command.

## Memory Management 🧠

The text editor uses dynamic arrays to manage memory efficiently. The `add_text` function ensures that the array is resized when necessary. Memory is allocated and deallocated properly to avoid memory leaks.

## Additional Resources 📕

For more information on the concepts used in this project, refer to the following resources:

- [Programming Languages Principles and Paradigms](https://cplusplus.com/reference/cstdio/fopen/)
- [Computer Systems: A Programming Perspective](https://cplusplus.com/reference/cstdio/fopen/)

## Conclusion 🏆

This simple console-based text editor is a great way to understand the basics of procedural and structural programming, memory management, and dynamic arrays in C. It provides hands-on experience with common operations such as adding, printing, saving, loading, and searching text.
