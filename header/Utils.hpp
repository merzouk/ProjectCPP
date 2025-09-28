#ifndef UTILS_H_FILE
#define UTILS_H_FILE

//#include <iostream>
//#include <stdlib.h>
#include <string>
#include "Logger.hpp"

using namespace std;

namespace Manage
{

      class Utils
      {
      public:
            Utils() {}
            ~Utils() {}
            char *to_char(std::string s, char *ptr);
            int str_to_int(std::string s);
            int validate_sexe(string s);
            int validate_statut(string s);
            bool validate_first_last_name(string s);
            bool validate_entreprise(string s);
            int validate_entreprise_name(string s);
            bool check_email(string email);
            char *to_upper_last_name(char *s);
            char *str_to_char(string s, char *ptr);
            int str_length(char *s);
            char *to_upper_first_name(char *s);
      };
}

#endif // UTILS_H_FILE
