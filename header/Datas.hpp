#ifndef DATAS_H
#define DATAS_H

#include <iostream>
#include <string>

using namespace std;

namespace ToolsDate
{
	class Datas
	{
	private:
		int day;
		int month;
		int year;

		std::string deleteBlanckChar(const std::string &s);
		bool checkIsDigitContaint(const std::string &str);
		void decomposeString(const std::string &str);
		std::string searchCharDelimiter(const std::string &s);
		std::string searchDelimiter(std::string str);
		// for string delimiter
		void split(std::string s, std::string delimiter);
		// for string delimiter
		void split(std::string s);

	public:
		Datas();
		~Datas();
		int getDay();
		int getMonth();
		int getYear();
		void buildDate(std::string s, std::string delimiter);
		void buildDate(std::string s);
	};
}

#endif
