#include<stdio.h>
#include <iostream>

char* encrypt(const char* raw_text, int key) {
	int text_length = strlen(raw_text);
	char* encrypted_text = new char[text_length+1];

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

char* decrypt(char* encrypted_text, int key) {
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


int main()
{	
	const char* raw_text = "Roses are red, violets are blue.";
	int key = 69;
	char* encrypted_text = encrypt(raw_text, key);
	printf("Encrypted text: %s\n", encrypted_text);
	
	char* decrypted_text = decrypt(encrypted_text, key);
	printf("Decrypted text: %s\n", decrypted_text);

	return 0;
}