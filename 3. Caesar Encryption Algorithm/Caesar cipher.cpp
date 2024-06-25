#include<stdio.h>
#include <iostream>

bool is_letter(char c) {
	printf("%d\n", c);
	printf("%d\n", 'A');
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

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

int main()
{	
	const char* raw_text = "Test!{Z}";
	int key = 69;
	char* encrypted_text = encrypt(raw_text, key);
	printf("Encrypted text: %s\n", encrypted_text);
	return 0;
}