#include "../header/DataAccessObject.hpp"



namespace Manage
{

                      void DataAccessObject::add_new_elt(Contact *contact)  {  };
                      void DataAccessObject::delete_elt_by_key(string key)  {  };
                      void DataAccessObject::delete_elt_by_id(int pid)  {  };
                      void DataAccessObject::update_elt_by_id(int pid)  {  };
                      Contact *DataAccessObject::get_elt_by_email(string email) { return nullptr; };
                      Contact *DataAccessObject::get_elt_by_key(string key)  { return nullptr; };
                      vector<Contact*> DataAccessObject::get_list_elts_by_keys(vector<string> keys)  { return nullptr; };
                      Contact *DataAccessObject::get_elt_by_id(int pid) { return nullptr; };
                      vector<Contact*> DataAccessObject::get_list_elts_by_last_name(string lastname) { return nullptr; };
                      vector<Contact*> DataAccessObject::get_list_elts_by_first_name(string firstname) { return nullptr; };
                      vector<Contact*> DataAccessObject::get_list_elts_by_zip_code(int zip_code) { return nullptr; };
                      vector<Contact*> DataAccessObject::get_list_elts_by_department(int departement) { return nullptr; };
                      vector<Contact*> DataAccessObject::get_list_elts_by_town(string town) {  return nullptr:};

                      int DataAccessObject::size_list()  { return 0; };
                      bool DataAccessObject::check_elt_by_key(string key)  { return true; };
                      string DataAccessObject::build_key(Contact *contact)  { return ""; };

                     void DataAccessObject::load_annuaire_from_files(string fileContactPrivate, string fileContactPro) {  };
                     void DataAccessObject::buildContactPro(string fileContactPro)  {  };
                     void DataAccessObject::buildContactPrive(string fileContactPro)  {  };
                     DateNaissance *DataAccessObject::build_date_naissance(string date_naissance_str)  { return nullptr; };
                     map<string, Contact*> DataAccessObject::get_map_annuaire()  { return nullptr; };

                     int DataAccessObject::get_next_pid()  { return 0; };
}
