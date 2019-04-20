#include <iostream>
#include <list>
#include "board.hpp"

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{

}

void Graph::addVertex(int name, tile* tile1, tile* tile2, tile* tile3, tile* tile4)
{
   vertex newVertex;
   newVertex.name = name;
   newVertex.tile1 = tile1;
   newVertex.tile2 = tile2;
   newVertex.tile3 = tile3;
   newVertex.tile4 = tile4;
   newVertex.settlement = false;
   vertices.push_back(newVertex);
}
void Graph::addEdge(int vertex1, int vertex2)
{
   if(vertex1 <25 && vertex2 <25)
   {
      Edge newEdge;
      for(int i =0; i<=vertices.size(); ++i)
      {
         if(vertex1 == vertices[i].name)
         {
            newEdge.v1 = &vertices[i];
         }
      }
      for(int i =0; i<=vertices.size(); ++i)
      {
         if(vertex2 == vertices[i].name)
         {
            newEdge.v2 = &vertices[i];
         }
      }
      for(int i =0; i<=vertices.size(); ++i)
      {
         if(vertices[i].name == vertex1)
         {
            vertices[i].Edges.push_back(newEdge);
         }
      }
      for(int i =0; i<=vertices.size(); ++i)
      {
         if(vertices[i].name == vertex2)
         {
            vertices[i].Edges.push_back(newEdge);
         }
      }
   }
   else
   {
      cout << "Not in the board" << endl;
   }
}
void Graph::addTile(tile newTile)
{
   tiles.push_back(newTile);
}
tile* Graph::getTile(int index)
{
   return &tiles[index];
}
bool Graph::isEdge(int vertex1, int vertex2)
{
   for(int i=0;i<vertices.size(); ++i)
   {
      vertex current = vertices[i];
      for(int j=0; j<current.Edges.size(); ++j)
      {
         if(current.Edges[j].v1->name == vertex1 && current.Edges[j].v2->name == vertex2)
         {
            return true;
         }
         else if(current.Edges[j].v1->name == vertex2 && current.Edges[j].v2->name == vertex1)
         {
            return true;
         }
      }
   }
   return false;
}
bool Graph::isPlayerVertex(player play, int ver)
{
   for(int i=0; i<vertices.size(); ++i)
   {
      if(vertices[i].name == ver && vertices[i].p == play.name)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
}
bool Graph::isSettlement(int vertex)
{
   for(int i=0; i<25; ++i)
   {
      if(vertices[i].name == vertex)
      {
         if(vertices[i].settlement == true)
         {
            return true;
         }
         else
         {
            return false;
         }
      }
   }
}
void Graph::displayEdges()
{
   for(int i =0; i<vertices.size(); ++i)
   {
      vertex current = vertices[i];
      cout << current.name << ": ";
      for(int j =0; j<current.Edges.size(); ++j)
      {
         cout << current.Edges[j].v1->name << "--" << current.Edges[j].v2->name << "    ";
      }
      cout << endl;
   }
}
void Graph::setAllVerticesUnvisited()
{
   for(int i =0; i<vertices.size(); ++i)
   {
      vertices[i].visited = false;
   }
}
void Graph::buildSettlement(player* x, int vertex)
{
   for(int i=0; i<25; ++i)
   {
      if(vertices[i].name == vertex)
      {
         vertices[i].p = x->name;
         vertices[i].settlement = true;
      }
   }
}


vertex *Graph::findVertex(int name)
{
   for(int i=0; i<=vertices.size(); ++i)
   {
      if(name == vertices[i].name)
      {
         return &vertices[i];
      }
   }
}

void Graph::displayBoard()
{
   for(int i=0; i<vertices.size(); ++i)
   {
      cout << vertices[i].name;
   }
}

void Graph::displayTiles()
{
   for(int i=0; i<4; ++i)
   {
      for(int j=0; j<4; ++j)
      {
         cout << tiles[(4*i) + j].type << "(" << tiles[(4*i) + j].value << ")" << "---";
      }
      cout << endl;
   }
}
