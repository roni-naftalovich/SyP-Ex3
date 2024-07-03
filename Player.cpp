// Roni Naftalovich 319049060, roni100400100400@gmail.com
#include "Player.hpp"
#include "Board.hpp"
#include "DevelopmentCard.hpp"
#include "KnightCard.hpp"
#include "VictoryCard.hpp"
#include "Monopoly.hpp"
#include "RoadBuilding.hpp"
#include "YearOfPlentyCard.hpp"
#include "ResourceType.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int Player::nextSeqNum = 1; // Initialize static member variable
int Player::currentTurn = 1;


Player::Player(const string &name)
    : name(name), resources(5, 0) , hasRolledDice(false)
{
    seqNum = nextSeqNum++;
    if (nextSeqNum > 3) {
        nextSeqNum = 1; // Reset to 1 after reaching 3
    }
    points = 2;
    developmentCardCount = 0;
    knightCardsCount = 0;
    winner = -1;
}

void Player::endTurn() {
    if (!hasRolledDice) {
        std::cout << "Player " << this->getName() << " must roll the dice before ending their turn." << std::endl;
        return;
    }
    currentTurn++;
    if (currentTurn > 3) {
        currentTurn = 1;
    }
    hasRolledDice = false;  // Reset for the next turn
}

int Player::getSeqNum() const
{
    return this->seqNum;
}

const string &Player::getName() const
{
    return name;
}

