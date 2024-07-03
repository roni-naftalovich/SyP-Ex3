// Roni Naftalovich 319049060, roni100400100400@gmail.com
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Tile.hpp"
#include "Board.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Player.hpp"  
#include "DevelopmentCard.hpp"
#include "ResourceType.hpp"
#include "VictoryCard.hpp"
#include "KnightCard.hpp"
#include "Monopoly.hpp"
#include "YearOfPlentyCard.hpp"
using namespace std;

int main()
{
        Player p1("Amit");
        Player p2("Yossi");
        Player p3("Dana");
        Board catan(p1, p2, p3);
        catan.initialPlacements();

        // Example of initial resource distribution after placing settlements and roads
        // This part depends on how your resource allocation is handled
        p1.showResources();
        p2.showResources();
        p3.showResources();
        p1.rollDice(catan);
        p1.tradeResources(catan, 2 , "Oats", 1, "Wood", 1); // p1 wants to trades 1 wood for 1 brick with p2.
        p1.placeRoad(5, 4, catan); 
        p1.endTurn(); // p1 ends his turn.

        p2.rollDice(catan);
        p2.endTurn();

        p3.rollDice(catan);
        p3.endTurn(); // p3 ends his turn.

        try
        {
            p2.rollDice(catan); // p2 tries to roll the dice again, but it's not his turn.
        }
        catch (const std::exception &e)
        {
            cout << e.what() << endl;
        }

        p1.rollDice(catan);
        p1.chooseDevelopmentCard(catan);
        p1.playDevelopmentCard(catan);
        p1.endTurn(); // p1 ends his turn.

        p2.rollDice(catan); 
        p2.tradeResources(catan, 1 , "Wool", 1, "Brick", 1);
        p2.playDevelopmentCard(catan);
        p2.endTurn(); // p2 ends his turn.

        cout << "Player " << p1.getName() << " has " << p1.getVictoryPoints() << " points" << endl; // p1 has 2 points because it has two settlements.
        cout << "Player " << p2.getName() << " has " << p2.getVictoryPoints() << " points" << endl; // p2 has 3 points because it has two settlements and a bonus points card.
        cout << "Player " << p3.getName() << " has " << p3.getVictoryPoints() << " points" << endl; // p3 has 2 points because it has two settlements.

        p3.rollDice(catan);
        p3.endTurn();

        p1.rollDice(catan);
        p1.endTurn();

        p2.rollDice(catan);
        p2.endTurn();

        p3.rollDice(catan);
        p3.showResources();
        p3.placeRoad(15, 25, catan);
        p3.endTurn();

        p1.rollDice(catan);
        p1.placeRoad(3,4,catan);
        p1.endTurn();

        p2.rollDice(catan);
        p2.endTurn();

        p3.rollDice(catan);
        p3.tradeResources(catan , 1 , "Wool", 1, "Oats", 1);
        p3.placeSettlement(25, catan);
        p3.endTurn();

        catan.cleanup();
    


    return 0;
}
