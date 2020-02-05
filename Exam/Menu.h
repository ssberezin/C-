#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <iomanip>
#include<fstream>
#include <conio.h>
#include<vector>
#include <map>
#include<algorithm>
#include <typeinfo>



using namespace std;
class Menu
{
protected:
	vector <string> Item ;	
	int size;
	int curr;
public:
	Menu();
	Menu(string str);
	int choose();
	virtual void show();	
	void GetStrToVec(string &str, vector<string> &obj);


	~Menu() {};
	
};

class MenuTest:public Menu
{

	
public:	
	MenuTest(string str) :Menu(str) {};
	int choose();
	void show();
};