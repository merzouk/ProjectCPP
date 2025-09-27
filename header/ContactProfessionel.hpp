
#ifndef CONTACT_PRO_H_FILE
#define CONTACT_PRO_H_FILE
#include <regex>

#include "Contact.hpp"
#include "AdressePostale.hpp"
#include "Utils.hpp"
#include "Status.hpp"

using namespace Manage;

namespace Heritage
{
       class ContactProfessionel : public Contact
       {
       private:
              char *entreprise;
              STATUS status;
              string email;
              Utils *utils;

       public:
              ContactProfessionel(char *entreprise, string statut, string email, int identifiant, char *nom, char *prenom, string sexe, string situation, AdressePostale *adressePostale)
                  : Contact(identifiant, nom, prenom, sexe, situation, adressePostale)
              {
                     this->utils = new Utils();
                     this->set_entreprise(entreprise);
                     set_statut(statut);
                     set_email(email);
              }
              ~ContactProfessionel()
              {
                     free(this->entreprise);
                     delete this->utils;
                     this->utils = nullptr;
              }
              char *get_entreprise() { return this->entreprise; }
              string get_statut()
              {
                     string stt;
                     switch (this->status)
                     {
                     case 0:
                            stt = "SARL";
                            break;
                     case 1:
                            stt = "SA";
                            break;
                     case 2:
                            stt = "SAS";
                            break;
                     case 3:
                            stt = "EURL";
                            break;
                     }
                     return stt;
              }
              string get_email() { return this->email; }

              void set_entreprise(char *entreprise)
              {
                     int len = this->utils->str_length(entreprise);
                     string s = entreprise;
                     if (len == 0 || len > 50)
                            throw ContactException("\nLe champs nom entreprise n'est pas correct : "+s);
                     this->entreprise = entreprise;
              }
              void set_statut(string statut)
              {
                     if (statut == "SARL")
                            this->status = SARL;
                     if (statut == "SA")
                            this->status = SA;
                     if (statut == "SAS")
                            this->status = SAS;
                     if (statut == "EURL")
                            this->status = EURL;
              }
              void set_email(string email)
              {
                     if (!this->utils->check_email(email))
                            throw ContactException("\nLe champs adresse mail n'est pas correct : "+email);
                     this->email = email;
              }
              void infos() override;

              string build_key() override;

              void afficher() override;
       };
}
#endif // CONTACT_PRO_H_FILE
