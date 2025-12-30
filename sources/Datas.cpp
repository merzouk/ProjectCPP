/* Implementation for Date Class (Date.cpp) */
#include <iostream>
#include <stdexcept>
#include "../header/Datas.hpp"
using namespace std;

namespace ToolsDate
{
	std::string Datas::deleteBlanckChar(const std::string &s)
	{
		std::string result = "";
		int size = s.size();
		for (int i = 0; i < size; i++)
		{
			char c = s[i];
			if (c != ' ')
			{
				result += s[i];
			}
		}
		return result;
	}

	bool Datas::checkIsDigitContaint(const std::string &str)
	{
		int size = str.size();
		if (size == 6 || size == 8)
		{
			for (int i = 0; i < size; i++)
			{
				char c = str[i];
				if (!std::isdigit(c))
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	void Datas::decomposeString(const std::string &str)
	{
		std::string result = "";
		int size = str.size();
		if (size == 6)
		{
			result += str[0];
			this->day = stoi(result);
			result = "";
			result += str[1];
			this->month = stoi(result);
			result = "";
			for (int i = 2; i < size; i++)
			{
				result += str[i];
			}
			this->year = stoi(result);
		}

		if (size == 8)
		{
			std::string result = "";
			for (int i = 0; i < 2; i++)
			{
				result += str[i];
			}
			this->day = stoi(result);
			result = "";
			for (int i = 2; i < 4; i++)
			{
				result += str[i];
			}
			this->month = stoi(result);
			result = "";
			for (int i = 4; i < size; i++)
			{
				result += str[i];
			}
			this->year = stoi(result);
		}
	}

	std::string Datas::searchCharDelimiter(const std::string &s)
	{
		std::string result = "";
		int size = s.size();
		for (int i = 0; i < size; i++)
		{
			char c = s[i];
			if (!std::isdigit(c))
			{
				result += s[i];
				// cout << result << endl;
				return result;
			}
		}
		return "";
	}

	std::string Datas::searchDelimiter(std::string str)
	{
		if (str.find(":") != std::string::npos)
			return ":";

		if (str.find("-") != std::string::npos)
			return "-";

		if (str.find("/") != std::string::npos)
			return "/";

		if (str.find("$") != std::string::npos)
			return "$";

		return (searchCharDelimiter(str));
	}

	// for string delimiter
	void Datas::split(std::string s, std::string delimiter)
	{
		s = deleteBlanckChar(s);
		if (checkIsDigitContaint(s))
		{
			decomposeString(s);
			return;
		}
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		int i = 0;
		while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
		{
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			if (i == 0)
			{
				this->day = stoi(token);
				i++;
			}
			if (i == 1)
			{
				this->month = stoi(token);
			}
		}
		this->year = stoi(s.substr(pos_start));
	}

	// for string delimiter
	void Datas::split(std::string s)
	{
		s = deleteBlanckChar(s);
		if (checkIsDigitContaint(s))
		{
			decomposeString(s);
			return;
		}
		std::string delimiter = this->searchDelimiter(s);
		// cout <<" delimiter = " << delimiter << endl;
		if (delimiter.size() == 0)
		{
			this->day = 0;
			this->month = 0;
			this->year = 0;
			return;
		}
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		int i = 0;
		while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
		{
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			if (i == 0)
			{
				this->day = stoi(token);
				i++;
			}
			if (i == 1)
			{
				this->month = stoi(token);
			}
		}
		this->year = stoi(s.substr(pos_start));
	}

	void Datas::buildDate(std::string s)
	{
		this->split(s);
	}

	Datas::Datas() : day(0), month(0), year(0)
	{
	}
	Datas::~Datas()
	{
	}
	int Datas::getDay()
	{
		return this->day;
	}
	int Datas::getMonth()
	{
		return this->month;
	}
	int Datas::getYear()
	{
		return this->year;
	}
	void Datas::buildDate(std::string s, std::string delimiter)
	{
		this->split(s, delimiter);
	}
}