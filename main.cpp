#include "Menu.hpp"
#include <string>


using namespace std;
using namespace Manage;

int main(int argc, char ** argv)
{
       string fileContactPrivate;
       string fileContactPro;
/*
       if(argc == 3)
       {
             fileContactPrivate = argv[1];
             fileContactPro = argv[2];
       }
       else
       {
       */
              fileContactPro = "pros.dat";
              fileContactPrivate = "privates.dat";
       //}
       Menu * menu = new Menu();
       menu->launch_programm_manage_annuaire(fileContactPrivate, fileContactPro);


       delete menu;
       menu = nullptr;
       return 0;
}
