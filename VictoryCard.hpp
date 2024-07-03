#ifndef VICTORYCARD_HPP
#define VICTORYCARD_HPP

#include "DevelopmentCard.hpp"
#include "Board.hpp"
#include "Player.hpp"

class VictoryCard : public DevelopmentCard {
public:
    void play(Player& player) override;
    std::string getType() const override;
};

#endif // VICTORYCARD_HPP