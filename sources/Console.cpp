#include "../header/Console.hpp"
#include "../header/ContactException.hpp"
#include "../header/AdressePostale.hpp"
#include "../header/ContactPrive.hpp"
#include "../header/ContactProfessionel.hpp"


#include <regex>
#include <exception>

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstring>
#include <bits/stdc++.h>

using namespace Errors;

using namespace std;

namespace Manage {


       int check_input_value(int limit_inf, int limit_max)
       {
              int opc;
              bool aux = true;
              cin.exceptions(std::istream::failbit);
              do {
                     try {
                            cout << "Veuillez saisir un entier positif compris entre "
                                 << limit_inf
                                 << " et "
                                 << limit_max
                                 << endl;
                            cin >> opc;
                            aux = true;
                     } catch (std::ios_base::failure &fail) {
                            aux = false;
                            cout << "Veuillez saisir un entier valide." << endl;
                            cin.clear();
                            std::string tmp;
                            getline(cin, tmp);
                     }
              } while (aux == false || (opc < limit_inf || opc > limit_max));
              return opc;
       }

       int check_input_value()
       {
              int opc;
              bool aux = true;
              cin.exceptions(std::istream::failbit);
              do {
                     try {
                            cout << "Veuillez saisir un entier positif :" << endl;
                            cin >> opc;
                            aux = true;
                     } catch (std::ios_base::failure &fail) {
                            aux = false;
                            cout << "Veuillez saisir un entier valide." << endl;
                            cin.clear();
                            std::string tmp;
                            getline(cin, tmp);
                     }
              } while (aux == false || (opc < 0));
              return opc;
       }

       string Console::get_str_value(string key)
       {
              string str;
              try
              {
                     cin.ignore();
                     getline(cin, str);
              }
              catch(exception & ex)
              {
                      Logger::log(2, "Erreur lors de la saisie de la valeur de " +key );
                     str = "";
              }
              return str;
       }

       void Console::load_datas(string fileContactPrivate, string fileContactPro)
       {
              this->annuaire->load_annuaire_from_files(fileContactPrivate,
                            fileContactPro);
       }

       void Console::rechercher_contact_nom()
       {
              cout << "Veuillez saisir le nom du contact : " << endl;
              string nom = get_str_value("Nom");
              char *ptr = NULL;
              ptr = utils->str_to_char(nom, ptr);
              vector<Contact*> vects = this->annuaire->get_list_elts_by_last_name(
                            utils->to_upper_last_name(ptr));
              if(vects.size() == 0)
                      Logger::log(1, "Aucun contact trouve pour le nom : " + nom );
              else if(vects.size() == 1)
                     vects[0]->infos();
              else
                     this->display->display(vects);
              free(ptr);
       }

       void Console::rechercher_contact_prenom()
       {
              cout << "Veuillez saisir le prenom du contact : " << endl;
              string prenom = get_str_value("Prenom");
              char *ptr = NULL;
              vector<Contact*> vects = this->annuaire->get_list_elts_by_first_name(
                            utils->to_upper_first_name(utils->str_to_char(prenom, ptr)));
              if(vects.size() == 0)
                     Logger::log(1, "Aucun contact trouve pour le prenom : " + prenom);
              else if(vects.size() == 1)
                     vects[0]->infos();
              else
                     this->display->display(vects);
              free(ptr);
       }

       void Console::afficher_annuaire()
       {
              map<string, Contact*> map_annuaire = this->annuaire->get_map_annuaire();
              this->display->display(map_annuaire);
       }

       void Console::rechercher_contact_pid()
       {

              cout << "Veuillez saisir l'identifiant du contact" << endl;
              int pid = check_input_value();
              Contact *contact = this->annuaire->get_elt_by_id(pid);
              ContactPrive *contact_prive = dynamic_cast<ContactPrive*>(contact);
              if (contact_prive) {
                       contact_prive->infos();
              } else {
                     ContactProfessionel *contact_prof =
                                   dynamic_cast<ContactProfessionel*>(contact);
                     if(contact_prof)
                         contact_prof->infos();
                      Logger::log(1, "Aucun contact trouve pour l'identifiant : " +to_string(pid));
              }
       }

       void Console::rechercher_contact_code_postale()
       {
              cout << "Veuillez saisir le code postale du contact"
                   << endl;
              int zip_code = check_input_value();
              vector<Contact*> contacts = this->annuaire->get_list_elts_by_zip_code(
                            zip_code);
              if(contacts.size() == 0)
                      Logger::log(1,"Aucun contact trouve pour le code postale : " + zip_code);
              else if(contacts.size() == 1)
                     contacts[0]->infos();
              else
                     this->display->display(contacts);
       }

       void Console::rechercher_contact_departement()
       {
              cout << "Veuillez saisir le code du departement du contact" << endl;
              int departement = check_input_value();
              vector<Contact*> contacts = this->annuaire->get_list_elts_by_department(
                            departement);
               if(contacts.size() == 0)
                      Logger::log(1, "Aucun contact trouve pour le departement : " +departement);
              else if(contacts.size() == 1)
                     contacts[0]->infos();
              else
                     this->display->display(contacts);
       }

