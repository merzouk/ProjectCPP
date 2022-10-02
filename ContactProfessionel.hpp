
#ifndef CONTACT_PRO_H_FILE
#define CONTACT_PRO_H_FILE
#include<regex>

#include "Contact.hpp"
#include "AdressePostale.hpp"

namespace Heritage
{
       enum statut {SARL = 0, SA = 1, SAS = 2, EURL = 3};

       class ContactProfessionel: public Contact
       {
              private:
                     char *entreprise;
                     statut st;
                     string email;
                     int str_length(char *s)
                     {
                                   if(!s) return 0;
                                   int len = 0;
                                   while(*(s+len) != '\0') len++;
                                   return len;
                     }

                     bool check_email(string email)
                     {
                         const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
                         return regex_match(email,pattern);
                     }

              public:
                     ContactProfessionel(char * entreprise, string statut,  string email, int identifiant , char *nom, char *prenom, string sexe, string situation, AdressePostale *adressePostale)
                       :Contact(identifiant , nom, prenom, sexe, situation, adressePostale)
                       {
                            int len = str_length(entreprise);
                            if(len == 0 || len > 50)
                                   throw ContactException("\nLe champs nom entreprise n'est pas correct");

                            if(!check_email(email))
                                   throw ContactException("\nLe champs addresse mail n'est pas correct");
                            this->entreprise = entreprise;
                            set_statut(statut);
                            this->email = email;
                     }
                     ~ContactProfessionel()
                     {
                            free(this->entreprise);
                     }
                     char * get_entreprise(){return this->entreprise;}
                     string get_statut()
                     {
                            string stt;
                            switch(this->st)
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
                     string get_email(){return this->email;}

                     void set_entreprise(char * entreprise)
                     {
                             int len = str_length(entreprise);
                            if(len == 0 || len > 50)
                                   throw ContactException("\nLe champs nom entreprise n'est pas correct");
                            this->entreprise = entreprise;
                     }
                     void set_statut(string statut){

                                   if(statut == "SARL")
                                          st = SARL;
                                   if(statut == "SA")
                                       st = SA;
                                   if(statut == "SAS")
                                        st = SAS;
                                   if(statut =="EURL")
                                        st = EURL;

                     }
                     void set_email(string email)
                     {
                             if(!check_email(email))
                                   throw ContactException("\nLe champs addresse mail n'est pas correct");
                            this->email = email;
                     }
                     void infos() override;

                     string build_key() override;

                     void afficher() override;

       };
}
#endif // CONTACT_PRO_H_FILE
