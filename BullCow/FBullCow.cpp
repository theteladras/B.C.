#include "FBullCow.h"
#include <map>
#include <vector>
#include <time.h>
#define TMap std::map

using int32 = int;

FBullCow::FBullCow() {
	reset();
} // constructor

int32 FBullCow::getCurrentTry() const { return myCurrentTry; }
int32 FBullCow::getLevel() const { return level; }
int32 FBullCow::getHiddenWordLength() const { return myHiddenWord.length(); }
bool FBullCow::isGameWon() const { return bGameWon; }
int32 FBullCow::getMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 5}, {5, 6}, {6, 8}, {7, 10}, {8, 15}, {9, 20}, {10, 30} };
	return WordLengthToMaxTries[myHiddenWord.length()];
}

void FBullCow::reset() {
	srand(time(0));
	myHiddenWord = getHiddenWord(rand());
	myCurrentTry = 1;
	bGameWon = false;
	return;
}

void FBullCow::changeLevel(bool flag)
{
	// icrease level on success
	if (flag) {
		level++;
		return;
	}
	// reset level on fail
	else {
		level = 1;
	}
}

EGuessStatus FBullCow::checkGuessValidity(FString Guess) const {
	if (!isIsogram(Guess)) {
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (isLowerCase(Guess)) {
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (Guess.length() != getHiddenWordLength()) {
		return EGuessStatus::WRONG_LENGTH;
	}
	else {
		return EGuessStatus::OK;
	}
}

// if its a valid guess => counting bulls and cows, increment number of try
FBullCowCount FBullCow::SubmitValidGuess(FString Guess)
{
	// incriment the turn number
	myCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	int32 HiddenWordLength = myHiddenWord.length();
	int32 GuessedWordLength = Guess.length();
	
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) { // loop through all letters in the hidden word
		for (int32 GChar = 0; GChar < GuessedWordLength; GChar++) { // loop through all letters in the guess
			if (Guess[GChar] == myHiddenWord[MHWChar]) { // compare letters against the hidden word
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameWon = true;
	}
	else {
		bGameWon = false;
	}
	return BullCowCount;
}

bool FBullCow::isIsogram(FString Word) const {
	if (Word.length() < 2) { return true; }

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {
		Letter = tolower(Letter);

		if (LetterSeen[Letter]) {
			return false; // not ISOGRAM
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCow::isLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return true;
		}
	}
	return false;
}

FString FBullCow::getHiddenWord(int32 rnum)
{
	std::vector<std::string> HIDEN_WORD = { "planet", "world", "traveling", "main", "mom", "yes", "nope", "capitalism", "america" };
	int32 HIDEN_WORD_LENGTH = std::size(HIDEN_WORD);
	int32 newHWindex = rnum % HIDEN_WORD_LENGTH;
	
	HWindex = newHWindex;
	return HIDEN_WORD[HWindex];
}


