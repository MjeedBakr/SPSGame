#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;

enum enSPS {Stone = 1, Paper = 2, Scissor = 3};
enum enSPSPlayer {Player1 = 1, Computer = 2, NoWinner = 3};

struct  strRoundInfo
{
	string roundID;
	enSPS computerChoice;
	enSPS playerChoice;
	enSPSPlayer winner;
	short drawTimes = 0;
};

struct strGameInfo
{
	strRoundInfo roundInfo[10];
	short numberOfRounds = 0;
	short player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short drawTimes = 0;
	enSPSPlayer finalWinner;
};

int randomNumber(int from, int to)
{
	int randNum = rand() % (to - from + 1) + from;
	return randNum;
}

int readNumberInRange(int from, int to)
{
	int number;
	do
	{
		cout << "\nPlease Enter a number between " << from << " and " << to << ": ";
		cin >> number;
	} while (number > to || number < from);

	return number;
}

string printPlayerChoice(enSPS choice)
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

string printPlayerName(enSPSPlayer player)
{
	switch (player)
	{
	case Player1:
		return "Player1";
	case Computer:
		return "Computer";
	case NoWinner:
		return "No Winner";
	default:
		break;
	}
}

void increaseWinTimes(strGameInfo &gameInfo, enSPSPlayer player)
{
	switch (player)
	{
	case Player1:
		gameInfo.player1WinTimes++;
		break;
	case Computer:
		gameInfo.ComputerWinTimes++;
		break;
	case NoWinner:
		gameInfo.drawTimes++;
		break;
	default:
		break;
	}
}

void findWinner(strRoundInfo &roundInfo, strGameInfo& gameInfo)
{
	if (roundInfo.playerChoice == roundInfo.computerChoice)
		roundInfo.winner = enSPSPlayer::NoWinner;
	else
	{
		if (roundInfo.playerChoice == enSPS::Paper)
		{
			if (roundInfo.computerChoice == enSPS::Stone)
				roundInfo.winner = enSPSPlayer::Player1;
			else
				roundInfo.winner = enSPSPlayer::Computer;
		}
		else if (roundInfo.playerChoice == enSPS::Scissor)
		{
			if (roundInfo.computerChoice == enSPS::Paper)
				roundInfo.winner = enSPSPlayer::Player1;
			else
				roundInfo.winner = enSPSPlayer::Computer;
		}
		else
		{
			if (roundInfo.computerChoice == enSPS::Scissor)
				roundInfo.winner = enSPSPlayer::Player1;
			else
				roundInfo.winner = enSPSPlayer::Computer;
		}

	}
	increaseWinTimes(gameInfo, roundInfo.winner);


}

void createRound(strRoundInfo &roundInfo, strGameInfo& gameInfo)
{
	cout << "\nRound [" << roundInfo.roundID << "] begins: \n";

	cout << "\nYour choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
	short playerChoice;
	cin >> playerChoice;
	if (playerChoice > 3 || playerChoice < 1)
		playerChoice = readNumberInRange(1, 3);

	roundInfo.playerChoice = (enSPS)playerChoice;
	roundInfo.computerChoice = (enSPS)randomNumber(1, 3);

	findWinner(roundInfo, gameInfo);

	switch (roundInfo.winner)
	{
	case enSPSPlayer::NoWinner:
		system("color 6F");
		break;
	case enSPSPlayer::Player1:
		system("color 2F");
		break;
	case enSPSPlayer::Computer:
		cout << "\a";
		system("color 4F");
	}

	cout << "\n\n";
	cout << "-------------Round [" << roundInfo.roundID << "]-------------\n";
	cout << "\nPlayer1  choice: " << printPlayerChoice(roundInfo.playerChoice);
	cout << "\nComputer choice: " << printPlayerChoice(roundInfo.computerChoice);
	cout << "\nRound winner   : [" << printPlayerName(roundInfo.winner) << "]\n";

	cout << "\n-----------------------------------\n" << endl;

}

void findFinalWinner(strGameInfo& gameInfo)
{
	if (gameInfo.ComputerWinTimes == gameInfo.player1WinTimes)
		gameInfo.finalWinner = enSPSPlayer::NoWinner;
	else
		if (gameInfo.player1WinTimes > gameInfo.ComputerWinTimes)
			gameInfo.finalWinner = enSPSPlayer::Player1;
		else
			gameInfo.finalWinner = enSPSPlayer::Computer;
}

void createRounds(strGameInfo &gameInfo)
{
	cout << "How many Rounds 1 to 10? ";
	cin >> gameInfo.numberOfRounds;
	if (gameInfo.numberOfRounds > 10 || gameInfo.numberOfRounds < 1)
		gameInfo.numberOfRounds = readNumberInRange(1, 10);


	for (int i = 0; i < gameInfo.numberOfRounds; i++)
	{
		gameInfo.roundInfo[i].roundID = to_string(i + 1);
		createRound(gameInfo.roundInfo[i], gameInfo);
	}
	findFinalWinner(gameInfo);

}

void endGame(strGameInfo gameInfo)
{

	cout << "\t\t\t\t\t-------------------------------------------\n\n";
	cout << "\t\t\t\t\t            | G A M E O V E R |            \n\n";
	cout << "\t\t\t\t\t-------------------------------------------\n\n";
	cout << "\t\t\t\t\t              [ Game Results ]             \n\n";

	cout << "\t\t\t\t\tGame Rounds        : " << gameInfo.numberOfRounds << "\n";
	cout << "\t\t\t\t\tPlayer1 won times  : " << gameInfo.player1WinTimes << "\n";
	cout << "\t\t\t\t\tComputer won times : " << gameInfo.ComputerWinTimes << "\n";
	cout << "\t\t\t\t\tDraw times         : " << gameInfo.drawTimes << "\n";
	cout << "\t\t\t\t\tFinal winner       : " << printPlayerName(gameInfo.finalWinner) << "\n\n";

	cout << "\t\t\t\t\t-------------------------------------------\n\n";

}

void startGame()
{
	system("color 8F");

	char playAgainChoice;
	strGameInfo gameInfo;
	gameInfo.numberOfRounds = 0;

	createRounds(gameInfo);
	endGame(gameInfo);

	cout << "\t\t\t\t\tDo you want to play again? Y/N? ";
	cin >> playAgainChoice;
	if (playAgainChoice == 'y' || playAgainChoice == 'Y') {
		system("cls");
		startGame();
	}
	else
		cout << "\nEnding the game............\n\n";
}


int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));

	startGame();

}


