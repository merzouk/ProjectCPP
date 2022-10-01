#include "Annuaire.hpp"
#include "Contact.hpp"
#include "ContactException.hpp"
#include "ContactProfessionel.hpp"
#include "ContactPrive.hpp"

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

namespace Manage {

       void Annuaire::add_new_elt(Contact *contact) {
              if (!contact) {
                     throw ContactException(
                                   "\nAjout impossible, le contact n'est pas renseigne");
              }
              string key = contact->build_key();
              if (!this->check_elt_by_key(key)) {
                     this->map_annuaire[key] = contact;
              } else {
                     cout << "Cle contact " << key << endl;
                     throw ContactException("\nAjout impossible, la cle existe dans l'annuaire");
              }

       }

       void Annuaire::delete_elt_by_key(string key) {
              if (this->check_elt_by_key(key)) {
                     delete this->map_annuaire[key];
                     this->map_annuaire.erase(key);
              } else {
                     cout << "Cle de l'contact " << key << endl;
                     throw ContactException(
                                   "\nSuppression impossible, la cle n'existe pas dans l'annuaire");
              }
       }

       void Annuaire::delete_elt_by_id(int pid) {
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              bool delete_contact = false;
              for (; it != map_annuaire.end(); it++) {
                     if (pid == it->second->get_identifiant()) {
                            string key = build_key(it->second);
                            delete this->map_annuaire[key];
                            this->map_annuaire.erase(key);
                            delete_contact = true;
                     }
              }
              if (!delete_contact) {
                     cout << "pid : " << pid << endl;
                     throw ContactException(
                                   "\nSuppression contact par identifiant en echec, le pid n'existe pas dans l'annuaire");
              } else {
                     cout << "Le contact pid = " << pid
                                   << " est supprime avec succes de l'annuaire" << endl;
              }

       }

