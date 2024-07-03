// Monopoly.hpp
#ifndef MONOPOLY_HPP
#define MONOPOLY_HPP

#include <string>
#include "Player.hpp"  
#include "DevelopmentCard.hpp"
#include "Board.hpp"



class Monopoly : public DevelopmentCard {
public:
    Monopoly();
    void play(Player& player) override;
    std::string getType() const override;
};

#endif // MONOPOLY_HPP
