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
//using namespace Manage;

namespace Manage
{
void Annuaire::add_new_elt(Contact *contact)
{
	if(!contact)
	{
		throw ContactException("\nAjout impossible, l'contact n'est pas renseigne");
	}
	string key = contact->build_key();
	if(!this->check_elt_by_key(key))
	{
		this->map_annuaire[key] = contact;
	}
	else
	{
		cout <<"Cle contact "<<key <<endl;
		throw ContactException("\nAjout impossible, la cle existe dans la map");
	}

}

void Annuaire::delete_elt_by_key(string key)
{
	if(this->check_elt_by_key(key))
	{
		delete this->map_annuaire[key];
		this->map_annuaire.erase(key);
	}
	else
	{
		cout <<"Cle de l'contact "<< key << endl;
		throw ContactException("\nSuppression impossible, la cle n'existe pas dans la map");
	}
}

void Annuaire::delete_elt_by_pid(int pid)
{
	map<string, Contact*>::iterator it = this->map_annuaire.begin();
	bool delete_contact = false;
	for (; it != map_annuaire.end(); it++)
	{
		if(pid == it->second->get_identifiant())
		{
			string key = build_key(it->second);
			delete this->map_annuaire[key];
			this->map_annuaire.erase(key);
			delete_contact = true;
		}
	}
	if(!delete_contact)
	{
	       cout <<"pid : "<<pid << endl;
		throw ContactException("\nSuppression contact par identifiant en echec, le pid n'existe pas dans l'annuaire");
	}
	else
       {
              cout << "Le contact pid = "<<pid << " est supprime avec succes de l'annuaire" << endl;
       }

}

Contact *Annuaire::get_elt_by_key(string key)
{
	map<string, Contact*>::iterator it = this->map_annuaire.begin();
	for (; it != map_annuaire.end(); it++)
	{
		if(key == it->first) return it->second;
	}
	return nullptr;
}

vector<Contact*> Annuaire::get_list_elts_by_keys(vector<string> keys)
{
	vector<Contact*> contacts;
	for(string key : keys)
	{
		Contact * contact = get_elt_by_key(key);
		if(contact) contacts.push_back(contact);
	}
	return contacts;
}

int Annuaire::size_list()
{
	return this->map_annuaire.size();
}

bool Annuaire::check_elt_by_key(string key)
{
	map<string, Contact*>::iterator it = this->map_annuaire.begin();
	for (; it != map_annuaire.end(); it++)
	{
		if(key == it->first) return true;
	}
	return false;
}

string Annuaire::build_key(Contact *contact)
{
	string key = contact->build_key();
	return key;
}

Contact* Annuaire::get_elt_by_id(int pid)
{
	map<string, Contact*>::iterator it = this->map_annuaire.begin();
	for (; it != map_annuaire.end(); it++)
	{
		if(pid == it->second->get_identifiant()) return it->second;
	}
	return nullptr;
}

int Annuaire::get_next_pid()
{
       int pid = 0;
	map<string, Contact*>::iterator it = this->map_annuaire.begin();
	for (; it != map_annuaire.end(); it++)
	{
		if(pid < it->second->get_identifiant())
                     pid = it->second->get_identifiant();
	}
	pid++;
	return pid;
}

void Annuaire::update_elt_by_id(int pid)
{
	Contact* contact = get_elt_by_id(pid);
	if(contact)
	{
		cout <<"update " <<endl;
	}
}

vector<Contact*> Annuaire::get_list_elts_by_last_name(string lastname)
{
	vector<Contact*> contacts;
	map<string, Contact*>::iterator it = this->map_annuaire.begin();
	for (; it != map_annuaire.end(); it++)
	{
	       //cout << "it->second->get_nom() : " << it->second->get_nom() <<"    lastname   " <<lastname << endl;
		if(lastname == it->second->get_nom())
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
		if(zip_code == it->second->get_adressePostale()->get_code_postale())
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
		int depart = (int)(float(it->second->get_adressePostale()->get_code_postale())/1000.0);
		if(departement == depart)
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
		if(town == it->second->get_adressePostale()->get_ville())
		contacts.push_back(it->second);
	}
	return contacts;
}

void Annuaire::display()
{

	if(this->map_annuaire.size() == 0)
	{
		cout << "Aucun contact dans la liste" << endl << endl;
		return;
	}
	cout <<"Identifiant  " <<"Nom  " <<"Prenom  " << "Sexe  " <<"Statut juri " <<"Libelle  " <<"Complement  "<<"Code Post  " <<"Ville  " <<"Mail de contact " <<"Date de naiss" <<endl;
	cout << "*****************************************************************************************************************************************" << endl;
	map<string, Contact*>::iterator it = this->map_annuaire.begin();
	for (; it != this->map_annuaire.end(); it++)
	{
		ContactPrive *contact_prive = dynamic_cast<ContactPrive*>(it->second);
		if(contact_prive)
		{
			print_contact_prive(contact_prive);
		}
		else
		{
			ContactProfessionel *contact_prof = dynamic_cast<ContactProfessionel*>(it->second);
			print_contact_professionnel(contact_prof);
		}
		cout << "*****************************************************************************************************************************************" << endl;
	}

}

void Annuaire::display(vector<Contact *> vects)
{

	if(vects.size() == 0)
	{
		cout << "Aucun contact dans l'annuaire" << endl << endl;
		return;
	}
	cout <<"Identifiant  " <<"Nom  " <<"Prenom  " << "Sexe  " <<"Statut juri " <<"Libelle  " <<"Complement  "<<"Code Post  " <<"Ville  " <<"Mail de contact " <<"Date de naiss" <<endl;
       cout << "*****************************************************************************************************************************************" << endl;
	for(Contact * contact : vects)
	{
		ContactPrive *contact_prive = dynamic_cast<ContactPrive*>(contact);
		if(contact_prive)
		{
			print_contact_prive(contact_prive);
		}
		else
		{
			ContactProfessionel *contact_prof = dynamic_cast<ContactProfessionel*>(contact);
			print_contact_professionnel(contact_prof);
		}
		cout << "*****************************************************************************************************************************************" << endl;
	}

}

void Annuaire::print_contact_prive(ContactPrive *contact_prive)
{
	if(!contact_prive) return;

	cout <<contact_prive->get_identifiant()<<"  "
	<<contact_prive->get_nom()<<"  "
	<<contact_prive->get_prenom()<<"  "
	<<contact_prive->get_sexe()<<"  "
	<<"         "
	<<"         "
	<<contact_prive->get_adressePostale()->get_numero() <<", "
	<<contact_prive->get_adressePostale()->get_rue()<<"  "
	<<contact_prive->get_adressePostale()->get_complement()<<"  "
	<<contact_prive->get_adressePostale()->get_code_postale()<<"  "
	<<contact_prive->get_adressePostale()->get_ville()<<"  "
	<<"              "
	<<contact_prive->get_dateNaissance()->get_jour() <<"/"
	<<contact_prive->get_dateNaissance()->get_mois() <<"/"
	<<contact_prive->get_dateNaissance()->get_annee()
	<<endl;
}

void Annuaire::print_contact_professionnel(ContactProfessionel *contact_prof)
{
	if(!contact_prof) return;
	cout <<contact_prof->get_identifiant() <<"  "
	<<contact_prof->get_nom() <<"  "
	<<contact_prof->get_prenom() <<"  "
	<<contact_prof->get_sexe() <<"  "
	<<contact_prof->get_entreprise() <<"  "
	<<contact_prof->get_statut() <<"  "
	<<contact_prof->get_adressePostale()->get_numero()
	<<", "
	<<contact_prof->get_adressePostale()->get_rue() <<"  "
	<<contact_prof->get_adressePostale()->get_complement()<<"  "
	<<contact_prof->get_adressePostale()->get_code_postale()<<"  "
	<<contact_prof->get_adressePostale()->get_ville()<<"  "
	<<contact_prof->get_email()
	<<"              "
	<<endl;
}

void Annuaire::load_annuaire_from_files(string fileContactPrivate, string fileContactPro)
{

	buildContactPro(fileContactPro);
	buildContactPrive(fileContactPrivate);
}

char * to_char(string s, char *ptr)
{
	int n = s.length();
	ptr = (char *)malloc((n+1)*sizeof(char));
	for(int i = 0 ; i < n ; i++){
               *(ptr + i) = s[i];
	}
       *(ptr + n) = '\0';
      return ptr;
}

int str_to_int(string s)
{
       try{
              return stoi(s.c_str());
       }catch(...)
       {
              cout << "Erreur de conversion string vers int "<<s << endl;
       }
       return -1;
}

void Annuaire::buildContactPro(string fileContactPro)
{
	ifstream inputFile;
	inputFile.open(fileContactPro);
	string line = "";
	while (getline(inputFile, line)) {
		if(line.size()  == 0) continue;
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

		//cout << identifiant << "  "<< nom << "  " << prenom << "    " << entreprise << "     " << statut << " " << numero << "  " << rue << endl;

              int zip_code = str_to_int(code_postale);
              //cout <<" code_postale : "<<code_postale<<" zip_code : " << zip_code << endl;

              int num = str_to_int(numero);

		AdressePostale * adressePostale = new AdressePostale(num, rue, complement, zip_code, ville);

		char *entr ;
		entr = to_char(entreprise, entr);
		char *n ;
		n = to_char(nom, n);
		char *p ;
		p = to_char(prenom, p);
		int id = str_to_int(identifiant);



		ContactProfessionel * pro = new ContactProfessionel(entr, statut, email, id, n, p, sexe, situation, adressePostale);
		//pro->infos();
		this->add_new_elt(pro);
	}

}

DateNaissance *Annuaire::build(string dat)
{
	stringstream inputString(dat);

	string jour;
	string mois;
	string annee;

	getline(inputString, jour, '/');

	getline(inputString, mois, '/');

	getline(inputString, annee, '/');
	DateNaissance *datenaissance = new DateNaissance(str_to_int(jour), str_to_int(mois), str_to_int(annee));
	return datenaissance;
}

void Annuaire::buildContactPrive(string fileContactPrivate)
{
	ifstream inputFile;
	inputFile.open(fileContactPrivate);
	string line = "";
	while (getline(inputFile, line)) {
		if(line.size()  == 0) continue;
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

		//cout << identifiant << "  "<< nom << "  " << prenom << "    " << complement << "     " << statut << " " << numero << "  " << rue << endl;
              int zip_code = str_to_int(code_postale);
              //cout <<" code_postale : "<<code_postale<<" zip_code : " << zip_code << endl;
		AdressePostale * adressePostale = new AdressePostale(stoi(numero.c_str()), rue, complement, zip_code, ville);
		//adressePostale->infos();
		char *n = NULL;
		char *p= NULL;
		n = to_char(nom, n);
		p = to_char(prenom, p);
		ContactPrive * prive = new ContactPrive(dat, stoi(identifiant.c_str()),n , p, sexe, situation, adressePostale);
		this->add_new_elt(prive);
	}

}

}
