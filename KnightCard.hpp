// KnightCard.hpp
#ifndef KNIGHTCARD_HPP
#define KNIGHTCARD_HPP

#include "DevelopmentCard.hpp"
#include "Board.hpp"
#include "Player.hpp"

class KnightCard : public DevelopmentCard {
public:
    void play(Player& player) override;
    std::string getType() const override;
};

#endif // KNIGHTCARD_HPP
