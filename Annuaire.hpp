#ifndef MAGASIN_H_FILE
#define MAGASIN_H_FILE
#include "Tools.hpp"
#include "Contact.hpp"
#include "ContactPrive.hpp"
#include "ContactProfessionel.hpp"
#include "Utils.hpp"

using namespace std;
using namespace MapTools;
using namespace Heritage;


namespace Manage
{
       class Annuaire: public Tools<string, int, Contact>
       {
             private:
                     Utils * utils;

              public:
                     Annuaire(){ this->utils = new Utils();}
                     ~Annuaire()
                        {
                               delete this->utils;
                               this->utils = nullptr;
                        }

                     /*virtual*/ void add_new_elt(Contact *contact)  override;
                     /*virtual*/ void delete_elt_by_key(string key)  override;
                     /*virtual*/ void delete_elt_by_id(int pid)  override;
                     /*virtual*/ void update_elt_by_id(int pid)  override;
                     /*virtual*/ Contact *get_elt_by_email(string email) override;
                     /*virtual*/ Contact *get_elt_by_key(string key)  override;
                     /*virtual*/ vector<Contact*> get_list_elts_by_keys(vector<string> keys)  override;
                     /*virtual*/ Contact *get_elt_by_id(int pid) override;
                     /*virtual*/ vector<Contact*> get_list_elts_by_last_name(string lastname) override;
                     /*virtual*/ vector<Contact*> get_list_elts_by_zip_code(int zip_code) override;
                     /*virtual*/ vector<Contact*> get_list_elts_by_department(int departement) override;
                     /*virtual*/ vector<Contact*> get_list_elts_by_town(string town) override;
                     /*virtual*/ void display()  override;
                     /*virtual*/ void display(vector<Contact *> vects) override;
                     /*virtual*/ int size_list()  override;
                     /*virtual*/ bool check_elt_by_key(string key)  override;
                     /*virtual*/ string build_key(Contact *contact)  override;
                     void print_contact_professionnel(ContactProfessionel *contact_prof );
                     void print_contact_prive(ContactPrive *contact_prive );
                     void load_annuaire_from_files(string fileContactPrivate, string fileContactPro);
                     void buildContactPro(string fileContactPro);
                     void buildContactPrive(string fileContactPro);
                     DateNaissance *build(string dat);
                     int get_next_pid();
       };
}
#endif // MAGASIN_H_FILE
