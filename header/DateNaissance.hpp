#ifndef DAT_NAISS_H_FILE
#define DAT_NAISS_H_FILE

#include "ContactException.hpp"

using namespace Errors;

namespace Heritage
{
       class DateNaissance
       {
       private:
              int jour;
              int mois;
              int annee;
       public:
              DateNaissance(int jour, int mois, int annee)
              {
                     if(jour < 1 || jour > 31)
                            throw ContactException("\nLa valeur du champs jour de naissance n'est pas correcte");
                      if(mois < 1 || mois > 12)
                            throw ContactException("\nLa valeur du champs mois de naissance n'est pas correcte");
                      if(annee < 0 )
                            throw ContactException("\nLa valeur du champs annee de naissance n'est pas correcte");
                     this->jour = jour;
                     this->mois = mois;
                     this->annee = annee;

              }
              int get_jour(){return this->jour;}
              int get_mois(){return this->mois;}
              int get_annee(){return this->annee;}

              void set_jour(int jour)
              {
                     if(jour < 1 || jour > 31)
                            throw ContactException("\nLa valeur du champs jour de naissance n'est pas correcte");
                     this->jour = jour;
              }
              void set_mois(int mois)
              {
                     if(mois < 1 || mois > 12)
                            throw ContactException("\nLa valeur du champs mois de naissance n'est pas correcte");
                     this->mois = mois;
              }
              void set_annee(int annee)
              {
                     if(annee < 0 )
                            throw ContactException("\nLa valeur du champs annee de naissance n'est pas correcte");
                     this->annee = annee;
              }

              void infos();

       };
}

#endif // DAT_NAISS_H_FILE
