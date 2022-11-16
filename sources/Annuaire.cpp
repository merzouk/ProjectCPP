#include "../header/AdressePostale.hpp"
#include "../header/Contact.hpp"
#include "../header/ContactException.hpp"
#include "../header/ContactProfessionel.hpp"
#include "../header/ContactPrive.hpp"
#include "../header/Annuaire.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

using namespace Errors;
using namespace Heritage;

namespace Manage
{

       map<string, Contact*> Annuaire::get_map_annuaire()
       {
              return this->map_annuaire;
       }

       void Annuaire::add_new_elt(Contact *contact)
       {
              if (!contact) {
                     throw ContactException(
                                   "\nAjout impossible, le contact n'est pas renseigne");
              }
              string key = contact->build_key();
              if (!this->check_elt_by_key(key))
              {
                     this->map_annuaire[key] = contact;
              }
              else
              {
                     throw ContactException("Cle contact " +key+"\nAjout impossible, la cle existe dans l'annuaire");
              }
       }

       void Annuaire::delete_elt_by_key(string key)
       {
              if (this->check_elt_by_key(key))
              {
                     //delete this->map_annuaire[key];
                     this->map_annuaire.erase(key);
              }
              else
              {
                     throw ContactException(
                                   "Cle du contact " + key +"\nSuppression impossible, la cle n'existe pas dans l'annuaire");
              }
       }

       void Annuaire::delete_elt_by_id(int pid)
       {
              if(pid <= 0)
              {
                     Logger::log(3,  "L'identifiant du contact "+ to_string(pid) + " n'est pas valide ");
                     return;
              }
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              bool delete_contact = false;
              for (; it != map_annuaire.end(); it++)
              {
                     if (pid == it->second->get_identifiant())
                     {
                            string key = build_key(it->second);
                            //delete this->map_annuaire[key];
                            this->map_annuaire.erase(key);
                            delete_contact = true;
                     }
              }
              if (!delete_contact)
              {
                     throw ContactException(
                                 "pid : " + to_string(pid) +  "\nSuppression contact par identifiant en echec, le pid n'existe pas dans l'annuaire");
              }
              else
              {
                     Logger::log(1,  "Le contact pid = " + to_string(pid) +
                                    " est supprime de l'annuaire avec succes");
              }

       }

