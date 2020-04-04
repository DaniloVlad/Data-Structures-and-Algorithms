#include "Node.h"

Node::Node(int i) {
    this -> member = i;
    this -> parent = i;
    this -> rank = 0;
    this -> size = 1;
}

int Node::getParent() {
    return this -> parent;
}

void Node::setParent(int parent) {
    this -> parent = parent;
}

int Node::getMember() {
    return this -> member;
}

void Node::setRank(int rank) {
    this -> rank = rank;
}

int Node::getRank() {
    return this->rank;
}

int Node::getSize() {
    return this -> size;
}

void Node::setSize(int n) {
    this -> size = n;
}