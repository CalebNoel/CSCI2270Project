#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <algorithm>
#include "cards.hpp"
#include "player.hpp"
#include "board.hpp"
#include "queue.hpp"

using namespace std;

void main_menu()
{
   cout << "1) Start a new game" << endl;
   cout << "2) Queue up a song" << endl;
   cout << "3) Quit" << endl;
}
void create_edges(Graph* a)
{
   for(int i =0; i<25; i++)
   {
      if(i%5 != 0 && !a->isEdge(i, (i-1)))
      {
         a->addEdge(i, (i-1));
      }
      if((i+1)%5 != 0 && !a->isEdge(i, (i+1)))
      {
         a->addEdge(i, (i+1));
      }
      if(i>=5 && !a->isEdge(i, (i-5)))
      {
         a->addEdge(i, (i-5));
      }
      if(i<20 && !a->isEdge(i, (i+5)))
      {
         a->addEdge(i, (i+5));
      }
   }
}
Graph create_board()
{
   Graph a;

   tile z;
   z.name = -1;
   z.type = -1;
   z.value = -1;

   //Populates a queue with the tiles for the board
   int array[16] = {1,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5};
   random_shuffle(&array[0], &array[15]);
   queue q;
   for(int i=0; i<16; ++i)
   {
      q.enqueue("name", array[i], z);
   }
   //Populates queue with values of tiles
   int array2[16] = {2,3,4,5,5,6,6,7,7,8,8,9,9,10,11,12};
   random_shuffle(&array2[0], &array2[15]);
   queue q2;
   for(int i=0; i<16; ++i)
   {
      q2.enqueue("name", array2[i], z);
   }
   queue tile_stack;
   for(int i =0; i<16; ++i)
   {
      tile newTile;
      newTile.name = i;
      newTile.type = q.pop()->value;
      newTile.value = q2.pop()->value;
      tile_stack.enqueue("name", -1, newTile);
   }
   tile_stack.print_queue();

   for(int i =0; i<16; ++i)
   {
      a.addTile(tile_stack.pop()->t);
   }
   //Adds all tiles to board
   //Top row
   a.addVertex(0, &z, &z, &z, a.getTile(0));
   a.addVertex(1, &z, &z, a.getTile(0), a.getTile(1));
   a.addVertex(2, &z, &z, a.getTile(1), a.getTile(2));
   a.addVertex(3, &z, &z, a.getTile(2), a.getTile(3));
   a.addVertex(4, &z, &z, a.getTile(3), &z);
   //2nd row
   a.addVertex(5, &z, a.getTile(0), &z, a.getTile(4));
   a.addVertex(6, a.getTile(0), a.getTile(1), a.getTile(4), a.getTile(5));
   a.addVertex(7, a.getTile(1), a.getTile(2), a.getTile(5), a.getTile(6));
   a.addVertex(8, a.getTile(2), a.getTile(30), a.getTile(6), a.getTile(7));
   a.addVertex(9, a.getTile(3), &z, a.getTile(7), &z);
   //3rd row
   a.addVertex(10, &z, a.getTile(4), &z, a.getTile(8));
   a.addVertex(11, a.getTile(4), a.getTile(5), a.getTile(8), a.getTile(9));
   a.addVertex(12, a.getTile(5), a.getTile(6), a.getTile(9), a.getTile(10));
   a.addVertex(13, a.getTile(6), a.getTile(7), a.getTile(10), a.getTile(11));
   a.addVertex(14, a.getTile(7), &z, a.getTile(11), &z);
   //4th row
   a.addVertex(15, &z, a.getTile(8), &z, a.getTile(12));
   a.addVertex(16, a.getTile(8), a.getTile(9), a.getTile(12), a.getTile(12));
   a.addVertex(17, a.getTile(9), a.getTile(10), a.getTile(13), a.getTile(14));
   a.addVertex(18, a.getTile(10), a.getTile(11), a.getTile(14), a.getTile(15));
   a.addVertex(19, a.getTile(11), &z, a.getTile(15), &z);
   //5th row
   a.addVertex(20, &z, a.getTile(12), &z, &z);
   a.addVertex(21, a.getTile(12), a.getTile(13), &z, &z);
   a.addVertex(22, a.getTile(13), a.getTile(14), &z, &z);
   a.addVertex(23, a.getTile(14), a.getTile(15), &z, &z);
   a.addVertex(24, a.getTile(15), &z, &z, &z);

   create_edges(&a);
   return a;
}
int roll()
{
   int die1 = (rand() % 6) + 1;
   int die2 = (rand() % 6) + 1;
   int sum = die1 + die2;
   return sum;
}
bool game_over(int high_score, int score1, int score2, int score3, int score4)
{
   if(score1 > high_score)
   {
      high_score = score1;
   }
   if(score2 > high_score)
   {
      high_score = score2;
   }
   if(score3 > high_score)
   {
      high_score = score3;
   }
   if(score4 > high_score)
   {
      high_score = score4;
   }
   if(high_score > 10)
   {
      return true;
   }
   else
   {
      return false;
   }
}
void get_resources(Graph* a, int r, player* x)
{
   int wood_total = 0;
   int bricks_total = 0;
   int stone_total = 0;
   int wheat_total = 0;
   int wool_total = 0;
   for(int i=0; i<25; ++i)
   {
      if(a->findVertex(i)->tile1->value == r && a->findVertex(i)->p == x->name)
      {
         int type = (a->findVertex(i)->tile1->type);
         if(type ==1)
         {
            x->add_wood(1);
            ++wood_total;
         }
         if(type ==2)
         {
            x->add_bricks(1);
            ++bricks_total;
         }
         if(type ==3)
         {
            x->add_stone(1);
            ++stone_total;
         }
         if(type ==4)
         {
            x->add_wheat(1);
            ++wheat_total;
         }
         if(type ==5)
         {
            x->add_wool(1);
            ++wool_total;
         }
      }
      if(a->findVertex(i)->tile2->value == r && a->findVertex(i)->p == x->name)
      {
         int type = (a->findVertex(i)->tile2->type);
         if(type ==1)
         {
            x->add_wood(1);
            ++wood_total;
         }
         if(type ==2)
         {
            x->add_bricks(1);
            ++bricks_total;
         }
         if(type ==3)
         {
            x->add_stone(1);
            ++stone_total;
         }
         if(type ==4)
         {
            x->add_wheat(1);
            ++wheat_total;
         }
         if(type ==5)
         {
            x->add_wool(1);
            ++wool_total;
         }
      }
      if(a->findVertex(i)->tile3->value == r && a->findVertex(i)->p == x->name)
      {
         int type = (a->findVertex(i)->tile3->type);
         if(type ==1)
         {
            x->add_wood(1);
            ++wood_total;
         }
         if(type ==2)
         {
            x->add_bricks(1);
            ++bricks_total;
         }
         if(type ==3)
         {
            x->add_stone(1);
            ++stone_total;
         }
         if(type ==4)
         {
            x->add_wheat(1);
            ++wheat_total;
         }
         if(type ==5)
         {
            x->add_wool(1);
            ++wool_total;
         }
      }
      if(a->findVertex(i)->tile4->value == r && a->findVertex(i)->p == x->name)
      {
         int type = (a->findVertex(i)->tile4->type);
         if(type ==1)
         {
            x->add_wood(1);
            ++wood_total;
         }
         if(type ==2)
         {
            x->add_bricks(1);
            ++bricks_total;
         }
         if(type ==3)
         {
            x->add_stone(1);
            ++stone_total;
         }
         if(type ==4)
         {
            x->add_wheat(1);
            ++wheat_total;
         }
         if(type ==5)
         {
            x->add_wool(1);
            ++wool_total;
         }
      }
   }


   if(wood_total > 0)
   {
      cout << x->name <<" got " << wood_total << " wood" << endl;
   }
   if(bricks_total > 0)
   {
      cout << x->name <<" got " << bricks_total << " bricks" << endl;
   }
   if(stone_total > 0)
   {
      cout << x->name <<" got " << stone_total << " stone" << endl;
   }
   if(wheat_total > 0)
   {
      cout << x->name <<" got " << wheat_total << " wheat" << endl;
   }
   if(wool_total > 0)
   {
      cout << x->name <<" got " << wool_total << " wool" << endl;
   }
}

