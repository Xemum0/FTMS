#include "avlt.h"
#include <stack>
using namespace std;


void AVLT::makeEmpty(node* t)
{
    if(t == NULL)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

AVLT::node* AVLT::insert(const Game &x, node* t)
{
    if(t == NULL)
    {
        t = new node(x);
    }
    else if(x < t->data)
    {
        t->left = insert(x, t->left);
        if(height(t->left) - height(t->right) == 2)
        {
            if(x < t->left->data)
                t = singleRightRotate(t);
            else
                t = doubleRightRotate(t);
        }
    }
    else if(x > t->data)
    {
        t->right = insert(x, t->right);
        if(height(t->right) - height(t->left) == 2)
        {
            if(x > t->right->data)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
        }
    }

    t->height = max(height(t->left), height(t->right))+1;
    return t;
}

AVLT::node* AVLT::insert(Game &&x, node* t)
{
    if(t == NULL)
    {
        t = new node(move(x));
    }
    else if(x < t->data)
    {
        t->left = insert(x, t->left);
        if(height(t->left) - height(t->right) == 2)
        {
            if(x < t->left->data)
                t = singleRightRotate(t);
            else
                t = doubleRightRotate(t);
        }
    }
    else if(x > t->data)
    {
        t->right = insert(x, t->right);
        if(height(t->right) - height(t->left) == 2)
        {
            if(x > t->right->data)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
        }
    }

    t->height = max(height(t->left), height(t->right))+1;
    return t;
}

AVLT::node* AVLT::singleRightRotate(node* &t)
{
    node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(u->left), t->height)+1;
    return u;
}

AVLT::node* AVLT::singleLeftRotate(node* &t)
{
    node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(t->right), t->height)+1 ;
    return u;
}

AVLT::node* AVLT::doubleLeftRotate(node* &t)
{
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

AVLT::node* AVLT::doubleRightRotate(node* &t)
{
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

AVLT::node* AVLT::findMin(node* t)
{
    if(t == NULL)
        return NULL;
    else if(t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

AVLT::node* AVLT::findMax(node* t)
{
    if(t == NULL)
        return NULL;
    else if(t->right == NULL)
        return t;
    else
        return findMax(t->right);
}

AVLT::node* AVLT::remove(Game x, node* t)
{
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
    if(t == NULL)
        return t;

    t->height = max(height(t->left), height(t->right))+1;

    if(height(t->left) - height(t->right) == 2)
    {
        if(height(t->left->left) - height(t->left->right) == 1)
            return singleLeftRotate(t);
        else
            return doubleLeftRotate(t);
    }
    else if(height(t->right) - height(t->left) == 2)
    {
        if(height(t->right->right) - height(t->right->left) == 1)
            return singleRightRotate(t);
        else
            return doubleRightRotate(t);
    }
    return t;
}

int AVLT::height(node* t)
{
    return (t == NULL ? -1 : t->height);
}

int AVLT::getBalance(node* t)
{
    if(t == NULL)
        return 0;
    else
        return height(t->left) - height(t->right);
}

void AVLT::inorder(node* t)
{
    if(t == NULL)
        return;
    inorder(t->left);
    std::cout << t->data.getHomeTeam().getName() << "vs" << t->data.getAwayTeam().getName() << " ";
    inorder(t->right);
}

AVLT::node* AVLT::find(node* t, Date x, int time) {
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


AVLT::AVLT()
{
    root = NULL;
}

void AVLT::insert(const Game & x)
{
    root = insert(x, root);
}

void AVLT::insert(Game && x)
{
    root = insert(move(x), root);
}

void AVLT::remove(Game x)
{
    root = remove(x, root);
}

void AVLT::display()
{
    inorder(root);
    std::cout << std::endl;
}

Game AVLT::search(Date x, int time)
{
    return find(root, x, time)->data;
}

Game AVLT::findMax()
{
    return findMax(root)->data;
}

Game AVLT::findMin()
{
    return findMin(root)->data;
}

void AVLT::makeEmpty()
{
    makeEmpty(root);
}

void AVLT::printTree(node* t, std::string indent)
{
    if(t != NULL)
    {
        std::cout << indent << t->data.getHomeTeam().getName() << "vs" << t->data.getAwayTeam().getName() << std::endl;
        indent += "  ";
        printTree(t->left, indent);
        printTree(t->right, indent);
    }
}

void AVLT::printTree()
{
    printTree(root, "");
    std::cout << std::endl;
}

vector<Game> AVLT::search(Date begin, Date end) {
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
        // cout << "last: " << last->data.getAwayTeam();

        if(last->data.getDate() < begin) {
            if(last->right != nullptr)
                stackNodes.push(last->right);
        } else if(last->data.getDate() > end) {
            if(last->left != nullptr)
                stackNodes.push(last->left);
        } else {
            toreturn.push_back(last->data);
            if(last->left != nullptr && last->data.getDate() > begin)
                stackNodes.push(last->left);
            if(last->right != nullptr && last->data.getDate() < end)
                stackNodes.push(last->right);
        }
    }
    return toreturn;
}
