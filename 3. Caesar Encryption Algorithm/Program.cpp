#include <Windows.h>
#include <iostream>
using namespace std;

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

	char string[] = "Roses are red, violets are blue."; // Text to encrypt
	char* raw_text = string;
	cout << encr_ptr(raw_text, 3) << endl;
	cout << decr_ptr(raw_text, 3) << endl;

	FreeLibrary(handle);


	return 0;
}