#include "BST.h"
#include <stack>

BST::BST() {
    root = NULL;
}

BST::~BST() {
    root = makeEmpty(root);
}

// Function to make the tree empty
BST::node* BST::makeEmpty(node* t) {
    if(t == NULL)
        return NULL;
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    return NULL;
}

Date BST::firstGameInSeason(int season) {
    Date d1(season, 8, 1), d2(season, 8, 31);
    vector<Game> games = search(d1, d2);
    for(Game g: games) {
        if(d2 > g.getDate())
            d2 = g.getDate();
    }
    return d2;
}

Date BST::LastGameInSeason(int season) {
    Date d1(season+1, 5, 1), d2(season+1, 5, 31);
    vector<Game> games = search(d1, d2);
    for(Game g: games) {
        if(d1 < g.getDate())
            d1 = g.getDate();
    }
    return d1;
}

// Function to insert data
BST::node* BST::insert(const Game &x, node* t)
{
    if(t == NULL)
    {
        t = new node(x);
    }
    else if(x < t->data)
        t->left = insert(x, t->left);
    else
        t->right = insert(x, t->right);
    return t;
}

// Function to insert data
BST::node* BST::insert(Game &&x, node* t)
{
    if(t == NULL)
    {
        t = new node(move(x));
    }
    else if(x < t->data)
        t->left = insert(x, t->left);
    else if(x > t->data)
        t->right = insert(x, t->right);
    return t;
}

// Function to find the minimum value
BST::node* BST::findMin(node* t)
{
    if(t == NULL)
        return NULL;
    else if(t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

// Function to find the maximum value
BST::node* BST::findMax(node* t) {
    if(t == NULL)
        return NULL;
    else if(t->right == NULL)
        return t;
    else
        return findMax(t->right);
}

// Function to remove a value
BST::node* BST::remove(Game x, node* t) {
    node* temp;
    if(t == NULL)
        return NULL;
    else if(x < t->data)
        t->left = remove(x, t->left);
    else if(x > t->data)
        t->right = remove(x, t->right);
    else if(t->left && t->right)
    {
        temp = findMin(t->right);
        t->data = temp->data;
        t->right = remove(t->data, t->right);
    }
    else
    {
        temp = t;
        if(t->left == NULL)
            t = t->right;
        else if(t->right == NULL)
            t = t->left;
        delete temp;
    }

    return t;
}

// Function to display the tree in order
void BST::inorder(node* t) {
    if(t == NULL)
        return;
    inorder(t->left);
    cout << t->data.getHomeTeam().getName() << "vs" << t->data.getAwayTeam().getName() << " ";
    inorder(t->right);
}

// Function to find a value
BST::node* BST::find(node* t, Date x, int time) {
    if(t == NULL)
        return NULL;
    else if(x < t->data.getDate())
        return find(t->left, x, time);
    else if(x > t->data.getDate())
        return find(t->right, x, time);
    else if(time < t->data.getStartTime())
        return find(t->left, x, time);
    else if(time > t->data.getStartTime())
        return find(t->right, x, time);
    else
        return t;
}

// Public function to insert a value
void BST::insert(const Game &x) {
    root = insert(x, root);
}

// Public function to insert a value
void BST::insert(Game &&x) {
    root = insert(move(x), root);
}

// Public function to remove a value
void BST::remove(Game x) {
    root = remove(x, root);
}

// Public function to display the tree
void BST::display() {
    inorder(root);
    cout << endl;
}

// Public function to search for a value
Game BST::search(Date x, int time) {
    return find(root, x, time)->data;
}

// Public function to make the tree empty
void BST::makeEmpty() {
    root = makeEmpty(root);
}

// Public function to find the minimum value
Game BST::findMin() {
    return findMin(root)->data;
}

// Public function to find the maximum value
Game BST::findMax() {
    return findMax(root)->data;
}

vector<Game> BST::search(Date begin, Date end) {
    vector<Game> toreturn;
        if(end < begin) {
            cout << "end must be bigger than begin";
            return toreturn;
        }
    stack<node*> stackNodes;

    stackNodes.push(root);
    while(!stackNodes.empty()) {
        node* last = stackNodes.top();
        stackNodes.pop();

        if(last->data.getDate() < begin) {
            if(last->right != nullptr)
                stackNodes.push(last->right);
        } else if(last->data.getDate() > end) {
            if(last->left != nullptr)
                stackNodes.push(last->left);
        } else {
            toreturn.push_back(last->data);
            if(last->left != nullptr)
                stackNodes.push(last->left);
            if(last->right != nullptr)
                stackNodes.push(last->right);
        }
    }
    return toreturn;
}


