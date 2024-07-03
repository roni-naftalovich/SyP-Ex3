// Monopoly.cpp
// Roni Naftalovich 319049060, roni100400100400@gmail.com
#include "Monopoly.hpp"
#include "Edge.hpp"
#include "Player.hpp"  
#include "DevelopmentCard.hpp"
#include "Board.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

class Player;
class Board;


Monopoly::Monopoly() {}

void Monopoly::play(Player& player) {
    std::cout << player.getName() << " played a Monopoly card." << std::endl;
}

std::string Monopoly::getType() const {
    return "Monopoly";
}
