#include "Admin.h"







void Admin::ShowInfo()
{
	cout<< left << setw(10) << FName << setw(10) << LName << setw(6) <<
		status << setw(8) << Position << setw(8) << log << setw(8) <<
		pass << setw(10) << right << phone << setw(10) << ID << "\n";
}
void Admin::ShowStudbase()
{
	Student obj_st;
	vector<Student>vec;
	obj_st.GetStrStud(vec,"files\\StudData.dat");
	cout << "\n\n";
	cout << left << setw(12) << "First name" << setw(12) << "Last name" << setw(14) <<
		"Status" << setw(8) << "Groupe" << setw(8) << "Login" << setw(9) <<
		"Password" << setw(14) << right << "Phone num." <<left<< setw(12) << "\tID" << "\n"
		"-----------------------------------------------------------------------------------------\n";
	for (auto it = vec.begin(); it != vec.end(); ++it)
		it->ShowInfo();
}
//"files\\AdminData.dat"
void Admin::RegStud(string path, string FileLog)
{
	Student obj_st;
	string FName, LName, phone, log, pass, status, groupe;
	int ID;
	cout << "\n";
	cout << right << setw(17) << "First name: "; getline(cin, FName);
	cout << right << setw(17) << "Last name: "; getline(cin, LName);
	cout << right << setw(17) << "Enter phone: "; getline(cin, phone);
	cout << right << setw(17) << "Enter status: "; getline(cin, status);
	cout << right << setw(17) << "Enter groupe: "; getline(cin, groupe);
	cout << right << setw(17) << "Enter ID: "; cin >> ID;
	cin.clear();	cin.ignore();
	
	while (1)
	{
		cout << "\nEnter login: "; getline(cin, log);
		if (obj_st.CheckLogStudAvail(log, FileLog))
		{
			cout << "\nThis login is allready exist. Reenter login...\n\n";
			while (_getch() == 0);
		}
		else			
			break;		
	}

	cout << "Enter password: "; getline(cin, pass);

	Student obj(groupe, FName, LName, phone, log, pass, status, ID);
	vector<Student>arr;
	arr.push_back(obj);	
	SaveToFileAPP(arr, path);
	vector <string>arr_log;
	arr_log.push_back(obj.GetLogin());
	arr_log.push_back(obj.GetPassword());
	SaveToFileAPP(arr_log, FileLog);
	cout << "\n\t\t\tDone.\n";
}

void Admin:: RegAdmin()
{
	string FName, LName, phone, log, pass, status, position;
	int ID;

	cout << right << setw(17) << "First name: "; getline(cin, FName);
	cout << right << setw(17) << "Last name: "; getline(cin, LName);
	cout << right << setw(17) << "Enter phone: "; getline(cin, phone);
	cout << right << setw(17) << "Enter status: "; getline(cin, status);
	cout << right << setw(17) << "Enter position: "; getline(cin, position);
	cout << right << setw(17) << "Enter your ID: "; cin >> ID;
	cin.clear(); cin.ignore();
	cout << "\nEnter login: "; getline(cin, log);
	cout << "Enter password: "; getline(cin, pass);

	Admin obj(position, FName, LName, phone, log, pass, status, ID);
	vector<Admin>arr;
	arr.push_back(obj);
	obj.SaveToFileOUT(arr, "files\\AdminData.dat");
	CodeFile("files\\AdminData.dat");
	vector <string>arr_log;
	arr_log.push_back(obj.GetLogin());
	arr_log.push_back(obj.GetPassword());
	obj.SaveToFileOUT(arr_log, "files\\AdminLog.dat");
	CodeFile("files\\AdminLog.dat");
	cout << "\n\t\t\tDone.\n\n\t\t You mast to login in system\n\n";

}

void Admin:: CheckRegAdminData(string path)
{
	
	string  str, login, password;
	ifstream file(path);
	if (!file)
	{
		cout << "\n\t\tAdmin are not registred."
			"You mast registerede befor login.\n\n";
		while (_getch() == 0);
		RegAdmin();		
		while (_getch() == 0);
		return;
	}
	cout << "\n\n\n\n\n" << right << setw(40) << "Login: "; getline(cin, login);
	cout << right << setw(40) << "Password: "; getline(cin, password);
	DeCodeFile("files\\AdminLog.dat");

	if (!CheckLog(login, password, "files\\AdminLog.dat"))
		{
		cout << "\n\n" << setw(40) << "Incorrect login ore password...\n\n";		
		CodeFile("files\\AdminLog.dat");
		while (_getch() == 0);
		
	}
	else
	{
		cout << "\n\n" << setw(40) << "Access is allowed.";
		while (_getch() == 0);
		CodeFile("files\\AdminLog.dat");
		ChooswAdmMet (login);
		
	}
}


ostream & operator<<(ostream & s, const Admin & obj)
{
	s << obj.FName << "#" << obj.LName <<"#" <<
		obj.status << "#" << obj.Position << "#" << obj.log << "#" <<
		obj.pass << "#" << obj.phone << "#" << obj.ID << "\n";
	return s;
}


