#include "Persone.h"






Persone::Persone(string FName, string LName, string phone, string log, string pass, string status, int ID) :FName(FName), LName(LName), phone(phone), log(log), pass(pass), status(status), ID(ID) {}

void Persone::SetFName(string FName)
{
	this->FName = FName;
}

void Persone::SetLName(string LName)
{
	this->LName = LName;
}

void Persone::SetPhone(string phone)
{
	this->phone = phone;
}

void Persone::SetLogin(string log)
{
	this->log = log;
}

void Persone::SetPassword(string pass)
{
	this->pass = pass;
}

void Persone::SetStatus(string status)
{
	this->status = status;
}

void Persone::SetID(int ID)
{
	this->ID = ID;
}

string Persone::GetFName()const
{
	return FName;
}

string Persone::GetLName()const
{
	return LName;
}

string Persone::GetPhone()const
{
	return phone;
}

string Persone::GetLogin()const
{
	return log;
}

string Persone::GetPassword()const
{
	return pass;
}

string Persone::GetStatus()const
{
	return status;
}

int Persone::GetID()
{
	return ID;
}

int Persone::GetID()const
{
	return ID;
}

void Persone::CodeFile(string path)
{
	string  str;
	ifstream file(path);
	if (!file.is_open())
		throw myErr("Error in opening file!", 41);

	//output file contents to the screen
	vector <string>vec;
	while (!file.eof())

	{
		getline(file, str);
		//coding line
		for (int i = 0; i <= str.size(); i++)			
			if (str[i] == ' ')
				str[i] += 4;
			else
				if (str[i] == '\n' || str[i] == '\0')
					continue;
				else
				str[i] += 3;
		vec.push_back(str);
	}
	file.close();

	ofstream file_out(path, ios::out);
	if (!file_out)
		throw myErr("Error in opening file to rewrite!", 46);

	for (auto it = vec.begin(); it != vec.end(); ++it)	
			file_out << (*it)<<"\n";	
	
	file_out.close();
}

void Persone::DeCodeFile(string path)
{
	string  str;
	ifstream file(path);
	if (!file.is_open())
		throw myErr("Error in opening file!", 41);

	
	//output file contents to the screen
	vector <string>vec;
	while (!file.eof())

	{
		getline(file, str);
		if (str != "")
		{//coding line
			for (int i = 0; i <= str.size(); i++)

				if (str[i] == '$')
					str[i] -= 4;
				else
					str[i] -= 3;

			str += '\n';
			vec.push_back(str);
		}
		else
		{
			vec.push_back(str);
			break;
		}
	}
	file.close();

	ofstream file_out(path, ios::out);
	if (!file_out)
		throw myErr("Error in opening file to rewrite!", 46);

	for (auto it = vec.begin(); it != vec.end(); ++it)
		file_out << (*it);

	file_out.close();
}






Persone::~Persone()
{
}