void turn_menu()
{
   cout << "1) View resources" << endl;
   cout << "2) View Development Cards" << endl;
   cout << "3) Use Development Card" << endl;
   cout << "4) Purchase Something" << endl;
   cout << "5) Pass" << endl;
}
void buy_menu()
{
   cout << "1) Buy settlement" << endl;
   cout << "2) Buy road" << endl;
   cout << "3) Buy city" << endl;
   cout << "4) Buy devlopment card" << endl;
   cout << "5) Leave" << endl;
}

void turn_helper(Graph* a, player* x)
{
   turn_menu();
   string choice = "1";

   while(choice == "1" || choice == "2")
   {
      getline(cin, choice);
      switch(stoi(choice))
      {
         case 1:
         {
            x->print_resources();
            break;
         }
         case 2:
         {
            x->print_dev();
            break;
         }
         case 3:
         {
            cout << "Choose a card" << endl;
            string input;
            getline(cin, input);
            if(stoi(input) <= x->card_count()-1)
            {
               int type = x->use_card(stoi(input));
               //TODO
               //Implement Action
            }
            else
            {
               cout << "Invalid input" << endl;
               turn_helper(a, x);
            }
         }
         case 4:
         {
            buy_menu();
            string input;
            getline(cin, input);
            switch (stoi(choice))
            {
               case 1:
               {
                  //if(x->)
               }
               case 2:
               {

               }
               case 3:
               {

               }
               case 4:
               {

               }
               case 5:
               {
                  turn_helper(a, x);
               }
            }

         }
         case 5:
         {

         }
         default:
         {

         }
      }
   }
}

