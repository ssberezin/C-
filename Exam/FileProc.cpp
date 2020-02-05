#include "FileProc.h"


void ShowFileContStud(string path, int mode)
{
	
	cout << left << setw(10) << "First name" << setw(10) << "Last name" << setw(6) <<
		"Status" << setw(8) << "Groupe" << setw(8) << "Login" << setw(8) <<
		"Password" << setw(10) << right << "Phone" <<
		"\n---------------------------------------------------------------------------------------------\n";
	string  tmp;
	ifstream file(path);
	if (!file.is_open())
		throw myErr("Error in opening file!", 41);

	//output file contents to the screen

	while (!file.eof())
	{
		getline(file, tmp);
		cout << tmp << "\n";
	}
	file.close();
	
}

void SelectStatus()
{
	Admin obj_adm;	
	Menu m("#Admin#Student#Exit#");
	
	
	while (1)
	{
		try
		{
		switch (m.choose())
		{
		case 0:
			//admin entrence				
			obj_adm.CheckRegAdminData("files\\AdminLog.dat");
			break;
		case 1:
			//student entrence
			SelectAutorization();			
			//while (_getch() == 0);
			break;
		case 2:


			//Exit				
			return;
		}

		}
		catch (myErr obj)
		{
			obj.showMes();
			while (_getch() == 0);

		}
		
	}
	
}

void SelectAutorization()
{
	Menu m("#...#Login#Registration");
	Admin obj_adm;
	Student obj_st;
	string login="";
	while (1)
	{
		switch (m.choose())
		{
		case 0:
			//exit			

			return;
		case 1:
			//student login
			obj_st.DeCodeFile("files\\StudLog.dat");
			if (obj_st.CheckRegStudData("files\\StudLog.dat", login))
			{
				
				obj_st.CodeFile("files\\StudLog.dat");
				obj_st.SelectStudMethod(login);
				break;
			}
			else
			{
				obj_st.CodeFile("files\\StudLog.dat");
				break;
			}
		case 2:
			//registration
			obj_adm.DeCodeFile("files\\StudData.dat");
			obj_adm.DeCodeFile("files\\StudLog.dat");

			obj_adm.RegStud("files\\StudData.dat", "files\\StudLog.dat");

			obj_adm.CodeFile("files\\StudData.dat");
			obj_adm.CodeFile("files\\StudLog.dat");
			break;
		}
	}
}

void ShowOwnRegData(string path, string login)
{
	
	
	Student obj_stud;
	vector<Student>vec;
	
	string  str;
	ifstream file(path);
	if (!file.is_open())
		throw myErr("Error in opening file !", 41);

	while (!file.eof())
	{
		getline(file, str);
		if (str[str.size()] == '\n')
			str[str.size()] = '\0';
		if (str == "")
			continue;
		obj_stud.GetVecStud(vec, str);
		string tm = vec[vec.size()-1].GetLogin();
		if (vec[vec.size()-1].GetLogin() == login)
		{
			cout <<"\n\n"<<left << setw(12) << "First name" << setw(12) 
				<< "Last name"<< setw(12) <<"Status" << setw(12) 
				<< "Position" << setw(12) << "Login"<< setw(8)
				<<"Password" << setw(12) << right << "Phone num."
				<< left << setw(10) << "\tID" << "\n"
				"-----------------------------------------------------------------------------------------\n";
			vec[vec.size()-1].ShowInfo();
			while (_getch() == 0);
			break;
		}
	}

	file.close();
	

}

void GetStr(vector<string>& arr, string path)
{
	
	
	Student obj_st;
	string  str;
	ifstream file(path);
	if (!file.is_open())
		throw myErr("Error in opening file !", 41);

	while (!file.eof())
	{
		getline(file, str);
		if (str[str.size()] == '\n')
			str[str.size()] = '\0';
		obj_st.GetVec(arr, str);
	}

	file.close();
	

}