       Contact* Annuaire::get_elt_by_key(string key) {
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++) {
                     if (key == it->first)
                            return it->second;
              }
              return nullptr;
       }

       vector<Contact*> Annuaire::get_list_elts_by_keys(vector<string> keys) {
              vector<Contact*> contacts;
              for (string key : keys) {
                     Contact *contact = get_elt_by_key(key);
                     if (contact)
                            contacts.push_back(contact);
              }
              return contacts;
       }

       int Annuaire::size_list() {
              return this->map_annuaire.size();
       }

       bool Annuaire::check_elt_by_key(string key) {
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++) {
                     if (key == it->first)
                            return true;
              }
              return false;
       }

       string Annuaire::build_key(Contact *contact) {
              string key = contact->build_key();
              return key;
       }

       Contact* Annuaire::get_elt_by_id(int pid) {
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++) {
                     if (pid == it->second->get_identifiant())
                            return it->second;
              }
              return nullptr;
       }

       int Annuaire::get_next_pid() {
              int pid = 0;
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++) {
                     if (pid < it->second->get_identifiant())
                            pid = it->second->get_identifiant();
              }
              pid++;
              return pid;
       }

       void Annuaire::update_elt_by_id(int pid) {
              Contact *contact = get_elt_by_id(pid);
              if (contact) {
                     cout << "update " << endl;
              }
       }

       vector<Contact*> Annuaire::get_list_elts_by_last_name(string lastname)
       {
              vector<Contact*> contacts;
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     if (lastname == it->second->get_nom())
                            contacts.push_back(it->second);
              }
              return contacts;
       }

       vector<Contact*> Annuaire::get_list_elts_by_zip_code(int zip_code)
       {
              vector<Contact*> contacts;
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
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     int depart = (int) (float(
                                   it->second->get_adressePostale()->get_code_postale()) / 1000.0);
                     if (departement == depart)
                            contacts.push_back(it->second);
              }
              return contacts;
       }

       vector<Contact*> Annuaire::get_list_elts_by_town(string town)
       {
              vector<Contact*> contacts;
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

       void Annuaire::display() {
              cout.fill(' ');
              if (this->map_annuaire.size() == 0) {
                     cout << "Aucun contact dans la liste" << endl << endl;
                     return;
              }
                          cout << setw(5)   << "Id"
                               << setw(30)  << "Nom"
                               << setw(30)  << "Prenom"
				   << setw(6)   << "Sexe"
				   << setw(10)  << "Entre"
				   << setw(6)   << "Stat"
				   << setw(5)   << "Num"
				   << setw(40)  << "Rue"
				   << setw(15)  << "Compl"
				   << setw(6)   << "C_P"
				   << setw(20)  << "Ville"
                               << setw(14)  << "Date Naiss"
                               << setw(30)  << "Email"								<< endl;
              cout
                            << "*********************************************************************************************************************************************************************************************************************************"
                            << endl;
              map<string, Contact*>::iterator it = this->map_annuaire.begin();
              for (; it != this->map_annuaire.end(); it++) {
                     ContactPrive *contact_prive = dynamic_cast<ContactPrive*>(it->second);
                     if (contact_prive) {
                            print_contact_prive(contact_prive);
                     } else {
                            ContactProfessionel *contact_prof =
                                          dynamic_cast<ContactProfessionel*>(it->second);
                            print_contact_professionnel(contact_prof);
                     }
                     cout
                                   << "*********************************************************************************************************************************************************************************************************************************"
                                   << endl;
              }

       }

       void Annuaire::display(vector<Contact*> vects)
       {
              cout.fill(' ');
              if (vects.size() == 0) {
                     cout << "Aucun contact dans l'annuaire" << endl << endl;
                     return;
              }
                   cout        << setw(5)   << "Id"
                               << setw(30)  << "Nom"
                               << setw(30)  << "Prenom"
				   << setw(6)   << "Sexe"
				   << setw(10)  << "Entre"
				   << setw(6)   << "Stat"
				   << setw(5)   << "Num"
				   << setw(40)  << "Rue"
				   << setw(15)  << "Compl"
				   << setw(6)   << "C_P"
				   << setw(20)  << "Ville"
				   << setw(14)  << "Date Naiss"
                               << setw(30)  << "Email"								<< endl;
              cout
                            << "*********************************************************************************************************************************************************************************************************************************"
                            << endl;
              for (Contact *contact : vects) {
                     ContactPrive *contact_prive = dynamic_cast<ContactPrive*>(contact);
                     if (contact_prive) {
                            print_contact_prive(contact_prive);
                     } else {
                            ContactProfessionel *contact_prof =
                                          dynamic_cast<ContactProfessionel*>(contact);
                            print_contact_professionnel(contact_prof);
                     }
                     cout
                                   << "*********************************************************************************************************************************************************************************************************************************"
                                   << endl;
              }

       }

       string format_date(ContactPrive *contact_prive)
       {
              string date_naissance =    to_string(contact_prive->get_dateNaissance()->get_jour())
                                       + "/"
                                       + to_string(contact_prive->get_dateNaissance()->get_mois())
                                       +  "/"
                                       + to_string(contact_prive->get_dateNaissance()->get_annee()) ;
              return date_naissance;
       }

       void Annuaire::print_contact_prive(ContactPrive *contact_prive)
       {
              if (!contact_prive)
                     return;
              cout.fill(' ');

              cout << setw(5)   << contact_prive->get_identifiant()
                   << setw(30)  << contact_prive->get_nom()
                   << setw(30)  << contact_prive->get_prenom()
		     << setw(6)   << contact_prive->get_sexe()
                   << setw(10)  << " "
                   << setw(6)   << " "
                   << setw(5)   << contact_prive->get_adressePostale()->get_numero()
                   << setw(40)  << contact_prive->get_adressePostale()->get_rue()
                   << setw(15)  << contact_prive->get_adressePostale()->get_complement()
                   << setw(6)   << contact_prive->get_adressePostale()->get_code_postale()
                   << setw(20)  << contact_prive->get_adressePostale()->get_ville()
                   << setw(14)  << format_date(contact_prive)
                   << setw(30)  << " "
                   << endl;
       }

       void Annuaire::print_contact_professionnel(ContactProfessionel *contact_prof)
       {
              if (!contact_prof)
                     return;
              cout.fill(' ');
              cout << setw(5)  << contact_prof->get_identifiant()
                   << setw(30) << contact_prof->get_nom()
                   << setw(30) << contact_prof->get_prenom()
                   << setw(6)  << contact_prof->get_sexe()
                   << setw(10) << contact_prof->get_entreprise()
		     << setw(6)  << contact_prof->get_statut()
		     << setw(5)  << contact_prof->get_adressePostale()->get_numero()
		     << setw(40) << contact_prof->get_adressePostale()->get_rue()
		     << setw(15) << contact_prof->get_adressePostale()->get_complement()
                   << setw(6)  << contact_prof->get_adressePostale()->get_code_postale()
                   << setw(20) << contact_prof->get_adressePostale()->get_ville()
                   << setw(14) << " "
                   << setw(30) << contact_prof->get_email() << endl;
       }

       void Annuaire::load_annuaire_from_files(string fileContactPrivate, string fileContactPro)
       {
              buildContactPro(fileContactPro);
              buildContactPrive(fileContactPrivate);
       }



       void Annuaire::buildContactPro(string fileContactPro)
       {
              ifstream inputFile;
              inputFile.open(fileContactPro);
              string line = "";
              while (getline(inputFile, line)) {
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

       DateNaissance* Annuaire::build(string dat) {
              stringstream inputString(dat);

              string jour;
              string mois;
              string annee;

              getline(inputString, jour, '/');
              getline(inputString, mois, '/');
              getline(inputString, annee, '/');
              DateNaissance *datenaissance = new DateNaissance(utils->str_to_int(jour),
                            utils->str_to_int(mois), utils->str_to_int(annee));
              return datenaissance;
       }

       void Annuaire::buildContactPrive(string fileContactPrivate) {
              ifstream inputFile;
              inputFile.open(fileContactPrivate);
              string line = "";
              while (getline(inputFile, line)) {
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
                     dat = build(dat_naiss);

                     int zip_code = utils->str_to_int(code_postale);

                     AdressePostale *adressePostale = new AdressePostale(
                                   stoi(numero.c_str()), rue, complement, zip_code, ville);
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
