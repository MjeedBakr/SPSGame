#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
using namespace std;

enum enSPS {Stone = 1, Paper = 2, Scissor = 3};
enum enSPSResults {Player1 = 1, Computer = 2, NoWinner = 3};

struct strPlayerInfo
{
	enSPS playerChoice;
};

struct strComputerInfo
{
	enSPS computerChoice;
};

struct  strRoundInfo
{
	string roundID;
	strComputerInfo computer;
	strPlayerInfo player;
	enSPSResults winner;
	string winnerName;


};

int randomNumber(int from, int to)
{
	int randNum = rand() % (to - from + 1) + from;
	return randNum;
}

string printChoice(enSPS choice)
{
	switch (choice)
	{
	case Stone:
		return "Stone";
	case Paper:
		return "Paper";
	case Scissor:
		return "Scissor";
	default:
		break;
	}
}

void findWinnerInfo(strRoundInfo &roundInfo)
{
	if (roundInfo.player.playerChoice == roundInfo.computer.computerChoice)
		roundInfo.winner = enSPSResults::NoWinner;
	else
	{
		if (roundInfo.player.playerChoice == enSPS::Paper)
		{
			if (roundInfo.computer.computerChoice == enSPS::Stone)
				roundInfo.winner = enSPSResults::Player1;
			else
				roundInfo.winner = enSPSResults::Computer;
		}
		else if (roundInfo.player.playerChoice == enSPS::Scissor)
		{
			if (roundInfo.computer.computerChoice == enSPS::Paper)
				roundInfo.winner = enSPSResults::Player1;
			else
				roundInfo.winner = enSPSResults::Computer;
		}
		else
		{
			if (roundInfo.computer.computerChoice == enSPS::Scissor)
				roundInfo.winner = enSPSResults::Player1;
			else
				roundInfo.winner = enSPSResults::Computer;
		}

	}

	switch (roundInfo.winner)
	{
	case enSPSResults::NoWinner:
		roundInfo.winnerName = "No Winner";
		break;
	case enSPSResults::Player1:
		roundInfo.winnerName = "Player1";
		break;
	case enSPSResults::Computer:
		roundInfo.winnerName = "Computer";
		break;
	default:
		break;

	}

}

void createRound(strRoundInfo &roundInfo)
{
	cout << "\nRound [" << roundInfo.roundID << "] begins: \n";

	cout << "\nYour choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
	short playerChoice;
	cin >> playerChoice;

	roundInfo.player.playerChoice = (enSPS)playerChoice;
	roundInfo.computer.computerChoice = (enSPS)randomNumber(1, 3);
	findWinnerInfo(roundInfo);

	switch (roundInfo.winner)
	{
	case enSPSResults::NoWinner:
		system("color 6F");
		break;
	case enSPSResults::Player1:
		system("color 2F");
		break;
	case enSPSResults::Computer:
		cout << "\a";
		system("color 4F");
	}

	cout << "\n\n";
	cout << "-------------Round [" << roundInfo.roundID << "]-------------\n";
	cout << "\nPlayer1  choice: " << printChoice(roundInfo.player.playerChoice);
	cout << "\nComputer choice: " << printChoice(roundInfo.computer.computerChoice);
	cout << "\nRound winner   : [" << roundInfo.winnerName << "]\n";

	cout << "\n-----------------------------------\n" << endl;

}


void createRounds(strRoundInfo roundsArray[10], int& roundsArrLength)
{
	cout << "How many Rounds 1 to 10? ";
	cin >> roundsArrLength;
	for (int i = 0; i < roundsArrLength; i++)
	{
		roundsArray[i].roundID = to_string(i + 1);
		createRound(roundsArray[i]);
	}

}

void startGame()
{
	strRoundInfo roundsArray[10];
	int roundsArrLength = 0;

	createRounds(roundsArray, roundsArrLength);


}

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));

	startGame();

}


