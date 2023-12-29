/* Header for the Date class (Date.h) */
#ifndef DATE_H
#define DATE_H

#include "Datas.hpp"
#include <string>
using namespace std;

namespace ToolsDate
{
	class Date
	{
	private:
		int year;  // 1753-9999
		int month; // 1-12
		int day;   // 1-31
		const static string STR_MONTHS[];
		const static string STR_MOIS[];
		const static string STR_DAYS[];
		const static string STR_JOURS[];
		const static int DAYS_IN_MONTHS[];
		const static int JOURS_DANS_MOIS[];
		const static int DAYS_IN_MOIS[];
		const static int YEAR_MIN = 1753;
		const static int YEAR_MAX = 9999;
		Datas *datas;

	public:
		static bool isLeapYear(int y);
		static bool isValidDate(int y, int m, int d);
		static int getDayOfWeek(int y, int m, int d);

		Date(int y, int m, int d);
		Date(string date, string delimiter);
		Date(string date);
		~Date();
		
		void setDate(int y, int m, int d);
		int getYear() const;
		int getMonth() const;
		int getDay() const;
		void setYear(int y);
		void setMonth(int m);
		void setDay(int d);
		void print() const;

		Date &nextDay();
		Date &previousDay();
		Date &nextMonth();
		Date &previousMonth();
		Date &nextYear();
		Date &previousYear();
	};
}
#endif