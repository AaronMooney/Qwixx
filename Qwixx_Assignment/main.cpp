/*
Assignment:		Qwixx
Author:			Aaron Mooney 20072163
Module:			Games Development 1
*/


//Caters for 2-5 human players
//locking of rows attempted but not implemented

#include "scoreSheet.h"
#include "die.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


void showRules();
void showMenu();
void endGame(vector<Player*>& players);
inline void throwDice(vector<Die*>& const dice);
bool makeMove(Player& currentPlayer, vector<Die*>& dice);
vector<int> getColorCombo(vector<Die*>& dice);
bool makeSecondMove(Player& currentPlayer, vector<Die*>& dice, bool& doubleMove, vector<int>& combos);

int main() {
	bool game = true;		//game loob boolean
	int choice;				//switch choice
	bool menu = true;
	Player* currentPlayer;		//pointer for current player
	int playerId = 0;
	vector<Die*> dice{ new Die, new Die, new Die("red"), new Die("yellow"), new Die("green"), new Die("blue") };			//create the 6 die
	vector<Player*> players;		//vector of player pointers
	while (menu != false)
	{
		showMenu();
		cout << "Your choice : " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			menu = false;
		}
		case 2:
		{
			showRules();
			break;
		}
		case 3:
		{
			cout << "Goodbye" << endl;
			return 0;
		}
		}
	}
	bool howMany = true;			//switch loop
	int option;
	while (howMany != false)
	{
		cout << "How many players are playing? : " << endl;
		cin >> option;
		switch (option)
		{
		case 1:
		{
			cout << "Must have 2 - 5 players" << endl;
			break;
		}
		case 6:
		{
			cout << "Too many players!" << endl;
			break;
		}
		default:
		{
			howMany = false;
		}
		}
	}
	for (int i = 0; i < option; i++) {
		players.push_back(new Player(i));
	}
	/*
	Bug happening where the current player gets another go at the end of every turn loop, for example the dice does not roll
	until player 1's turn so player 0 gets another turn beforehand
	*/
	while (game != false) {			//game loop
		throwDice(dice);
		bool doubleMove = true;					//current player gets two turns
		for (int i = 0; i <= players.size(); i++) {
			currentPlayer = players.at(playerId);
			if (currentPlayer->getMisthrows() == 4) game = false;			//end game
			cout << "\nPlayer : " << currentPlayer->getId() << endl;
			cout << "\nMisthrows : " << currentPlayer->getMisthrows() << endl;
			cout << "\n" << endl;
			currentPlayer->printBoard();
			makeMove(*currentPlayer, dice);
			vector<int> combos = getColorCombo(dice);
			makeSecondMove(*currentPlayer, dice, doubleMove, combos);
			currentPlayer->isMisthrow();
			doubleMove = false;
			playerId = ++playerId % players.size();				//increment player id until it reaches the max players and reset to 0
		}
	}
	endGame(players);
	cin.get();
	cin.get();
	return 0;
}

bool makeMove(Player& currentPlayer, vector<Die*>& dice)
{
	bool misthrow = false;
	int value = dice.at(0)->getValue() + dice.at(1)->getValue();		//add two white dice
	int option;
	bool choosing = true;
	while (choosing != false)
	{
		cout << "\nTwo white dice value : " << value << "\n";
		cout << "\nWhat would you like to do?\n" <<
			"1) Pick a row and cross the number\n" <<
			"2) Don't pick a row\n";
		cin >> option;
		switch (option)
		{
		case 1:
		{
			int row;
			cout << "What board do you want to use :\nRed : 0\nYellow : 1\nGreen : 2\nBlue : 3\n";
			cin >> row;
			if (row < 0 || row > 3) return false;
			return currentPlayer.move(row, value);
		}
		case 2:
		{
			misthrow = true;							//sets the first misthrow value to true, if the second is also true a misthrow is added
			currentPlayer.setFirstMisthrow(misthrow);
			return true;
		}
		default:
		{
			break;
		}
		}
	}
}


vector<int> getColorCombo(vector<Die*>& dice)
{
	// 0: white 1: white 2: red 3: yellow 4: green 5: blue
	//get sums of each dice with white dice
	int redValue1 = dice.at(2)->getValue() + dice.at(0)->getValue();
	int redValue2 = dice.at(2)->getValue() + dice.at(1)->getValue();
	int yellowValue1 = dice.at(3)->getValue() + dice.at(0)->getValue();
	int yellowValue2 = dice.at(3)->getValue() + dice.at(1)->getValue();
	int greenValue1 = dice.at(4)->getValue() + dice.at(0)->getValue();
	int greenValue2 = dice.at(4)->getValue() + dice.at(1)->getValue();
	int blueValue1 = dice.at(5)->getValue() + dice.at(0)->getValue();
	int blueValue2 = dice.at(5)->getValue() + dice.at(1)->getValue();
	vector<int> combos;
	combos.push_back(redValue1);
	combos.push_back(redValue2);
	combos.push_back(yellowValue1);
	combos.push_back(yellowValue2);
	combos.push_back(greenValue1);
	combos.push_back(greenValue2);
	combos.push_back(blueValue1);
	combos.push_back(blueValue2);
	return combos;
}