       Contact* Annuaire::get_elt_by_key(string key)
       {
              int len = int(key.length());
              if(len == 0)
              {
                     Logger::log(3, "La cle du contact "+ key + "n'est pas valide ");
                     return nullptr;
              }
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     if (key == it->first)
                            return it->second;
              }
              return nullptr;
       }

       vector<Contact*> Annuaire::get_list_elts_by_keys(vector<string> keys)
       {
              vector<Contact*> contacts;
              if(keys.size() == 1)
              {
                     Logger::log(3,  "Aucune cle renseignee, recherche impossible ");
                     return contacts;
              }
              for (string key : keys)
              {
                     Contact *contact = get_elt_by_key(key);
                     if (contact)
                            contacts.push_back(contact);
              }
              return contacts;
       }

       int Annuaire::size_list()
       {
              return this->map_annuaire.size();
       }

       bool Annuaire::check_elt_by_key(string key)
       {
              int len = int(key.length());
              if(len == 0)
              {
                     Logger::log(3, "La cle du contact "+ key + "n'est pas valide ");
                     return false;
              }
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     if (key == it->first)
                            return true;
              }
              return false;
       }

       string Annuaire::build_key(Contact *contact)
       {
              if(!contact)
              {
                    Logger::log(3,  "Le contact n'est pas renseigne, impossible de construire la cle ");
                    return "";
              }
              string key = contact->build_key();
              return key;
       }

       Contact* Annuaire::get_elt_by_id(int pid)
       {
              if(pid <= 0)
              {
                     Logger::log(3,  "L'identifiant du contact "+to_string(pid) + " n'est pas valide ");
                     return nullptr;
              }
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     if (pid == it->second->get_identifiant())
                            return it->second;
              }
              return nullptr;
       }

       int Annuaire::get_next_pid()
       {
              int pid = 0;
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     if (pid < it->second->get_identifiant())
                            pid = it->second->get_identifiant();
              }
              pid++;
              return pid;
       }

       void Annuaire::update_elt_by_id(int pid)
       {
              Contact *contact = get_elt_by_id(pid);
              if (contact)
              {
                     Logger::log(3,  "This method not used, see Console class");
              }
       }

       vector<Contact*> Annuaire::get_list_elts_by_last_name(string lastname)
       {
              vector<Contact*> contacts;
              int len = int(lastname.length());
              if(len == 0)
              {
                     Logger::log(3,  "Le nom " +lastname + " n'est pas valide");
                     return contacts;
              }
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     if (lastname == it->second->get_nom())
                            contacts.push_back(it->second);
              }
              return contacts;
       }

       vector<Contact*> Annuaire::get_list_elts_by_first_name(string firstname)
       {
              vector<Contact*> contacts;
              int len = int(firstname.length());
              if(len == 0)
              {
                     Logger::log(3,  "Le prenom " +firstname + " n'est pas valide");
                     return contacts;
              }
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     if (firstname == it->second->get_prenom())
                            contacts.push_back(it->second);
              }
              return contacts;
       }

       vector<Contact*> Annuaire::get_list_elts_by_zip_code(int zip_code)
       {
              vector<Contact*> contacts;
              if(zip_code <= 1000)
              {
                     Logger::log(3,  "Le code postale " + to_string(zip_code) + " n'est pas valide");
                     return contacts;
              }
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     if (zip_code == it->second->get_adressePostale()->get_code_postale())
                            contacts.push_back(it->second);
              }
              return contacts;

       }

       vector<Contact*> Annuaire::get_list_elts_by_department(int departement)
       {
              vector<Contact*> contacts;
              if(departement < 0 || departement > 100)
              {
                     Logger::log(3,  "Le code departement " + to_string(departement) + " n'est pas valide");
                     return contacts;
              }
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     int departmt = (int) (float(
                                   it->second->get_adressePostale()->get_code_postale()) / 1000.0);
                     if (departement == departmt)
                            contacts.push_back(it->second);
              }
              return contacts;
       }

       vector<Contact*> Annuaire::get_list_elts_by_town(string town)
       {
              vector<Contact*> contacts;
              int len = int(town.length());
              if(len == 0)
              {
                     Logger::log(3,  "Le nom de la ville " +town + " n'est pas valide");
                     return contacts;
              }
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     if (town == it->second->get_adressePostale()->get_ville())
                            contacts.push_back(it->second);
              }
              return contacts;
       }

       Contact *Annuaire::get_elt_by_email(string email)
       {
              int len = int(email.length());
              if(len == 0)
              {
                     Logger::log(3, "L'addresse mail " +email + " n'est pas valide");
                     return nullptr;
              }
              if(!utils->check_email(email))
              {
                     Logger::log(3, "Le format de l'addresse mail " +email + " n'est pas valide");
                     return nullptr;
              }
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     ContactProfessionel *pro = dynamic_cast<ContactProfessionel*>(it->second);
                     if(pro)
                     {
                            if(pro->get_email() == email)
                            {
                                   return pro;
                            }
                     }
              }
              return nullptr;
       }



       void Annuaire::load_annuaire_from_files(string fileContactPrivate, string fileContactPro)
       {
              buildContactPro(fileContactPro);
              buildContactPrive(fileContactPrivate);
       }

       void Annuaire::buildContactPro(string fileContactPro)
       {
              ifstream inputFile;
              try
              {
                     inputFile.open(fileContactPro);
              }
              catch (const ifstream::failure& e)
              {
                      Logger::log(2,"Echec lors de la tentative d'ouverture du fichier des contacts professionnels " + fileContactPro +"  " + e.what());
                      return;
              }
              catch(const exception & ex)
              {
                      Logger::log(2, "Echec lors de la tentative d'ouverture du fichier des contacts professionnels " + fileContactPro +"  "+ ex.what());
                      return;
              }
              catch(...)
              {
                      Logger::log(2, "Echec lors de la tentative d'ouverture du fichier des contacts professionnels " + fileContactPro );
                      return;
              }
              string line = "";
              while (getline(inputFile, line))
              {
                     if (line.size() == 0)
                            continue;
                     stringstream inputString(line);
                     string entreprise;
                     string statut;
                     string email;
                     string identifiant;
                     string nom;
                     string prenom;
                     string sexe;
                     string situation;
                     string numero;
                     string rue;
                     string complement;
                     string code_postale;
                     string ville;

                     getline(inputString, identifiant, ';');
                     getline(inputString, nom, ';');
                     getline(inputString, prenom, ';');
                     getline(inputString, sexe, ';');
                     getline(inputString, entreprise, ';');
                     getline(inputString, statut, ';');
                     getline(inputString, numero, ';');
                     getline(inputString, rue, ';');
                     getline(inputString, complement, ';');
                     getline(inputString, code_postale, ';');
                     getline(inputString, ville, ';');
                     getline(inputString, email, ';');

                     int zip_code = utils->str_to_int(code_postale);
                     int num = utils->str_to_int(numero);

                     AdressePostale *adressePostale = new AdressePostale(num, rue,
                                   complement, zip_code, ville);

                     char *entr = NULL;
                     entr = utils->to_char(entreprise, entr);
                     char *n = NULL;
                     n = utils->to_char(nom, n);
                     char *p = NULL;
                     p = utils->to_char(prenom, p);
                     int id = utils->str_to_int(identifiant);

                     ContactProfessionel *pro = new ContactProfessionel(entr, statut, email,
                                   id, n, p, sexe, situation, adressePostale);
                     this->add_new_elt(pro);
              }
       }

       DateNaissance* Annuaire::build_date_naissance(string date_naissance_str)
       {
              stringstream inputString(date_naissance_str);

              string jour;
              string mois;
              string annee;

              getline(inputString, jour,  '/');
              getline(inputString, mois,  '/');
              getline(inputString, annee, '/');
              DateNaissance *datenaissance = new DateNaissance(
                                                               utils->str_to_int(jour),
                                                               utils->str_to_int(mois),
                                                               utils->str_to_int(annee)
                                                               );
              return datenaissance;
       }

       void Annuaire::buildContactPrive(string fileContactPrivate)
       {
              ifstream inputFile;
              try
              {
                     inputFile.open(fileContactPrivate);
              }
              catch (const ifstream::failure& e)
              {
                     Logger::log(2, "Echec lors de la tentative d'ouverture du fichier des contacts prives " + fileContactPrivate + "  "+e.what());
                     return;
              }
              catch(const exception & ex)
              {
                     Logger::log(2, "Echec lors de la tentative d'ouverture du fichier des contacts prives " + fileContactPrivate + "  "+ex.what());
                     return;
              }
              catch(...)
              {
                     Logger::log(2, "Echec lors de la tentative d'ouverture du fichier des contacts prives " + fileContactPrivate);
                     return;
              }
              string line = "";
              while (getline(inputFile, line))
              {
                     if (line.size() == 0)
                            continue;
                     stringstream inputString(line);
                     string statut;
                     string identifiant;
                     string nom;
                     string prenom;
                     string sexe;
                     string situation = "Marie";
                     string dat_naiss;
                     string jour;
                     string mois;
                     string annee;
                     string numero;
                     string rue;
                     string complement;
                     string code_postale;
                     string ville;

                     DateNaissance *dat;
                     getline(inputString, identifiant, ';');
                     getline(inputString, nom, ';');
                     getline(inputString, prenom, ';');
                     getline(inputString, sexe, ';');
                     getline(inputString, numero, ';');
                     getline(inputString, rue, ';');
                     getline(inputString, complement, ';');
                     getline(inputString, code_postale, ';');
                     getline(inputString, ville, ';');
                     getline(inputString, dat_naiss, ';');
                     dat = build_date_naissance(dat_naiss);

                     int zip_code = utils->str_to_int(code_postale);

                     AdressePostale *adressePostale = new AdressePostale(
                                   utils->str_to_int(numero), rue, complement, zip_code, ville);
                     char *n = NULL;
                     char *p = NULL;
                     n = utils->to_char(nom, n);
                     p = utils->to_char(prenom, p);
                     ContactPrive *prive = new ContactPrive(dat, utils->str_to_int(identifiant.c_str()),
                                   n, p, sexe, situation, adressePostale);
                     this->add_new_elt(prive);
              }
       }
}
