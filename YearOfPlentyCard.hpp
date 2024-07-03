// Roni Naftalovich 319049060, roni100400100400@gmail.com
#ifndef YEAROFPLENTYCARD_HPP
#define YEAROFPLENTYCARD_HPP

#include "DevelopmentCard.hpp"
#include "Player.hpp"
#include "Board.hpp"

class YearOfPlentyCard : public DevelopmentCard {
public:
    void play(Player& player) override;
    std::string getType() const override;
};

#endif // YEAROFPLENTYCARD_HPP