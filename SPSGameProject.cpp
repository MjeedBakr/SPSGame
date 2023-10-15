#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;

enum enSPS {Stone = 1, Paper = 2, Scissor = 3};
enum enSPSPlayer {Player1 = 1, Computer = 2, NoWinner = 3};

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
	enSPSPlayer winner;
	short drawTimes = 0;
};

struct strRoundsInfo
{
	strRoundInfo roundInfo[10];
	short numberOfRounds;
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

void increaseWinTimes(strRoundsInfo &roundsInfo, enSPSPlayer player)
{
	switch (player)
	{
	case Player1:
		roundsInfo.player1WinTimes++;
		break;
	case Computer:
		roundsInfo.ComputerWinTimes++;
		break;
	case NoWinner:
		roundsInfo.drawTimes++;
		break;
	default:
		break;
	}
}

void findWinner(strRoundInfo &roundInfo, strRoundsInfo& roundsInfo)
{
	if (roundInfo.player.playerChoice == roundInfo.computer.computerChoice)
		roundInfo.winner = enSPSPlayer::NoWinner;
	else
	{
		if (roundInfo.player.playerChoice == enSPS::Paper)
		{
			if (roundInfo.computer.computerChoice == enSPS::Stone)
				roundInfo.winner = enSPSPlayer::Player1;
			else
				roundInfo.winner = enSPSPlayer::Computer;
		}
		else if (roundInfo.player.playerChoice == enSPS::Scissor)
		{
			if (roundInfo.computer.computerChoice == enSPS::Paper)
				roundInfo.winner = enSPSPlayer::Player1;
			else
				roundInfo.winner = enSPSPlayer::Computer;
		}
		else
		{
			if (roundInfo.computer.computerChoice == enSPS::Scissor)
				roundInfo.winner = enSPSPlayer::Player1;
			else
				roundInfo.winner = enSPSPlayer::Computer;
		}

	}
	increaseWinTimes(roundsInfo, roundInfo.winner);


}

void createRound(strRoundInfo &roundInfo, strRoundsInfo& roundsInfo)
{
	cout << "\nRound [" << roundInfo.roundID << "] begins: \n";

	cout << "\nYour choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
	short playerChoice;
	cin >> playerChoice;
	if (playerChoice > 3 || playerChoice < 1)
		playerChoice = readNumberInRange(1, 3);

	roundInfo.player.playerChoice = (enSPS)playerChoice;
	roundInfo.computer.computerChoice = (enSPS)randomNumber(1, 3);
	findWinner(roundInfo, roundsInfo);

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
	cout << "\nPlayer1  choice: " << printPlayerChoice(roundInfo.player.playerChoice);
	cout << "\nComputer choice: " << printPlayerChoice(roundInfo.computer.computerChoice);
	cout << "\nRound winner   : [" << printPlayerName(roundInfo.winner) << "]\n";

	cout << "\n-----------------------------------\n" << endl;

}

void findFinalWinner(strRoundsInfo& roundsInfo)
{
	if (roundsInfo.ComputerWinTimes == roundsInfo.player1WinTimes)
		roundsInfo.finalWinner = enSPSPlayer::NoWinner;
	else
		if (roundsInfo.player1WinTimes > roundsInfo.ComputerWinTimes)
			roundsInfo.finalWinner = enSPSPlayer::Player1;
		else
			roundsInfo.finalWinner = enSPSPlayer::Computer;
}

void createRounds(strRoundsInfo &roundsInfo)
{
	cout << "How many Rounds 1 to 10? ";
	cin >> roundsInfo.numberOfRounds;
	if (roundsInfo.numberOfRounds > 10 || roundsInfo.numberOfRounds < 1)
		roundsInfo.numberOfRounds = readNumberInRange(1, 10);


	for (int i = 0; i < roundsInfo.numberOfRounds; i++)
	{
		roundsInfo.roundInfo[i].roundID = to_string(i + 1);
		createRound(roundsInfo.roundInfo[i], roundsInfo);
	}
	findFinalWinner(roundsInfo);

}

void endGame(strRoundsInfo& roundsInfo)
{

	cout << "\t\t\t\t\t-------------------------------------------\n\n";
	cout << "\t\t\t\t\t            | G A M E O V E R |            \n\n";
	cout << "\t\t\t\t\t-------------------------------------------\n\n";
	cout << "\t\t\t\t\t              [ Game Results ]             \n\n";

	cout << "\t\t\t\t\tGame Rounds        : " << roundsInfo.numberOfRounds << "\n";
	cout << "\t\t\t\t\tPlayer1 won times  : " << roundsInfo.player1WinTimes << "\n";
	cout << "\t\t\t\t\tComputer won times : " << roundsInfo.ComputerWinTimes << "\n";
	cout << "\t\t\t\t\tDraw times         : " << roundsInfo.drawTimes << "\n";
	cout << "\t\t\t\t\tFinal winner       : " << printPlayerName(roundsInfo.finalWinner) << "\n\n";

	cout << "\t\t\t\t\t-------------------------------------------\n\n";

}

void startGame()
{
	system("color 8F");

	char playAgainChoice;
	strRoundsInfo roundsInfo;
	roundsInfo.numberOfRounds = 0;

	createRounds(roundsInfo);
	endGame(roundsInfo);

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


