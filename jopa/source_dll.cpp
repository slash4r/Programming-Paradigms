#include <string.h>
#include "pch.h"
#include "framework.h"

extern "C"
{
	__declspec(dllexport) char* encrypt(char* raw_text, int key) {
		int text_length = strlen(raw_text);
		char* encrypted_text = new char[text_length + 1];

		key = key % 26;
		for (int i = 0; i < text_length; i++) {
			char c = raw_text[i];

			// dealing with lower case letters
			if ((c >= 'a' && c <= 'z'))
			{
				encrypted_text[i] = (c - 'a' + key) % 26 + 'a';
			}
			// dealing with upper case letters
			else if ((c >= 'A' && c <= 'Z'))
			{
				encrypted_text[i] = (c - 'A' + key) % 26 + 'A';
			}
			else
			{
				encrypted_text[i] = c;
			}
			encrypted_text[text_length] = '\0';
		}

		return encrypted_text;

	}


	__declspec(dllexport) char* decrypt(char* encrypted_text, int key) {
		int text_length = strlen(encrypted_text);
		char* decrypted_text = new char[text_length + 1];

		key = key % 26;
		for (int i = 0; i < text_length; i++) {
			char c = encrypted_text[i];

			// dealing with lower case letters
			if ((c >= 'a' && c <= 'z'))
			{
				// +26 to avoid negative numbers
				decrypted_text[i] = (c - 'a' - key + 26) % 26 + 'a';
			}
			// dealing with upper case letters
			else if ((c >= 'A' && c <= 'Z'))
			{
				decrypted_text[i] = (c - 'A' - key + 26) % 26 + 'A';
			}
			else
			{
				decrypted_text[i] = c;
			}
			decrypted_text[text_length] = '\0';
		}

		return decrypted_text;
	}

};