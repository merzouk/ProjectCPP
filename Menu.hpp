#ifndef MENU_H_FILE
#define MENU_H_FILE

using namespace std;
#include <string>


namespace Manage
{

       class Menu
       {
             public:
                     Menu(){}
                     ~Menu(){}
                     int check_input_value();
                     void launch_programm_manage_annuaire(string fileContactPrivate, string fileContactPro);

       };
}

#endif // MENU_H_FILE
