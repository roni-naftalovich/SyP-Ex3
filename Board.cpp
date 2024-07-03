#include "Board.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include "ResourceType.hpp"
#include <iostream>
#include <vector>
#include <tuple>
#include "DevelopmentCard.hpp"
#include "KnightCard.hpp"
#include "Monopoly.hpp"
#include "VictoryCard.hpp"
#include "YearOfPlentyCard.hpp"
#include <algorithm>
#include <random> // for default_random_engine and random_device
#include <chrono> // for system_clock

class Tile;
class Player;


void Board::printBoard() const {
    for (const auto& tile : tiles) {
        std::cout << "Tile " << tile.getSeqNum() << ": " << tile.getResource() << " (" << tile.getNumber() << ")\n";
    }
}

// Constructor for the Board class
Board::Board(Player &player1, Player &player2, Player &player3)
{
    cout << "Preparing board..." << endl;

    players.reserve(3);
    tiles.reserve(19);

    // Add players to the players vector
    players.push_back(&player1);
    players.push_back(&player2);
    players.push_back(&player3);

    cout<< "Added all the players" <<endl;

    // Initialize the board with tiles as shown in the image
    tiles[0] = Tile(ResourceType::Iron, 10, 0);
    tiles[1] = Tile(ResourceType::Wool, 2, 1);
    tiles[2] = Tile(ResourceType::Wood, 9, 2);
    tiles[3] = Tile(ResourceType::Oats, 12, 3);
    tiles[4] = Tile(ResourceType::Brick, 6, 4);
    tiles[5] = Tile(ResourceType::Wool, 4, 5);
    tiles[6] = Tile(ResourceType::Brick, 10, 6);
    tiles[7] = Tile(ResourceType::Oats, 9, 7);
    tiles[8] = Tile(ResourceType::Wood, 11, 8);
    tiles[9] = Tile(ResourceType::None, 7, 9); // Desert
    tiles[10] = Tile(ResourceType::Wood, 3, 10);
    tiles[11] = Tile(ResourceType::Iron, 8, 11);
    tiles[12] = Tile(ResourceType::Wood, 8, 12);
    tiles[13] = Tile(ResourceType::Iron, 3, 13);
    tiles[14] = Tile(ResourceType::Oats, 4, 14);
    tiles[15] = Tile(ResourceType::Wool, 5, 15);
    tiles[16] = Tile(ResourceType::Brick, 5, 16);
    tiles[17] = Tile(ResourceType::Oats, 6, 17);
    tiles[18] = Tile(ResourceType::Wool, 11, 18);

    cout << "Initializing tiles" <<endl;
    // Initialize vertices (54 vertices)
    vertices.reserve(54);
    for (size_t i = 0; i < 54; ++i)
    {
        vertices.emplace_back(Vertex(i));
    }

    // Connections between tiles and vertices based on specified order
    std::vector<std::vector<size_t>> vertexMapping = {
        {0, 1, 2, 8, 9, 10}, {2, 3, 4, 12, 11, 10}, {4, 5, 6, 14, 13, 12}, {7, 8, 9, 19, 18, 17}, {9, 10, 11, 21, 20, 19}, {11, 12, 13, 23, 22, 21}, {13, 14, 15, 25, 24, 22}, {16, 17, 18, 29, 28, 27}, {18, 19, 20, 31, 30, 29}, {20, 21, 22, 33, 32, 31}, {22, 23, 24, 35, 34, 33}, {24, 25, 26, 37, 36, 35}, {28, 29, 30, 40, 39, 38}, {30, 31, 32, 42, 41, 40}, {32, 33, 34, 44, 43, 42}, {34, 35, 36, 46, 45, 44}, {39, 40, 41, 49, 48, 47}, {41, 42, 43, 51, 50, 49}, {43, 44, 45, 53, 52, 51}};
    // Set the vertices for each plot
    for (size_t i = 0; i < 19; i++)
    {
        for (size_t j = 0; j < 6; j++)
        {
            tiles[i].vertices.push_back((&vertices[vertexMapping[i][j]]));
            vertices[vertexMapping[i][j]].addRelatedResource(tiles[i].getResource());
        }
    }

    //Set up vertex neighbors
    vertices[0].addNeighbor(&vertices[1]);
    vertices[0].addNeighbor(&vertices[8]);
    vertices[1].addNeighbor(&vertices[0]);
    vertices[1].addNeighbor(&vertices[2]);
    vertices[2].addNeighbor(&vertices[1]);
    vertices[2].addNeighbor(&vertices[3]);
    vertices[2].addNeighbor(&vertices[10]);
    vertices[3].addNeighbor(&vertices[2]);
    vertices[3].addNeighbor(&vertices[4]);
    vertices[4].addNeighbor(&vertices[3]);
    vertices[4].addNeighbor(&vertices[5]);
    vertices[4].addNeighbor(&vertices[12]);
    vertices[5].addNeighbor(&vertices[4]);
    vertices[5].addNeighbor(&vertices[6]);
    vertices[6].addNeighbor(&vertices[5]);
    vertices[6].addNeighbor(&vertices[14]);
    vertices[7].addNeighbor(&vertices[8]);
    vertices[8].addNeighbor(&vertices[7]);
    vertices[8].addNeighbor(&vertices[9]);
    vertices[8].addNeighbor(&vertices[0]);
    vertices[9].addNeighbor(&vertices[8]);
    vertices[9].addNeighbor(&vertices[10]);
    vertices[9].addNeighbor(&vertices[19]);
    vertices[10].addNeighbor(&vertices[9]);
    vertices[10].addNeighbor(&vertices[2]);
    vertices[10].addNeighbor(&vertices[11]);
    vertices[11].addNeighbor(&vertices[10]);
    vertices[11].addNeighbor(&vertices[12]);
    vertices[11].addNeighbor(&vertices[21]);
    vertices[12].addNeighbor(&vertices[11]);
    vertices[12].addNeighbor(&vertices[4]);
    vertices[12].addNeighbor(&vertices[13]);
    vertices[13].addNeighbor(&vertices[12]);
    vertices[13].addNeighbor(&vertices[14]);
    vertices[13].addNeighbor(&vertices[23]);
    vertices[14].addNeighbor(&vertices[13]);
    vertices[14].addNeighbor(&vertices[6]);
    vertices[14].addNeighbor(&vertices[15]);
    vertices[15].addNeighbor(&vertices[14]);
    vertices[15].addNeighbor(&vertices[25]);
    vertices[16].addNeighbor(&vertices[17]);
    vertices[17].addNeighbor(&vertices[16]);
    vertices[17].addNeighbor(&vertices[18]);
    vertices[17].addNeighbor(&vertices[7]);
    vertices[18].addNeighbor(&vertices[17]);
    vertices[18].addNeighbor(&vertices[19]);
    vertices[18].addNeighbor(&vertices[29]);
    vertices[19].addNeighbor(&vertices[18]);
    vertices[19].addNeighbor(&vertices[9]);
    vertices[19].addNeighbor(&vertices[20]);
    vertices[20].addNeighbor(&vertices[19]);
    vertices[20].addNeighbor(&vertices[21]);
    vertices[20].addNeighbor(&vertices[31]);
    vertices[21].addNeighbor(&vertices[20]);
    vertices[21].addNeighbor(&vertices[11]);
    vertices[21].addNeighbor(&vertices[22]);
    vertices[22].addNeighbor(&vertices[21]);
    vertices[22].addNeighbor(&vertices[23]);
    vertices[22].addNeighbor(&vertices[33]);
    vertices[23].addNeighbor(&vertices[22]);
    vertices[23].addNeighbor(&vertices[13]);
    vertices[23].addNeighbor(&vertices[24]);
    vertices[24].addNeighbor(&vertices[23]);
    vertices[24].addNeighbor(&vertices[25]);
    vertices[24].addNeighbor(&vertices[35]);
    vertices[25].addNeighbor(&vertices[24]);
    vertices[25].addNeighbor(&vertices[15]);
    vertices[25].addNeighbor(&vertices[26]);
    vertices[26].addNeighbor(&vertices[25]);
    vertices[26].addNeighbor(&vertices[37]);
    vertices[27].addNeighbor(&vertices[28]);
    vertices[28].addNeighbor(&vertices[27]);
    vertices[28].addNeighbor(&vertices[29]);
    vertices[28].addNeighbor(&vertices[16]);
    vertices[29].addNeighbor(&vertices[28]);
    vertices[29].addNeighbor(&vertices[18]);
    vertices[29].addNeighbor(&vertices[30]);
    vertices[30].addNeighbor(&vertices[29]);
    vertices[30].addNeighbor(&vertices[31]);
    vertices[30].addNeighbor(&vertices[40]);
    vertices[31].addNeighbor(&vertices[30]);
    vertices[31].addNeighbor(&vertices[20]);
    vertices[31].addNeighbor(&vertices[32]);
    vertices[32].addNeighbor(&vertices[31]);
    vertices[32].addNeighbor(&vertices[33]);
    vertices[32].addNeighbor(&vertices[42]);
    vertices[33].addNeighbor(&vertices[32]);
    vertices[33].addNeighbor(&vertices[22]);
    vertices[33].addNeighbor(&vertices[34]);
    vertices[34].addNeighbor(&vertices[33]);
    vertices[34].addNeighbor(&vertices[35]);
    vertices[34].addNeighbor(&vertices[44]);
    vertices[35].addNeighbor(&vertices[34]);
    vertices[35].addNeighbor(&vertices[24]);
    vertices[35].addNeighbor(&vertices[36]);
    vertices[36].addNeighbor(&vertices[35]);
    vertices[36].addNeighbor(&vertices[37]);
    vertices[36].addNeighbor(&vertices[46]);
    vertices[37].addNeighbor(&vertices[36]);
    vertices[37].addNeighbor(&vertices[26]);
    vertices[37].addNeighbor(&vertices[38]);
    vertices[38].addNeighbor(&vertices[37]);
    vertices[38].addNeighbor(&vertices[39]);
    vertices[39].addNeighbor(&vertices[38]);
    vertices[39].addNeighbor(&vertices[28]);
    vertices[39].addNeighbor(&vertices[40]);
    vertices[40].addNeighbor(&vertices[39]);
    vertices[40].addNeighbor(&vertices[30]);
    vertices[40].addNeighbor(&vertices[41]);
    vertices[41].addNeighbor(&vertices[40]);
    vertices[41].addNeighbor(&vertices[42]);
    vertices[41].addNeighbor(&vertices[49]);
    vertices[42].addNeighbor(&vertices[41]);
    vertices[42].addNeighbor(&vertices[32]);
    vertices[42].addNeighbor(&vertices[43]);
    vertices[43].addNeighbor(&vertices[42]);
    vertices[43].addNeighbor(&vertices[44]);
    vertices[43].addNeighbor(&vertices[51]);
    vertices[44].addNeighbor(&vertices[43]);
    vertices[44].addNeighbor(&vertices[34]);
    vertices[44].addNeighbor(&vertices[45]);
    vertices[45].addNeighbor(&vertices[44]);
    vertices[45].addNeighbor(&vertices[46]);
    vertices[45].addNeighbor(&vertices[53]);
    vertices[46].addNeighbor(&vertices[45]);
    vertices[46].addNeighbor(&vertices[36]);
    vertices[47].addNeighbor(&vertices[48]);
    vertices[48].addNeighbor(&vertices[47]);
    vertices[48].addNeighbor(&vertices[49]);
    vertices[49].addNeighbor(&vertices[48]);
    vertices[49].addNeighbor(&vertices[41]);
    vertices[49].addNeighbor(&vertices[50]);
    vertices[50].addNeighbor(&vertices[49]);
    vertices[50].addNeighbor(&vertices[51]);
    vertices[51].addNeighbor(&vertices[50]);
    vertices[51].addNeighbor(&vertices[43]);
    vertices[51].addNeighbor(&vertices[52]);
    vertices[52].addNeighbor(&vertices[51]);
    vertices[52].addNeighbor(&vertices[53]);
    vertices[53].addNeighbor(&vertices[52]);
    vertices[53].addNeighbor(&vertices[45]);

    // Edges consists by the num of vertices 
    vector<vector<size_t>> edgeMapping = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {0, 8}, {2, 10}, {4, 12}, {6, 14}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 14}, {14, 15}, {7, 17}, {9, 19}, {11, 21}, {13, 23}, {15, 25}, {16, 17}, {17, 18}, {18, 19}, {19, 20}, {20, 21}, {21, 22}, {22, 23}, {23, 24}, {24, 25}, {25, 26}, {16, 27}, {18, 29}, {20, 31}, {22, 33}, {24, 35}, {26, 37}, {27, 28}, {28, 29}, {29, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35}, {35, 36}, {36, 37}, {28, 38}, {30, 40}, {32, 42}, {34, 44}, {36, 46}, {38, 39}, {39, 40}, {40, 41}, {41, 42}, {42, 43}, {43, 44}, {44, 45}, {45, 46}, {39, 47}, {41, 49}, {43, 51}, {45, 53}, {47, 48}, {48, 49}, {49, 50}, {50, 51}, {51, 52}, {52, 53}};

    // Set the vertices for each edge
    edges.reserve(72);
    for (size_t i = 0; i < 72; ++i)
    {
        edges.emplace_back(Edge(i));
        edges[i].setVertex1(&vertices[edgeMapping[i][0]]);
        edges[i].setVertex2(&vertices[edgeMapping[i][1]]);
        vertices[edgeMapping[i][0]].addEdge(&edges[i]);
        vertices[edgeMapping[i][1]].addEdge(&edges[i]);
    }

    // Initialize the deck of 25 development cards: 14 knights, 5 victory points, 2 year of plenty, 2 monopoly
    for (int i = 0; i < 3; i++) {
        developmentCards.push_back(new KnightCard());
    }
    for (int i = 0; i < 5; i++) {
        developmentCards.push_back(new VictoryCard());
    }
    for (int i = 0; i < 2; i++) {
        developmentCards.push_back(new YearOfPlentyCard());
    }
    for (int i = 0; i < 2; i++) {
        developmentCards.push_back(new Monopoly());
    }

    // Shuffle the deck
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine engine(seed);
    std::shuffle(developmentCards.begin(), developmentCards.end(), engine);

    // Print message indicating game setup is complete and initial board configuration
    std::cout << "Board initialization succeed! we are ready to play, please choose your initial settlemets" << std::endl;
    printBoard();
}

