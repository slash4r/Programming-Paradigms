#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <functional>

using namespace std;

vector<string> variables;
vector<double> variables_values;


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
	string current_alpha_token = "";

	for (int i = 0; i < end; i++)
	{
		char token = s[i];

		if (token != ' ')
		{
			if (isalpha(token))
			{
				current_alpha_token += token;
				continue;
			}

			else
			{
				if (is_token_function(current_alpha_token))
				{
					tokens.push_back(current_alpha_token);
					current_alpha_token = "";
				}

				else if (current_alpha_token != "")
				{
					// find index of a variabe in the variables array
					for (int i = 0; i < variables.size(); i++)
					{
						if (current_alpha_token == variables[i])
						{
							double value = variables_values[i];
							tokens.push_back(to_string(value));
							break;
						}
					}
					current_alpha_token = "";
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

					if (token == '-' && i + 1 < end && isdigit(s[i + 1]))
					{
						current_token += token;
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

	if (is_token_function(current_alpha_token))
	{
		tokens.push_back(current_alpha_token);
		current_alpha_token = "";
	}

	else if (current_alpha_token != "")
	{
		// find index of a variabe in the variables array
		for (int i = 0; i < variables.size(); i++)
		{
			if (current_alpha_token == variables[i])
			{
				double value = variables_values[i];
				tokens.push_back(to_string(value));
				break;
			}
		}
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


vector<string> ShuntingYard(vector<string>& tokens) {
    vector<string> output;
    stack<string> operators;

    for (const string& token : tokens) {
		if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1) || (token[0] == '-' && token.size() > 1))  // If token is a number
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


double evaluate(const vector<string>& postfix) {
	stack<double> numbers;

	for (const string& token : postfix) {
		if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1) || token.size() > 1 && isdigit(token[1]))
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
				numbers.push(pow(num2, num1)); // error here
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


bool check_variable(string& token)
{
	// take substring from 0 to 3 to check if its a variable
	string variable = token.substr(0, 3);
	if (variable == "var")
	{
		return true;
	}
	return false;
}

void get_variables(string& token, vector<string>& var_array, vector<double>& var_val_array)
{
	string variable = "";
	int var_end;
	// get the variables and their values
	for (int i = 3; i < token.size(); i++)
	{
		if (token[i] == ' ')
		{
			continue;
		}

		if (token[i] == '=')
		{
			var_end = i;
			var_array.push_back(variable);
			break;
		}

		if (token[i] != ' ')
		{
			variable += token[i];
			continue;
		}
	}

	double value;
	string equation = token.substr(var_end + 1, token.size());

	vector<string> tokens = get_tokens(equation);
	vector<string> shunting_yard = ShuntingYard(tokens);
	value = evaluate(shunting_yard);
	var_val_array.push_back(value);
}

int main()
{
	string input;
	getline(cin, input);

	while (true) 
	{
		if (!check_variable(input))
		{
			break;
		}

		get_variables(input, variables, variables_values);
		
		getline(cin, input);
	}

	vector<string> tokens = get_tokens(input);

	vector<string> output = ShuntingYard(tokens);

	cout << "Result: " << evaluate(output) << endl;

	return 0;
}