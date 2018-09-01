#include "FBullCow.h"

using int32 = int;

FBullCow::FBullCow() {
	reset();
}

int32 FBullCow::getMaxTries() const { return myMaxTries; }
int32 FBullCow::getCurrentTry() const { return myCurrentTry; }
int32 FBullCow::getLevel() const { return level; }
int32 FBullCow::getHiddenWordLength() const { return myHiddenWord.length(); }

void FBullCow::reset() {
	constexpr int32 MAX_TRIES = 8;
	myMaxTries = MAX_TRIES;
	const FString HIDEN_WORD = "planet";
	myHiddenWord = HIDEN_WORD;
	myCurrentTry = 1;
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

bool FBullCow::isGameWon() const {
	return false;
}

EGuessStatus FBullCow::checkGuessValidity(FString Guess) const {
	if (false) {
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (Guess.length() != getHiddenWordLength()) {
		return EGuessStatus::WRONG_LENGTH;
	}
	else if (false) {
		return EGuessStatus::NOT_LOWERCASE;
	}
	else {
		return EGuessStatus::OK;
	}
}

// if its a valid guess => counting bulls and cows, increment number of try
FBullCowCount FBullCow::SubmitGuess(FString Guess)
{
	// incriment the turn number
	myCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	int32 HiddenWordLength = myHiddenWord.length();
	int32 GuessedWordLength = Guess.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < GuessedWordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == myHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	return BullCowCount;
}
