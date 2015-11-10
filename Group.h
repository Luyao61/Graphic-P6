//
//  Group.hpp
//  CSE167 Spring 2015 Starter Code
//

#ifndef Group_h
#define Group_h

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Node.h"
#include "Geode.h"

class Group : public Node
{
    
public:
    //variables
    std::vector<Node*> *children;
    int number;
    
    //constructor
    Group();
    
    //methods
    void addChild(Node* newchild);
    void removeChild(std::string childname);
    void draw(Matrix4 C);
    //void update();

};

#endif /* Group_h */