       void Console::rechercher_contact_ville()
       {
              cout << "Veuillez saisir le nom de la ville du contact" << endl;
              string ville = get_str_value("Ville");
              vector<Contact*> contacts = this->annuaire->get_list_elts_by_town(ville);
              if(contacts.size() == 0)
                      Logger::log(1, "Aucun contact trouve pour la ville : " + ville);
              else if(contacts.size() == 1)
                     contacts[0]->infos();
              else
                     this->display->display(contacts);
       }

       void Console::rechercher_contact_email()
       {
             string email;
             do
             {
                     cout << "Veuillez saisir une adresse mail de contact valide : " << endl;
                     cin.clear();
                     getline(cin, email);
              } while (!utils->check_email(email));
              Contact* contact = this->annuaire->get_elt_by_email(email);
              if(contact)
                     contact->infos();
              else
                      Logger::log(1, "Aucun contact trouve dans l'annuaire pour l'adresse mail : " + email);
       }

       void Console::supprimer_contact_pid()
       {
              cout << "Veuillez saisir l'identifiant du contact" << endl;
              int pid = check_input_value();
              try
              {
                     this->annuaire->delete_elt_by_id(pid);
                      Logger::log(1,  "La suppression du contact id : " + to_string(pid) + " s'est correctement terminee");
              }
              catch (const ContactException &ex)
              {
                      Logger::log(2,  "Suppression en echec : " );
                      Logger::log(2, ex.what());
              }
              catch (...)
              {
                     Logger::log(2, "Erreur inattendue pendant la tentative de suppression du contact par son id "+
                          to_string(pid));
              }

       }

       void Console::modifier_contact_pid()
       {
              cout << "Seule l'adresse postale sera modifiee " << endl;
              cout << "Veuillez saisir l'identifiant du contact " << endl;
              int pid = check_input_value();
              Contact *contact = this->annuaire->get_elt_by_id(pid);
              if(contact)
              {
                     ContactPrive *contact_prive = dynamic_cast<ContactPrive*>(contact);
                     if (contact_prive)
                     {
                            this->display->print_contact_prive(contact_prive);

                     }
                     else
                     {
                            ContactProfessionel *contact_prof =
                                          dynamic_cast<ContactProfessionel*>(contact);
                            this->display->print_contact_professionnel(contact_prof);
                     }
                     try
                     {
                            AdressePostale *adr = new_address();
                            contact->set_adressePostale(adr);
                            Logger::log(1, "L'adresse postale du contact est modifiee avec succes");
                     }
                     catch (...)
                     {
                           Logger::log(2, "Erreur inattendue s'est produite pendant la tentative de modification de l'adresse postale");
                     }
              }
              else
              {
                  Logger::log(1,"Aucun contact trouve dans l'annuaire pour l'identifiant : " +to_string(pid));
              }

       }

       AdressePostale* Console::new_address()
       {
              int numero;
              string rue;
              string complement;
              int code_postale;
              string ville;
              try{
                     cout << "Veuillez saisir le numero de la rue : " << endl;
                     numero = check_input_value();
                     cout << "Veuillez saisir le nom de la rue : " << endl;
                     cin.ignore();
                     getline(cin, rue);
                     cout << "Veuillez saisir le complement d'addresse, sinon un espace et validez: " << endl;
                     cin.ignore();
                     getline(cin, complement);
                     cout << "Veuillez saisir le code postale : " << endl;
                     code_postale = check_input_value();
                     cout << "Veuillez saisir le nom de la ville : " << endl;
                     cin.ignore();
                     getline(cin, ville);
                     AdressePostale *adr = new AdressePostale(numero, rue, complement,
                                   code_postale, ville);
                     return adr;
              }
              catch(const std::ios_base::failure& ex)
              {
                       Logger::log(2, "Erreur inattendue durant la tentative de modification de l'addresse postale ");
                       Logger::log(2, ex.what());
              }
              catch (const exception& ex)
              {
                  Logger::log(2, "Erreur inattendue durant la tentative de modification de l'addresse postale ");
                  Logger::log(2, ex.what());
              }
              catch(...)
              {
                      Logger::log(2, "Erreur inattendue durant la tentative de modification de l'addresse postale");
              }
              return nullptr;
       }

