#include <iostream>
#include "queue.hpp"
using namespace std;

queue::queue()
{
   head = NULL;
}

void queue::enqueue(string name, int value, tile t)
{
   node* newNode = new node;
   newNode->name = name;
   newNode->value = value;
   newNode->next = NULL;
   newNode->t = t;

   if(head == NULL)
   {
      head = newNode;
   }
   else
   {
      node* current = head;
      while(current->next != NULL)
      {
         current = current->next;
      }
      current->next = newNode;
   }
}
node* queue::pop()
{
   node* temp = head;
   head = head->next;
   return temp;
}

void queue::print_queue()
{
   node* current = head;
   while(current->next != NULL)
   {
      cout << current->t.name << ": " << current->t.type << "(" << current->t.value << ")" << endl;
      current = current->next;
   }
   cout << current->t.name << ": " << current->t.type << "(" << current->t.value << ")" << endl;
}
