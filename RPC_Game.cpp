//Sean Conrad
//CSCI 201
//Extra Credit 1

#include <iostream>

using namespace std;

int main()
{
	string player1, player2;
	
	cout << "Welcome to ROCK! PAPER! SCISSORS!" << endl;
	cout << "This program requires 2 players." << endl;
	cout << "You may only enter rock, paper, scissors. All lower case, no symbols." <<endl;
	cout << "Player 1, Please enter your decision." << endl;
	cin >> player1;
	cout << "Player 2, Please enter your decision." << endl;
	cin >> player2;
	
	//rock > scissors > paper > rock
	
	if (player1 == player2)
	{
		cout << "You tied!";
	}
	else if (player1 == "rock")
	{
		if (player2 == "scissors")
		{
			cout << "Player 1 wins";
		}
		else
		{
			cout << "Player 2 wins!";
		}
	}
	else if (player1 == "scissors")
	{
		if (player2 == "rock")
		{
			cout << "Player2 wins!";
		}
		else
		{
			cout << "Player 1 wins!";
		}
	}
	else if (player1 == "paper")
	{
		if (player2 == "scissors")
		{
			cout << "Player 2 wins!";
		}
		else
		{
			cout << "Player 1 wins!";
		}
	}
	else
	{
		cout << "You didnt type your choices correctly. ONLY type 'rock' or 'paper' or 'scissors' without the quotes. All lower case" << endl;
	}
	return 0;
}