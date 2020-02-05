#pragma once
#include "Admin.h"

//============================FILE OPERATIONS =====================================


void ShowFileContStud(string path, int mode);//Show file content with stud info

//============================ADMIN AUTHORIZATION=========================================

void SelectStatus();//authorization under administrator ore student

void GetStr(vector<string>& arr, string path);//it form vector from line tockens (constituent  GetVec)

//============================STUDENT AUTHORIZATION=========================================

void SelectAutorization();//for choose: login ore registration

//========================Methods for work with reg user data ==============================

void ShowOwnRegData(string path, string login);//to see own usere register data

void ChangePass(string login);//change pass for student 
