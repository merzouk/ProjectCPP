#ifndef LOGGER_H_FILE
#define LOGGER_H_FILE

#pragma once

#include <iostream> // std::cout, std::ostream, std::ios
#include <fstream>
#include <sys/stat.h>

#include <ctime>
#include <string>
#include "Level.hpp"

using namespace std;

namespace Manage
{
      class Logger
      {
      private:
            // enum LEVEL { INFO = 1 , ERROR = 2, WARNING = 3, DEBUG = 4 };

            string static convertToString(char *a)
            {
                  string s = "";
                  if (!a)
                        return s;
                  int i = 0;
                  while (*(a + i) != '\0')
                  {
                        s = s + *(a + i);
                        i++;
                  }
                  return s;
            }

            string static constConvertToString(const char *a)
            {
                  string s = "";
                  if (!a)
                        return s;
                  int i = 0;
                  while (*(a + i) != '\0')
                  {
                        s = s + *(a + i);
                        i++;
                  }
                  return s;
            }

            string static prepare_time_logger()
            {
                  // current date/time based on current system
                  time_t now = time(0);

                  // cout << "Number of sec since January 1,1970 is:: " << now << endl;

                  tm *ltm = localtime(&now);

                  // calculate various components of tm structure.
                  string str_year = to_string(1900 + ltm->tm_year);

                  string str_minute = "";
                  (ltm->tm_min < 10) ? (str_minute = "0" + to_string(ltm->tm_min)) : (str_minute = to_string(ltm->tm_min));

                  string str_seconde = "";
                  (ltm->tm_sec < 10) ? (str_seconde = "0" + to_string(ltm->tm_sec)) : (str_seconde = to_string(ltm->tm_sec));

                  string str_hour = "";
                  (ltm->tm_hour < 10) ? (str_hour = "0" + to_string(ltm->tm_hour)) : (str_hour = to_string(ltm->tm_hour));

                  string str_month = "";
                  ((ltm->tm_mon + 1) < 10) ? (str_month = "0" + to_string(ltm->tm_mon + 1)) : (str_month = to_string(ltm->tm_mon + 1));

                  string str_day = "";
                  (ltm->tm_mday < 10) ? (str_day = "0" + to_string(ltm->tm_mday)) : (str_day = to_string(ltm->tm_mday));

                  string date_str = str_year + "/" + str_month + "/" + str_day + "  " + str_hour + ":" + str_minute + ":" + str_seconde;
                  return date_str;
            }

            string static prepare_file_logger_archive(int size_file)
            {
                  // current date/time based on current system
                  time_t now = time(0);

                  // cout << "Number of sec since January 1,1970 is:: " << now << endl;

                  tm *ltm = localtime(&now);

                  // calculate various components of tm structure.
                  string str_year = to_string(1900 + ltm->tm_year);

                  string str_minute = "";
                  (ltm->tm_min < 10) ? (str_minute = "0" + to_string(ltm->tm_min)) : (str_minute = to_string(ltm->tm_min));

                  string str_seconde = "";
                  (ltm->tm_sec < 10) ? (str_seconde = "0" + to_string(ltm->tm_sec)) : (str_seconde = to_string(ltm->tm_sec));

                  string str_hour = "";
                  (ltm->tm_hour < 10) ? (str_hour = "0" + to_string(ltm->tm_hour)) : (str_hour = to_string(ltm->tm_hour));

                  string str_month = "";
                  ((ltm->tm_mon + 1) < 10) ? (str_month = "0" + to_string(ltm->tm_mon + 1)) : (str_month = to_string(ltm->tm_mon + 1));

                  string str_day = "";
                  (ltm->tm_mday < 10) ? (str_day = "0" + to_string(ltm->tm_mday)) : (str_day = to_string(ltm->tm_mday));

                  string date_str = str_year + "_" + str_month + "_" + str_day + "_" + str_hour + "_" + str_minute + "_" + str_seconde + "_" + to_string(size_file);
                  return date_str;
            }

            string static prepare_message_logger(int level_logger, string msg_logger)
            {
                  if (level_logger == INFO)
                        return "\033[0;34m[INFO ]\033[0;0m" + msg_logger;
                  else if (level_logger == ERROR)
                        return "\033[0;31m[ERROR ]\033[0;0m" + msg_logger;
                  else if (level_logger == WARNING)
                        return "\033[0;33m[WARNING ]\033[0;0m" + msg_logger;
                  else if (level_logger == DEBUG)
                        return "\033[0;35m[DEBUG ]\033[0;0m" + msg_logger;
                  else
                        return "\033[0;34m[INFO ]\033[0;0m" + msg_logger;
            }

