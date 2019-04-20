#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <iostream>
#include "player.hpp"

struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */

struct Edge
{
    vertex *v1;
    vertex *v2;
    bool road;
    string player;
};
struct tile
{
   int name;
   int type;
   int value;
};

/*this is the struct for each vertex in the graph. */
struct vertex
{
    int name;
    int value;
    bool settlement;
    bool city;
    tile* tile1; //Top left corner
    tile* tile2; //Top right corner
    tile* tile3; //Bottom left corner
    tile* tile4; //Bottom right corner
    string p;
    bool visited;
    std::vector<Edge> Edges; //stores edges to adjacent vertices
};

class Graph
{
  public:
    Graph();
    ~Graph();
    void addVertex(int name, tile* tile1, tile* tile2, tile* tile3, tile* tile4);
    void addEdge(int vertex1, int vertex2);
    void addTile(tile);
    tile *getTile(int index);
    bool isEdge(int vertex1, int vertex2);
    bool isPlayerVertex(player, int name);
    bool isSettlement(int vertex);
    void displayEdges();
    void setAllVerticesUnvisited();
    void buildSettlement(player*, int vertex);
    void displayTiles();

    vertex *findVertex(int name);

    void displayBoard();

  private:
    std::vector<vertex> vertices; //stores vertices
    std::vector<tile> tiles;

};

#endif // GRAPH_HPP
