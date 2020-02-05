#include "Student.h"


void Student::SetGroupe(string Groupe)
{
	this->Groupe = Groupe;
}

string Student::GetGroupe() const
{
	return Groupe;
}

void Student::ShowInfo()


{
	cout << left << setw(12) << FName << setw(12) << LName << setw(12) <<
		status << setw(12) << Groupe << setw(12) << log << setw(8) <<
		pass << setw(12) <<right<< phone << setw(10) << ID << "\n";
}

void Student::ShowOwnRegStudData(string login)
{
	Test test_obj;
	string  tmp;
	string path = "files\\StudData.dat";
	ifstream file(path);
	if (file)
	{
		if (!file.is_open())
			throw myErr("Error in opening file!", 41);

		//output file contents to the screen
		vector<string>vec;
		while (!file.eof())
		{

			getline(file, tmp);
			test_obj.GetStrVectFromLine(vec, tmp);
			if (vec[4] == login)
			{
				cout <<"\n\n"<< left << setw(12) << "First name" << setw(12) << "Last name" << setw(14) <<
					"Status" << setw(8) << "Groupe" << setw(8) << "Login" << setw(9) <<
					"Password" << setw(14) << right << "Phone num" << left << setw(12) << "  ID" << "\n"
					"-----------------------------------------------------------------------------------------\n";

				cout << left << setw(12) << vec[0] << setw(12) << vec[1] << setw(14) <<
					vec[2] << setw(8) << vec[3] << setw(8) << vec[4] << setw(9) << vec[5] << setw(14) << right << vec[6]  << setw(12) << vec[7] << "\n";
				file.close();
				return;
			}
			else
				vec.clear();
		}
		
	}
	else
	{
		cout << "\tNot found file with database...\n\n";
		while (_getch() == 0);
	}
}

void Student::SelectStudMethod(string &login)
{

	Menu m("#...#Change password#Show own reg data#Show statistic#Get test#");
	Test test_obj;
	while (1)
	{
		switch (m.choose())
		{
		case 0:
			//exit			

			return;
		case 1:
			//Change password
			DeCodeFile("files\\StudData.dat");
			DeCodeFile("files\\StudLog.dat");
			ChangePass(login);
			CodeFile("files\\StudData.dat");
			CodeFile("files\\StudLog.dat");
			while (_getch() == 0);
			break;
		case 2:
			//Show own reg data
			DeCodeFile("files\\StudData.dat");
			ShowOwnRegStudData(login);
			CodeFile("files\\StudData.dat");
			while (_getch() == 0);
			break;
		case 3:
			//Show statistic
			test_obj.ShowStat(login);
			while (_getch() == 0);
			break;
		case 4:
			//Get test			
			test_obj.ShowTest("files\\Tests\\test1.dat", "files\\Tests\\test1_ans.dat",login);
			while (_getch() == 0);
			break;
		case 5:
			break;
		}
	}
}

ostream & operator<<(ostream & s, const Student & obj)
{
	s << obj.FName << "#" << obj.LName << "#" <<
		obj.status << "#" << obj.Groupe<< "#" << obj.log << "#" <<
		obj.pass << "#"<< obj.phone << "#" << obj.ID << "\n";
	return s;
}

bool operator==(const Student &p1, const Student &p2)

	{
		return (p1.ID == p2.ID) ? true : false;
	}

string Student::GetFirst(string str)
{
	char *tmp = new char[str.size() + 1];
	char *context = new char[str.size() + 1];
	strcpy(tmp, str.c_str());
	char *pstr = strtok_s(tmp, "#", &context);
	string temp;
	if (pstr == NULL)
		temp = "";
	else
		temp = pstr;

	return temp;
}

bool Student::CheckLogStudAvail(string inp_log, string path)
{
	vector<string> vec;
	string  str;	
	ifstream file(path, ios::app || ios::out);

	while (!file.eof())
	{
		getline(file, str);
		
		if (str[str.size()] == '\n')
			str[str.size()] = '\0';
		string tmp = GetFirst(str);
		if (tmp == "")
		{		
			file.close();			
			return false;
		}
		if (inp_log == tmp)
		{	
			file.close();			
			return true;
		}

	}	
	file.close();	
	return false;
}

bool Student::CheckLogStud(string inp_log, string inp_pass, string path)
{

	
	vector<string> vec;
	string  str;
	ifstream file(path);
	if (!file.is_open())
		throw myErr("Error in opening file !", 41);
	int i = 0;
	while (!file.eof())
	{
		getline(file, str);
		if (str == "")
			break;
		if (str[str.size()] == '\n')
			str[str.size()] = '\0';
		
		GetVec(vec, str);
		if (inp_log == vec[i] && inp_pass == vec[i + 1])
		{
			file.close();			
			return true;
		}

		i += 2;
	}
	file.close();
	return false;
	
	
}

void Student:: GetVec(vector<string>&vec, string str)
{
	char *tmp = new char[str.size() + 1];
	char *context = new char[str.size() + 1];
	strcpy(tmp, str.c_str());
	char *pstr = strtok_s(tmp, "#", &context);

	while (pstr != NULL)
	{
		vec.push_back(pstr);
		pstr = strtok_s(NULL, "#", &context);
	}

}

