//
// Created by David on 11/07/2024.
//
#pragma once

#include "Node.hpp"

class Router;       // Forward declaration

class AdjNode : public Node<Router> {     // Inherits from Node
    private:
        int weight = 0;
    public:
        explicit AdjNode(Router*);
        AdjNode(Router*, int);
        void setWeight(int);
        int getWeight() const;
};