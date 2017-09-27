/*
Assignment:		Qwixx
Author:			Aaron Mooney 20072163
Module:			Games Development 1
*/
#include "scoreSheet.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

//create new board with the default rows
ScoreSheet::ScoreSheet()
{
	sheet = new vector<vector<string>>();
	sheet->push_back(m_red);
	sheet->push_back(m_yellow);
	sheet->push_back(m_green);
	sheet->push_back(m_blue);
}

//deconstructor
ScoreSheet::~ScoreSheet()
{
	delete sheet;
	sheet = 0;
}

//iterate through and print each row
void ScoreSheet::printSheet()
{
	for (int i = 0; i < sheet->size(); i++) {
		for (vector<string>::const_iterator it = sheet->at(i).begin(); it != sheet->at(i).end(); it++) {
			cout << *it + " ";
		}
		cout << endl;
	}
}

vector<vector<string>>& ScoreSheet::getSheet()
{
	return *this->sheet;
}


bool ScoreSheet::lockRow()
{
	vector<string>lockedRed;
	vector<string>lockedYellow;
	vector<string>lockedGreen;
	vector<string>lockedBlue;
	if (count(sheet->at(0).begin(), sheet->at(0).end(), "X") > 5 && sheet->at(0).at(10) == "X") {
		lockedRed = sheet->at(0);
		sheet->erase(sheet->begin());
		return true;
	}
	if (count(sheet->at(1).begin(), sheet->at(1).end(), "X") > 5 && sheet->at(1).at(10) == "X") {
		lockedYellow = sheet->at(0);
		sheet->erase(sheet->begin() + 1);
		return true;
	}
	if (count(sheet->at(2).begin(), sheet->at(2).end(), "X") > 5 && sheet->at(2).at(10) == "X") {
		lockedGreen = sheet->at(2);
		sheet->erase(sheet->begin() + 2);
		return true;
	}
	if (count(sheet->at(3).begin(), sheet->at(3).end(), "X") > 5 && sheet->at(3).at(10) == "X") {
		lockedBlue = sheet->at(3);
		sheet->erase(sheet->begin() + 3);
		return true;
	}
	return false;
}
