#include "Console.hpp"
#include "ContactException.hpp"
#include "AdressePostale.hpp"
#include "ContactPrive.hpp"
#include "ContactProfessionel.hpp"
#include<regex>

using namespace Errors;

using namespace std;

namespace Manage {


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
              char *ptr = NULL;
              ptr = utils->str_to_char(nom, ptr);
              vector<Contact*> vects = this->annuaire->get_list_elts_by_last_name(
                            utils->to_upper_last_name(ptr));
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

       void Console::modifier_contact_pid()
       {
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
              do{
                     cout << "Veuillez saisir le sexe (M/F): ";
                     cin.clear();
                     getline(cin, sexe);
              }while(utils->validate_sexe(sexe) == 1);
              do{
                     cout
                                   << "Veuillez saisir la situation Familliale (Marie, Celibataire, Veuf, Pasce ou Autres : "
                                   << endl;
                     cin.clear();
                     getline(cin, situation);
              }while(utils->validate_statut(situation) == 1);
              cout << "Veuillez saisir l'annee de naissance : " << endl;
              annee = check_input_value();
              cout << "Veuillez saisir le mois de naissance : " << endl;
              mois = check_input_value();
              cout << "Veuillez saisir le jour de naissance : " << endl;
              jour = check_input_value();

              DateNaissance *dateNaissance = new DateNaissance(jour, mois, annee);
              AdressePostale *adressePostale = new_adress();
              char *n = NULL;
              n = utils->str_to_char(nom, n);
              char *p = NULL;
              p = utils->str_to_char(prenom, p);
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
              do{
                     cout << "Veuillez saisir une valeur valide du sexe (M/F): ";
                     cin.clear();
                     getline(cin, sexe);
             }while(utils->validate_sexe(sexe) == 1);
             do{
                     cout
                                   << "Veuillez saisir la situation Familliale (Marie, Celibataire, Veuf, Pasce ou Autres : "
                                   << endl;
                     cin.clear();
                     getline(cin, situation);
             }while(utils->validate_statut(situation) == 1);

                     cout << "Veuillez saisir le nom de l'entreprise : " << endl;
                     cin.ignore();
                     getline(cin, entreprise);

              do{
                     cout
                                   << "Veuillez saisir le statut juridique valide de l'entreprise SARL/SA/SAS/EURL : "
                                   << endl;
                     cin.clear();
                     getline(cin, statut);
              }while(utils->validate_entreprise_name(statut) == 1);
              do {
                     cout << "Veuillez saisir une adresse  mail de contact valide : "
                                   << endl;
                     cin.clear();
                     getline(cin, email);
              } while (!utils->check_email(email));

              AdressePostale *adressePostale = new_adress();
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

       }

       int Console::get_next_pid()
       {
              return this->annuaire->get_next_pid();
       }
}