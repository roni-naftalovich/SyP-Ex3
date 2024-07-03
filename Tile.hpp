
#pragma once
#include <string>
#include <array>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "ResourceType.hpp"
using namespace std;

class Vertex;

class Tile {

private:
    ResourceType resource;
    int number;
    size_t seqNum;

public:

    Tile(ResourceType resource, int number, size_t seqNum);
    //void setVertex(Vertex& vertex);
    ResourceType getResource() const;
    int getNumber() const;
    size_t getSeqNum() const;
    vector<Vertex*> vertices;
};
