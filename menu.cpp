#include "Menu.hpp"

#include "Console.hpp"

#include <iostream>

using namespace std;

namespace Manage
{

       int Menu::check_input_value()
       {
           int opc;
           bool aux = true;
           cin.exceptions(std::istream::failbit);
           do {
                     try
                     {
                            cout << "Veuillez saisir un entier compris entre 0 et 11 :" << endl;
                            cin >> opc;
                            aux = true;
                     }
                     catch (std::ios_base::failure &fail)
                     {
                            aux = false;
                            cout << "Veuillez saisir une option valide." << endl;
                            cin.clear();
                            std::string tmp;
                            getline(cin, tmp);
                     }
           } while (aux == false || (0 < opc && opc > 11));
           return opc;
       }

       void Menu::launch_programm_manage_annuaire(string fileContactPrivate, string fileContactPro)
       {

               Console * console = new Console();
               console->load_datas(fileContactPrivate, fileContactPro);

               int menu = -1;

               do
               {
                  menu = -1;
                         cout<<  endl << " ----------------------- MENU -----------------------" <<endl <<endl;
                         cout<<"1.  Voir le contenu de l'annuaire "                              <<endl;
                         cout<<"2.  Ajouter un Contact prive a l'annuaire"                       <<endl;
                         cout<<"3.  Ajouter un Contact professionnel a l'annuaire"               <<endl;
                         cout<<"4.  Rechercher un Contact par son numero unique"                 <<endl;
                         cout<<"5.  Rechercher un Contact par son nom"                           <<endl;
                         cout<<"6.  Rechercher un Contact par son code postale"                  <<endl;
                         cout<<"7.  Rechercher un contact par son Departement"                   <<endl;
                         cout<<"8.  Rechercher un contact par sa ville"                          <<endl;
                         cout<<"9.  Rechercher un contact par son email"                         <<endl;
                         cout<<"10. Supprimer un contact par son identifiant"                    <<endl;
                         cout<<"11. Modifier un contact par son identifiant"                     <<endl;
                         cout<<"0.  Quitter"                                                     <<endl;
                         cout<<endl <<"Votre choix : "                                           <<endl;

                         menu = check_input_value();
                         cout<<endl;

                         switch(menu)
                            {
                            case 0 :
                                break;
                            case 1 :
                                   console->afficher_annuaire();
                                break;
                            case 2 :
                                   console->ajouter_contact_prive();
                                break;
                            case 3 :
                                    console->ajouter_contact_professionnel();
                                break;
                            case 4 :
                                   console->rechercher_contact_pid();
                                break;
                            case 5 :
                                    console->rechercher_contact_nom();
                                break;
                            case 6 :
                                    console->rechercher_contact_code_postale();
                                break;
                            case 7 :
                                   console->rechercher_contact_departement();
                                break;
                            case 8 :
                                   console->rechercher_contact_ville();
                                break;
                            case 9 :
                                   console->rechercher_contact_email();
                                break;
                            case 10 :
                                   console->supprimer_contact_pid();
                                break;
                            case 11 :
                                    console->modifier_contact_pid();
                                break;
                            }
              }
              while (menu != 0);
              delete console;
              console = nullptr;
       }

}