            string static prepare_message_logger_file(int level_logger, string msg_logger)
            {
                  if (level_logger == INFO)
                        return "[INFO ]" + msg_logger;
                  else if (level_logger == ERROR)
                        return "[ERROR ]" + msg_logger;
                  else if (level_logger == WARNING)
                        return "[WARNING ]" + msg_logger;
                  else if (level_logger == DEBUG)
                        return "[DEBUG ]" + msg_logger;
                  else
                        return "[INFO ]" + msg_logger;
            }

            void static check_file_size(std::string filename, std::string path_file_archive, int limit_size_file_log, string shell_file_mv)
            {
                  try
                  {
                        ifstream in_file(filename, ios::binary);
                        in_file.seekg(0, ios::end);
                        int size_file = in_file.tellg();

                        if (size_file >= limit_size_file_log)
                        {
                              string file_to_archive = path_file_archive + prepare_file_logger_archive(size_file);
                              try
                              {
                                    string command = shell_file_mv + "  " + filename + " " + file_to_archive;
                                    system(command.c_str());
                              }
                              catch (exception &e)
                              {
                                    std::cerr << "Error during move file \"" << filename << "\" to \"" << file_to_archive << "\"" << std::endl;
                                    std::cerr << "Details : " << e.what() << std::endl;
                              }
                        }
                  }
                  catch (exception &ex)
                  {
                        cerr << ex.what() << endl;
                  }
            }

      public:
            Logger() {}
            ~Logger() {}

            void static log(int level_logger, string message_logger)
            {
                  message_logger = " [" + prepare_time_logger() + "] " + message_logger + "\n";
                  cout << prepare_message_logger(level_logger, message_logger);
            }

            void static log(int level_logger, string message_logger, const char *ptr)
            {
                  message_logger = " [" + prepare_time_logger() + "] " + message_logger + " " + constConvertToString(ptr) + "\n";
                  cout << prepare_message_logger(level_logger, message_logger);
            }

            void static log(int level_logger, string message_logger, char *ptr)
            {
                  message_logger = " [" + prepare_time_logger() + "] " + message_logger + " " + convertToString(ptr) + "\n";
                  cout << prepare_message_logger(level_logger, message_logger);
            }

            void static log(int level_logger, char *message_logger)
            {
                  string msg_logger = " [" + prepare_time_logger() + "] " + convertToString(message_logger) + "\n";
                  cout << prepare_message_logger(level_logger, msg_logger);
            }

            void static log(int level_logger, const char *message_logger)
            {
                  string msg_logger = " [" + prepare_time_logger() + "] " + constConvertToString(message_logger) + "\n";
                  cout << prepare_message_logger(level_logger, msg_logger);
            }

            void static log(int level_logger, int msg)
            {
                  string message_logger = " [" + prepare_time_logger() + "] " + to_string(msg) + "\n";
                  cout << prepare_message_logger(level_logger, message_logger);
            }

            void static log(int level_logger, string message_logger, string path_logger_file, std::string path_file_archive, int limit_size_file_log, string shell_file_mv)
            {
                  check_file_size(path_logger_file, path_file_archive, limit_size_file_log, shell_file_mv);
                  message_logger = " [" + prepare_time_logger() + "] " + message_logger + "\n";
                  message_logger = prepare_message_logger_file(level_logger, message_logger);
                  fstream filestr;
                  try
                  {
                        filestr.open(path_logger_file, fstream::in | fstream::out | fstream::app);
                        filestr << message_logger;
                        filestr.close();
                  }
                  catch (exception &ex)
                  {
                        cerr << "Error during open in writing log file : " << path_logger_file << endl;
                        cerr << "Details : " << ex.what() << endl;
                        if (filestr)
                        {
                              filestr.close();
                        }
                  }
                  catch (...)
                  {
                        cerr << "Error during open in writing log file : " << path_logger_file << endl;
                        if (filestr)
                        {
                              filestr.close();
                        }
                  }
            }
      };
}

#endif // LOGGER_H_FILE
