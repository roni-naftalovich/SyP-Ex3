#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include "Vertex.hpp"
#include "DevelopmentCard.hpp"
#include "Edge.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "ResourceType.hpp"


// Forward declaration of Board class
class Board;
class DevelopmentCard;

using namespace std;

class Player
{
public:
    Player(const string &name);
    int getSeqNum() const;
    const string &getName() const;
    
    void canBuyDevelopmentCard();
    bool canbuySettlement();
    bool canbuyCity();
    bool canbuyRoad();

    //void placeInitialSettlementAndRoad(int vertexIndex, int vertexIndex2, Board &board);
    void placeSettlement(int vertexIndex, Board &board);
    void upgradeToCity(int vertexIndex, Board &board);
    void placeRoad(int vertexIndex1, int vertexIndex2, Board &board);
    

    // void getSettlements(Board &board) const;
    // void getCities(Board &board) const;

    // void getResources() const;
    void addResource(size_t type, int amount);
    
    void addSettlement(int vertexIndex);
    void addRoad(int newRoads);

    void rollDice(Board &board);

    void chooseDevelopmentCard(Board &board);
    // Vector to hold the development cards
    vector<DevelopmentCard*> developmentCards;
    // Function to trade resources with other players
    void tradeResources(Board &board, int player, string resource1, int amount, string resource2, int amount2);
    void addKnightCard();
    int getKnightCards();
    void addDevelopmentCard(DevelopmentCard* card);
    void playDevelopmentCard( Board &board);
    int getVictoryPoints() const;
    void addVictoryPoint();
    void showResources() const;

    void checkWinner();

    // Function to discard half of the resources of a player
    void discardResources(Board &board);

    // get the resources amount
    int getResourceAmaount(size_t type);

    void setResourceAmaount(size_t type, int amount);

    void endTurn();

    void cleanUp();

private:
    //Vector to store the player's resources
    vector<int> resources;
    // Key to get the winner of the game
    int winner;
    // The sequence number of the player
    int seqNum;
    // Name of the player
    string name;
    // Number of points the player has
    int points;
    // Vector to hold the settlements
    vector<int> settlements;
    // Vector to hold the cities
    vector<int> cities;
    // Vector to hold the roads
    vector<int> roads;
    // counter to the development cards
    int developmentCardCount = 0;
    // flag to make sure player rolled the dice in his turn
    bool hasRolledDice;

    // int to keep track of the number of development cards
    static int nextSeqNum;
    static int currentTurn;
    int knightCardsCount;
    //std::vector<DevelopmentCard*> developmentCards;
};

#endif // PLAYER_HPP