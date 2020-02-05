#include "myErr.h"

myErr::myErr(string typeErr, int kodErr) : typeErr(typeErr), kodErr(kodErr) {}

void myErr::showMes()
{
	
		cout << "Error :\"" << typeErr << "\","<<kodErr<<"\n\n";
	
	
}

string myErr::GetTypeErr()
{
	return typeErr;
}

int myErr::GetKodeErr()
{
	return kodErr;
}


