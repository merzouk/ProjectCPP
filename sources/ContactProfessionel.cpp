
#include "../header/ContactProfessionel.hpp"



namespace Heritage
{

       void ContactProfessionel::infos()
       {
           cout.fill('0');
           cout << "Professionel : "<< setw(5) << this->get_identifiant() << endl;
           cout <<"              Societe " <<this->get_entreprise() <<endl;
           cout <<"              Contact : " << this->get_filiation() <<" "<<this->get_nom() <<"  "<<this->get_prenom() <<endl;
           this->get_adressePostale()->infos();
           cout << endl << endl;
           cout <<"              Mail : " << this->get_email() << endl;
       }

       string ContactProfessionel::build_key()
       {
                     string key = Contact::build_key();
                     string n = this->get_email();
                     for ( int i = 0; i < int(n.size()); i++)
                     {
                                   if(n[i] != ' ')
                                          key += n[i];
                     }
                     key += ':';
                     return key;
       }

       void ContactProfessionel::afficher()
       {

       }
}
