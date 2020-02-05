#pragma once
#include"Persone.h"
//#include "Admin.h"
#include "Student.h"

class Test
{
	string Question, v1, v2, v3, v4;
	int ans, mark;
	
public:

	Test();

	Test(string Question, string v1, string v2, string v3, string v4, int ans, int mark ) :Question(Question), v1(v1),
		v2(v2), v3(v3), v4(v4), ans(ans), mark(mark) {	};

	void SetQuestion(string Question);
	void SetV1(string v1);
	void SetV2(string v2);
	void SetV3(string v3);
	void SetV4(string v4);
	void SetAns(int ans);
	void SetMark(int mark) { this->mark = mark; };
	string GetQuestion();
	string GetV1();
	string GetV2();
	string GetV3();
	string GetV4();
	
	int GetAns() { return ans; };
	int GetMark() { return mark; };
	bool GetObjTest(vector<Test>&vec, string str);//return vector<Test>&vec

	//upload test for user and process its results
	void ShowTest(string path, string path_res, string login);
	
	void ResVecFromFileRes(vector<int> &,string path_file_res);//get vector with numbers of right answers from file
	
	void GetIntFromStr(vector<int>&vec, string str);//Get  int vector from string

	void ShowInfo();//show info to screen

	void ShowStat(string login);//show file content with test result statistic

	string TestObjToStr(Test &obj);//transfor ojf of Test to obj of string
	
	bool SelectAnswers(Test& );//fo show user test and get answers. 
	
	//create mark by test result. Return % of right answers and mark 
	int CreateMark(vector<Test> & vec_test, vector<int>vec_res, double &);

	void GetStrVectFromLine(vector<string>&, string &);//return vector<string>  from string line

	string CreateResFile(string login);//return name of file whot create

	//for save test result to file
	void SaveResTestToFileAppOUT(string Categ, string SubCateg, int FinalAnswer, int makr, double percent, string path);
	



	~Test() {};
};

