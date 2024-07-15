//
// Created by David on 11/07/2024.
//

#include "../include/AdjNode.hpp"
#include "../include/Router.hpp"

AdjNode::AdjNode(Router* router)
            : Node(router) {}

AdjNode::AdjNode(Router* router, int weight)
            : Node(router), weight(weight) {}

void AdjNode::setWeight(int newWeight) {
    this->weight = newWeight;
}

int AdjNode::getWeight() const {
    return this->weight;
}