#ifndef TOOLS_H_FILE
#define TOOLS_H_FILE

#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace MapTools
{
       template<class U, class T, class V>
       class Tools
       {
              protected:
                     map<U, V*> map_annuaire;

              public:
                     Tools(){};
                     virtual~Tools(){}
                     virtual void add_new_elt(V *v) = 0;
                     virtual void delete_elt_by_key(U u) = 0;
                     virtual void delete_elt_by_id(T t) = 0;
                     virtual void update_elt_by_id(T t) = 0;
                     virtual V *get_elt_by_key(U u) = 0;
                     virtual V *get_elt_by_id(T t) = 0;
                     virtual V *get_elt_by_email(U email) = 0;
                     virtual vector<V*> get_list_elts_by_last_name(U lastname) = 0;
                     virtual vector<V*> get_list_elts_by_first_name(U firstname) = 0;
                     virtual vector<V*> get_list_elts_by_zip_code(T t) = 0;
                     virtual vector<V*> get_list_elts_by_department(T departement) = 0;
                     virtual vector<V*> get_list_elts_by_town(U town) = 0;
                     virtual vector<V*> get_list_elts_by_keys(vector<U> keys) = 0;
                     virtual void display() = 0;
                     virtual void display(vector<V*> vects) = 0;
                     virtual int size_list() = 0;
                     virtual bool check_elt_by_key(U u) = 0;
                     virtual U build_key(V *v) = 0;
       };
}

#endif // TOOLS_H_FILE
