#include "../header/Contact.hpp"

namespace Heritage {

       void Contact::infos() {
              if (this->get_sexe() == 0)
                     cout << "M." << " " << this->get_nom() << " " << this->get_prenom()
                                   << endl;
              else
                     cout << "Mme." << " " << this->get_nom() << " " << this->get_prenom()
                                   << endl;
       }

       void Contact::set_nom(char *nom) {
              int len = utils->str_length(nom);
              if (len == 0 || len > 30)
                     throw ContactException(
                                   "\nLa longeueur du chmaps nom n'est pas correcte");
              this->nom = utils->to_upper_last_name(nom);
       }
       void Contact::set_prenom(char *prenom) {
              int len = utils->str_length(prenom);
              if (len == 0 || len > 30)
                     throw ContactException(
                                   "\nLa longeueur du chmaps prenom n'est pas correcte");
              this->prenom = utils->to_upper_first_name(prenom);
       }

       string Contact::build_key() {
              string key;
              key += ':';
              string d = std::to_string(this->get_identifiant());
              for (int i = 0; i < int(d.size()); i++) {
                     if (d[i] != ' ')
                            key += d[i];
              }
              key += ':';
              string n = this->get_nom();
              for (int i = 0; i < int(n.size()); i++) {
                     if (n[i] != ' ')
                            key += n[i];
              }
              key += ':';
              string p = this->get_prenom();
              for (int i = 0; i < int(p.size()); i++) {
                     if (p[i] != ' ')
                            key += p[i];
              }
              key += ':';
              return key;
       }

}
