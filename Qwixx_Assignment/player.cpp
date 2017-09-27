/*
Assignment:		Qwixx
Author:			Aaron Mooney 20072163
Module:			Games Development 1
*/
#include "player.h"
#include <iostream>
#include <algorithm>
using namespace std;

//Create new player and scoresheet for that player
Player::Player(int playerId) :
	m_playerId(playerId)
{
	p_board = new ScoreSheet();
}

//deconstructor
Player::~Player()
{
	delete p_board;
	p_board = 0;
}

int & Player::getId()
{
	return this->m_playerId;
}

bool Player::move(int  rowId, int  value)
{
	vector<string>& row = this->p_board->sheet->at(rowId);				//red/yellow/green/blue row
	if (rowId < 2) {
		if (row.at(value - 2) == "X" || row.at(value - 2) == "/") {
			return false;
		}
	}																	//if the value is crossed already or is left of the cross return false
	else {
		if (row.at(12 - value) == "X" || row.at(12 - value) == "/") {
			return false;
		}
	}
	vector<string>::reverse_iterator it;								//cycle backwards from the value to block previous values until another cross or
	if (rowId < 2) it = row.rend() - (value - 2);						//the first element is reached		
	else it = row.rend() - (12 - value);
	for (it; it != row.rend(); it++) {
		if (*it == "X") break;
		*it = "/";
	}
	if (rowId < 2) {
		row.at(value - 2) = "X";
	}
	else row.at(12 - value) = "X";
	return true;
}

int &Player::getMisthrows()
{
	return this->m_misthrows;
}

void Player::addMisthrow()
{
	this->m_misthrows++;
}

void Player::setFirstMisthrow(bool& misthrow)
{
	this->firstTurnMisthrow = true;
}

void Player::setSecondMisthrow(bool& misthrow)
{
	this->secondTurnMisthrow = true;
}

void Player::isMisthrow()
{
	if (this->secondTurnMisthrow == true && this->firstTurnMisthrow == true)
	{
		this->addMisthrow();
	}
}

ScoreSheet& Player::getSheet()
{
	return *this->p_board;
}
/*
This method checks the frequency of 'X' in each row with the count() method and calculates the scores.
*/
int Player::getScore() {
	vector<int> chart{ 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78 };
	int redXFrequency = count(this->p_board->sheet->at(0).begin(), this->p_board->sheet->at(0).end(), "X");
	int yellowXFrequency = count(this->p_board->sheet->at(1).begin(), this->p_board->sheet->at(1).end(), "X");
	int greenXFrequency = count(this->p_board->sheet->at(2).begin(), this->p_board->sheet->at(2).end(), "X");
	int blueXFrequency = count(this->p_board->sheet->at(3).begin(), this->p_board->sheet->at(3).end(), "X");
	int redTotal = 0;
	int yellowTotal = 0;
	int greenTotal = 0;
	int blueTotal = 0;
	for (vector<int>::const_iterator it = chart.begin(); it != chart.end(); it++)
	{
		if (redXFrequency == *it) redTotal = redXFrequency * *it;
		if (yellowXFrequency == *it) yellowTotal = yellowXFrequency * *it;
		if (greenXFrequency == *it) greenTotal = greenXFrequency * *it;
		if (blueXFrequency == *it) blueTotal = blueXFrequency * *it;
	}
	int total = (redTotal + yellowTotal + greenTotal + blueTotal) - (getMisthrows() * 5);
	this->m_score = total;
	return total;
}

int Player::getTotalScore() {
	return this->m_score;
}

void Player::printBoard() {
	this->getSheet().printSheet();
}
