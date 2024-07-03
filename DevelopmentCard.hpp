// DevelopmentCard.hpp
#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>
#include "Player.hpp"
#include "Tile.hpp"
#include "Vertex.hpp"
#include "Edge.hpp" 

class Player;

class DevelopmentCard {
public:
    virtual ~DevelopmentCard() = default;
    virtual void play(Player& player) = 0; // Pure virtual function to be overridden by derived classes
    virtual std::string getType() const = 0;
};

#endif // DEVELOPMENTCARD_HPP
