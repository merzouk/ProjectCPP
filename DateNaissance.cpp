#include "DateNaissance.hpp"

namespace Heritage
{

       void DateNaissance::infos()
       {
            cout <<"              Ne le " <<this->get_jour()<<"/"<<this->get_mois()<<"/"<<this->get_annee() << endl;
       }

}
