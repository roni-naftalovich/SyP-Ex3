// Roni Naftalovich 319049060, roni100400100400@gmail.com
#ifndef BUILDINGROADSCARD_HPP
#define BUILDINGROADSCARD_HPP

#include "DevelopmentCard.hpp"
#include "Player.hpp"

class BuildingRoadsCard : public DevelopmentCard {
public:
    BuildingRoadsCard();
    void play(Player& player) override;
    std::string getType() const override;
};

#endif // BUILDINGROADSCARD_HPP