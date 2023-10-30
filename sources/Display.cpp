#include "../header/Display.hpp"

namespace Manage
{
       string delimiter = "*****************************************************************************************************************************************************************************************************";

       void display_header_table()
       {
              cout.fill(' ');
              cout << setw(5) << "Id"
                   << setw(20) << "Nom"
                   << setw(20) << "Prenom"
                   << setw(6) << "Sexe"
                   << setw(10) << "Entre"
                   << setw(6) << "Stat"
                   << setw(5) << "Num"
                   << setw(30) << "Rue"
                   << setw(15) << "Compl"
                   << setw(6) << "C_P"
                   << setw(20) << "Ville"
                   << setw(11) << "Date Naiss"
                   << setw(30) << "Email"
                   << endl;
       }

       string format_date(ContactPrive *contact_prive)
       {
              if (!contact_prive)
              {
                     Logger::log(INFO, "Le contact n'est pas renseigne, construction date au format string impossible");
                     return "";
              }
              string date_naissance = to_string(contact_prive->get_dateNaissance()->get_jour()) + "/" + to_string(contact_prive->get_dateNaissance()->get_mois()) + "/" + to_string(contact_prive->get_dateNaissance()->get_annee());
              return date_naissance;
       }

       void Display::print_contact_prive(ContactPrive *contact_prive)
       {
              if (!contact_prive)
              {
                     // Logger::log(INFO,  "Le contact prive n'est pas renseigne");
                     return;
              }
              cout.fill(' ');

              cout << setw(5) << contact_prive->get_identifiant()
                   << setw(20) << contact_prive->get_nom()
                   << setw(20) << contact_prive->get_prenom()
                   << setw(6) << contact_prive->get_sexe()
                   << setw(10) << " "
                   << setw(6) << " "
                   << setw(5) << contact_prive->get_adressePostale()->get_numero()
                   << setw(30) << contact_prive->get_adressePostale()->get_rue()
                   << setw(15) << contact_prive->get_adressePostale()->get_complement()
                   << setw(6) << contact_prive->get_adressePostale()->get_code_postale()
                   << setw(20) << contact_prive->get_adressePostale()->get_ville()
                   << setw(11) << format_date(contact_prive)
                   << setw(30) << " "
                   << endl;
       }

       void Display::print_contact_professionnel(ContactProfessionel *contact_prof)
       {
              if (!contact_prof)
              {
                     // Logger::log(INFO, "Le contact professionnel n'est pas renseigne");
                     return;
              }
              cout.fill(' ');
              cout << setw(5) << contact_prof->get_identifiant()
                   << setw(20) << contact_prof->get_nom()
                   << setw(20) << contact_prof->get_prenom()
                   << setw(6) << contact_prof->get_sexe()
                   << setw(10) << contact_prof->get_entreprise()
                   << setw(6) << contact_prof->get_statut()
                   << setw(5) << contact_prof->get_adressePostale()->get_numero()
                   << setw(30) << contact_prof->get_adressePostale()->get_rue()
                   << setw(15) << contact_prof->get_adressePostale()->get_complement()
                   << setw(6) << contact_prof->get_adressePostale()->get_code_postale()
                   << setw(20) << contact_prof->get_adressePostale()->get_ville()
                   << setw(11) << " "
                   << setw(30) << contact_prof->get_email() << endl;
       }

       void Display::display(vector<Contact *> vects)
       {
              cout.fill(' ');
              if (vects.size() == 0)
              {
                     Logger::log(INFO, "Aucun contact dans l'annuaire");
                     return;
              }
              display_header_table();
              cout << delimiter << endl;
              for (Contact *contact : vects)
              {
                     ContactPrive *contact_prive = dynamic_cast<ContactPrive *>(contact);
                     if (contact_prive)
                     {
                            print_contact_prive(contact_prive);
                            cout << delimiter << endl;
                     }
                     else
                     {
                            ContactProfessionel *contact_prof =
                                dynamic_cast<ContactProfessionel *>(contact);
                            print_contact_professionnel(contact_prof);
                            cout << delimiter << endl;
                     }
              }
       }

       void Display::display(map<string, Contact *> map_annuaire, int mode)
       {

              if (map_annuaire.size() == 0)
              {
                     Logger::log(INFO, "Aucun contact dans l'annuaire");
                     return;
              }
              display_header_table();
              cout << delimiter << endl;
              map<string, Contact *>::iterator it = map_annuaire.begin();
              for (; it != map_annuaire.end(); it++)
              {
                     ContactPrive *contact_prive = dynamic_cast<ContactPrive *>(it->second);
                     if (contact_prive && (mode == 0 || mode == 1))
                     {
                            print_contact_prive(contact_prive);
                            cout << delimiter << endl;
                     }
                     else if (mode == 0 || mode == 2)
                     {
                            ContactProfessionel *contact_prof =
                                dynamic_cast<ContactProfessionel *>(it->second);
                            if (contact_prof)
                            {
                                   print_contact_professionnel(contact_prof);
                                   cout << delimiter << endl;
                            }
                     }
              }
       }
}
