#pragma once
#include "Student.h"
#include "FileProc.h"
class Admin:public Persone
{
	string Position;
public:
	
	Admin() :Persone() { this->Position = "EMPTY"; };	
	
	Admin(string Position, string FName, string LName, string phone, string log, string pass, string status,
		int ID) : Persone(FName, LName, phone, log, pass, status, ID) {
		this->Position = Position;
	};
	
	void SetPosition(string Position) { this->Position = Position; };//setter
	
	string GetPosition() { return Position; };//getter
	
	friend ostream& operator << (ostream &, const Admin &obj);//for output object to file
	
	void ShowInfo();//show Admin object to screen

	void ShowStudbase();//for shor student reg info

	void RegStud(string path, string FileLog);//for registration student user

	void RegAdmin();//for registration admin user

	void CheckRegAdminData(string path);//check for available admin data

	bool CheckLog(string inp_log, string inp_pass, string path);//compare log/password pares


	//===========================================delete entrie=============================
	void DeleteStud(string FileName, string FileLog );//for delete nedd studentn entrie 

	void DelLogStud(string del_log,  string path);// fore delete log and pass of student

	void CMPandDEL(vector<Student>& , int ID, string FileName, string FileLog);//compare and delete need entrie (constituent of DeleteStud)

	//==========================================Edit entrie================================
	void EditStud(string FileName);//for edit entries about students

	void ShowObj(Student &obj);//show Admin object to the screen

	void ChoiceEditStud(Student &);//for choose methods to edit about students
	
	//===========================================File operations ==========================
	//have not taken root in FileProc.h//не прижились в FileProc.h,хз....
	template<typename T>
	void SaveToFileAPP(vector<T>&, string path);//save to file with add

	template<typename T>
	void SaveToFileOUT(vector<T>&, string path);//save to file with rewrite

	

	void SelectAdmMethod();//for choose any Admin methouds

	//=========================Methods for work with admin reg data========================
	
	void ChangeRegData(string path, string FileLog);//for change login and password 

	void SelectOwnAdmRegData(string login);//menu for select method du work with user reg data
	
	void ChooswAdmMet(string login);//menu for select any adm methods

	void EditAdm(string old_log, string new_log, string new_pass, string path);//for edit admin reg data
	
	


	~Admin() {};
};


//=================Operations with files ================================================
//have not taken root in FileProc.h//не прижились в FileProc.h,хз....

//save to file with add
template<typename T>
inline void Admin::SaveToFileAPP(vector<T>& arr, string path)
{
	if (!arr.size())
		throw myErr("There are no entries to input the file...", 50);

	ofstream file(path, ios::app);
	if (!file)
		throw myErr("Error in opening file to add!", 45);
	int i = 1;
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		string tmp = typeid((*it)).name();
		if (tmp == "class Student")
			file << (*it);
		else
		{
			file << (*it) << "#";
			i++;
			if (i>1 && i % 2)
				file << '\n';
		}
	}
	file.close();

}

//save to file with rewrite
template<typename T>
inline void Admin::SaveToFileOUT(vector<T>& arr, string path)
{

	if (!arr.size())
		throw myErr("There are no entries to input the file...", 50);

	ofstream file(path, ios::out);
	if (!file)
		throw myErr("Error in opening file to rewrite!", 46);

	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		string tmp = typeid((*it)).name();
		if (tmp == "class Student" || tmp == "class Admin")
			file << (*it);
		else
			file << (*it) << "#";
	}
	file.close();

}

