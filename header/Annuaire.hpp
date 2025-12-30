#ifndef ANNUAIRE_H_FILE
#define ANNUAIRE_H_FILE
#include "Tools.hpp"
#include "Contact.hpp"
#include "ContactPrive.hpp"
#include "Utils.hpp"

using namespace std;
using namespace MapTools;
using namespace Heritage;

namespace Manage
{
       class Annuaire : public Tools<string, int, Contact>
       {
       private:
              Utils *utils;

       public:
              Annuaire() { this->utils = new Utils(); }
              ~Annuaire() override {
                     delete this->utils;
                     this->utils = nullptr;
              }

              /*virtual*/ void add_new_elt(Contact *contact) override;
              /*virtual*/ void delete_elt_by_key(string key) override;
              /*virtual*/ void delete_elt_by_id(int pid) override;
              /*virtual*/ void update_elt_by_id(int pid) override;
              /*virtual*/ Contact *get_elt_by_email(string email) override;
              /*virtual*/ Contact *get_elt_by_key(string key) override;
              /*virtual*/ vector<Contact *> get_list_elts_by_keys(vector<string> keys) override;
              /*virtual*/ Contact *get_elt_by_id(int pid) override;
              /*virtual*/ vector<Contact *> get_list_elts_by_last_name(string lastname) override;
              /*virtual*/ vector<Contact *> get_list_elts_by_first_name(string firstname) override;
              /*virtual*/ vector<Contact *> get_list_elts_by_zip_code(int zip_code) override;
              /*virtual*/ vector<Contact *> get_list_elts_by_department(int departement) override;
              /*virtual*/ vector<Contact *> get_list_elts_by_town(string town) override;

              /*virtual*/ int size_list() override;
              /*virtual*/ int check_elt_by_key(string key) override;
              /*virtual*/ string build_key(Contact *contact) override;

              void load_annuaire_from_files(string fileContactPrivate, string fileContactPro);
              void buildContactPro(string fileContactPro);
              void buildContactPrive(string fileContactPro);
              DateNaissance *build_date_naissance(string date_naissance_str);
              map<string, Contact *> get_map_annuaire();

              int get_next_pid();
       };
}
#endif // ANNUAIRE_H_FILE
