//
//  Group.cpp
//  CSE167 Spring 2015 Starter Code
//

#include <iostream>

#include "Group.h"
#include <vector>
#include "Globals.h"

Group::Group() : Node()
{
    this->number = 0;
    children = new std::vector<Node*>;

}

void Group::addChild(Node* newchild){
    children->push_back(newchild);
    this->number++;
    //std::cout << "add new " <<(newchild -> name) << std::endl;
}

void Group::removeChild(std::string childname){
    
    for (std::vector<Node*>::iterator it=children->begin(); it!=children->end(); it++) {
        if(childname == (*it)->name){
            children->erase(it);
            this->number--;
        }
    }
     
}

//Loop through all Node* in children and call draw(C) passing in Matrix4 C as an argument
void Group::draw(Matrix4 C){
    
    for(int i = 0; i < children->size();i++){
        (children->at(i))->draw(C);
    }
}

//void Group::update(){
    //for(int i = 0; i < children->size();i++){
    //    (children->at(i)) -> update();
    //}
//}