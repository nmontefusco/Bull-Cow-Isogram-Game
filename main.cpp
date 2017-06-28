/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC Pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.
*/
#include <iostream> 
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());
	return 0;
}

//Intro to game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows Game\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try #" << CurrentTry << "\n";
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);
		std::cout << std::endl;

		Status = BCGame.IsGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n ";
			break;
		default:
			break;
		}
	} while (Status !=EGuessStatus::OK); //loops until there are no errors
	return Guess;
}

void PlayGame()
{
	BCGame.Reset();
	int32 Maxtry = BCGame.GetMaxTries();
	
	//loop asking for guesses while game is NOT Won && Tries still remain.
	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= Maxtry)
	{
		FText Guess = GetValidGuess(); 
		
		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

	bool AskToPlayAgain()
	{
		std::cout << "Do you want to play again with the same hidden word? y/n ";
		FText Response = "";
		std::getline(std::cin, Response);
		if ((Response[0]=='y') || (Response[0]=='Y'))
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
	
	void PrintGameSummary() 
	{
		if (BCGame.IsGameWon())
		{
			std::cout << "Well Done - You Win!\n";
		}
		else
		{
			std::cout << "Better luck next time!\n";
		}
	}