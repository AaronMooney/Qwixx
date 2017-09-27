/*
Assignment:		Qwixx
Author:			Aaron Mooney 20072163
Module:			Games Development 1
*/
#pragma once
#ifndef DIE_H
#define DIE_H

#include<string>
using namespace std;

class Die {
public:
	Die(string color = "white");
	const string& getColor();
	void roll();
	const int& getValue();
private:
	string m_color;
	int m_value;
};

#endif