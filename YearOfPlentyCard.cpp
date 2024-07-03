#include "YearOfPlentyCard.hpp"
#include <iostream>
#include <map>


void YearOfPlentyCard::play(Player& player) {
    std::cout << "Playing Year of Plenty card." << std::endl;
    
    // Define a map from resource names to ResourceType
    std::map<std::string, ResourceType> resourceMap = {
        {"Wood", ResourceType::Wood},
        {"Brick", ResourceType::Brick},
        {"Wool", ResourceType::Wool},
        {"Oats", ResourceType::Oats},
        {"Iron", ResourceType::Iron}
    };

    std::string resource1, resource2;
    
    // Loop to get valid resource choices from player
    while (true) {
        std::cout << "Choose the first resource type (Wood, Brick, Wool, Oats, Iron): ";
        std::cin >> resource1;

        if (resourceMap.find(resource1) == resourceMap.end()) {
            std::cout << "Invalid resource type chosen. Please try again." << std::endl;
            continue;
        }

        std::cout << "Choose the second resource type (Wood, Brick, Wool, Oats, Iron): ";
        std::cin >> resource2;

        if (resourceMap.find(resource2) == resourceMap.end()) {
            std::cout << "Invalid resource type chosen. Please try again." << std::endl;
            continue;
        }

        // Add one of each chosen resource to the player
        player.addResource(static_cast<size_t>(resourceMap[resource1]), 1);
        player.addResource(static_cast<size_t>(resourceMap[resource2]), 1);

        std::cout << "Player " << player.getName() << " received 1 unit of " << resource1 << " and 1 unit of " << resource2 << "." << std::endl;
        break;
    }
}

std::string YearOfPlentyCard::getType() const {
    return "Year Of Plenty";
}