bool makeSecondMove(Player& currentPlayer, vector<Die*>& dice, bool& doubleMove, vector<int>& combos)
{
	if (doubleMove == true) {
		bool choosing = true;		//switch boolean
		int value = 0;				//dice value
		int option = 0;				//switch statement choice
		int rowNo = 0;
		while (choosing != false)
		{
			cout << "possible combinations:" << endl;

			cout << "Select an option from the list of values" << endl;
			cout << "1 : " << "White + red 1 : " << combos.at(0) << endl;
			cout << "2 : " << "White + red 2 : " << combos.at(1) << endl;
			cout << "3 : " << "White + yellow 1 : " << combos.at(2) << endl;
			cout << "4 : " << "White + yellow  2: " << combos.at(3) << endl;
			cout << "5 : " << "White + green 1 : " << combos.at(4) << endl;
			cout << "6 : " << "White + green 2 : " << combos.at(5) << endl;
			cout << "7 : " << "White + blue 1 : " << combos.at(6) << endl;
			cout << "8 : " << "White + blue 2 : " << combos.at(7) << endl;
			cin >> option;
			switch (option)
			{
			case 1:
			{
				value = combos.at(0);
				rowNo = 0;
				choosing = false;
			}
			case 2:
			{
				value = combos.at(1);
				rowNo = 0;
				choosing = false;
			}
			case 3:
			{
				value = combos.at(2);
				rowNo = 1;
				choosing = false;
			}
			case 4:
			{
				value = combos.at(3);
				rowNo = 1;
				choosing = false;
			}
			case 5:
			{
				value = combos.at(4);
				rowNo = 2;
				choosing = false;
			}
			case 6:
			{
				value = combos.at(5);
				rowNo = 2;
				choosing = false;
			}
			case 7:
			{
				value = combos.at(6);
				rowNo = 3;
				choosing = false;
			}
			case 8:
			{
				value = combos.at(7);
				rowNo = 3;
				choosing = false;
			}
			default:
			{
				break;
			}
			}
		}
		int choice;
		bool misthrow = false;
		bool picking = true;
		while (picking != false)
		{
			cout << "\nWhat would you like to do?\n" <<
				"1) Cross the number\n" <<
				"2) Don't pick a row\n";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				return currentPlayer.move(rowNo, value);
			}
			case 2:
			{
				misthrow = true;								//set second misthrow to true
				currentPlayer.setSecondMisthrow(misthrow);
				return true;
			}
			default:
			{
				break;
			}
			}
		}
	}
}

void getScores(vector<Player*>& players) {
	cout << "Scores: \n" << endl;
	for (vector<Player*>::const_iterator it = players.begin(); it != players.end(); it++)				//iterate through players and print scores
	{
		cout << "Player : " << (*it)->getId() << " Score : " << (*it)->getScore() << endl;
	}
}

inline void throwDice(vector<Die*>& const dice)
{
	cout << "Throwing dice \n" << endl;
	for (vector<Die*>::iterator it = dice.begin(); it != dice.end(); it++) {
		(*it)->roll();
		cout << (*it)->getColor() << " : " << (*it)->getValue() << "\n";				//roll each dice and print values and colors
	}
}

void endGame(vector<Player*>& players) {
	getScores(players);
}


void showMenu()
{
	cout << "\nMENU\n" <<
		"1) Start Game\n" <<
		"2) Read Instructions\n" <<
		"3) Exit\n" << endl;
}

void showRules()
{
	cout << "\n\t\t** RULES **\n\n"
		<< "Roll 6 dice ( 2 white, 1 blue, 1 green, 1 red and 1 yellow),\nthen the player rolling can choose any row and cross off the\nnumber the "
		<< "two white dice show. Then, all other players can do\nthe same. The player that rolled can then add one white dice\nwith a colored dice and "
		<< "cross off the sum, in the colored row.\nOnce a number has been chosen you mark it with an 'X'\nand you can't choose a number left of that 'X' again.\n"
		<< "choosing a number is optional but you will be punished with a misthrow.\n"
		<< "When a player marks at least 5 numbers on the same row they can then\ncross the number on the extreme right of the row. "
		<< "If this occurs then\nthat row will be locked for all players and that colored dice will be\nremoved from play. "
		<< "\n\nThe game will end under the following conditions: "
		<< "\n1: If a player gets a 4th misthrow. "
		<< "\n2: Two rows become locked.\n\n" << endl;
}