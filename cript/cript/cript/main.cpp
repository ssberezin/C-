#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void CodeString(string &str);
void DeCodeString(string &str);

int main()
{
	string Text= "Hello World";	
	cout << "\n Before" << Text << "\n";
	CodeString(Text);
	cout << "\n Cripted text: " << Text << "\n";
	DeCodeString(Text);
	cout << "\n UNcripted text: " << Text << "\n";
	getchar();
}

void CodeString(string &str)
{
	for (int i = 0; i <= str.size(); i++)
		if (str[i] == ' ')
			str[i] += 4;
		else
			str[i] += 3;
	
}

void DeCodeString(string &str)
{
	for (int i = 0; i <= str.size(); i++)
		if (str[i] == '$')
			str[i] -= 4;
		else
			str[i] -= 3;

}