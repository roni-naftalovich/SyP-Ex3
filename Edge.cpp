#include "Edge.hpp"
#include "Vertex.hpp"


Edge::Edge(size_t index) : index(index), owner(-1) {}

Edge::Edge(const Edge& other) {
    this->v1 = other.v1;
    this->v2 = other.v2;
    this->index = other.index;
    this->owner = other.owner;
}

void Edge::setOwner(int seqNum) {
    this->owner = seqNum;
}

int Edge::getOwner() const {
    return this->owner;
}

size_t Edge::getSeqNum() const {
    return this->index;
}

const Vertex& Edge::getVertex1() const {
    return *v1;
}

const Vertex& Edge::getVertex2() const {
    return *v2;
}

void Edge::setVertex1(Vertex* vertex1) {
    this->v1 = vertex1;
}

void Edge::setVertex2(Vertex* vertex2) {
    this->v2 = vertex2;
}