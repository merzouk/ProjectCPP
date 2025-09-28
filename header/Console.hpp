#ifndef CONSOLE_H_FILE
#define CONSOLE_H_FILE
#include "Annuaire.hpp"
#include "AdressePostale.hpp"
//#include "ContactPrive.hpp"
//#include "ContactPrive.hpp"
#include "Display.hpp"
//#include "Contact.hpp"
//#include <map>

#include <string>

using namespace std;

typedef struct
{
       int year;
       int month;
       int day;
} dat_naiss;

namespace Manage
{
       class Console
       {

       private:
              Annuaire *annuaire;
              string get_str_value(string key);
              Utils *utils;
              Display *display;

       public:
              Console()
              {
                     this->annuaire = new Annuaire();
                     this->utils = new Utils();
                     this->display = new Display();
              }
              ~Console()
              {
                     delete this->annuaire;
                     this->annuaire = nullptr;
                     delete this->utils;
                     this->utils = nullptr;
                     delete this->display;
                     this->display = nullptr;
              }
              Annuaire *get_annuaire()
              {
                     return this->annuaire;
              }
              void afficher_annuaire();
              void afficher_annuaire_prive();
              void afficher_annuaire_pros();
              void ajouter_contact_prive();
              void ajouter_contact_professionnel();
              void rechercher_contact_pid();
              void rechercher_contact_nom();
              void rechercher_contact_prenom();
              void rechercher_contact_email();
              void rechercher_contact_code_postale();
              void rechercher_contact_departement();
              void rechercher_contact_ville();
              void supprimer_contact_pid();
              void modifier_contact_pid();
              dat_naiss saisir_date_naissance();
              void load_datas(string fileContactPrivate, string fileContactPro);
              AdressePostale *new_address();
              int get_next_pid();
              bool check_email(string email);
       };

}

#endif // CONSOLE_H_FILE
