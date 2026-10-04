#pragma once

#include <string>
#include <vector>
#include "CIOStream.h"

//---------------------------------------------------------------------------------------------------------------------

class CApplication
{	
private:	
	using string = std::string;

	template<typename T>
	using vector = std::vector<T>;

	CIOStream ios;					// input/output stream wrapper

	// Task display names
	vector<string> exerciseNames = {
		"Obliczanie objetosci kuli",
		"Gra 'Kolko i krzyzyk'",
		"Testowa klasa CComplex dla liczb zespolonych",
		"'Game of life'"
	};

	void ShowMenu();
	void DoExercise(int id, bool clearScreen = true);

	// Methods implementing individual tasks
	void CalculateSphereVolume();
	void RunTicTacToeGame();
	void TestCComplex();
	void RunLifeGame();

public:
	int Run();
};

//---------------------------------------------------------------------------------------------------------------------
