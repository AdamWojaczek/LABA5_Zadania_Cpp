#include "StrUtils.h"

//---------------------------------------------------------------------------------------------------------------------

namespace StrUtils
{
	string IntToStr(int value)
	{
		return std::to_string(value);
	}

	string DoubleToStr(double value)
	{
		std::ostringstream stream;
		stream << std::defaultfloat << value;
		return stream.str();
	}

	string DoubleToStrFixed(double value, unsigned int precision)
	{
		if (precision > 15)
			precision = 15;

		std::ostringstream stream;
		stream << std::fixed << std::setprecision(precision) << value;

		return stream.str();
	}

	string DoubleToStrScientific(double value)
	{
		std::ostringstream stream;
		stream << std::scientific << value;

		return stream.str();
	}

	bool StrToInt(const string& text, int& value)
	{
		bool result = false;

		try
		{
			std::size_t pos;
			int temp = std::stoi(text, &pos);
			if (pos == text.length())
			{
				value = temp;
				result = true;
			}
		}
		catch (const std::exception)
		{
			result = false;
		}

		return result;
	}

	bool StrToDouble(const string& text, double& value)
	{
		bool result = false;
		string textCopy = Replace(text, ',', '.');

		try
		{
			std::size_t pos;
			double temp = std::stod(textCopy, &pos);
			if (pos == textCopy.length())
			{
				value = temp;
				result = true;
			}
		}
		catch (const std::exception)
		{
			result = false;
		}

		return result;
	}

	bool StrCompareIC(const string& text1, const string& text2)
	{
		string t1 = StrToUpper(StrTrim(text1));
		string t2 = StrToUpper(StrTrim(text2));

		return (t1 == t2);
	}

	string StrToUpper(const string& text)
	{
		string result = text;
		
		for (char& c : result)
			c = std::toupper(static_cast<unsigned char>(c));

		return result;
	}

	string StrToLower(const string& text)
	{
		string result = text;

		for (char& c : result)
			c = std::tolower(static_cast<unsigned char>(c));

		return result;
	}

	string StrTrim(const string& text)
	{
		string result = text;

		std::size_t first = result.find_first_not_of(" \n\r\t");
		if (first == string::npos)
			result.clear();
		else
		{
			result.erase(0, first);
			std::size_t last = result.find_last_not_of(" \n\r\t");
			result.erase(last + 1);
		}

		return result;
	}

	string Replace(const string& text, char oldChar, char newChar)
	{
		string result = text;

		for (char& c : result)
		{
			if (c == oldChar)
				c = newChar;
		}

		return result;
	}
}

//---------------------------------------------------------------------------------------------------------------------