void turn(Graph* a, player* x, player* other1, player* other2, player* other3)
{
   int r=roll();

   cout << "Its " << x->name << "'s turn!" << endl;
   cout << x->name << " rolled a " << r << endl << endl;

   get_resources(a, r, x);
   get_resources(a, r, other1);
   get_resources(a, r, other2);
   get_resources(a, r, other3);

   turn_helper(a, x);
}
void start_game(Graph* a, player* player1, player* player2, player* player3, player* player4)
{
   string input;
   bool finished = true;

   cout << "Its player1's turn!" << endl;
   cout << "Choose a starting settlement: " << endl;
   getline(cin, input);

   a->buildSettlement(player1, stoi(input));
   if(a->isSettlement(stoi(input)))
   {
      cout << "Settlement built!" << endl << endl;
   }
   else
   {
      cout << "Failed" << endl << endl;
   }

   cout << "Its player2's turn!" << endl;
   while(finished)
   {
      cout << "Choose a starting settlement: " << endl;
      getline(cin, input);
      if(!a->isSettlement(stoi(input)))
      {
         a->buildSettlement(player2, stoi(input));
         if(a->isSettlement(stoi(input)))
         {
            cout << "Settlement built!" << endl << endl;
         }
         else
         {
            cout << "Failed" << endl << endl;
         }
         break;
      }
      else
      {
         cout << "That spot is already taken" << endl;
      }
   }
   cout << "Its player3's turn!" << endl;
   while(finished)
   {
      cout << "Choose a starting settlement: " << endl;
      getline(cin, input);
      if(!a->isSettlement(stoi(input)))
      {
         a->buildSettlement(player3, stoi(input));
         if(a->isSettlement(stoi(input)))
         {
            cout << "Settlement built!" << endl << endl;
         }
         else
         {
            cout << "Failed" << endl << endl;
         }
         break;
      }
      else
      {
         cout << "That spot is already taken" << endl;
      }
   }
   cout << "Its player4's turn!" << endl;
   while(finished)
   {
      cout << "Choose a starting settlement: " << endl;
      getline(cin, input);
      if(!a->isSettlement(stoi(input)))
      {
         a->buildSettlement(player4, stoi(input));
         if(a->isSettlement(stoi(input)))
         {
            cout << "Settlement built!" << endl << endl;
         }
         else
         {
            cout << "Failed" << endl << endl;
         }
         break;
      }
      else
      {
         cout << "That spot is already taken" << endl;
      }
   }

}


int main()
{
   srand(time(0));
   cout << "*-------------------------*" << endl;
   cout << "    SETTLERS OF CATAN" << endl;
   cout << "*-------------------------*" << endl << endl << endl;

   main_menu();

   string choice = "0";

   while(choice != "3")
   {
      getline(cin, choice);
      switch(stoi(choice))
      {
         case 1:
         {
            player player1;
            player player2;
            player player3;
            player player4;
            player1.name = "player1";
            player2.name = "player2";
            player3.name = "player3";
            player4.name = "player4";

            Graph a = create_board();
            a.displayEdges();
            a.displayTiles();
            int high_score = 0;

            start_game(&a, &player1, &player2, &player3, &player4);

            while(high_score < 10)
            {
               turn(&a, &player1, &player2, &player3, &player4);
               if(game_over(high_score, player1.get_vp(), player2.get_vp(), player3.get_vp(), player4.get_vp()) == true)
               {
                  break;
               }
               turn(&a, &player2, &player1, &player3, &player4);
               if(game_over(high_score, player1.get_vp(), player2.get_vp(), player3.get_vp(), player4.get_vp()) == true)
               {
                  break;
               }
               turn(&a, &player3, &player1, &player2, &player4);
               if(game_over(high_score, player1.get_vp(), player2.get_vp(), player3.get_vp(), player4.get_vp()) == true)
               {
                  break;
               }
               turn(&a, &player4, &player1, &player2, &player3);
               if(game_over(high_score, player1.get_vp(), player2.get_vp(), player3.get_vp(), player4.get_vp()) == true)
               {
                  break;
               }
               high_score = 11;
            }
            int score1 = player1.get_vp();
            int score2 = player2.get_vp();
            int score3 = player3.get_vp();
            int score4 = player4.get_vp();
            if(score1 > score2 && score1 > score3 && score1 > score4)
            {
               cout << "Player 1 won, congratulations!" << endl;
            }
            else if(score2 > score1 && score2 > score3 && score2 > score4)
            {
               cout << "Player 2 won, congratulations!" << endl;
            }
            else if(score3 > score1 && score3 > score2 && score3 > score4)
            {
               cout << "Player 3 won, congratulations!" << endl;
            }
            else if(score4 > score1 && score1 > score2 && score1 > score3)
            {
               cout << "Player 4 won, congratulations!" << endl;
            }
            break;
         }
         case 2:
         {
            cout << "--------" << endl;
            cout << " Music" << endl;
            cout << "--------" << endl;
            string input;
            cout << "Please enter a filename" << endl;
            getline(cin, input);

            string command = "afplay " + input;
            system(command.c_str());
            break;
         }
         case 3:
         {
            cout << "Thanks for playing" << endl;
            break;
         }
         default:
         {
            cout << "Please enter a valid input" << endl;
            break;
         }
      }
   }

}
