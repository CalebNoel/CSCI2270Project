#include <iostream>
#include <vector>
#include "player.hpp"
#include "cards.hpp"
using namespace std;

player::player()
{
   vp = 0;
   bricks = 0;
   wheat = 0;
   stone = 0;
   wood = 0;
   wool = 0;
}
int player::get_vp()
{
   return vp;
}
void player::add_vp(int a)
{
   vp+= a;
}
void player::print_resources()
{
   cout << "You have " << bricks << "brick[s]" << endl;
   cout << "You have " << stone << "stone" << endl;
   cout << "You have " << wheat << "wheat" << endl;
   cout << "You have " << wood << "wood" << endl;
   cout << "You have " << wool << "wool" << endl;
}
void player::print_dev()
{
   for(int i=0; i<player_cards.size(); ++i)
   {
      cout << i << ") " << player_cards[i].get_name() << endl;
   }
}
void player::add_card(cards a)
{
   player_cards.push_back(a);
}
int player::use_card(int index)
{
   int type = player_cards[index].get_type();
   player_cards.erase(player_cards.begin()+index);
   return type;
}
int player::card_count()
{
   return player_cards.size();
}

void player::add_bricks(int i)
{
   bricks = bricks + i;
}
int player::get_bricks()
{
   return bricks;
}
void player::add_wheat(int i)
{
   wheat = wheat = i;
}
int player::get_wheat()
{
   return wheat;
}
void player::add_stone(int i)
{
   stone = stone + i;
}
int player::get_stone()
{
   return stone;
}
void player::add_wood(int i)
{
   wood = wood + i;
}
int player::get_wood()
{
   return wood;
}
void player::add_wool(int i)
{
   wool = wool + i;
}
int player::get_wool()
{
   return wool;
}
