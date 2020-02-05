#pragma once
#include"Menu.h"



class myErr
{
	string typeErr;
	int kodErr;
public:
	myErr(string typeErr,int kodErr);
	void showMes();
	string GetTypeErr();
	int GetKodeErr();
	
};
