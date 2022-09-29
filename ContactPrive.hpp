#ifndef CONTACT_PRIVE_H_FILE
#define CONTACT_PRIVE_H_FILE

#include "Contact.hpp"
#include "AdressePostale.hpp"
#include "DateNaissance.hpp"

namespace Heritage
{
       class ContactPrive: public Contact
       {
       private:

              DateNaissance *dateNaissance;

       public:
            ContactPrive(DateNaissance *dateNaissance, int identifiant , char *nom, char *prenom, string sexe, string situation, AdressePostale *adressePostale)
            : Contact(identifiant , nom, prenom, sexe, situation, adressePostale), dateNaissance(dateNaissance)
            {
            }

            ~ContactPrive()
            {
                     delete dateNaissance;
                     dateNaissance = nullptr;
            }

              DateNaissance * get_dateNaissance(){return this->dateNaissance;}
              string build_key() override;


            void infos() override;
            void afficher() override;
       };
}
#endif // CONTACT_PRIVE_H_FILE