const vector<Tile>& Board::getTiles() const {
    return tiles;
}

vector<Vertex> &Board::getVertices()
{
    return vertices;
}

int Board::getEdge(size_t vertexIndex1, size_t vertexIndex2)
{
    if (vertexIndex1 > vertexIndex2)
    {
        std::swap(vertexIndex1, vertexIndex2);
    }
    for (size_t i = 0; i < 72; i++)
    {
        if (edges[i].getVertex1().getSeqNum() == vertexIndex1 && edges[i].getVertex2().getSeqNum() == vertexIndex2)
        {
            return i;
        }
    }
    return -1;
}

void Board::giveResources(int diceResult) {
    for (size_t i = 0; i < 19; ++i) {
        if (tiles[i].getNumber() == diceResult) {
            for (Vertex* vertex : tiles[i].vertices) {
                if (vertex->getOwner() != -1) {
                    ResourceType resource = tiles[i].getResource();
                    int amount = vertex->getIsCity() ? 2 : 1; // Cities give double resources
                    players[static_cast<size_t>(vertex->getOwner()-1)]->setResourceAmaount(static_cast<size_t>(resource), amount);
                }
            }
        }
    }
}

void Board::drawDevelopmentCard(int seqNum)
{
    // take the first card from the deck and give it to the player
    players[static_cast<size_t>(seqNum -1)]->developmentCards.push_back(developmentCards.back());
    developmentCards.erase(developmentCards.begin());
}

