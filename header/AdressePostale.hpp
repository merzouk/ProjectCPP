#ifndef ADR_PST_H_FILE
#define ADR_PST_H_FILE
#include <iostream>

using namespace std;

namespace Heritage
{

       class AdressePostale
       {
       private:
              int numero;
              int code_postale;
              string rue;
              string complement;
              string ville;

       public:
              AdressePostale(int numero, string rue, string complement, int code_postale, string ville)
              {
                     this->numero = numero;
                     this->rue = rue;
                     this->complement = complement;
                     this->ville = ville;
                     this->code_postale = code_postale;
              }

              ~AdressePostale() {}

              int get_numero() { return this->numero; }
              int get_code_postale() { return this->code_postale; }
              string get_rue() { return this->rue; }
              string get_complement() { return this->complement; }
              string get_ville() { return this->ville; }

              void set_numero(int numero) { this->numero = numero; }
              void set_code_postale(int) { this->code_postale = code_postale; }
              void set_rue(string rue) { this->rue = rue; }
              void set_complement(string complement) { this->complement = complement; }
              void set_ville(string ville) { this->ville = ville; }
              void infos();
       };
}

#endif // ADR_PST_H_FILE
