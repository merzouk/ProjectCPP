#ifndef MENU_H_FILE
#define MENU_H_FILE

using namespace std;
#include <string>

namespace Manage
{

       class Menu
       {
       public:
              Menu() {}
              ~Menu() {}
              void printMenu();
              int check_input_value(int limit_inf, int limit_max);
              void launch_programm_manage_annuaire(string fileContactPrivate, string fileContactPro);
       };
}

#endif // MENU_H_FILE
