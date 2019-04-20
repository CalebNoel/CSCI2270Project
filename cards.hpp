#ifndef CARDS_HPP
#define CARDS_HPP

#include <iostream>
using namespace std;

class cards
{
   private:
      string name;
      int type;

   public:
      cards();
      int get_type();
      string get_name();

};

#endif