bool Board::canPlaceInitialSettlementAndRoad(Player &player, size_t vertexIndex, size_t vertexIndex2)
{
    // Check if vertexIndex is valid
    if (vertexIndex >= vertices.size() || vertexIndex < 0 || vertexIndex2 >= vertices.size() || vertexIndex2 < 0)
    {
        std::cerr << "Invalid vertex index." << endl;
        return false;
    }

    // Get the vertex at the specified index
    Vertex &vertex = vertices[vertexIndex];

    // Check if the vertex is already occupied by a settlement or city
    if (vertex.getOwner() != -1)
    {
        std::cerr << "Vertex " << vertexIndex << " is already setteled." << endl;
        return false;
    }
    // Check if the vertex is adjacent to a vertex that is already occupied by one of the players
    const vector<Vertex *> &adjacentPlots = vertex.getNeighbors();
    for (const Vertex *adjacentVertex : adjacentPlots)
    {
        if (adjacentVertex->getOwner() != -1)
        {
            std::cerr << "Player " << player.getName() << " can't place settelment on vertex "<< vertexIndex << " because adjacent vertex " << adjacentVertex->getSeqNum() << " already setteled." << endl;
            return false;
        }
    }
    // Check if the edge we are trying to place a road on is occupied
    size_t edgeIndex = static_cast<size_t>(getEdge(vertexIndex, vertexIndex2));
    if (edgeIndex != -1)
    {
        if (edges[edgeIndex].getOwner() != -1)
        {
            std::cerr << "Player "<< player.getName() << " can't place road on edge "<< vertexIndex << " to " << vertexIndex2 << " because it is already setteled." << endl;
            return false;
        }
    }
    // Set the owner of the vertex to the playerID
    vertex.setOwner(player);

    // Set the owner of the edge to the playerID
    edges[edgeIndex].setOwner(player.getSeqNum());

    // Give the player the resources that the vertex sits on
    for (size_t i = 0; i < 19; i++)
    {
        const vector<Vertex* > &vertices = tiles[i].vertices;
        for (Vertex* v : vertices)
        {
            if (v->getSeqNum() == vertexIndex)
            {
                if (tiles[i].getResource() == ResourceType::Iron)
                {
                    player.setResourceAmaount(5, 1);
                }
                else if (tiles[i].getResource() == ResourceType::Wool)
                {
                    player.setResourceAmaount(3, 1);
                }
                else if (tiles[i].getResource() == ResourceType::Wood)
                {
                    player.setResourceAmaount(1, 1);
                }
                else if (tiles[i].getResource() == ResourceType::Oats)
                {
                    player.setResourceAmaount(4, 1);
                }
                else if (tiles[i].getResource() == ResourceType::Brick)
                {
                    player.setResourceAmaount(2, 1);
                }
            }
        }
    }

    return true;
}

