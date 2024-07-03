#include "RoadBuilding.hpp"
#include <iostream>

BuildingRoadsCard::BuildingRoadsCard() {}

void BuildingRoadsCard::play(Player& player) {
    std::cout << "Playing Building Roads card." << std::endl;
}

std::string BuildingRoadsCard::getType() const {
    return "Building Roads";
}