#include "CIOStream.h"

//---------------------------------------------------------------------------------------------------------------------

void CIOStream::ClearScreen()
{
	system("cls");
}

//---------------------------------------------------------------------------------------------------------------------

void CIOStream::Print(const string& text)
{
	std::cout << text;
}

//---------------------------------------------------------------------------------------------------------------------

void CIOStream::Print(int value)
{
	std::cout << value;
}

//---------------------------------------------------------------------------------------------------------------------

void CIOStream::Print(double value)
{
	std::cout << value;
}

//---------------------------------------------------------------------------------------------------------------------

void CIOStream::PrintLine(const string& text)
{
	std::cout << text << std::endl;
}

//---------------------------------------------------------------------------------------------------------------------

void CIOStream::WaitForEnter()
{
	PrintLine("\nNacisnij ENTER...");
	ClearInput();
}

//---------------------------------------------------------------------------------------------------------------------

void CIOStream::ClearInput()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//---------------------------------------------------------------------------------------------------------------------

bool CIOStream::ReadInt(int& value)
{
	bool result = false;
	string text;

	if (ReadString(text) && StrUtils::StrToInt(text, value))
		result = true;
	else
		PrintLine("Wprowadzona wartosc jest pusta lub nie jest liczba calkowita!");

	m_last = std::move(text);

	return result;
}

//---------------------------------------------------------------------------------------------------------------------

bool CIOStream::ReadInt(const string& info, int& value)
{
	Print(info + " ");
	return ReadInt(value);
}

//---------------------------------------------------------------------------------------------------------------------

bool CIOStream::ReadDouble(double& value)
{
	bool result = false;
	string text;
	
	if (ReadString(text) && StrUtils::StrToDouble(text, value))
		result = true;
	else
		PrintLine("Wprowadzona wartosc jest pusta lub nie jest liczba rzeczywista!");

	m_last = std::move(text);

	return result;
}

//---------------------------------------------------------------------------------------------------------------------

bool CIOStream::ReadDouble(const string& info, double& value)
{
	Print(info + " ");
	return ReadDouble(value);
}

//---------------------------------------------------------------------------------------------------------------------

bool CIOStream::ReadString(string& text)
{
	std::getline(std::cin, text);
	m_last = text;

	return !text.empty();
}

//---------------------------------------------------------------------------------------------------------------------

bool CIOStream::ReadString(const string& info, string& text)
{
	Print(info + " ");
	return ReadString(text);
}

//---------------------------------------------------------------------------------------------------------------------