bool Board::canPlaceSettlement(Player& player, size_t vertexIndex)
{
    // Check if vertexIndex is valid
    if (vertexIndex >= vertices.size() || vertexIndex < 0)
    {
        std::cerr << "Invalid vertex index." << endl;
        return false;
    }

    // Get the vertex at the specified index
    Vertex &vertex = vertices[vertexIndex];

    // Check if the vertex is already occupied by a settlement or city
    if (vertex.getOwner() != -1)
    {
        std::cerr << "Vertex is already setteled." << endl;
        return false;
    }

    // Check adjacency of vertecies to the vertex for existing settlements or cities
    const vector<Vertex *> &adjacentPlots = vertex.getNeighbors();
    for (Vertex *adjacentVertex : adjacentPlots)
    {
        if (adjacentVertex->getOwner() != -1)
        {
            std::cerr << "Adjacent vertex " << adjacentVertex->getSeqNum() << " already setteled." << endl;
            return false;
        }
    }

    // check if we have at least one edge that belong to the player that connected to the vertex we are trying to place a settlement on
    const vector<Edge *> &adjacentEdges = vertex.getEdges();

    for (const Edge *edge : adjacentEdges)
    {
        if (edge->getOwner() == player.getSeqNum())
        {
            vertex.setOwner(player);
            return true;
        }
    }
    std::cerr << "No adjacent edges belong to the player." << endl;
    return false;
}

