#ifndef AVLT_H
#define AVLT_H

#include<iostream>
#include "game.hpp"

class AVLT
{
    struct node
    {
        Game data;
        node* left;
        node* right;
        int height;

        node(Game x) : data(x), left(NULL), right(NULL), height(0) {}
        node(Game &&x) : data(move(x)), left(NULL), right(NULL), height(0) {}
    };

    node* root;

    void makeEmpty(node* t);
    node* insert(const Game &x, node* t);
    node* insert(Game &&x, node* t);
    node* singleRightRotate(node* &t);
    node* singleLeftRotate(node* &t);
    node* doubleLeftRotate(node* &t);
    node* doubleRightRotate(node* &t);
    node* find(node* t, Date x, int time);
    node* findMin(node* t);
    node* findMax(node* t);
    node* remove(Game x, node* t);
    int height(node* t);
    int getBalance(node* t);
    void inorder(node* t);
    void printTree(node* t, std::string indent);

public:
    AVLT();
    void insert(const Game &x);
    void insert(Game&& x);
    void remove(Game x);
    void display();
    Game search(Date x, int time);
    vector<Game> search(Date, Date);
    void makeEmpty(); 
    Game findMin();
    Game findMax();
    void printTree();

};
#endif
