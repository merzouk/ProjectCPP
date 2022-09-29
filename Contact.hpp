#ifndef CONTACT_H_FILE
#define CONTACT_H_FILE
#include <string.h>
#include "ContactException.hpp"
#include "AdressePostale.hpp"

using namespace std;

#include <iomanip>
#include <ctime>
#include <vector>

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

              int str_length(char *s)
              {
                            if(!s) return 0;
                            int len = 0;
                            while(*(s+len) != '\0') len++;
                            return len;
              }

              char * to_upper_last_name(char *s)
              {
                            int i = 0;
                            while(*(s + i) != '\0')
                            {
                                    s[i] = toupper(s[i]);
                                   i++;
                            }
                            return s;
              }

              char * to_upper_first_name(char *s)
              {
                            if(!s) return s;
                            s[0] = toupper(s[0]);
                            return s;
              }


       public:
              Contact(int identifiant , char *nom, char *prenom, string sexe, string situation, AdressePostale *adressePostale)
              {
                     int len = str_length(nom);
                     if(len == 0 || len > 30)
                           throw ContactException("\nLa longeueur du chmaps nom n'est pas correcte");
                     len = str_length(prenom);
                     if(len == 0 || len > 30)
                           throw ContactException("\nLa longeueur du chmaps prenom n'est pas correcte");
                     this->nom = to_upper_last_name(nom);
                     this->prenom = to_upper_first_name(prenom);
                     this->identifiant = identifiant;
                     this->s = s;
                     this->f = f;
                     this->adressePostale = adressePostale;
              }

              ~Contact(){}
               AdressePostale *get_adressePostale(){return this->adressePostale;};
              int get_identifiant(){return this->identifiant;}
              char * get_nom(){return this->nom;}
              char * get_prenom(){return this->prenom;}
              char get_sexe(){
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
              string get_situation_familliale(){
                     string situ_famille;
                     //enum situation {Marie = 0, Celibataire = 1, Veuf = 2, Pacse = 3};
                     switch (this->f)
                     {
                     case 0:
                           if(this->get_sexe() == 'M')
                                situ_famille = "Marie";
                            else
                                situ_famille = "Marie";
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
                                situ_famille = "Pacse";
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
              void set_sexe(string sex){

                     if(sex == "M")
                        this->s = M;
                     else
                         this->s = F;
              }
              //enum situation {Marie = 0, Celibataire = 1, Veuf = 2, Pacse = 3};
              void set_situation(string situa ){
                     if(situa == "Marie")
                            this->f =  Marie;
                     if(situa == "Celibataire")
                            this->f = Celibataire;
                     if(situa == "Veuf" || situa == "Veuve")
                            this->f = Veuf;
                     if(situa == "Pacse")
                            this->f = Pacse;
              }


              virtual string build_key() = 0;
              virtual void infos() = 0;
              virtual void afficher() = 0;

       };
}
#endif // CONTACT_H_FILE
