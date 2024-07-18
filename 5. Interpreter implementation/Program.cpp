#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <functional>

using namespace std;


vector<char> valid_operators = {
	'+', 
	'-', 
	'*', 
	'/',
};


vector<string> valid_functions = {
	"max",
	"min", 
	"abs",
	"pow",
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


bool is_token_function(string token)
{
	for(const string& function : valid_functions)
	{
		if (token == function)
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
	string current_token = "";
	string current_function = "";

	for (int i = 0; i < end; i++)
	{
		char token = s[i];

		if (token != ' ')
		{
			if (isalpha(token))
			{
				current_function += token;
				continue;
			}

			else
			{
				if (current_function != "")
				{
					tokens.push_back(current_function);
					current_function = "";
				}

				// check if its a number
				if (isdigit(token) || token == '.')
				{
					current_token += token;
					continue;
				}

				else
				{
					if (current_token != "")
					{
						tokens.push_back(current_token);
						current_token = "";
					}

					if (token == ',')
					{
						current_token += token;
						tokens.push_back(current_token);
						current_token = "";
						continue;
					}

					if (is_token_operator(token))
					{
						current_token += token;
						tokens.push_back(current_token);
						current_token = "";
						continue;
					}

					cout << "Invalid token: " << token << endl;
					return {};
				}
			}			
		}
	}

	if (current_token != "")
	{
		tokens.push_back(current_token);
	}

	if (current_function != "")
	{
		tokens.push_back(current_function);
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
	else if (is_token_function(token))
	{
		return 3;
	}

	return -1; // invalid token
}


vector<string> ShuntingYard(vector<string> tokens) {
    vector<string> output;
    stack<string> operators;

    for (const string& token : tokens) {
        if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1))  // If token is a number
		{ 
			output.push_back(token);
        } 

		else if (is_token_function(token))
		{
			operators.push(token);
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

			// handle functions
			if (!operators.empty() && is_token_function(operators.top()))
			{
				output.push_back(operators.top());
				operators.pop();
			}
        }

		// handle commas
		else if (token == ",")
		{
			while (!operators.empty() && operators.top() != "(")
			{
				output.push_back(operators.top());
				operators.pop();
			}
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


double evaluate(vector<string> postfix) {
	stack<double> numbers;

	for (const string& token : postfix) {
		if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1))
		{
			numbers.push(stod(token));
		} 

		else if (is_token_function(token))
		{
			double num1 = numbers.top();
			numbers.pop();

			if (token == "max") 
			{
				double num2 = numbers.top();
				numbers.pop();
				numbers.push(max(num1, num2));
			} 
			else if (token == "min") 
			{
				double num2 = numbers.top();
				numbers.pop();
				numbers.push(min(num1, num2));
			} 
			else if (token == "abs") 
			{
				numbers.push(abs(num1));
			} 
			else if (token == "pow") 
			{
				double num2 = numbers.top();
				numbers.pop();
				numbers.push(pow(num1, num2));
			}
		}

		else 
		{
			double num2 = numbers.top();
			numbers.pop();
			double num1 = numbers.top();
			numbers.pop();

			if (token == "+") 
			{
				numbers.push(num1 + num2);
			} 
			else if (token == "-") 
			{
				numbers.push(num1 - num2);
			} 
			else if (token == "*") 
			{
				numbers.push(num1 * num2);
			} 
			else if (token == "/") 
			{
				numbers.push(num1 / num2);
			}
		}
	}

	return numbers.top();
}


int main()
{
	string input;
	cout << "Enter an equation: ";
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

	cout << "Result: " << evaluate(output) << endl;

	return 0;
}