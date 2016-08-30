
#include<stack>
#include<string>
#include<iostream>
using namespace std;

string convert_char_to_string(char s)
{
	string a = "1";//простите за костыль
	a[0] = s;
	return a;
}
bool it_is_number(string a)
{
	if ('0' <= a[0] && a[0] <= '9')
		return true;
	else
		return false;
}
bool it_is_num(char s)
{
	if (s == '+' || s == '-' || s == '*' || s == '/' || s == '(' || s == ')')
		return false;
	else
		return true;
	
}
bool num_is_true(string s)
{
	int n = s.size();
	if (!('0' <= s[n - 1] && s[n - 1] <= '9'))
		return false;
	if (!('0' <= s[0] && s[0] <= '9'))
		return false;
	for (int i = 0; i < n; i++)
	{
		if ( s[i] != '.'&&s[i] != ',' && (s[i]<'0' || s[i]>'9'))
			return false;
	}
	return true;
}
double convert_string_to_double(string a)
{
	double result = 0.0;
	int a_size = a.size();
	int i = 0;
	for (i = 0; i < a_size && (a[i] != '.' && a[i] != ','); i++)
	{
		result *= 10;
		result += (a[i] - '0');
	}
	double k = 0.1;
	i++;
	for (; i < a_size; i++)
	{
		result += (k*(a[i] - '0'));
		k *= 0.1;
	}
	return result;
}

int main()

{
	setlocale(0, "");
	string input;
	getline(cin, input);

	stack<string>output;
	stack<char>operators;
	int input_size = input.size();
	//переведем из инфиксной записи в обратную польскую
	for (int i = 0; i < input_size; )
	{
		bool exit_brecket = false;
		while (input[i] == ' ')
			i++;
		string symbol = "";
		if (i < input_size && (input[i] == '-' || input[i] == '+'))
		{
			if (!operators.empty() && (operators.top() == '*' || operators.top() == '/' || operators.top() == '+' || operators.top() == '-'))
			{
				output.push(convert_char_to_string(operators.top()));
				operators.pop();
			}
			operators.push(input[i]);
			i++;
		}
		if (i < input_size && (input[i] == '/' || input[i] == '*'))
		{
			if (!operators.empty() && (operators.top() == '*' || operators.top() == '/'))
			{
				output.push(convert_char_to_string(operators.top()));
				operators.pop();
			}
			operators.push(input[i]);
			i++;
		}
		while (i < input_size && (input[i] == '('||input[i] == ' ' ))
		{
			if (input[i] != ' ')
				operators.push('(');
			i++;
		}
		while (i < input_size&&(input[i] == ')' || input[i] == ' ' ))
		{
			if (input[i] != ' ')
			{
				while (operators.empty() == false && operators.top() != '(')
				{
					output.push(convert_char_to_string(operators.top()));
					operators.pop();
					exit_brecket = true;
				}
				if (operators.empty())
				{
					cout << "неправильно расставлены скобки" << endl;
					return 0;
				}
				else
					operators.pop();
			}
			i++;
		}
		if (exit_brecket)
			continue;
		while (i < input_size&&it_is_num(input[i]) )
		{
			if (input[i] != ' ')
				symbol += input[i];
			i++;
		}
		if (symbol.compare("")!=0&&num_is_true(symbol) == false)
		{
			cout << "некорректный ввод, строка содержит недопустимое выражение " << symbol << endl; 
			return 0;
		}
		else
		{
			output.push(symbol);
		}
	}
	while (!operators.empty())
	{
		if (operators.top() == '(')
		{
			cout << "количество закрывающих и открывающих скобок не совпадает";
			return 0;
		}
		output.push(convert_char_to_string(operators.top()));
		operators.pop();
	}
	int symbols_size = output.size();
	string*symbols = new string[symbols_size];
	for (int i = symbols_size - 1; !output.empty(); i--)
	{
		symbols[i] = output.top();
		output.pop();
	}
	stack<double>result;
	for (int i = 0; i < symbols_size; i++)
	{
		double a, b;
		if (it_is_number(symbols[i]))
			result.push(convert_string_to_double(symbols[i]));
		else
		{
			if (symbols[i].compare("*") == 0)
			{
				
				if (!result.empty())
				{
					a = result.top();
					result.pop();
				}
				else
				{
					cout << "ERROR!!!!";
					return 0;
				}
				if (!result.empty())
				{
					b = result.top();
					result.pop();
				}
				else
				{
					cout << "ERROR!!!!";
					return 0;
				}
				result.push(a*b);
			}
			else 
			if (symbols[i].compare("/") == 0)
			{
				if (!result.empty())
				{
					a = result.top();
					result.pop();
				}
				else
				{
					cout << "ERROR!!!!";
					return 0;
				}
				if (!result.empty())
				{
					b = result.top();
					result.pop();				
					if (a == 0)
					{
					cout << "присутствует деление на 0!";
					return 0;

					}
					result.push(b/a);
				}
				else
				{
					cout << "ERROR!!!!";
					return 0;
				}
			}
			else
			if (symbols[i].compare("+") == 0)
			{
				if (!result.empty())
				{
					a = result.top();
					result.pop();
				}
				else
				{
					cout << "ERROR!!!!";
					return 0;
				}
				if (!result.empty())
				{
					b = result.top();
					result.pop();
					result.push(a+b);
				}
				else
				{
					cout << "ERROR!!!!";
					return 0;
				}
			}
			else
			if (symbols[i].compare("-") == 0)
			{
				if (!result.empty())
				{
					a = result.top();
					result.pop();
				}
				else
				{
					cout << "ERROR!!!!";
					return 0;
				}
				if (!result.empty())
				{
					b = result.top();
					result.pop();
					result.push(b-a);
				}
				else
				{
					result.push(-a);
				}
			}
		}
	}
	if (result.size() != 1)
		cout << "Ошибка!" << endl;
	else
		printf("%.2f", result.top());
	delete[]symbols;
	return 0;
}

