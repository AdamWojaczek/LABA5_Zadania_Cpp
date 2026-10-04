#pragma once

#include <string>

//---------------------------------------------------------------------------------------------------------------------

class CIOStream
{
private:
	using string = std::string;

	string m_last{};					// last read from input stream

public:
	void ClearScreen();
	
	void Print(const string& text);
	void Print(int value);
	void Print(double value);
	void PrintLine(const string& text = "");
	
	void WaitForEnter();
	void ClearInput();
	
	bool ReadInt(int& value);
	bool ReadInt(const string& info, int& value);
	bool ReadDouble(double& value);
	bool ReadDouble(const string& info, double& value);
	bool ReadString(string& text);
	bool ReadString(const string& info, string& text);
};

//---------------------------------------------------------------------------------------------------------------------
