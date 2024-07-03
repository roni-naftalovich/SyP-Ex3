// VictoryPointCard.cpp
#include "VictoryCard.hpp"
#include <iostream>

void VictoryCard::play(Player& player) {
    std::cout << player.getName() << " played a Victory Point card." << std::endl;
    player.addVictoryPoint();
}

std::string VictoryCard::getType() const {
    return "Victory Point";
}