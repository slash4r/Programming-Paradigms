#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;


vector<char> valid_operators = {
	'+', 
	'-', 
	'*', 
	'/',
};


bool is_token_operator(char token)
// check if token is in valid_tokens
{

	int end = valid_operators.size();
	for (int i = 0; i < end; i++)
	{
		if (token == valid_operators[i] || token == '(' || token == ')')
		{
			return true;
		}
	}
	return false;
}


vector<string> get_tokens(string& s)
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

				if (is_token_operator(token))
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


int get_precedence(const string& token)
{
	if (token == "+" || token == "-")
	{
		return 1;
	}
	else if (token == "*" || token == "/")
	{
		return 2;
	}

	return -1; // invalid token
}

vector<string> ShuntingYard(vector<string> tokens) {
    vector<string> output;
    stack<string> operators;

    for (const string& token : tokens) {
        if (isdigit(token[0]))  // If token is a numbeê
		{ 
			output.push_back(token);
        } 
		
		else if (token == "(" ) 
		{
            operators.push(token);
        } 
		
		else if (token == ")" ) 
		{
            while (!operators.empty() && operators.top() != "(" ) 
			{
                output.push_back(operators.top());
                operators.pop();
            }
            operators.pop(); // Pop the "("
        } 
		
		else 
		{
            int tokenPrecedence = get_precedence(token); // error here
            while (!operators.empty() && get_precedence(operators.top()) >= tokenPrecedence) 
			{
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }

    // Pop any remaining operators
    while (!operators.empty()) 
	{
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
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

	cout << "Shunting Yard: \n" << endl;

	vector<string> output = ShuntingYard(tokens);
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i] << endl;
	}

	return 0;
}