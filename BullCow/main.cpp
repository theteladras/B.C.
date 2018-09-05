#include <iostream>
#include <string>	
#include "FBullCow.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
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
	
	// loop for the number of turns asking for guesses while the game is NOT won
	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= MaxTries) {
		
		FText Guess = GetValidGuess();
		
		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}

	PrintGameSummary();
}

// loop untill valid guess
FText GetValidGuess()
{	
	FText Guess = "";
	EGuessStatus status = EGuessStatus::INVALID_STATUS;
	do {
		int32 CurrentTry = BCGame.getCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.getMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		status = BCGame.checkGuessValidity(Guess);
		switch (status) {
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n\n" << std::endl;
			break;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter word without repeating letters.\n\n" << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter lower case word.\n\n";
			break;
		default:
			break;
		}
	} while (status != EGuessStatus::OK); // loop untill valid
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.isGameWon()) {
		std::cout << "You have won!" << std::endl;
	}
	else {
		std::cout << "You lost..." << std::endl;
	}
}