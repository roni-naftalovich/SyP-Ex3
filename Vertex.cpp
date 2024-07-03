// Roni Naftalovich 319049060, roni100400100400@gmail.com
#include "Vertex.hpp"
#include "ResourceType.hpp"
#include "Tile.hpp"
#include "Edge.hpp"
#include "Player.hpp"

// Constructor to initialize the vertex with an index
Vertex::Vertex(size_t index) : seqNum(index), owner(-1), isCity(false){}

// Get the index of the vertex
size_t Vertex::getSeqNum() const {
    return this->seqNum;
}

// Set the owner of the vertex
bool Vertex::getIsSetteled() {
    return this->isSetteled;
}

void Vertex::setIsSetteled(bool setteled){
    isSetteled= setteled;
}
void Vertex::setOwner(Player& player){
    this->owner = player.getSeqNum();
}

int Vertex::getOwner() const{
    return owner;
}


// Add an adjacent plot to the vertex
void Vertex::addRelatedResource(ResourceType resource) {
    relatedResources.push_back(resource);
}

// Get the adjacent plots
const vector<ResourceType>& Vertex::getRelatedResources() const {
    return relatedResources;
}

// Add an adjacent vertex to the vertex
void Vertex::addNeighbor(Vertex* vertex) {
    neighbors.push_back(vertex);
}

// Check if a vertex is a neighbor
bool Vertex::isNeighbor(const Vertex& vertex) const {
    for (const Vertex* neighbor : neighbors) {
        if (neighbor->getSeqNum() == vertex.getSeqNum()) {
            return true;
        }
    }
    return false;
}

// Get the adjacent vertices
const vector<Vertex*>& Vertex::getNeighbors() const {
    return neighbors;
}

// Add an adjacent edge to the vertex
void Vertex::addEdge(Edge* edge) {
    edges.push_back(edge);
}

// Get the adjacent edges
const vector<Edge*>& Vertex::getEdges() const {
    return edges;
}

// Set the city of the vertex
void Vertex::setIsCity(bool City) {
    this->isCity = City;
}

// Get the city of the vertex
bool Vertex::getIsCity() const {
    return isCity;
}