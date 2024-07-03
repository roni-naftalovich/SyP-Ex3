#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Board.hpp"
#include "Player.hpp"
#include "DevelopmentCard.hpp"
#include "KnightCard.hpp"
#include "Monopoly.hpp"
#include "VictoryCard.hpp"
#include "YearOfPlentyCard.hpp"
#include <iostream>
#include <cassert>
#include <sstream>

class Player;
class Board;

Player p1("Amit");
Player p2("Yossi");
Player p3("Dana");
Board board(p1, p2, p3);

TEST_CASE("discardResources") {
    p1.addResource(static_cast<size_t>(ResourceType::Oats), 10);
    p1.addResource(static_cast<size_t>(ResourceType::Wool), 10);
    p1.addResource(static_cast<size_t>(ResourceType::Brick),10);
    p1.addResource(static_cast<size_t>(ResourceType::Wood), 10);
    p1.addResource(static_cast<size_t>(ResourceType::Iron), 10);
    p2.addResource(static_cast<size_t>(ResourceType::Oats), 10);
    p2.addResource(static_cast<size_t>(ResourceType::Wool), 10);
    p2.addResource(static_cast<size_t>(ResourceType::Brick), 10);
    p2.addResource(static_cast<size_t>(ResourceType::Wood), 10);
    p2.addResource(static_cast<size_t>(ResourceType::Iron), 10);
    p3.addResource(static_cast<size_t>(ResourceType::Oats), 10);
    p3.addResource(static_cast<size_t>(ResourceType::Wool), 10);
    p3.addResource(static_cast<size_t>(ResourceType::Brick), 10);
    p3.addResource(static_cast<size_t>(ResourceType::Wood), 10);
    p3.addResource(static_cast<size_t>(ResourceType::Iron), 10);
    board.initialPlacements(); 
    // place p1 initial on vertex 9 -8 and 30-31
    // place p2 initial on vertex 36-37, 42-43
    // place p3 on vertex 14-15, 38-39
    p1.rollDice(board);
    //Try to place road on valid edge
    CHECK(p1.getResourceAmaount(ResourceType::Wood) == 6);
    CHECK(p1.getResourceAmaount(ResourceType::Brick) == 5);
    CHECK(p1.getResourceAmaount(ResourceType::Wool) == 5);
    CHECK(p1.getResourceAmaount(ResourceType::Oats) == 6);
    CHECK(p1.getResourceAmaount(ResourceType::Iron) == 12);
}

TEST_CASE("Place settlement") {

    p1.placeRoad(8, 0, board);

    // Try to place a settlement on a valid vertex
    p1.placeSettlement(0, board);
    CHECK(board.getVertices()[0].getOwner() == p1.getSeqNum());
    p1.endTurn();
    p2.rollDice(board);
    // P2 try to place a settlement on vertex 0 where p1 alredy has settled.
    p2.placeSettlement(0, board);
    CHECK(board.getVertices()[0].getOwner() == p1.getSeqNum());
    p2.endTurn();
}
    

TEST_CASE("upgradeToCity") {
    p3.rollDice(board); 
    p3.endTurn(); 

    p1.showResources();
    
    p1.rollDice(board);
    //Upgrade settlement to city
    p1.upgradeToCity(0, board);

    CHECK(p1.getVictoryPoints() == 4);  // Verify points increased
    CHECK(board.getVertices()[0].getIsCity() == true);  // Verify city status
    p1.endTurn();
}



TEST_CASE("canPlaceRoad") {
    p2.rollDice(board);

    // Test canPlaceRoad with various conditions
    SUBCASE("Invalid road placement on a self-owned edge") {
        CHECK(board.canPlaceRoad(p2.getSeqNum(), 36, 37) == false);
    }

    SUBCASE("Invalid road placement on an already occupied road") {
        CHECK(board.canPlaceRoad(p2.getSeqNum(), 9, 8) == false);
    }

    SUBCASE("Invalid road placement between non-neighbor vertices") {
        CHECK(board.canPlaceRoad(p2.getSeqNum(), 6, 11) == false);
    }

    SUBCASE("Valid road placement extending from an owned road") {
        CHECK(board.canPlaceRoad(p2.getSeqNum(), 37, 26) == true);
    }
    board.cleanup();
}



// void testCanPlaceRoad()
// {
//     // Create players
//     Player p1("Amit");
//     Player p2("Yossi");
//     Player p3("Dana");

//     // Create a board
//     Board board(p1, p2, p3);

//     // Initialize the vertices and edges in the board
//     // This setup depends on your game's rules and board initialization logic
//     // Example initialization:
//     // board.initVerticesAndEdges(); // Assume this function initializes the vertices and edges

//     // Test case 1: Valid road placement between two neighboring vertices
//     size_t v1 = 0;
//     size_t v2 = 1;
//     // Set up neighbors and ensure they are adjacent
//     board.vertices[v1].addNeighbor(board.vertices[v2]);
//     board.vertices[v2].addNeighbor(board.vertices[v1]);
//     board.vertices[v1].addEdge(board.edges[0]);
//     board.vertices[v2].addEdge(board.edges[0]);

//     assert(board.canPlaceRoad(p1.getSeqNum(), v1, v2) == true);
//     std::cout << "Test case 1 passed." << std::endl;

//     // Test case 2: Invalid road placement with non-neighboring vertices
//     size_t v3 = 2;
//     size_t v4 = 3;
//     // Ensure v3 and v4 are not neighbors
//     assert(board.canPlaceRoad(p1.getSeqNum(), v3, v4) == false);
//     std::cout << "Test case 2 passed." << std::endl;

//     // Test case 3: Road placement where the road is already occupied
//     board.edges[0].setOwner(p2.getSeqNum());
//     assert(board.canPlaceRoad(p1.getSeqNum(), v1, v2) == false);
//     std::cout << "Test case 3 passed." << std::endl;

//     // Reset the owner for further tests
//     board.edges[0].setOwner(-1);

//     // Test case 4: Player has a settlement on one of the vertices
//     board.vertices[v1].setOwner(p1);
//     assert(board.canPlaceRoad(p1.getSeqNum(), v1, v2) == true);
//     std::cout << "Test case 4 passed." << std::endl;

//     // Test case 5: Player has an adjacent road
//     board.vertices[v1].setOwner(-1); // Remove settlement owner
//     board.edges[1].setOwner(p1.getSeqNum()); // Set ownership of an adjacent road
//     board.vertices[v1].addEdge(board.edges[1]);
//     assert(board.canPlaceRoad(p1.getSeqNum(), v1, v2) == true);
//     std::cout << "Test case 5 passed." << std::endl;

//     // Test case 6: Edge case with invalid vertex indices
//     assert(board.canPlaceRoad(p1.getSeqNum(), -1, v2) == false);
//     assert(board.canPlaceRoad(p1.getSeqNum(), v1, 100) == false);
//     std::cout << "Test case 6 passed." << std::endl;

//     // Test case 7: Edge case where both vertices are the same
//     assert(board.canPlaceRoad(p1.getSeqNum(), v1, v1) == false);
//     std::cout << "Test case 7 passed." << std::endl;
// }

// int main()
// {
//     // Run the test suite
//     testCanPlaceRoad();

//     std::cout << "All test cases passed." << std::endl;
//     return 0;
// }
