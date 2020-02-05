#include "Test.h"



Test::Test()
{
	Question = "";
	v1 = "";
	v2 = "";
	v3 = "";
	v4 = "";
	ans = 0;
	mark = 0;
	
}

void Test::SetQuestion(string Question)
{
	this->Question = Question;
}

void Test::SetV1(string v1){this->v1 = v1;}

void Test::SetV2(string v2) { this->v2 = v2; }

void Test::SetV3(string v3) { this->v3 = v3; }

void Test::SetV4(string v4) { this->v4 = v4; }

void Test::SetAns(int ans) { this->ans = ans; }

string Test::GetQuestion()
{
	return Question;
}

string Test::GetV1()
{
	return v1;
}

string Test::GetV2()
{
	return v2;
}

string Test::GetV3()
{
	return v3;
}

string Test::GetV4()
{
	return v4;
}

string Test:: CreateResFile(string login)
{
	//create path to save result
	string path_save_res = "files\\Tests\\" + login + ".dat";
	//create file to save test result
	ofstream file_save_res(path_save_res, ios::out);
	file_save_res.close();
	return path_save_res;
}

void Test::ShowTest(string path, string path_res, string login)
{
	string  str;
	ifstream file(path);
	if (!file.is_open())
		throw myErr("Error in opening file !", 41);
	vector <Test> TestVec;
	vector<int> vec_res;
	//create path to save result
	string path_save_res = CreateResFile(login);	
	ResVecFromFileRes(vec_res,path_res);
	while (!file.eof())
	{
		getline(file, str);
		if (str[str.size()] == '\n')
			str[str.size()] = '\0';
		if (str == "")
			continue;
		if (!GetObjTest(TestVec, str))
			break;
		
	}	
	file.close();
	double percent = 0;
	int mark = 0;
	int size = TestVec.size();
	if (size == 12)			
		int mark = CreateMark(TestVec, vec_res, percent);
	string Categ = "OOP", SubCateg = "C++";
	SaveResTestToFileAppOUT(Categ, SubCateg, size, mark, percent, path_save_res);
	
	
}

void Test:: ResVecFromFileRes(vector<int> &vec_res, string path_file_res)
{
	string  str;
	ifstream file(path_file_res);
	if (!file.is_open())
		throw myErr("Error in opening file !", 41);

	while (!file.eof())
	{
		getline(file, str);
		if (str[str.size()] == '\n')
			str[str.size()] = '\0';
		if (str == "")
			continue;
		GetIntFromStr(vec_res, str);
	}
	file.close();

}

void Test::GetIntFromStr(vector<int>&vec, string str)

{
	char *tmp = new char[str.size() + 1];
	char *context = new char[str.size() + 1];
	strcpy(tmp, str.c_str());
	char *pstr = strtok_s(tmp, "#", &context);
	vector<string>arr;
	while (pstr != NULL)
	{
		vec.push_back(stoi(pstr));
		pstr = strtok_s(NULL, "#", &context);
	}
}


bool Test::GetObjTest(vector<Test>&vec, string str)

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
	Test obj(arr[0], arr[1], arr[2], arr[3], arr[4], 0,0);
	if (SelectAnswers(obj))
		vec.push_back(obj);
	else
		return false;
	
	return true;
}

void Test::ShowInfo()
{
	cout << left << setw(12) << Question <<"\n 1)"<<setw(12) << v1 
		<< "\n 2)" << setw(12)<<v2 << "\n 3)" << setw(12)<<v3
		<< "\n 4)" << setw(12)<<v4<<"\n";
}

void Test::ShowStat(string login)
{
	
	string  tmp;

	string path = "files\\Tests\\" + login + ".dat";
	
	ifstream file(path);
	if (file)
	{
		cout <<left<< setw(20) << "Category" << setw(20) << "Subcategory" << setw(13) << "Count answers" << setw(15) <<
			"% right ans-s" << setw(10) << "Mark " << "\n"
			<< "-----------------------------------------------------------------------------\n";
		if (!file.is_open())
			throw myErr("Error in opening file!", 41);

		//output file contents to the screen
		vector<string>vec;
		while (!file.eof())
		{
			getline(file, tmp);
			GetStrVectFromLine(vec, tmp);
			cout << setw(20) << vec[0] << setw(20) << vec[1] << setw(13) << vec[2] << setw(15) <<
				vec[3] << setw(10) << vec[4] << "\n";
		}
		file.close();
	}
	else
	{
		cout << "\tThere are no results so far. To get started, go through at least one test...\n\n";
		while (_getch() == 0);
	}
}

string Test::TestObjToStr(Test &obj)
{
	string tmp;
	tmp += obj.GetQuestion() + '#';
	tmp += obj.GetV1() + '#';
	tmp += obj.GetV2() + '#';
	tmp += obj.GetV3() + '#';
	tmp += obj.GetV4() +"#...";
	
	return tmp;
}

bool Test:: SelectAnswers( Test& obj)
{
	MenuTest m(TestObjToStr(obj));
	
	while (1)
	{	switch (m.choose())
			{
						
			case 0:
				//V1
				SetAns(1);
				return true;
			case 1:
				//V2
				SetAns(2);
				return true;
			case 2:
				//V3				
				SetAns(3);
				return true;
			case 3:
				//V4				
				SetAns(4);
				return true;
			case 4:
				//exit
				cout << "\n\nYou left the test ahead of schedule...\n\n";
				while (_getch() == 0);
				return false;

			}	
	}
}

int Test:: CreateMark(vector<Test> & vec_test, vector<int>vec_res, double &percent)
{
	
	int sum = vec_test.size();
	int i = 0, count = 0;
	for (auto it = vec_test.begin(); it != vec_test.end(); ++it)
	{
		if (it->GetAns() == vec_res[i])
			count++;
		i++;
	}
	percent = count / (sum*1.0)*100;
	if (percent > 91)
		return 12;
	else
		if (percent <= 91&& percent > 82.66)
			return 11;
		else
			if (percent <= 82.66 && percent > 74.32)
				return 9;
			else
				if (percent <= 74.32 && percent >65.98)
					return 8;
				else
					if (percent <= 65.98 && percent >57.64)
						return 7;
					else
						if (percent <= 57.64 && percent >49.3)
							return 6;
						else
							if (percent <= 49.3 && percent >40.96)
								return 5;
							else
								if (percent <= 40.96 && percent >32.62)
									return 4;
								else
									if (percent <= 32.62 && percent >24.28)
										return 3;
									else
										if (percent <= 24.28 && percent >15.94)
											return 2;
										else										
												return 1;
		
}

void Test::GetStrVectFromLine(vector<string>& vec, string & str)
{
	char *tmp = new char[str.size() + 1];
	char *context = new char[str.size() + 1];
	strcpy(tmp, str.c_str());
	char *pstr = strtok_s(tmp, "#", &context);
	vector<string>arr;
	while (pstr != NULL)
	{
		vec.push_back(pstr);
		pstr = strtok_s(NULL, "#", &context);
	}
}

void Test::SaveResTestToFileAppOUT(string Categ, string SubCateg,  int FinalAnswer, int makr, double percent, string path)
{
	ofstream file(path, ios::out || ios::app);
	if (!file)
		throw myErr("Error in opening file to rewrite!", 46);
	
	file <<Categ<<"#"<<SubCateg<< "#" <<FinalAnswer<< "#" <<percent << "#" << mark << "\n";
	file.close();
}

