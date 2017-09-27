/*
Assignment:		Qwixx
Author:			Aaron Mooney 20072163
Module:			Games Development 1
*/
#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Die.h"
#include "scoreSheet.h"

using namespace std;

class Player {
protected:
	int m_playerId;
	int m_misthrows;
	bool firstTurnMisthrow;
	bool secondTurnMisthrow;
	ScoreSheet* p_board;
	int m_score;
public:
	Player(int playerId);
	~Player();
	int& getId();
	bool move(int row, int value);
	int& getMisthrows();
	void addMisthrow();
	void setFirstMisthrow(bool & misthrow);
	void setSecondMisthrow(bool & misthrow);
	void isMisthrow();
	int Player::getScore();
	int getTotalScore();
	ScoreSheet& getSheet();
	void printBoard();
};
#endif