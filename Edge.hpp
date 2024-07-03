// Roni Naftalovich 319049060, roni100400100400@gmail.com
#pragma once
#include "Vertex.hpp"

class Vertex;
using namespace std;

class Edge
{
public:
    Edge(size_t index);
    Edge(const Edge &other); // Copy constructor

    
    void setOwner(int seqNum);
    int getOwner() const;
    size_t getSeqNum() const;
    const Vertex& getVertex1() const;
    const Vertex& getVertex2() const;
    void setVertex1(Vertex* vertex1);
    void setVertex2(Vertex* vertex2);

private:
    Vertex *v1;  // First vertex
    Vertex *v2;  // Second vertex
    size_t index; // Index of the edge
    int owner;         // Owner of the edge
};