#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;

	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,15 },{ 7,20 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const
{
	if (!IsIsogram(Guess)) // if guess isn't isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) //if guess isn't lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}

//recieves a Valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	//loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++)
	{
		//comparing against the guess
		for (int32 j = 0; j < WordLength; j++)
		{
			if (Guess[j] == MyHiddenWord[i])
			{
				if (i == j)
				{
					BullCowCount.Bulls++; //increment bulls
				}
				else
				{
					BullCowCount.Cows++; //increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen; //setup our for all letters of word

	for (auto Letter : Word)
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter])
		{
			return false; //we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
