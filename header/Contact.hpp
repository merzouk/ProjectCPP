#ifndef CONTACT_H_FILE
#define CONTACT_H_FILE
#include <string.h>
#include "ContactException.hpp"
#include "AdressePostale.hpp"
#include <iomanip>
#include <ctime>
#include <vector>
#include "Utils.hpp"

using namespace std;

using namespace Manage;

using namespace Errors;

namespace Heritage
{
       enum sexe { M , F };
       enum situation {Marie, Celibataire, Veuf, Pacse, Autres};
       class Contact
       {
       private:
              int identifiant;
              char *nom;
              char *prenom;
              sexe s;
              situation f;
              AdressePostale *adressePostale;
              Utils * utils;

       public:
              Contact(int identifiant , char *nom, char *prenom, string sexe, string situation, AdressePostale *adressePostale)
              {
                     int len = utils->str_length(nom);
                     if(len == 0 || len > 30)
                           throw ContactException("\nLa longueur du champs nom n'est pas correcte");
                     len = utils->str_length(prenom);
                     if(len == 0 || len > 30)
                           throw ContactException("\nLa longueur du champs prenom n'est pas correcte");
                     this->nom = utils->to_upper_last_name(nom);
                     this->prenom = utils->to_upper_first_name(prenom);
                     this->identifiant = identifiant;
                     this->s = s;
                     this->f = f;
                     this->set_sexe(sexe);
                     this->adressePostale = adressePostale;
                     this->utils = new Utils();
              }
              ~Contact()
              {
                    free(this->nom);
                    free(this->prenom);
                    delete this->adressePostale;
                    this->adressePostale = nullptr;
                    delete this->utils;
                    this->utils = nullptr;
              }
              AdressePostale *get_adressePostale(){return this->adressePostale;};
              int get_identifiant(){return this->identifiant;}
              char * get_nom(){return this->nom;}
              char * get_prenom(){return this->prenom;}
              char get_sexe()
              {
                     char se;
                     switch (this->s)
                     {
                     case 0:
                            se = 'M';
                            break;
                     case 1:
                            se = 'F';
                            break;
                     }
                     return se;
              }
              string get_filiation()
              {
                     string se;
                     switch (this->s)
                     {
                     case 0:
                            se = "Mr";
                            break;
                     case 1:
                            se = "Mme";
                            break;
                     }
                     return se;

              }
              string get_situation_familliale()
              {
                     string situ_famille;
                     switch (this->f)
                     {
                     case 0:
                           if(this->get_sexe() == 'M')
                                situ_famille = "Marie";
                            else
                                situ_famille = "Mariee";
                            break;
                     case 1:
                            situ_famille = "Celibataire";
                            break;
                     case 2:
                            if(this->get_sexe() == 'M')
                                situ_famille = "Veuf";
                            else
                                situ_famille = "Veuve";
                            break;
                      case 3:
                            if(this->get_sexe() == 'M')
                                situ_famille = "Pacse";
                            else
                                situ_famille = "Pacsee";
                            break;
                      case 4:
                            situ_famille = "Autres";
                     }
                     return situ_famille;
               }

              void set_adressePostale(AdressePostale *adressePostale){this->adressePostale = adressePostale;}
              void set_identifiant(int identifiant){this->identifiant = identifiant;}
              void set_nom(char * nom);
              void set_prenom(char *prenom);

              void set_sexe(string sex)
              {
                     int x = sex.compare("M");
                     if(x == 0)
                        this->s = M;
                     else
                         this->s = F;
              }
              void set_situation(string situa)
              {
                     if(situa == "Marie" || situa == "Mariee")
                            this->f =  Marie;
                     if(situa == "Celibataire")
                            this->f = Celibataire;
                     if(situa == "Veuf" || situa == "Veuve")
                            this->f = Veuf;
                     if(situa == "Pacse" || situa == "Pacsee")
                            this->f = Pacse;
                     if(situa == "Autres")
                            this->f = Autres;
              }

              virtual string build_key() = 0;
              virtual void infos() = 0;
              virtual void afficher() = 0;
       };
}
#endif // CONTACT_H_FILE