bool Player::canbuySettlement()
{
    if (resources[ResourceType::Brick] >= 1 && resources[ResourceType::Oats] >= 1 && resources[ResourceType::Wood] >= 1 && resources[ResourceType::Wool] >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::canbuyCity()
{
    if (resources[3] >= 2 && resources[4] >= 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::canbuyRoad()
{
    if (resources[ResourceType::Wood] >= 1 && resources[ResourceType::Brick] >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Player::getResourceAmaount(size_t type){
    return this->resources[type];
}

void Player::setResourceAmaount(size_t type, int amount){
    this->resources[type]+= amount;
}

void Player::rollDice(Board &board)
{
    if (Player::currentTurn != this->getSeqNum()) {
        std::cout << "It's not " << this->getName() << "'s turn." << std::endl;
        return;
    }
    int result = (rand() % 6 + 1) + (rand() % 6 + 1);
    if (result == 7)
    {
        cout << "Player " << this->getName() << " rolled a 7" << endl;
        // every player with more than 7 resources will have to discard half of his resources
        discardResources(board);
    }
    else
    {
        cout << "Player " << this->getName() << " rolled a " << result << endl;

        board.giveResources(result);
    }
    hasRolledDice = true;  // Indicate that the player has rolled the dice
}

void Player::discardResources(Board &board) {
    for (Player* player : board.players) {
        int totalResources = 0;
        for (int amount : player->resources) {
            totalResources += amount;
        }
        if (totalResources > 7) {
            int resourcesToDiscard = totalResources / 2;
            for (size_t i = 0; i < 5; i++) {
                int discardFromThisResource = player->resources[i] / 2;
                player->resources[i] -= discardFromThisResource;
                resourcesToDiscard -= discardFromThisResource;
            }
            
            while (resourcesToDiscard > 0) {
                size_t j = static_cast<size_t>(rand() % 5);
                if (player->resources[j] > 0) {
                    player->resources[j]--;
                    resourcesToDiscard--;
                }
            }
            std::cout << "Player " << player->getName() << " discard half of their resources and left with: Wood- " << player->resources[ResourceType::Wood]
                      << ", Brick- " << player->resources[ResourceType::Brick]
                      << ", Wool- " << player->resources[ResourceType::Wool]
                      << ", Oats- " << player->resources[ResourceType::Oats]
                      << ", Iron- " << player->resources[ResourceType::Iron] << std::endl;
        }
    }
}

// void Player::placeInitialSettlementAndRoad(int vertexIndex, int vertexIndex2, Board &board)
// {
//     if (board.canPlaceInitialSettlementAndRoad(*this, static_cast<size_t>(vertexIndex), static_cast<size_t>(vertexIndex2)))
//     {
        
//     }
//     else
//     {
//         std::cout << this->getName() << " Please choose another settelment" << std::endl;
//     }
// }

void Player::placeSettlement(int vertexIndex, Board &board)
{
    if (Player::currentTurn != this->getSeqNum()) {
        std::cout << "It's not " << this->getName() << "'s turn." << std::endl;
        return;
    }
    
    if (!canbuySettlement())
    {
        std::cout << "Player " << this->getName() << " does not have the needed resources to place a settlement" << std::endl;
        return;
    }

    if (board.canPlaceSettlement(*this, static_cast<size_t>(vertexIndex)))
    {
        settlements.push_back(vertexIndex);
        std::cout << "Player " << this->getName() << " placed a settlement on vertex " << vertexIndex << std::endl;
        resources[ResourceType::Wood] -= 1;
        resources[ResourceType::Brick] -= 1;
        resources[ResourceType::Wool] -= 1;
        resources[ResourceType::Oats] -= 1;
        points += 1;
        this->showResources();
        std::cout << "Player " << this->getName() << " now has " << points << " points" << std::endl;
        checkWinner();
    }
    else
    {
        std::cout << "Player " << this->getName() << " cannot place a settlement on vertex " << vertexIndex << std::endl;
    }
}

void Player::upgradeToCity(int vertexIndex, Board &board)
{
    if (Player::currentTurn != this->getSeqNum()) {
        std::cout << "It's not " << this->getName() << "'s turn." << std::endl;
        return;
    }
    if (!canbuyCity())
    {
        std::cout << "Player " << this->getName() << " cannot upgrade a settlement to a city because they do not have the needed resources" << std::endl;
        return;
    }
    if (board.canPlaceCity(this->getSeqNum(), static_cast<size_t>(vertexIndex)))
    {
        cities.push_back(vertexIndex);
        std::cout << "Player " << this->getName() << " upgraded a settlement to a city on vertex " << vertexIndex << std::endl;
        resources[ResourceType::Oats] -= 2;
        resources[ResourceType::Iron] -= 3;
        points += 1;
        board.getVertices()[static_cast<size_t>(vertexIndex)].setIsCity(true);
        std::cout << "Player " << this->getName() << " now has " << points << " points" << std::endl;
        checkWinner();
    }
    else
    {
        std::cout << "Player " << this->getName() << " cannot upgrade a settlement to a city on vertex " << vertexIndex << std::endl;
    }
}

void Player::placeRoad(int vertexIndex1, int vertexIndex2, Board &board)
{
    if (Player::currentTurn != this->getSeqNum()) {
        std::cout << "It's not " << this->getName() << "'s turn." << std::endl;
        return;
    }
    if (!canbuyRoad())
    {
        std::cout << "Player " << this->getName() << " cannot place a road because they do not have the needed resources" << std::endl;
        return;
    }
    if (board.canPlaceRoad(this->getSeqNum(), static_cast<size_t>(vertexIndex1), static_cast<size_t>(vertexIndex2)))
    {
        roads.push_back(board.getEdge(static_cast<size_t>(vertexIndex1), static_cast<size_t>(vertexIndex2)));
        std::cout << "Player " << this->getName() << " placed a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << std::endl;
        resources[ResourceType::Wood] -= 1;
        resources[ResourceType::Brick] -= 1;
    }
    else
    {
        std::cout << "Player " << this->getName() << " cannot place a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << std::endl;
    }
}
void Player::canBuyDevelopmentCard()
{
    if (resources[2] >= 1 && resources[3] >= 1 && resources[4] >= 1)
    {
        resources[2] -= 1;
        resources[3] -= 1;
        resources[4] -= 1;
        cout << "Player " << this->getName() << " bought a development card" << endl;
        developmentCardCount++;
    }
    else
    {
        cout << "Player " << this->getName() << " cannot buy a development card because he does not has the needed resourses" << endl;
    }
}



void Player::showResources() const {
    std::cout << "Player " << getName() << " has the following resources:" << std::endl;
    std::cout << "Wood: " << resources[ResourceType::Wood] << std::endl;
    std::cout << "Brick: " << resources[ResourceType::Brick] << std::endl;
    std::cout << "Wool: " << resources[ResourceType::Wool] << std::endl;
    std::cout << "Oats: " << resources[ResourceType::Oats] << std::endl;
    std::cout << "Iron: " << resources[ResourceType::Iron] << std::endl;
}

void Player::addResource(size_t type, int amount) {
    if (type < 6) {
        resources[type] += amount;
    } else {
        std::cerr << "Invalid resource type: " << type << std::endl;
    }
}

// A function that took 1 random development card from the deck and gave it to the player. the card will be deleted from the deck
void Player::chooseDevelopmentCard(Board &board)
{
     if (Player::currentTurn != this->getSeqNum()) {
        std::cout << "It's not " << this->getName() << "'s turn." << std::endl;
        return;
    }
    if (board.developmentCards.size() == 0)
    {
        cout << "No more development cards in the deck" << endl;
        return;
    }
    // check if the player has the resources to buy a development card
    if (resources[ResourceType::Oats] < 1 || resources[ResourceType::Wool] < 1 || resources[ResourceType::Iron] < 1)
    {
        cout << "Player " << this->getName() << " cannot buy a development card because he does not has the needed resourses" << endl;
        return;
    }
    board.drawDevelopmentCard(this->getSeqNum());
    DevelopmentCard* cardP = board.developmentCards.back();
    board.developmentCards.pop_back();
    std::string card = cardP->getType();
    // print the development card that the player got
    cout << "Player " << this->getName() << " bought a development card, and got a: " << card << " card" << endl;
    developmentCardCount++;
    // subtract the resources that the player used to buy the development card
    resources[ResourceType::Oats] -= 1;
    resources[ResourceType::Wool] -= 1;
    resources[ResourceType::Iron] -= 1;

}

void Player::addDevelopmentCard(DevelopmentCard* card)
{
    developmentCards.push_back(card);
}

void Player::addKnightCard()
{
    this->knightCardsCount++;
}


int Player::getKnightCards() {
    return this->knightCardsCount;
}

void Player::playDevelopmentCard(Board &board) {
    if (Player::currentTurn != this->getSeqNum()) {
        std::cout << "It's not " << this->getName() << "'s turn." << std::endl;
        return;
    }
    if (developmentCards.empty()) {
        std::cout << "Player " << name << " doesn't have any development cards to play." << std::endl;
        return;
    }

    std::cout << "Player " << name << " has the following development cards:" << std::endl;
    for (DevelopmentCard* card : developmentCards) {
        std::cout << "- " << card->getType() << std::endl;
    }

    std::cout << "Which development card do you want to play? ";
    std::string type;
    std::cin.ignore(); // Clear the newline character left in the input buffer
    std::getline(std::cin, type);

    auto it = std::find_if(developmentCards.begin(), developmentCards.end(),
                           [&type](DevelopmentCard* card) { return card->getType() == type; });

    if (it == developmentCards.end()) {
        std::cout << "Player " << name << " does not have a " << type << " card." << std::endl;
        return;
    }

    DevelopmentCard* card = *it;

    if (type == "Knight") {
        KnightCard* knightCard = dynamic_cast<KnightCard*>(card);
        if (knightCard) {
            knightCard->play(*this);
            checkWinner();
        }
    } else if (type == "Victory Point") {
        VictoryCard* victoryCard = dynamic_cast<VictoryCard*>(card);
        if (victoryCard) {
            victoryCard->play(*this);
            checkWinner();
        }
    } else if (type == "Monopoly") {
        Monopoly* monopolyCard = dynamic_cast<Monopoly*>(card);
        if (monopolyCard) {
            monopolyCard->play(*this);
            std::string resourceName;
            ResourceType chosenResource;
            while (true) {
                std::cout << "Choose the resource type you would like to receive (Wood, Brick, Wool, Oats, Iron): ";
                std::cin >> resourceName;
                if (resourceName == "Wood") {
                    chosenResource = ResourceType::Wood;
                    break;
                } else if (resourceName == "Brick") {
                    chosenResource = ResourceType::Brick;
                    break;
                } else if (resourceName == "Wool") {
                    chosenResource = ResourceType::Wool;
                    break;
                } else if (resourceName == "Oats") {
                    chosenResource = ResourceType::Oats;
                    break;
                } else if (resourceName == "Iron") {
                    chosenResource = ResourceType::Iron;
                    break;
                } else {
                    std::cout << "Invalid resource type chosen. Please try again." << std::endl;
                }
            }
            for (Player* otherPlayer : board.players) {
                if (otherPlayer != this) {
                    int amount = otherPlayer->getResourceAmaount(chosenResource);
                    otherPlayer->setResourceAmaount(chosenResource, -amount);
                    this->addResource(static_cast<size_t>(chosenResource), amount);
                }
            }
        }
    } else if (type == "Year Of Plenty") {
        YearOfPlentyCard* yearOfPlentyCard = dynamic_cast<YearOfPlentyCard*>(card);
        if (yearOfPlentyCard) {
            yearOfPlentyCard->play(*this);
        }
    } else if (type == "Building Roads") {
        BuildingRoadsCard* buildingRoadsCard = dynamic_cast<BuildingRoadsCard*>(card);
        if (buildingRoadsCard) {
            buildingRoadsCard->play(*this);
            for (int i = 0; i < 2; ++i) {
            int vertexIndex1, vertexIndex2;
            bool flag= true;
            while (flag) {
            std::cout << "Enter the indices of the vertices to place the road between: ";
            std::cin >> vertexIndex1 >> vertexIndex2;
            if(board.canPlaceRoad(this->getSeqNum(), static_cast<size_t>(vertexIndex1), static_cast<size_t>(vertexIndex2))){
                roads.push_back(board.getEdge(static_cast<size_t>(vertexIndex1), static_cast<size_t>(vertexIndex2)));
                std::cout << "Player " << this->getName() << " placed a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << std::endl;
                flag= false;
            }
        }}}
    }else {
        std::cout << "Unknown development card type: " << type << std::endl;
        return;
    }

    delete card;
    developmentCards.erase(it);
}

int Player::getVictoryPoints() const {
     return points;
}

void Player::addVictoryPoint() { points++; }



void Player::tradeResources(Board &board, int player,  std::string resource1, int amount, std::string resource2, int amount2)
{
    if (Player::currentTurn != this->getSeqNum()) {
        std::cout << "It's not " << this->getName() << "'s turn." << std::endl;
        return;
    }
    ResourceType type1, type2;
    if (resource1 == "Wood")
        type1 = ResourceType::Wood;
    else if (resource1 == "Brick")
        type1 = ResourceType::Brick;
    else if (resource1 == "Wool")
        type1 = ResourceType::Wool;
    else if (resource1 == "Oats")
        type1 = ResourceType::Oats;
    else if (resource1 == "Iron")
        type1 = ResourceType::Iron;
    else
        return;

    if (resource2 == "Wood")
        type2 = ResourceType::Wood;
    else if (resource2 == "Brick")
        type2 = ResourceType::Brick;
    else if (resource2 == "Wool")
        type2 = ResourceType::Wool;
    else if (resource2 == "Oats")
        type2 = ResourceType::Oats;
    else if (resource2 == "Iron")
        type2 = ResourceType::Iron;
    else
        return;

    if (resources[type2] >= amount2 && board.players[static_cast<size_t>(player - 1)]->resources[type1] >= amount)
    {
        cout<< "Player " << this->getName() << " wants to trade with " << board.players[static_cast<size_t>(player - 1)]->getName() << " " << amount2 << " "  << resource2 << " for " << amount << " " << resource1 << endl;
        // Prompt the other player
        std::string response;
        std::cout << board.players[static_cast<size_t>(player - 1)]->getName() << ", do you accept the trade? (yes/no): ";
        std::cin >> response;

        if (response == "yes")
        {
            resources[type2] -= amount2;
            resources[type1] += amount;
            board.players[static_cast<size_t>(player - 1)]->resources[type1] -= amount;
            board.players[static_cast<size_t>(player - 1)]->resources[type2] += amount2;

            std::cout << "Player " << this->getName() << " traded " << amount2 << " " << resource2 << " with player " << board.players[static_cast<size_t>(player - 1)]->getName() << " for " << amount << " " << resource1 << std::endl;
            showResources();
            board.players[static_cast<size_t>(player -1)]->showResources();
        }
        else
        {
            std::cout << "Player " << board.players[static_cast<size_t>(player - 1)]->getName() << " declined the trade." << std::endl;
        }
    }
    else
    {
        std::cout << "Player " << this->getName() << " cannot trade " << amount << " " << resource1 << " with player " << board.players[static_cast<size_t>(player - 1)]->getName() << " for " << amount2 << " " << resource2 << std::endl;
    }
}

void Player::addSettlement(int vertexIndex) {
    settlements.push_back(vertexIndex);
}

void Player::addRoad(int newRoad) {
    roads.push_back(newRoad);
}

void Player::checkWinner() {
    if (points >= 10) {
        std::cout << "Player " << this->getName() << " reached 10 points and won the game!" << std::endl;
    }
}

void Player::cleanUp() {
    for (DevelopmentCard* card : developmentCards) {
        delete card;
    }
    developmentCards.clear();
}
