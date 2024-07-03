// Roni Naftalovich 319049060, roni100400100400@gmail.com
#include "Tile.hpp"

Tile::Tile(ResourceType resource, int number, size_t seqNum)
    : resource(resource), number(number), seqNum(seqNum) {}


// void Tile::setVertex(Vertex& vertex) {
//     {
//         vertices.push_back(vertex);
//     }
// }

ResourceType Tile::getResource() const {
    return resource;
}

int Tile::getNumber() const {
    return number;
}

size_t Tile::getSeqNum() const {
    return this->seqNum;
}

//  vector< Vertex*>& Plot::getVertices() {
//     return vertices;
// }

// const vector<Edge>& Plot::getEdges() const {
//     return edges;
// }