bool Board::canPlaceRoad(int seqNum, size_t vertexIndex1, size_t vertexIndex2)
{
    // Check if vertex indices are valid
    if (vertexIndex1 >= vertices.size() || vertexIndex2 >= vertices.size() || vertexIndex1 == vertexIndex2)
    {
        std::cerr << "Invalid vertex indices." << std::endl;
        return false;
    }

    // Get the vertices at the specified indices
    const Vertex &v1 = vertices[vertexIndex1];
    const Vertex &v2 = vertices[vertexIndex2];

    // Check if the vertices are neighbors
    if (!v1.isNeighbor(v2))
    {
        std::cerr << "Vertices are not neighbors." << std::endl;
        return false;
    }

    // Check if the road is already occupied
    const std::vector<Edge *> &adjacentEdges1 = v1.getEdges();
    const std::vector<Edge *> &adjacentEdges2 = v2.getEdges();
    for (const Edge *edge1 : adjacentEdges1)
    {
        for (const Edge *edge2 : adjacentEdges2)
        {
            if (edge1 == edge2 && edge1->getOwner() != -1)
            {
                std::cerr << "Road is already occupied." << std::endl;
                return false;
            }
        }
    }

    // Check if the player has a settlement or city on one of the vertices
    if (v1.getSeqNum() == seqNum || v2.getSeqNum() == seqNum)
    {
        size_t edgeIndex = static_cast<size_t>(getEdge(vertexIndex1, vertexIndex2));
        if (edgeIndex != static_cast<size_t>(-1))
        {
            edges[edgeIndex].setOwner(seqNum);
        }
        return true;
    }

    // Check if the player has an adjacent road
    for (const Edge *edge1 : adjacentEdges1)
    {
        if (edge1->getOwner() == seqNum)
        {
            size_t edgeIndex = static_cast<size_t>(getEdge(vertexIndex1, vertexIndex2));
            if (edgeIndex != static_cast<size_t>(-1))
            {
                edges[edgeIndex].setOwner(seqNum);
                return true;
            }
        }
    }

    for (const Edge *edge2 : adjacentEdges2)
    {
        if (edge2->getOwner() == seqNum)
        {
            size_t edgeIndex = static_cast<size_t>(getEdge(vertexIndex1, vertexIndex2));
            if (edgeIndex != static_cast<size_t>(-1))
            {
                edges[edgeIndex].setOwner(seqNum);
                return true;
            }
        }
    }

    return false;
}

