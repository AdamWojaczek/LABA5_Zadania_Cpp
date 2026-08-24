#pragma once

#include <string>
#include <vector>
#include "CIOStream.h"
#include "StrUtils.h"

//---------------------------------------------------------------------------------------------------------------------

class CApplication
{	
private:	
	using string = std::string;

	template<typename T>
	using vector = std::vector<T>;

	CIOStream ios;			// nak³adka na operacje cin/cout

	vector<string> exerciseNames {
								   "Obliczanie objetosci kuli",
								   "Gra 'Kolko i krzyzyk' (w przygotowaniu)",
								   "Zadanie kolejne (w planach)"
								 };
	void ShowMenu();
	void DoExercise(int id, bool clearScreen = true);

	// metody realizuj¹ce poszczególne zadania
	void CalculateSphereVolume();

public:
	int Run();
};

//---------------------------------------------------------------------------------------------------------------------
