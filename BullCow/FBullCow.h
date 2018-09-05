#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	INVALID_STATUS,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE
};

class FBullCow {
public:
	FBullCow();
	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getLevel() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	EGuessStatus checkGuessValidity(FString) const;

	void reset();
	void changeLevel(bool);
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 myCurrentTry;
	int32 level;
	int32 HWindex = 0;
	FString myHiddenWord;
	bool bGameWon;

	bool isIsogram(FString) const;
	bool isLowerCase(FString) const;
	FString getHiddenWord(int32);
};