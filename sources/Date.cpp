/* Implementation for Date Class (Date.cpp) */
#include <iostream>
#include <stdexcept>
#include "../header/Date.hpp"
using namespace std;

namespace ToolsDate
{
   // Initialize static non-integer variable (must be done outside the class declaration)
   const string Date::STR_MONTHS[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

   const string Date::STR_MOIS[] = {"Jan", "Fev", "Mar", "Avr", "Mai", "Jun",
                                    "Jul", "Aou", "Sep", "Oct", "Nov", "Dec"};

   const int Date::DAYS_IN_MONTHS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

   const int Date::JOURS_DANS_MOIS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

   const string Date::STR_DAYS[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                                    "Thursday", "Friday", "Saturday"};

   const string Date::STR_JOURS[] = {"Dimanche", "Lundi", "Mardi", "Mercredi",
                                     "Jeudi", "Vendredi", "Samedi"};

   // A static function that returns true if the given year is a leap year
   bool Date::isLeapYear(int year)
   {
      return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
   }

   // A static function that returns true if the given y, m, d constitutes a valid date
   bool Date::isValidDate(int y, int m, int d)
   {
      if (y >= YEAR_MIN && y <= YEAR_MAX && m >= 1 && m <= 12)
      {
         int lastDayOfMonth = DAYS_IN_MONTHS[m - 1];
         if (m == 2 && isLeapYear(y))
         {
            lastDayOfMonth = 29;
         }
         return (d >= 1 && d <= lastDayOfMonth);
      }
      else
      {
         return false;
      }
   }

   // A static function that returns the day of the week (0:Sun, 6:Sat) for the given date
   // Wiki "Determination of the day of the week" for the algorithm
   int Date::getDayOfWeek(int y, int m, int d)
   {
      int centuryTable[] = {4, 2, 0, 6, 4, 2, 0, 6}; // 17xx, 18xx, ...
      int MonthTable[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
      int MonthLeapYearTable[] = {6, 2, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

      int century = y / 100;
      int twoDigitYear = y % 100;
      int centuryTableIndex = (century - 17) % 8;
      // Date before 17xx are not valid, but needed to prevent negative index
      if (centuryTableIndex < 0)
      {
         centuryTableIndex += 8;
      }
      int sum = centuryTable[centuryTableIndex] + twoDigitYear + twoDigitYear / 4;
      if (isLeapYear(y))
      {
         sum += MonthLeapYearTable[m - 1];
      }
      else
      {
         sum += MonthTable[m - 1];
      }
      sum += d;
      return sum % 7;
   }

   // Constructor
   Date::Date(int y, int m, int d)
   {
      this->setDate(y, m, d);
   }

   // Constructor
   Date::Date(string date_str, string delimiter)
   {
      this->datas = new Datas();
      this->datas->buildDate(date_str, delimiter);
      this->setDate(this->datas->getYear(), this->datas->getMonth(), this->datas->getDay());
      delete this->datas;
      this->datas = nullptr;
   }

   // Constructor
   Date::Date(string date_str)
   {
      this->datas = new Datas();
      this->datas->buildDate(date_str);
      this->setDate(this->datas->getYear(), this->datas->getMonth(), this->datas->getDay());
      delete this->datas;
      this->datas = nullptr;
   }

   // Destructor
   Date::~Date()
   {
   }

   // With Input validation
   void Date::setDate(int y, int m, int d)
   {
      this->setYear(y);
      this->setMonth(m);
      this->setDay(d); // need to set the day after year and month
   }

   int Date::getYear() const
   {
      return year;
   }

   void Date::setYear(int y)
   {
      if (y >= this->YEAR_MIN && y <= this->YEAR_MAX)
      {
         year = y;
      }
      else
      {
         throw invalid_argument("Error: Invalid year (1753-9999)!");
      }
   }

   int Date::getMonth() const
   {
      return month;
   }

   void Date::setMonth(int m)
   {
      if (m >= 1 && m <= 12)
      {
         month = m;
      }
      else
      {
         throw invalid_argument("Error: Invalid month (1-12)!");
      }
   }

   int Date::getDay() const
   {
      return day;
   }

   // Assuming that the year and month are already set
   void Date::setDay(int d)
   {
      int lastDayOfMonth = this->DAYS_IN_MONTHS[month - 1];
      if (month == 2 && this->isLeapYear(year))
      {
         lastDayOfMonth = 29;
      }
      if (d >= 1 && d <= lastDayOfMonth)
      {
         day = d;
      }
      else
      {
         throw invalid_argument("Error: Invalid day (1-28|29|30|31)!");
      }
   }

   // Print this instance in the format "xxxday, d mmm yyyy".
   void Date::print() const
   {
      cout << this->STR_DAYS[getDayOfWeek(year, month, day)] << ", "
           << day << " " << this->STR_MONTHS[month - 1] << " " << year << endl;
   }

   // Increment this instance to the next day and return this instance by reference
   Date &Date::nextDay()
   {
      int lastDayOfMonth = this->DAYS_IN_MONTHS[month - 1];
      if (month == 2 && this->isLeapYear(year))
      {
         lastDayOfMonth = 29;
      }

      // check day against the end of month
      if (++day > lastDayOfMonth)
      {
         day = 1;
         if (++month > 12)
         {
            month = 1;
            if (++year > this->YEAR_MAX)
            {
               throw out_of_range("Error: Next day is out of range!");
            }
         }
      }
      return *this;
   }

   // Decrement this instance to the previous day and return this instance by reference
   Date &Date::previousDay()
   {
      int lastDayOfMonth = this->DAYS_IN_MONTHS[month - 1];
      if (month == 2 && this->isLeapYear(year))
      {
         lastDayOfMonth = 29;
      }

      // check day against the end of month
      if (--day < 1)
      {
         day = lastDayOfMonth;
         if (--month < 1)
         {
            month = 12;
            if (--year < this->YEAR_MIN)
            {
               throw out_of_range("Error: Previous day is out of range!");
            }
         }
      }
      return *this;
   }

   // Increment this instance to the next month and return this instance by reference
   Date &Date::nextMonth()
   {
      if (++month > 12)
      {
         month = 1;
         if (++year > this->YEAR_MAX)
         {
            throw out_of_range("Error: Next month is out of range!");
         }
      }
      // may need to adjust the last day of the month
      int lastDayOfMonth = this->DAYS_IN_MONTHS[month - 1];
      if (month == 2 && this->isLeapYear(year))
      {
         lastDayOfMonth = 29;
      }
      if (day > lastDayOfMonth)
      {
         day = lastDayOfMonth;
      }
      return *this;
   }

   // Decrement this instance to the previous month and return this instance by reference
   Date &Date::previousMonth()
   {
      if (--month < 1)
      {
         month = 12;
         if (--year < this->YEAR_MIN)
         {
            throw out_of_range("Error: Previous month is out of range!");
         }
      }
      // may need to adjust the last day of the month
      int lastDayOfMonth = this->DAYS_IN_MONTHS[month - 1];
      if (month == 2 && this->isLeapYear(year))
      {
         lastDayOfMonth = 29;
      }
      if (day > lastDayOfMonth)
      {
         day = lastDayOfMonth;
      }
      return *this;
   }

   // Increment this instance to the next year and return this instance by reference
   Date &Date::nextYear()
   {
      if (++year > this->YEAR_MAX)
      {
         throw out_of_range("Error: Next year is out of range!");
      }
      // may need to adjust the last day of the month for leap year (29 Feb)
      //  to non-leap year (28 Feb)
      if (month == 2 && day == 29 && !this->isLeapYear(year))
      {
         day = 28;
      }
      return *this;
   }

   // Decrement this instance to the previous year and return this instance by reference
   Date &Date::previousYear()
   {
      if (--year < this->YEAR_MIN)
      {
         throw out_of_range("Error: Previous year is out of range!");
      }
      // may need to adjust the last day of the month for leap year (29 Feb)
      //  to non-leap year (28 Feb)
      if (month == 2 && day == 29 && !this->isLeapYear(year))
      {
         day = 28;
      }
      return *this;
   }
}