bool Student:: CheckRegStudData(string path, string & login)
{
	string  str, password;
	ifstream file(path);
	if (!file)
	{
		cout << "\n\t\tThere are no registred students."
			"Contact the administrator.\n\n";
		return false;
	}
	cout << "\n\n\n\n\n" << right << setw(40) << "Login: "; getline(cin, login);
	cout << right << setw(40) << "Password: "; getline(cin, password);

	if (!CheckLogStud(login, password, path))
	{
		cout << "\n\n" << setw(40) << "Incorrect login ore password...\n\n";
		while (_getch() == 0);
	}
	else
	{
		cout << "\n\n" << setw(40) << "Access is allowed.";
		while (_getch() == 0);
		return true;
	}
	return false;
}

void Student:: GetVecStud(vector<Student>&vec, string str)

{
	char *tmp = new char[str.size() + 1];
	char *context = new char[str.size() + 1];
	strcpy(tmp, str.c_str());
	char *pstr = strtok_s(tmp, "#", &context);
	vector<string>arr;
	while (pstr != NULL)
	{
		arr.push_back(pstr);
		pstr = strtok_s(NULL, "#", &context);
	}


	Student obj(arr[3], arr[0], arr[1], arr[6], arr[4], arr[5], arr[2], stoi(arr[7]));
	vec.push_back(obj);

}

void Student:: GetStrStud(vector<Student>&vec, string path)
{
	
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
		GetVecStud(vec, str);
	}

	file.close();
	

}

string Student::NewPass()
{
	string new_pass, tmp;
	while (1)
	{
	cout << "\n\n"<<right << setw(40) << "Enter new password: "; getline(cin, new_pass);
	cout  << right << setw(40) <<"Reenter new password: "; getline(cin, tmp);
	cout << "\n";
	if (new_pass == tmp && tmp != "")
		return new_pass;	
	else
	cout <<"\n"<< right << setw(30)<<"Passwords do not match. Try agayn...\n\n";
	}		
}

void Student::ChangePass(string login)
{
	
	Test test_obj;
	//Admin adm_obj;
	string  tmp, new_pass;	
	string path_dat = "files\\StudData.dat";
	string path_log = "files\\StudLog.dat";
	if (!CheckLogPass(path_log,  login))
	{		
		cout << "\n" << right << setw(30) << "Passwords do not match. Try agayn...\n\n";
		return;
	}
	ifstream file_dat(path_dat);
	ifstream file_log(path_log);
	if (file_dat||file_log)
	{
		if (!file_dat.is_open() )
		{
			CodeFile(path_dat);
			CodeFile(path_log);
			throw myErr("Error in opening file!", 41);
		}
		if ( !file_log.is_open())
		{
			CodeFile(path_dat);
			CodeFile(path_log);
			throw myErr("Error in opening file!", 41);
		}
		vector<Student>VecSt;
		vector<string>vec;
		
		new_pass = NewPass();
		//prepare to save new password to "files\\StudData.dat"
		while (!file_dat.eof())
		{		
			getline(file_dat, tmp);
			test_obj.GetStrVectFromLine(vec, tmp);			
			if (tmp == "")
				continue;
			if (vec[4] == login)
				vec[5] = new_pass;
			Student obj_st(vec[2], vec[0], vec[1], vec[6],vec[4], vec[5], vec[2],stoi(vec[7]));
			VecSt.push_back(obj_st);				
			vec.clear();
		}
		
		file_dat.close();
		//save new password to "files\\StudData.dat"
		SaveToFileOUTST(VecSt, path_dat);
		//save new password to "files\\StudLog.dat"
		int i = 0;
		while (!file_log.eof())
		{
			getline(file_log, tmp);
			if (tmp == "")
				continue;
			test_obj.GetStrVectFromLine(vec, tmp);
			if (vec[i] == login)
				vec[i + 1] = new_pass;			
			i += 2;
		}
		SaveToFileOUTST(vec, path_log);

	}
	else
	{
		cout << "\tNot found file(s) with database...\n\n";
		while (_getch() == 0);
	}
}

bool Student::CheckLogPass(string path, string login)
{
	Test test_obj;
	string tmp, old_pass;
	vector<string>vec;
	ifstream file_log(path);
	if (file_log)
	{
		if (!file_log.is_open())
		{
			CodeFile(path);
			throw myErr("Error in opening file!", 41);
		}
		cout << "\n" << right << setw(30) << "Enter old password: "; getline(cin, old_pass);
		int i = 0;
		while (!file_log.eof())
		{
			getline(file_log, tmp);
			if (tmp == "")
				continue;
			test_obj.GetStrVectFromLine(vec, tmp);
			if (vec[i] == login && vec[i + 1] == old_pass)
				return true;
			i += 2;
		}

		return false;
	}
	else
	{
		cout << "\tNot found file(s) with database...\n\n";
		while (_getch() == 0);
	}

}
