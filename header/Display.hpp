
#ifndef DISPLAY_H_FILE
#define DISPLAY_H_FILE

#include "ContactProfessionel.hpp"
#include "ContactPrive.hpp"
#include "Contact.hpp"
#include <map>

using namespace Heritage;

namespace Manage
{
       class Display
       {
       public:
              Display() {}
              ~Display() {}
              void print_contact_professionnel(ContactProfessionel *contact_prof);
              void print_contact_prive(ContactPrive *contact_prive);
              void display(vector<Contact *> vects);
              void display(map<string, Contact *> map_annuaire, int mode);
       };
}

#endif // DISPLAY_H_FILE
