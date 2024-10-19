//
//  DataInsert.hpp
//
//

// data_loading.hpp one time
//this used instead of #define...
#pragma once
#include "bst.h"

class DataLoading {
public:
    void display();
    static BST bst;
    static void FunctionToFillData();//this is a   function  to insert data  into objects and then into the tree
    void printLoadingLine(int width, int sleepDuration);
private:
    void Loadingtime();
};
