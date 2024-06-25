#include <Windows.h>
#include <iostream>
using namespace std;

int const INPUT_LENGTH = 256;

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

int main()
{
	// Pointer to sum function
	typedef char* (*encr_ptr_t)(char*, int);
	// Pointer to multiply function
	typedef char* (*decr_ptr_t)(char*, int);
	HINSTANCE handle = LoadLibrary(TEXT("Caesar_lib.dll")); // Load the DLL

	if (handle == nullptr || handle == INVALID_HANDLE_VALUE) 
	{
		cout << "Lib not found" << endl;
		return 1;
	}

	encr_ptr_t encr_ptr = (encr_ptr_t)GetProcAddress(handle, TEXT("encrypt")); // Get the address of the function
	if (encr_ptr == nullptr)
	{
		cout << "Function not found" << endl;
		return 1;
	}
	decr_ptr_t decr_ptr = (decr_ptr_t)GetProcAddress(handle, TEXT("decrypt")); // Get the address of the function
	if (decr_ptr == nullptr)
	{
		cout << "Function not found" << endl;
		return 1;
	} 

	while (true)
	{
		cout << "Hello! And welcome to Caesar Encryption program" << endl;
		cout << "Do you want to encrypt or decrypt a message? e/d" << endl;
		char* choice = get_input();
		if (!strcmp(choice, "e"))
		{
			cout << "Enter the message you want to encrypt" << endl;
			char* raw_text = get_input();
			cout << "Enter the key" << endl;
			int key;
			cin >> key;
			cin.ignore();
			cout << "Encrypted text: " << encr_ptr(raw_text, key) << endl;
		}
		else if (!strcmp(choice, "d"))
		{
			cout << "Enter the message you want to decrypt" << endl;
			char* encrypted_text = get_input();
			cout << "Enter the key" << endl;
			int key;
			cin >> key;
			cin.ignore();
			cout << "Decrypted text: " << decr_ptr(encrypted_text, key) << endl;
		}
		else if (!strcmp(choice, "exit"))
		{
			break;
		}
		else
		{
			cout << "Invalid input! To exit the program enter \"exit\"" << endl;
		}
	}
	FreeLibrary(handle);


	return 0;
}
