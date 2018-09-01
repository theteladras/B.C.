#include <iostream>
#include <string>	
#include "FBullCow.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCow BCGame; // instantiate a new game

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);

	return 0; // exit the application
}

 
// introdduction of the game, game notes...
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.getHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.reset();
	int32 MaxTries = BCGame.getMaxTries();
	
	// loop for the number of turns asking for guesses
	// TODO change from FOR to WHILE loop once we are validating tries
	for (int32 count = 1; count <= MaxTries; count++) {
		
		FText Guess = GetValidGuess(); // TODO make loop checking valid
		
		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}

	// TODO summarise game
}

// loop untill valid guess
FText GetValidGuess()
{
	EGuessStatus status = EGuessStatus::INVALID_STATUS;
	do {
		int32 CurrentTry = BCGame.getCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		FText Guess = "";
		std::getline(std::cin, Guess);

		status = BCGame.checkGuessValidity(Guess);
		switch (status) {
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a" << BCGame.getHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter word without repeating letters." << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter lower case word." << std::endl;
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (status != EGuessStatus::OK); // loop untill valid
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}