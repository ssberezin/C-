#pragma once
#include "Persone.h"
#include "Test.h"




class Student :public Persone
{
	string Groupe;
public:
	Student() :Persone() { this->Groupe = "EMPTY"; };

	Student(string Groupe, string FName, string LName, string phone,
		string log, string pass, string status, int ID) :
		Persone(FName, LName, phone, log, pass, status, ID)
	{
		this->Groupe = Groupe;
	};

	friend ostream& operator << (ostream &s, const Student &obj);//output object

	void SetGroupe(string Groupe);// setter

	string GetGroupe()const;//getter

	void  ShowInfo();//show info about Student object to screen

	void ShowOwnRegStudData(string login);//for show student reg data

	void Testing() {};//not realized yet

	void SelectStudMethod(string &login);//for choose eny Student methode

	bool CheckLogStudAvail(string inp_log, string path);//checking for availebel login

	friend bool operator==(const Student&, const Student&);//overload == for algorithm

	string GetFirst(string str);//get first token from line

	bool CheckRegStudData(string path, string &login);//cheking for correct authorisation and for availeble eny data about stedent logs

	bool CheckLogStud(string inp_log, string inp_pass, string path);//constituent of CheckRegStudData

	void GetVec(vector<string>&vec, string str);//form vector from line tockens (constituent GetStr) 

	void GetVecStud(vector<Student>&vec, string str);//return vector of Student class from inp line

	void GetStrStud(vector<Student>&vec, string path); //return vector of Student class from file

	void ChangePass(string login);//for change password
	
	string NewPass();//return string whith value of new pass

	bool CheckLogPass(string path, string login);//check login adn password befor change

	template<typename T>
	void SaveToFileOUTST(vector<T>& arr, string path);
	~Student(){};
};

template<typename T>
inline void Student::SaveToFileOUTST(vector<T>& arr, string path)
{



	ofstream file(path, ios::out);
	if (!file)
	{
		CodeFile(path);
		throw myErr("Error in opening file to rewrite!", 46);
	}
	int i = 1;
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		string tmp = typeid((*it)).name();
		if (tmp == "class Student" || tmp == "class Admin")
			file << (*it);
		else
		{
			int k = i % 2;
			file << (*it) << "#";
			if (i > 1 && !k)
				file << "\n";
			i++;
		}
	}
	file.close();

}

