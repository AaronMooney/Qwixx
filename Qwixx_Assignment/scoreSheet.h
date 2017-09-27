/*
Assignment:		Qwixx
Author:			Aaron Mooney 20072163
Module:			Games Development 1
*/
#pragma once
#ifndef SCORESHEET_H
#define SCORESHEET_H

#include<vector>
using namespace std;

class ScoreSheet {
public:
	friend class player;
	ScoreSheet();
	~ScoreSheet();
	void printSheet();
	vector<vector<string>>& getSheet();
	vector<vector<string>>* sheet;
	bool lockRow();
private:
	vector<string> m_red{ "2","3","4","5","6","7","8","9","10","11","12" };
	vector<string> m_yellow{ "2","3","4","5","6","7","8","9","10","11","12" };
	vector<string> m_green{ "12","11","10","9","8","7","6","5","4","3","2" };
	vector<string> m_blue{ "12","11","10","9","8","7","6","5","4","3","2" };
};

#endif