       void Console::ajouter_contact_prive()
       {
              string nom;
              string prenom;
              string sexe;
              string situation;
              int mois;
              int jour;
              int annee;
              try
              {
                     do{
                            cout << "Veuillez saisir le nom du contact : " << endl;
                            cin.clear();
                            getline(cin, nom);
                     }while(utils->validate_first_last_name(nom) == false);
                     do{
                            cout << "Veuillez saisir le prenom du contact : " << endl;
                            cin.clear();
                            getline(cin, prenom);
                     }while(utils->validate_first_last_name(nom) == false);
                     do{
                            cout << "Veuillez saisir le sexe (M/F): ";
                            cin.clear();
                            getline(cin, sexe);
                     }while(utils->validate_sexe(sexe) == 1);
                     do{
                            cout << "Veuillez saisir la situation Familliale (Marie, Celibataire, Veuf, Pasce ou Autres) : "
                                 << endl;
                            cin.clear();
                            getline(cin, situation);
                     }while(utils->validate_statut(situation) == 1);
                     cout << "Veuillez saisir l'annee de naissance : " << endl;
                     annee = check_input_value();
                     cout << "Veuillez saisir le mois de naissance : " << endl;
                     mois = check_input_value(1, 12);
                     cout << "Veuillez saisir le jour de naissance : " << endl;
                     jour = check_input_value(1, 31);

                     DateNaissance *dateNaissance = new DateNaissance(jour, mois, annee);
                     AdressePostale *adressePostale = new_address();
                     if(!adressePostale)
                     {
                            Logger::log(2, "Erreur inattendue pendant la tentative d'ajout du contact prive");
                            return;
                     }
                     char *n = NULL;
                     n = utils->str_to_char(nom, n);
                     char *p = NULL;
                     p = utils->str_to_char(prenom, p);
                     int identifiant = get_next_pid();
                     ContactPrive *contactprive = new ContactPrive(dateNaissance, identifiant, n,
                                   p, sexe, situation, adressePostale);
                     this->annuaire->add_new_elt(contactprive);
                     Logger::log(1, "Le nouveau contact prive est ajoute a l'annuaire avec succes");
              }
              catch( std::ios_base::failure& ex)
              {
                      Logger::log(2, "Erreur inattendue durant la tentative d'ajout a l'annuaire du nouveau contact prive ") ;
                      Logger::log(2, ex.what());
              }
              catch ( exception& ex)
              {
                     Logger::log(2, "Erreur inattendue durant la tentative d'ajout a l'annuaire du nouveau contact prive ") ;
                     Logger::log(2, ex.what());
              }
              catch(...)
              {
                     Logger::log(2, "Erreur inattendue durant la tentative d'ajout a l'annuaire du nouveau contact prive");
              }
       }

       void Console::ajouter_contact_professionnel()
       {
              string nom;
              string prenom;
              string sexe;
              string situation;
              string entreprise;
              string statut;
              string email;
              try
              {
                     do{
                            cout << "Veuillez saisir le nom du contact : " << endl;
                            cin.clear();
                            getline(cin, nom);
                     }while(utils->validate_first_last_name(nom) == false);
                     do{
                            cout << "Veuillez saisir le prenom du contact : " << endl;
                            cin.clear();
                            getline(cin, prenom);
                     }while(utils->validate_first_last_name(nom) == false);
                     do{
                            cout << "Veuillez saisir une valeur valide du sexe (M/F): ";
                            cin.clear();
                            getline(cin, sexe);
                    }while(utils->validate_sexe(sexe) == 1);
                    do{
                            cout << "Veuillez saisir la situation Familliale (Marie, Celibataire, Veuf, Pasce ou Autres) : "
                                 << endl;
                            cin.clear();
                            getline(cin, situation);
                    }while(utils->validate_statut(situation) == 1);
                    do{
                            cout << "Veuillez saisir le nom d'entreprise valide : " << endl;
                            cin.ignore();
                            getline(cin, entreprise);
                    }while(utils->validate_entreprise(entreprise) == false);

                     do{
                            cout << "Veuillez saisir le statut juridique valide de l'entreprise (SARL/SA/SAS/EURL) : "
                                 << endl;
                            cin.clear();
                            getline(cin, statut);
                     }while(utils->validate_entreprise_name(statut) == 1);
                     do {
                            cout << "Veuillez saisir une adresse mail de contact valide : "
                                 << endl;
                            cin.clear();
                            getline(cin, email);
                     } while (!utils->check_email(email));

                     AdressePostale *adressePostale = new_address();
                     if(!adressePostale)
                     {
                            Logger::log(2,"Erreur inattendue pendant la tentative d'ajout du contact professionnel");
                            return;
                     }
                     char *n = NULL;
                     n = utils->str_to_char(nom, n);
                     char *entr = NULL;
                     entr = utils->str_to_char(nom, entr);
                     char *p = NULL;
                     p = utils->str_to_char(prenom, p);
                     int identifiant = get_next_pid();
                     ContactProfessionel *contactpros = new ContactProfessionel(entr, statut,
                                   email, identifiant, n, p, sexe, situation, adressePostale);
                     this->annuaire->add_new_elt(contactpros);
                     Logger::log(1,  "Le nouveau contact professionnel est ajoute a l'annuaire avec succes");
              }
              catch(const std::ios_base::failure& ex)
              {
                      Logger::log(2,  "Erreur inattendue durant la tentative d'ajout a l'annuaire du nouveau contact professionnel ") ;
                      Logger::log(2, ex.what());
              }
              catch (const exception & ex)
              {
                     Logger::log(2,  "Erreur inattendue durant la tentative d'ajout a l'annuaire du nouveau contact professionnel ") ;
                     Logger::log(2, ex.what());
              }
              catch(...)
              {
                     Logger::log(2,  "Erreur inattendue durant la tentative d'ajout a l'annuaire du nouveau contact professionnel");
              }
       }

       int Console::get_next_pid()
       {
              return this->annuaire->get_next_pid();
       }
}
