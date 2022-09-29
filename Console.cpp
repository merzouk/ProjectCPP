#include "Console.hpp"
#include "ContactException.hpp"
#include "AdressePostale.hpp"
#include "ContactPrive.hpp"
#include "ContactProfessionel.hpp"
#include<regex>

using namespace Errors;

using namespace std;

namespace Manage {

       char* to_upper_last_name(char *s) {
              int i = 0;
              while (*(s + i) != '\0') {
                     s[i] = toupper(s[i]);
                     i++;
              }
              return s;
       }

       char* str_to_char(string s, char *ptr) {
              int n = s.length();
              ptr = (char*) malloc((n + 1) * sizeof(char));
              for (int i = 0; i < n; i++) {
                     *(ptr + i) = s[i];
              }
              *(ptr + n) = '\0';
              return ptr;
       }

       int check_input_value() {
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
              } while (aux == false || opc < 0);
              return opc;
       }

       string Console::get_str_value() {
              string str;
              cin >> str;
              return str;
       }

       void Console::load_datas(string fileContactPrivate, string fileContactPro) {
              this->annuaire->load_annuaire_from_files(fileContactPrivate,
                            fileContactPro);
       }

       void Console::rechercher_contact_nom() {
              cout << "Veuillez saisir le nom du contact" << endl;
              string nom = get_str_value();
              char *ptr;
              ptr = str_to_char(nom, ptr);
              vector<Contact*> vects = this->annuaire->get_list_elts_by_last_name(
                            to_upper_last_name(ptr));
              if(vects.size() == 1)
                     vects[0]->infos();
              else
                     this->annuaire->display(vects);
       }

       void Console::afficher_annuaire() {
              this->annuaire->display();
       }

       void Console::rechercher_contact_pid() {

              cout << "Veuillez saisir l'identifiant du contact" << endl;
              int pid = check_input_value();
              Contact *contact = this->annuaire->get_elt_by_id(pid);
              ContactPrive *contact_prive = dynamic_cast<ContactPrive*>(contact);
              if (contact_prive) {
                       contact_prive->infos();
              } else {
                     ContactProfessionel *contact_prof =
                                   dynamic_cast<ContactProfessionel*>(contact);
                         contact_prof->infos();
              }

       }

       void Console::rechercher_contact_code_postale() {
              cout << "Veuillez saisir le code postale du contact" << endl;
              int zip_code = check_input_value();
              vector<Contact*> contacts = this->annuaire->get_list_elts_by_zip_code(
                            zip_code);
              if(contacts.size() == 1)
                     contacts[0]->infos();
              else
                     this->annuaire->display(contacts);
       }

       void Console::rechercher_contact_departement() {
              cout << "Veuillez saisir le code du departement du contact" << endl;
              int departement = check_input_value();
              vector<Contact*> contacts = this->annuaire->get_list_elts_by_department(
                            departement);
              if(contacts.size() == 1)
                     contacts[0]->infos();
              else
                     this->annuaire->display(contacts);
       }

       void Console::rechercher_contact_ville() {
              cout << "Veuillez saisir le nom de la ville du contact" << endl;
              string ville = get_str_value();
              vector<Contact*> contacts = this->annuaire->get_list_elts_by_town(ville);
              if(contacts.size() == 1)
                     contacts[0]->infos();
              else
                     this->annuaire->display(contacts);
       }

       void Console::supprimer_contact_pid() {
              cout << "Veuillez saisir l'identifiant du contact" << endl;
              int pid = check_input_value();
              try {
                     this->annuaire->delete_elt_by_pid(pid);
              } catch (const ContactException &ex) {
                     cout << "Suppression en echec : " << ex.what() << endl;
              } catch (...) {
                     cout
                                   << "Erreur inattendue pendant la tentative de suppression du contact par son id "
                                   << pid << endl;
              }

       }

       void Console::modifier_contact_pid() {
              cout << "Seule l'adresse postale sera modifiee " << endl;
              cout << "Veuillez saisir l'identifiant du contact " << endl;
              int pid = check_input_value();
              Contact *contact = this->annuaire->get_elt_by_id(pid);

              ContactPrive *contact_prive = dynamic_cast<ContactPrive*>(contact);
              if (contact_prive) {
                     this->annuaire->print_contact_prive(contact_prive);

              } else {
                     ContactProfessionel *contact_prof =
                                   dynamic_cast<ContactProfessionel*>(contact);
                     this->annuaire->print_contact_professionnel(contact_prof);
              }
              try {
                     AdressePostale *adr = new_adress();
                     contact->set_adressePostale(adr);
                     cout << "L'adresse postale du contact est modifiee avec succes" << endl;
              } catch (...) {
                     cout
                                   << "Erreur inattendue s'est produite pendant la tentative de modification de l'adresse postale"
                                   << endl;
              }

       }

       AdressePostale* Console::new_adress() {
              int numero;
              string rue;
              string complement;
              int code_postale;
              string ville;
              cout << "Veuillez saisir un numero de rue : " << endl;
              numero = check_input_value();
              cout << "Veuillez saisir le nom de la rue : " << endl;
              cin.ignore();
              getline(cin, rue);
              cout << "Veuillez saisir le complement, sinon un espace et validez: "
                            << endl;
              cin.ignore();
              getline(cin, complement);
              cout << "Veuillez saisir le code postale : " << endl;
              ;
              code_postale = check_input_value();
              cout << "Veuillez saisir le nom de la ville : " << endl;
              cin.ignore();
              getline(cin, ville);
              AdressePostale *adr = new AdressePostale(numero, rue, complement,
                            code_postale, ville);
              return adr;
       }

       void Console::ajouter_contact_prive() {
              string nom;
              string prenom;
              string sexe;
              string situation;
              int mois;
              int jour;
              int annee;
              cout << "Veuillez saisir le nom du contact : " << endl;
              cin.ignore();
              getline(cin, nom);
              cout << "Veuillez saisir le prenom du contact : " << endl;
              cin.ignore();
              getline(cin, prenom);
              cout << "Veuillez saisir le sexe (M/F): ";
              cin.ignore();
              getline(cin, sexe);
              cout
                            << "Veuillez saisir la situation Familliale (Marie, Celibataire, Veuf, Pasce ou autres : "
                            << endl;
              cin.ignore();
              getline(cin, situation);
              cout << "Veuillez saisir l'annee de naissance : " << endl;
              annee = check_input_value();
              cout << "Veuillez saisir le mois de naissance : " << endl;
              mois = check_input_value();
              cout << "Veuillez saisir le jour de naissance : " << endl;
              jour = check_input_value();

              DateNaissance *dateNaissance = new DateNaissance(jour, mois, annee);
              AdressePostale *adressePostale = new_adress();
              char *n;
              n = str_to_char(nom, n);
              char *p;
              p = str_to_char(prenom, p);
              int identifiant = get_next_pid();
              ContactPrive *contactprive = new ContactPrive(dateNaissance, identifiant, n,
                            p, sexe, situation, adressePostale);
              this->annuaire->add_new_elt(contactprive);
       }

       void Console::ajouter_contact_professionnel() {
              string nom;
              string prenom;
              string sexe;
              string situation;
              string entreprise;
              string statut;
              string email;

              cout << "Veuillez saisir le nom du contact : " << endl;
              cin.ignore();
              getline(cin, nom);
              cout << "Veuillez saisir le prenom du contact : " << endl;
              cin.ignore();
              getline(cin, prenom);
              //do{
              cout << "Veuillez saisir une valeur valide du sexe (M/F): ";
              cin.ignore();
              getline(cin, sexe);
             // }while((sexe != "F"  || sexe != "M"));
              cout
                            << "Veuillez saisir la situation Familliale (Marie, Celibataire, Veuf, Pasce ou autres : "
                            << endl;
              cin.ignore();
              getline(cin, situation);
              cout << "Veuillez saisir le nom de l'entreprise : " << endl;
              cin.ignore();
              getline(cin, entreprise);
              //do{
              cout
                            << "Veuillez saisir le statut juridique valide de l'entreprise SARL/SA/SAS/EURL : "
                            << endl;
              cin.ignore();
              getline(cin, entreprise);
              //}while(!(entreprise != "SARL" && entreprise != "SA" && entreprise != "SAS" && entreprise != "EURL"));
              do {
                     cout << "Veuillez saisir une adresse  mail de contact valide : "
                                   << endl;
                     cin.ignore();
                     getline(cin, email);
              } while (!check_email(email));

              AdressePostale *adressePostale = new_adress();
              char *n;
              n = str_to_char(nom, n);
              char *entr;
              entr = str_to_char(nom, entr);
              char *p;
              p = str_to_char(prenom, p);
              int identifiant = get_next_pid();
              ContactProfessionel *contactpros = new ContactProfessionel(entr, statut,
                            email, identifiant, n, p, sexe, situation, adressePostale);
              this->annuaire->add_new_elt(contactpros);

       }

       bool Console::check_email(string email) {
              const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
              return regex_match(email, pattern);
       }

       int Console::get_next_pid() {

              return this->annuaire->get_next_pid();
       }

}