bool Board::canPlaceCity(int playerNum, size_t vertexIndex)
{
    // Check if vertexIndex is valid
    if (vertexIndex >= 55 || vertexIndex < 0)
    {
        std::cerr << "Invalid vertex index." << endl;
        return false;
    }

    // Get the vertex at the specified index
    Vertex &vertex = vertices[vertexIndex];

    // Check if the vertex is already occupied by a city
    if (vertices[vertexIndex].getOwner() != playerNum)
    {
        std::cerr << "Vertex is not setteled by the player." << endl;
        return false;
    }

    // Check if the vertex is already occupied by a city
    if (vertex.getIsCity())
    {
        std::cerr << "Vertex is already setteled by a city." << endl;
        return false;
    }
    vertex.setIsCity(true);
    return true;
}

void Board::initialPlacements() {
    for (Player* player : players) {
        for (int i = 0; i < 2; ++i) {
            bool validPlacement = false;
            while (!validPlacement) {
                // Simulate or request user input for settlement and road placement
                int vertexIndex, vertexIndex2;
                std::cout << "Player " << player->getName() << ", place your initial settlement and road.\n";
                std::cout << "Enter the vertex index for the settlement: ";
                std::cin >> vertexIndex;
                std::cout << "Enter the second vertex index for the road: ";
                std::cin >> vertexIndex2;

                if (canPlaceInitialSettlementAndRoad(*player, static_cast<size_t>(vertexIndex), static_cast<size_t>(vertexIndex2))) {
                    player->addSettlement(vertexIndex);
                    vertices[static_cast<size_t>(vertexIndex)].setOwner(*player);
                    player->addRoad(this->getEdge(static_cast<size_t>(vertexIndex), static_cast<size_t>(vertexIndex2)));
                    std::cout << player->getName() << " placed an initial settlement on vertex " << vertexIndex << " and a road between vertices " << vertexIndex << " and " << vertexIndex2 << std::endl;
                    validPlacement = true;
                } else {
                    std::cout << "Invalid placement. Please try again.\n";
                }
            }
        }
    }
}


void Board::cleanup() {
    // Clean up dynamically allocated development cards
    for (DevelopmentCard* card : developmentCards) {
        delete card;
    }
    developmentCards.clear();
    for (Player* player : players) {
        player->cleanUp();
    }
}
