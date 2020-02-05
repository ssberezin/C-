//#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"



Menu::Menu()
{	
	string str= "#Do 1-st#Do 2-nd#Do 3-d#Do 4-th#Exit#" ;	
	GetStrToVec(str, Item);	
	size = Item.size();
	curr = 0;
	
}

Menu::Menu(string str)
{	
	GetStrToVec(str, Item);
	size = Item.size();
	curr = 0;
}

void Menu::GetStrToVec(string & str, vector<string> &obj)
{
	char *tmp = new char[str.size() + 1];
	char *context = new char[str.size() + 1];
	strcpy(tmp, str.c_str());
	char *pstr = strtok_s(tmp, "#", &context);	
	vector<string>arr;
	while (pstr != NULL)
	{
		obj.push_back(pstr);
		pstr = strtok_s(NULL, "#", &context);
	}
}



int Menu::choose()
{
	while (1)
	{
		show();
		switch (_getch())
		{
		case 72: //go up
			curr == 0 ? curr = size-1 : curr--;
			break;
		case 80: // go down
			curr == size-1 ? curr = 0 : curr++;
			break;
		case 13: //enter
			return curr;
			break;
		default:
			break;
		}
	}
}

void Menu::show()
{
	system("cls");
	cout << "\t\t\tOOP. EXAM TASK.\n\n";
	int i = 0;
	
	for (auto it = Item.begin(); it != Item.end(); ++it)
	{
		i == curr ? cout << ">> " : cout << "   ";
		cout << i + 1 << ": " << (*it) << "\n";
		i++;
	}
}

int MenuTest::choose()
{
	while (1)
	{
		show();
		switch (_getch())
		{
		case 72: //go up
			curr == 0 ? curr = size - 1 : curr--;
			break;
		case 80: // go down
			curr == size - 1 ? curr = 0 : curr++;
			break;
		case 13: //enter
			return curr;
			break;
		default:
			break;
		}
	}
	
}

void MenuTest::show()
{
	system("cls");
	cout << "\t\t\tOOP. EXAM TASK.\n\n";
	int i = 0;
	cout << Item[0] << "\n";
	for (auto it = Item.begin()+1; it != Item.end(); ++it)
	{
		/*i == curr ? cout << ">> " : cout << "   ";
		cout<< (*it) << "\n";
*/
		i == curr ? cout << ">> " : cout << "   ";
		cout << i + 1 << ": " << (*it) << "\n";
		i++;
		
	}
}


