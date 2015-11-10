//
//  Node.cpp
//  CSE167 Spring 2015 Starter Code
//


#include "Node.h"
using namespace std;
#include <iostream>

Node::Node(){
    this->name = "";
    minX = INT_MAX;
    maxX = INT_MIN;
    minY = INT_MAX;
    maxY = INT_MIN;
    minZ = INT_MAX;
    maxZ = INT_MIN;
}

Node::Node(std::string newname){
    this->name = newname;
}


void Node::setName(std::string newname){
    name = newname;
}

std::string Node::getName(){
    return this->name;
}