//===========================================delete entrie=============================


void Admin::DeleteStud(string FileName, string FileLog)
{
	Student obj_st;
	vector<Student>arr;
	int ID; string i;	
	cout << "\nEnter ID: "; getline(cin, i);
	ID = stoi(i);	
	obj_st.GetStrStud(arr, FileName);
	CMPandDEL(arr, ID, FileName, FileLog);
}


void Admin::CMPandDEL(vector<Student>& arr, int ID, string FileName, string FileLog)
{
	Admin obj;
	for (auto i = arr.begin(); i != arr.end(); ++i)
	{

		if (i->GetID() == ID)
		{
			//delete from StudLog.dat
			DelLogStud(i->GetLogin(), FileLog);
			//delete from StudData.dat
			arr.erase(remove(arr.begin(), arr.end(), (*i)), arr.end());
			cout << "Reg. data of deleting entrie are deleted\n";
			while (_getch() == 0);
			obj.SaveToFileOUT(arr, FileName);
			return;
		}
	}
	cout << "No matches...\n";
	while (_getch() == 0);

}

void Admin::DelLogStud(string del_log, string path)
{
	Student obj;
	Admin adm_obj;
	vector<string> vec;
	string  str;
	ifstream file(path);
	if (!file.is_open())
		throw myErr("Error in opening file !", 41);
	int i = 0;
	while (!file.eof())
	{
		getline(file, str);

		if (str[str.size()] == '\n')
			str[str.size()] = '\0';
		obj.GetVec(vec, str);
		if (del_log == vec[i])
		{
			vec.erase(remove(vec.begin(), vec.end(), vec[i]), vec.end());
			adm_obj.SaveToFileOUT(vec, path);
			file.close();
			cout << "\n Log data of deleting entrie are deleted\n";
			return;
		}

		i += 2;
	}	
	file.close();

	
}




//====================================Edit entrie ====================================

void Admin::ShowObj(Student &obj)
{
	cout << left << setw(12) << "First name" << setw(12) << "Last name" << setw(14) <<
		"Status" << setw(8) << "Groupe" << setw(8) << "Login" << setw(9) <<
		"Password" << setw(14) << right << "Phone num." << left << setw(12) << "ID" << "\n"
		"-----------------------------------------------------------------------------------------\n";
	obj.ShowInfo();
}

void Admin::EditStud(string FileName)
{
	Student obj_st;
	int ID;
	cout << "\nEnter ID: "; cin >> ID;
	cin.ignore(); cin.clear();;
	ifstream file(FileName);
	if (!file.is_open())
		throw myErr("Error in opening file!", 41);
	vector <Student> arr;
	obj_st.GetStrStud(arr, FileName);
	auto it = find_if(arr.begin(), arr.end(), [ID](Student &a)->bool {
		return a.GetID() == ID; });
	if (it == arr.end())
	{
		cout << "\nNo matches...\n";
		while (_getch() == 0);
		return;

	}
	ChoiceEditStud((*it));
	SaveToFileOUT(arr, FileName);

}

void Admin::ChoiceEditStud(Student &obj)
{
	string Groupe,FName, LName, phone, log, pass, status;
	int ID;	
	cout << "\nEditing entrie:\n\n";
	ShowObj(obj);
	string  tmp;
	Menu edst("...#Edit first name#Edit last name#Edit groupe#Edit login#"
				"Edit password#Edit phone number#Edit status#Edit ID");
	while (1)
	{
		cin.ignore();
		switch (edst.choose())
		{
		case 0:
			//...
			return;		
		case 1:
			cout << "\nEnter new first name : ";
			getline(cin, FName);			
			obj.SetFName(FName);
			cout << "\nDone...";
			while (_getch() == 0);
			break;
		case 2:
			cout << "\nEnter new last name: "; getline(cin, LName);			
			obj.SetLName(LName);
			cout << "\nDone...";
			while (_getch() == 0);
			break;
		case 3:
			cout << "\nEnter new groupe: "; getline(cin, Groupe);			
			obj.SetGroupe(Groupe);
			cout << "\nDone...";
			while (_getch() == 0);
			break;
		case 4:
			cout << "\nEnter new login : "; getline(cin, log);			
			obj.SetLogin(log);
			cout << "\nDone...";
			while (_getch() == 0);
			break;
		case 5:
			cout << "\nEnter new password : "; getline(cin, pass);

			obj.SetPassword(pass);
			cout << "\nDone...";
			while (_getch() == 0);
			break;
		case 6:
			cout << "\nEnter new phone number : "; getline(cin, phone);
			obj.SetPhone(phone);
			cout << "\nDone...";
			while (_getch() == 0);
			break;
		case 7:
			cout << "\nEnter new status : "; getline(cin, status);
			obj.SetStatus(status);
			cout << "\nDone...";
			while (_getch() == 0);
			break;
		case 8:
			cout << "\nEnter new ID : "; cin >> ID;
			obj.SetID(ID);
			cin.ignore(); cin.clear();
			cout << "\nDone...";			
			break;
		}
		cout << "\n\nEdited entrie:\n\n";
		ShowObj(obj);
		while (_getch() == 0);



	}

}


