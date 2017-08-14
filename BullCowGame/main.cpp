/*This is the console executable that uses the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.

*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string; //to conform with Unreal coding standards
using int32 = int; //to conform with Unreal coding standards

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game


//the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; //exit the app
}


// introduce the game
void PrintIntro()
{
	//constexpr int32 WORD_LENGTH = 9;
	int32 WordLength = BCGame.GetHiddenWordLength();
	std::cout << std::endl;
	std::cout << "*************************************************************************";
	std::cout << std::endl;
	std::cout << "**  Welcome to Bulls and Cows, a fun word game with intense action :)  **";
	std::cout << std::endl;
	std::cout << "*************************************************************************";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "    ,           ,                           ,/         \\,       " << std::endl;
	std::cout << "   /             \\      BULLS              ((__,-'''-,__))      " << std::endl;  
	std::cout << "  ((__-^^-,-^^-__))                         `--)~   ~(--`       " << std::endl;
	std::cout << "   `-_---' `---_-'                         .-'(       )`-.      " << std::endl;
	std::cout << "    <__|o` 'o|__>            &             `~~`d\\   /b`~~`      " << std::endl;
	std::cout << "       \\  `  /                                 |     |          " << std::endl;
	std::cout << "        ): :(                    COWS          (6___6)          " << std::endl;
	std::cout << "        :o_o:                                   `---`           " << std::endl;
	std::cout << "        ' - '                                                    " << std::endl;
	std::cout << std::endl;
	std::cout << "*************************************************************************";
	std::cout << std::endl;
	std::cout << "Can you guess the " << WordLength << " letter isogram* I'm thinking of?" << std::endl;
	std::cout << "(*An isogram is a word without repeating letters.)" << std::endl;
	std::cout << "*************************************************************************";
	std::cout << std::endl;
	
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while the game 
	//is NOT won and still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		//submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = [" << BullCowCount.Bulls;
		std::cout << "], Cows = [" << BullCowCount.Cows << "]";
		std::cout << std::endl;
		std::cout << std::endl;
	}

	PrintGameSummary();

	return;
}


//loop until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	int32 MaxTries = BCGame.GetMaxTries();
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{ 
		int32 CurrentTry = BCGame.GetCurrentTry();
		//get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << MaxTries << ". Enter your guess: ";
		getline(std::cin, Guess);

		//check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
			case EGuessStatus::Wrong_Length:
			{
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.";
				std::cout << std::endl;
				std::cout << std::endl;
				break;
			}
			case EGuessStatus::Not_Isogram:
			{
				std::cout << "Please enter a word without repeating letters.";
				std::cout << std::endl;
				std::cout << std::endl;
				break;
			}
			case EGuessStatus::Not_LowerCase:
			{
				std::cout << "Please enter only lowercase letters.";
				std::cout << std::endl;
				std::cout << std::endl;
				break;
			}
			default:
			{// the guess is valid
				break; 
			}
		}

	} while (Status != EGuessStatus::OK); // keep looping until we get no errors

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)?";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "CONGRATULATIONS! YOU HAVE WON!";
		std::cout << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "BETTER LUCK NEXT TIME, BUT STAY POSITIVE :) !";
		std::cout << std::endl;
		std::cout << std::endl;
	}

	return;

}


