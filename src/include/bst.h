#ifndef BST_H
#define BST_H

#include<iostream>
#include "game.hpp"
using namespace std;

class BST {
    
    struct node {
        Game data;
        node* left;
        node* right;
        node(const Game & x) : data(x), left(NULL), right(NULL) {}
        node(Game &&x) : data(move(x)), left(NULL), right(NULL) {}
    };

    node* root;

    node* makeEmpty(node* t);
    node* insert(const Game &x, node* t);
    node* insert(Game &&x, node* t);
    node* findMin(node* t);
    node* findMax(node* t);
    node* remove(Game x, node* t);
    void inorder(node* t);
    node* find(node* t, Date x, int time);

public:
    BST();
    ~BST();
    void insert(const Game &x);
    void insert(Game&& x);
    void remove(Game x);
    void display();
    Game search(Date x, int time);
    vector<Game> search(Date, Date);
    void makeEmpty(); 
    Game findMin();
    Game findMax();
    Date firstGameInSeason(int);
    Date LastGameInSeason(int);


};

#endif
