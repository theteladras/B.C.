#include <iostream>
#include <string>


void printIntro();
void playGame();
std::string getGuess();
bool askToPlayAgain();

int main() 
{
	do {
		printIntro();
		playGame();
	} while (askToPlayAgain());
	return 0;
}

// game intro / notes
void printIntro() {
	constexpr int WORD_LENGTH = 5;
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "Bulls and Cows is a word game, where ur goal would be to gess the word in a limit of number of guesses.\n";
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram ( word or phrase without a repeating letter )";
	std::cout << std::endl;
	return;
}

void playGame() {
	// loop for the number of required guesses
	constexpr int NUMBER_OF_TURNS = 5;
	for (int i = 1; i <= NUMBER_OF_TURNS; i++) {
		std::string Guess = "";
		Guess = getGuess();
		std::cout << "You guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}
}

// ask for user inout / guess
std::string getGuess() {
	std::cout << "Enter the guess: ";
	std::string Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

bool askToPlayAgain() {
	std::cout << "Do you want to play again? (y/n) ";
	std::string Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
