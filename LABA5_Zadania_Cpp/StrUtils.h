#pragma once

#include <string>

//---------------------------------------------------------------------------------------------------------------------

namespace StrUtils
{
	using string = std::string;

	string IntToStr(int value);
	string UIntToStr(unsigned int value);
	string DoubleToStr(double value);
	string DoubleToStrFixed(double value, unsigned int precision = 3);
	string DoubleToStrScientific(double value);
	
	bool StrToInt(const string& text, int& value);
	bool StrToUInt(const string& text, unsigned int& value);
	bool StrToDouble(const string& text, double& value);

	bool StrCompareIC(const string& text1, const string& text2);
	string StrToUpper(const string& text);
	string StrToLower(const string& text);
	string StrTrim(const string& text);
	string Replace(const string& text, char oldChar, char newChar);
};

//---------------------------------------------------------------------------------------------------------------------
