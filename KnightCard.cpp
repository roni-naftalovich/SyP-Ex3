// KnightCard.cpp
// Roni Naftalovich 319049060, roni100400100400@gmail.com
#include "KnightCard.hpp"
#include <iostream>

void KnightCard::play(Player& player) {
    std::cout << player.getName() << " played a Knight card." << std::endl;
    player.addKnightCard();
    if(player.getKnightCards() == 3){
        player.addVictoryPoint();
        player.addVictoryPoint();
    }
}

std::string KnightCard::getType() const {
    return "Knight";
}
