#include <iostream>
#include <vector>
#include <string>
using namespace std;


vector<char> valid_tokens = {
	'+', 
	'-', 
	'*', 
	'/', 
	'(', 
	')' 
};


bool is_valid_token(char token)
// check if token is in valid_tokens
{

	int end = valid_tokens.size();
	for (int i = 0; i < end; i++)
	{
		if (token == valid_tokens[i])
		{
			return true;
		}
	}
	return false;
}


vector<string> get_tokens(string s)
{
	vector<string> tokens;
	int end = s.size();
	string current_number = "";

	for (int i = 0; i < end; i++)
	{
		char token = s[i];

		if (s[i] != ' ')
		{
			// check if its a number
			if (isdigit(token))
			{
				current_number += token;
				continue;
			}

			else {
				if (current_number != "")
				{
					tokens.push_back(current_number);
					current_number = "";
				}

				if (is_valid_token(token))
				{
					current_number += token;
					tokens.push_back(current_number);
					current_number = "";
					continue;
				}

				cout << "Invalid token: " << token << endl;
				return {};
			}
		}
	}

	if (current_number != "")
	{
		tokens.push_back(current_number);
	}

	return tokens;
}




int main()
{
	string input;
	cout << "Enter a string: ";
	getline(cin, input);
	
	vector<string> tokens = get_tokens(input);

	for (int i = 0; i < tokens.size(); i++)
	{
		cout << tokens[i] << endl;
	}

	return 0;
}