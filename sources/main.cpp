#include "../header/Menu.hpp"

using namespace Manage;

int main(int argc, char **argv)
{
       string fileContactPrivate;
       string fileContactPro;

       if (argc == 3)
       {
              fileContactPrivate = argv[1];
              fileContactPro = argv[2];
       }
       else
       {
              fileContactPro = "datas/pros.dat";
              fileContactPrivate = "datas/privates.dat";
       }
       Menu *menu = new Menu();
       menu->launch_programm_manage_annuaire(fileContactPrivate, fileContactPro);

       delete menu;
       menu = nullptr;
       return 0;
}
