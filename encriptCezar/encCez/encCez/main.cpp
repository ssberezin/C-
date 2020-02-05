#include <iostream>
using namespace std;

int main()
{
	setlocale(0, "RUS");

	char buff[50] = { 0 };

	cout << "¬ведите сообщение,которое будет закодированно" << endl;
	cin >> buff;

	for (int i = 0; i < strlen(buff); i++)
		buff[i] += 3;
	cout << buff << endl;

	cout << "Decode: " << endl;
	for (int i = 0; i < strlen(buff); i++)
		buff[i] -= 3;
	cout << buff << endl;

	system("pause");
	return 0;
}