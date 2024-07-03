// Roni Naftalovich 319049060, roni100400100400@gmail.com
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <cstddef>
#include "Tile.hpp"
#include "ResourceType.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Player.hpp"

class Tile; // Forward declaration of the Plot class
class Edge; // Forward declaration of the Edge class
class Player;

using namespace std;

class Vertex {
public:
    // Constructor to initialize the vertex with an index
    Vertex(size_t index);

    // Getters and setters for index and owner
    size_t getSeqNum() const;
    bool getIsSetteled();
    void setIsSetteled(bool setteled);
    void setIsCity(bool city);
    int getOwner() const;
    bool getIsCity() const;

    void setOwner(Player& player);

    // Add an adjacent plot to the vertex
    // void addAdjacentPlot(Tile* tile);

    // Get the adjacent plots
    const vector<ResourceType>& getRelatedResources() const;
    void addRelatedResource(ResourceType resource);

    // Add an adjacent vertex to the vertex
    void addNeighbor(Vertex* vertex);

    // Check if a vertex is a neighbor
    bool isNeighbor(const Vertex& vertex) const;

    // Get the adjacent vertices
    const vector<Vertex*>& getNeighbors() const;

    // Add an adjacent edge to the vertex
    void addEdge(Edge* edge);

    // Get the adjacent edges
    const vector<Edge*>& getEdges() const;

private:
    size_t seqNum; // Index of the vertex
    bool isSetteled;
    int owner= -1;
    bool isCity; 
    vector<ResourceType> relatedResources; // Adjacent plots
    vector<Vertex*> neighbors; // Adjacent vertices (neighbors)
    vector<Edge*> edges; // Adjacent edges 
};

#endif // VERTEX_HPP