void Admin::SelectAdmMethod()
{

	Menu m("#...#Add student#Show students reg data#Delete entrie#Edit etrie#");
	Admin obj;
	while (1)
	{
		switch (m.choose())
		{
		case 0:
			//exit			

			return;
		case 1:
			//student registration
			DeCodeFile("files\\StudLog.dat");
			DeCodeFile("files\\StudData.dat");

			obj.RegStud("files\\StudData.dat", "files\\StudLog.dat");

			CodeFile("files\\StudData.dat");
			CodeFile("files\\StudLog.dat");
			while (_getch() == 0);
			break;
		case 2:
			//show stud base
			DeCodeFile("files\\StudData.dat");
			obj.ShowStudbase();
			CodeFile("files\\StudData.dat");
			while (_getch() == 0);
			break;
		case 3:
			//delete entrie
			DeCodeFile("files\\StudData.dat");
			DeCodeFile("files\\StudLog.dat");

			obj.DeleteStud("files\\StudData.dat","files\\StudLog.dat" );

			CodeFile("files\\StudLog.dat");
			CodeFile("files\\StudData.dat");
			while (_getch() == 0);
			break;
		case 4:
			//edit entrie
			DeCodeFile("files\\StudLog.dat");
			DeCodeFile("files\\StudData.dat");

			obj.EditStud("files\\StudData.dat");
			
			DeCodeFile("files\\StudData.dat");
			CodeFile("files\\StudLog.dat");
			break;


		}
	}
}

void Admin::ChangeRegData(string path, string FileLog)//must be "files\\AdminLog.dat"
{
	string old_pass, old_log, new_pass,tmp, new_log;
	cout << "\n" << right << setw(30) << "Enter old password: "; getline(cin, old_pass);
	vector <string> vec;
	GetStr(vec, FileLog);
	if (old_pass == vec[1])
	{
		cout << "\n"<< right <<setw(30)<<"Enter new login: "; getline(cin,new_log );
		while (1)
		{
			cout << right << setw(30) << "Enter new password: "; getline(cin, new_pass);
			cout  << right << setw(30) <<"Reenter new password: "; getline(cin, tmp);
			cout << "\n";
			if (new_pass == tmp&&tmp!="")
			{
				old_pass = vec[1];
				old_log = vec[0];
				vec[1] = new_pass;
				vec[0] = new_log;
				SaveToFileOUT(vec, FileLog);

				EditAdm(old_log, new_log, new_pass, path);

				cout << "\n" << right << setw(30) << "Done...\n";
				while (_getch() == 0);
				CodeFile(path);
				CodeFile(FileLog);
				throw myErr("Now You must to renter to the system...", 1);
				return;
			}
			else
				cout <<"\n"<< right << setw(30)<<"Passwords do not match. Try agayn...\n\n";
		}		
	}
	cout<<"\nLogin incorrect...\n";
	while (_getch() == 0);

}

void Admin::SelectOwnAdmRegData(string login)
{
	Menu m("#...#Show admin reg data#Edit reg data");
	Admin obj;
	while (1)
	{
		switch (m.choose())
		{
		case 0:
			//exit			

			return;
		case 1:
			//Show admin registration data
			DeCodeFile("files\\AdminData.dat");
			ShowOwnRegData("files\\AdminData.dat", login);
			CodeFile("files\\AdminData.dat");
			//while (_getch() == 0);
			break;
		case 2:
			//
			DeCodeFile("files\\AdminData.dat");
			DeCodeFile("files\\AdminLog.dat");
			ChangeRegData("files\\AdminData.dat","files\\AdminLog.dat" );
			CodeFile("files\\AdminData.dat");
			CodeFile("files\\AdminLog.dat");
			//while (_getch() == 0);
			break;
		}
	}
}

void Admin::ChooswAdmMet(string login)
{
	Menu m("#...#Work with admin reg data#Work with stud data");
	Admin obj;
	while (1)
	{
		switch (m.choose())
		{
		case 0:
			//exit			

			return;
		case 1:
			//Work with admin reg data
			SelectOwnAdmRegData(login);
			//while (_getch() == 0);
			break;
		case 2:
			//Work with stud data
			SelectAdmMethod();
			//while (_getch() == 0);
			break;
		}
	}
}

void Admin::EditAdm(string old_log, string new_log, string new_pass, string path)
{
	
	Student obj_st;	
	ifstream file(path);
	if (!file.is_open())
		throw myErr("Error in opening file!", 41);
	vector <Student> arr;
	obj_st.GetStrStud(arr, path);
	auto it = find_if(arr.begin(), arr.end(), [old_log](Student &a)->bool {
		return a.GetLogin() == old_log; });
	string tmp = it->GetLogin();
	it->SetLogin(new_log);
	it->SetPassword(new_pass);		
	SaveToFileOUT(arr, path);

}


bool Admin:: CheckLog(string inp_log, string inp_pass, string path)
{
	vector<string> vec;
	GetStr(vec, path);	
	return inp_log == vec[0] && inp_pass == vec[1];

}

