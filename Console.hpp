#ifndef CONSOLE_H_FILE
#define CONSOLE_H_FILE
#include "Annuaire.hpp"
#include "AdressePostale.hpp"
#include <vector>
#include <string>
#include "ContactPrive.hpp"
#include "ContactPrive.hpp"

namespace Manage
{

       class Console
       {

              private:
                     Annuaire * annuaire;
                     string get_str_value();
                      Utils * utils;

              public:
                     Console()
                     {
                            this->annuaire = new Annuaire();
                            this->utils = new Utils();
                     }
                     ~Console()
                     {
                            delete this->annuaire;
                            this->annuaire = nullptr;
                            delete this->utils;
                            this->utils = nullptr;
                     }
                     Annuaire *get_annuaire()
                     {
                            return this->annuaire;
                     }
                     void afficher_annuaire();
                     void ajouter_contact_prive();
                     void ajouter_contact_professionnel();
                     void rechercher_contact_pid();
                     void rechercher_contact_nom();
                     void rechercher_contact_code_postale();
                     void rechercher_contact_departement();
                     void rechercher_contact_ville();
                     void supprimer_contact_pid();
                     void modifier_contact_pid();
                     void load_datas(string fileContactPrivate, string fileContactPro);
                     AdressePostale *new_adress();
                     int get_next_pid();
                     bool check_email(string email);
       };

}

#endif // CONSOLE_H_FILE
