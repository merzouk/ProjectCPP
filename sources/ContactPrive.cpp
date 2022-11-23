#include "../header/ContactPrive.hpp"
#include <ctime>

namespace Heritage
{
       bool anniversaire(int jour, int mois)
       {
              time_t now = time(0);
              tm *ltm = localtime(&now);
              if(mois == (1 + ltm->tm_mon) && (ltm->tm_mday) == jour) return true;
              return false;
       }

       void ContactPrive::infos()
       {
              cout.fill('0');
              cout << "Particlier:"   << setw(5) << this->get_identifiant() << endl;
              cout <<"              " << this->get_filiation() << ". " << this->get_prenom() << " " << this->get_nom() << endl;
              this->get_adressePostale()->infos();
              cout <<"              " <<  "Situation Familliale : " << this->get_situation_familliale() << endl;
              DateNaissance *date_naiss = this->get_dateNaissance();

              time_t now = time(0);
              tm *ltm = localtime(&now);

              int year = 1900 + ltm->tm_year;
              int annee_naiss = date_naiss->get_annee();
              int age = year - annee_naiss;
              cout << "              "<<"Age : " <<age << " ans";
              (anniversaire(date_naiss->get_jour(), date_naiss->get_mois()) == true) ? cout <<" et Bon Anniversaire !": cout <<"";
              cout << endl;
       }

       string ContactPrive::build_key()
       {
                     string key = Contact::build_key();
                     string n = this->get_situation_familliale();
                     for ( int i = 0; i < int(n.size()); i++)
                     {
                                   if(n[i] != ' ')
                                          key += n[i];
                     }
                     key += ':';
                     return key;
       }

        void ContactPrive::afficher()
        {

        }

}
