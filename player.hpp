#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include "cards.hpp"
using namespace std;

class player
{
   private:
      int vp;
      vector<cards> player_cards;
      int bricks;
      int wheat;
      int stone;
      int wood;
      int wool;

   public:
      string name;
      player();
      int get_vp();
      void add_vp(int);
      void print_resources();
      void print_dev();
      void add_card(cards);
      int use_card(int index);
      int card_count();

      void add_bricks(int i);
      int get_bricks();
      void add_wheat(int i);
      int get_wheat();
      void add_stone(int i);
      int get_stone();
      void add_wood(int i);
      int get_wood();
      void add_wool(int i);
      int get_wool();
};

#endif
