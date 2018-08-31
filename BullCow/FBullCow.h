#pragma once
#include <string>

class FBullCow {
public:
	void reset();
	int getMaxTries();
	int getCurrentTry();
	bool isGameWon();
	bool checkGuessValidity(std::string);

private:
	int myCurrentTry;
	int myMaxTries;
};