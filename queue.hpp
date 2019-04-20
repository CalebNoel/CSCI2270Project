#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "board.hpp"
using namespace std;


struct node
{
   string name;
   int value;
   tile t;
   node *next;
};

class queue
{
   private:
      node *head;
   public:
      queue();
      void enqueue(string, int, tile);
      node* pop();
      void print_queue();
};
#endif
