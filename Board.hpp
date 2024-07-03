#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Tile.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Player.hpp"  
#include "DevelopmentCard.hpp"
#include "ResourceType.hpp"

// Forward declaration of Player class
class Player;
class Edge;
class DevelopmentCard;
class Tile;

using namespace std;

class Board {
public:
    // Constructor to initialize the board
    Board(Player &player1, Player &player2, Player &player3);

    // Getters for plots and vertices
    const vector<Tile>& getTiles() const;

    vector<Vertex>& getVertices();

    // Function to print the board configuration
    void printBoard() const;

    // Function to check if a settlement can be placed on a vertex
    bool canPlaceSettlement(Player &player, size_t vertexIndex);

    // Function to check if a road can be placed between two vertices
    bool canPlaceRoad(int playerId, size_t vertexIndex1, size_t vertexIndex2);

    // Function to check if a city can be placed on a vertex
    bool canPlaceCity(int playerId, size_t vertexIndex);

    // Function to get the edge between two vertices
    int getEdge(size_t vertexIndex1, size_t vertexIndex2);

    // function to check if a player can place his initial settlements
    bool canPlaceInitialSettlementAndRoad(Player& player, size_t vertexIndex, size_t vertexIndex2);

    // Function to give resources to the players based on the dice roll!
    void giveResources(int diceResult);

    // Vector to hold the Development Cards
    vector<DevelopmentCard*> developmentCards;

    // Function to draw a random development card for a player
    void drawDevelopmentCard(int playerId);

    void initialPlacements();

    // int to hold the index of the player with the biggest army
    int biggestArmyIndex = -1;

    // int that holds the number of knights played by the player with the biggest army
    int biggestArmy = 2;

    void cleanup();

    // Vector to hold the players
    std::vector<Player*> players;

private:
    // Vector to hold the plots
    vector<Tile> tiles;

    // Vector to hold the vertices
    vector<Vertex> vertices;

    // Vector to hold the edges
    vector<Edge> edges;
};

#endif // BOARD_HPP