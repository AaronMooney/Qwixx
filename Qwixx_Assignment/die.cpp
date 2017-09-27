/*
Assignment:		Qwixx
Author:			Aaron Mooney 20072163
Module:			Games Development 1
*/
#include "die.h"
#include<cstdlib>
#include<ctime>
using namespace std;

//create a new colored die default color is white
Die::Die(string color) {
	m_color = color;
	srand(static_cast<unsigned int>(time(0)));
}

const string& Die::getColor() {
	return this->m_color;
}

const int& Die::getValue() {
	return this->m_value;
}

//roll between 1 and 6 inclusive
void Die::roll() {
	this->m_value = (rand() % 6) + 1;
}
