#ifndef LOGGER_H_FILE
#define LOGGER_H_FILE

//#pragma once

#include <iostream>

#include <ctime>
#include <string>

using namespace std;

namespace Manage
{
       class Logger
       {
              private:
                     enum LEVEL { INFO = 1 , ERROR = 2, WARNING = 3, DEBUG = 4 };

                     string static prepare_time_logger()
                     {
                        // current date/time based on current system
                        time_t now = time(0);

                        //cout << "Number of sec since January 1,1970 is:: " << now << endl;

                        tm *ltm = localtime(&now);

                        // calculate various components of tm structure.
                        string str_year = to_string(1900 + ltm->tm_year);

                        string str_minute = "";
                        (ltm->tm_min < 10) ? (str_minute = "0"+to_string(ltm->tm_min)) : (str_minute = to_string(ltm->tm_min));

                        string str_seconde = "";
                        (ltm->tm_sec < 10) ? (str_seconde = "0"+to_string(ltm->tm_sec)) : (str_seconde = to_string(ltm->tm_sec));

                        string str_hour = "";
                        (ltm->tm_hour < 10) ? (str_hour = "0"+to_string(ltm->tm_hour)) : (str_hour = to_string(ltm->tm_hour));

                        string str_month = "";
                        ((ltm->tm_mon + 1) < 10) ? (str_month = "0"+to_string(ltm->tm_mon + 1)) : (str_month = to_string(ltm->tm_mon + 1));

                        string str_day = "";
                        (ltm->tm_mday < 10) ? (str_day = "0"+to_string(ltm->tm_mday)) : (str_day = to_string(ltm->tm_mday));

                        string date_str = str_year +"/"+ str_month + "/" + str_day + "  "
                                          + str_hour+":"+str_minute+":"+str_seconde;
                        return date_str;
                     }

                     string static prepare_message_logger(int level_logger, string msg_logger)
                     {
                             if (level_logger == INFO)    return "\033[0;34m[INFO ]\033[0;0m"    + msg_logger;
                        else if (level_logger == ERROR)   return "\033[0;31m[ERROR ]\033[0;0m"   + msg_logger;
                        else if (level_logger == WARNING) return "\033[0;33m[WARNING ]\033[0;0m" + msg_logger;
                        else if (level_logger == DEBUG)   return "\033[0;35m[DEBUG ]\033[0;0m"   + msg_logger;
                        else                              return "\033[0;34m[INFO ]\033[0;0m"    + msg_logger;
                     }

              public:
                     Logger(){}
                     ~Logger(){}

                     void static log(int level_logger, string message_logger)
                     {
                           message_logger = " [" + prepare_time_logger() + "] " + message_logger + "\n";
                           cout << prepare_message_logger(level_logger, message_logger);
                     }
       };
}

#endif // LOGGER_H_FILE
