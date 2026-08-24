#include "CApplication.h"

//---------------------------------------------------------------------------------------------------------------------

int CApplication::Run()
{
	bool close = false;
	
	while (!close)
	{
		ShowMenu();

		int id = 0;
		bool error = false;
		
		if (ios.ReadInt("Wybierz zadanie:", id))
		{
			if ((id > 0) && (id <= exerciseNames.size()))
				DoExercise(id);
			else if (id == 0)
			{
				close = true;
				ios.PrintLine("Zamykanie programu.");
			}
			else
				error = true;
		}
		else
			error = true;

		if (error)
		{
			ios.PrintLine("Podano nieprawidlowy numer zadania!");
			ios.WaitForEnter();
		}
	}

	return 0;
}

//---------------------------------------------------------------------------------------------------------------------

void CApplication::ShowMenu()
{
	ios.ClearScreen();
	
	string text = "-----------------------------------------------\n"
				  " Kurs Unreal Engine - zadania praktyczne w C++\n"
				  "   Prowadzacy: Maciej Celmer\n"
				  "   Kursant: Adam Wojaczek\n"
				  "-----------------------------------------------\n"
				  "\nTablica zadan:\n";
	
	for (int i = 0; i < exerciseNames.size(); i++)
		text += string("\n  [" + StrUtils::IntToStr(i + 1) + "] ") + exerciseNames[i];
		
	text += "\n\n  [0]\tKoniec\n\n";
	
	ios.Print(text);
}

//---------------------------------------------------------------------------------------------------------------------

void CApplication::DoExercise(int id, bool clearScreen)
{	
	if (clearScreen)
		ios.ClearScreen();

	ios.Print("*** ZADANIE NR " + StrUtils::IntToStr(id) + " ***\n\n");

	switch (id)
	{
		case 1:
			CalculateSphereVolume();
			break;
		
		default:
			ios.PrintLine("Brak zadanie o numerze " + StrUtils::IntToStr(id) + "!");
	}
	
	ios.WaitForEnter();
}

//---------------------------------------------------------------------------------------------------------------------
// [1] Napisz program w C++, który obliczy objêtoœæ kuli o promieniu podanym przez u¿ytkownika.
// Dodatkowo: Dodaæ mo¿liwoœæ konwersji jednostek. 

void CApplication::CalculateSphereVolume()
{	
	enum class EUnit : int { NONE, MM, CM, M, KM };
	constexpr double PI = 3.14159265358979323846;
	double radius = 0.0;

	if (ios.ReadDouble("Podaj wartosc promienia kuli:", radius) && (radius > 0))
	{
		EUnit unit = EUnit::NONE;
		string unitStr = "";

		// Uwaga: wygodniej i optymalniej jest to zrobiæ poprzez odczyt liczby: 1, 2...,
		// ale celowo (w ramach æwiczeñ) robiê to przez string,
		// aby odczytywa³o siê raz liczbê (wartoœæ), a raz string (jednostka).
		ios.ReadString("Wybierz jednostke (mm, cm, m, km) [Enter --> cm]: ", unitStr);
		unitStr = StrUtils::StrToLower(StrUtils::StrTrim(unitStr));
		
		if (StrUtils::StrCompareIC(unitStr, "mm"))
			unit = EUnit::MM;
		else if (StrUtils::StrCompareIC(unitStr, "cm"))
			unit = EUnit::CM;
		else if (StrUtils::StrCompareIC(unitStr, "m"))
			unit = EUnit::M;
		else if (StrUtils::StrCompareIC(unitStr, "km"))
			unit = EUnit::KM;
		else if (unitStr.empty())
		{
			unit = EUnit::CM;
			unitStr = "cm";
		}
		else
		{
			unit = EUnit::NONE;
			ios.PrintLine("Wybrano nieobslugiwana/bledna jednostke!");
		}

		if (unit != EUnit::NONE)
		{
			// wersja uproszczona - przeliczenie na bazowe cm
			double radiusCm = 0.0;

			switch (unit)
			{
				case EUnit::MM:	 radiusCm = radius / 10.0;		break;
				case EUnit::CM:	 radiusCm = radius;				break;
				case EUnit::M:	 radiusCm = radius * 100.0;		break;
				case EUnit::KM:	 radiusCm = radius * 100000.0;	break;
			}

			// obliczenie objêtoœci w cm3
			double valueCm3 = (4.0 / 3.0) * PI * pow(radiusCm, 3);

			// przeliczenie objêtoœci na pozosta³e jednostki
			double valueMm3 = valueCm3 * 1'000.0;
			double valueM3 = valueCm3 / 1'000'000.0;
			double valueKm3 = valueCm3 / 1'000'000'000'000'000.0;

			ios.PrintLine("\nObjetosc kuli o promieniu " + StrUtils::DoubleToStr(radius) + " " + unitStr + " wynosi: ");
			ios.PrintLine("\ta) " + StrUtils::DoubleToStr(valueMm3) + " mm3");
			ios.PrintLine("\tb) " + StrUtils::DoubleToStr(valueCm3) + " cm3");
			ios.PrintLine("\tc) " + StrUtils::DoubleToStr(valueM3) + " m3");
			ios.PrintLine("\td) " + StrUtils::DoubleToStr(valueKm3) + " km3");
		}
	}
	else
		ios.PrintLine("Promien kuli musi byc wiekszy od 0.0!");
}

//---------------------------------------------------------------------------------------------------------------------
