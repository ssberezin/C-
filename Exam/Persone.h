#pragma once
#include "myErr.h"
class Persone
{
protected:
	string FName, LName,  phone, log, pass, status;
	int ID;
public:
	Persone() :FName("EMPTY"), LName("EMPTY"), phone("EMPTY"), log("EMPTY"), pass("EMPTY"), status("EMPTY"), ID(0) {};
	Persone(string FName, string LName, string phone, string log, string pass, string status, int ID);

	void SetFName(string FName);
	void SetLName(string LName);
	void SetPhone(string phone);
	void SetLogin(string log);
	void SetPassword(string pass);
	void SetStatus(string status);
	void SetID(int ID);
	string GetFName()const;
	string GetLName()const;
	string GetPhone()const;
	string GetLogin()const;
	string GetPassword()const;
	string GetStatus()const;
	int GetID();
	int GetID()const;

	void CodeFile(string path);
	void DeCodeFile(string path);

	virtual void ShowInfo() = 0;

	
	~Persone();
};
