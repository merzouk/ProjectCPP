#include "../header/AdressePostale.hpp"

namespace Heritage
{
       void AdressePostale::infos()
       {
              cout <<"              "<< this->get_numero() << ", " << get_rue() << endl;
              cout <<"              "<< this->get_complement() << endl;
              cout <<"              "<< this->get_code_postale() << "  " << this->get_ville() << endl;
       }
}
