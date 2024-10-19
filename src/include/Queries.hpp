//
//  Queries.hpp
//

// queries.h
#pragma once
#include <iostream>
#include <cctype>
#include <conio.h>
#include "DATE.hpp"
using namespace std;
class Queries {
public:

    // Function declarations for queries
    void displayStandings();
    void displayGoalScorers();
    void displayKilometers();
    void displayBestScorers();
    Date getHiddenInput(const std::string& prompt);
};
