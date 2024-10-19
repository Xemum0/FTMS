//
//  DataInsert.cpp
//
//

#include "DataInsert.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iomanip>
#include <chrono>
#include<fstream>
#include <thread>
using  namespace std;



BST DataLoading::bst = BST();

void DataLoading::FunctionToFillData() {
    //auto start = chrono::high_resolution_clock::now();
    ifstream o("dataset/allplayers.json");
    if (!o.is_open()) {
        std::cerr << "Failed to open allplayers the file." << std::endl;
        return;
    }
    json j = json::parse(o);
    o.close();
    Player player;
    for (json jj : j) {
        player = jj;
        Team::addPlayer(player);
    }
    //auto end = chrono::high_resolution_clock::now();
    //auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    //cout << "Time taken To insert all players: " << duration.count() << " milliseconds" << endl;

   // start = chrono::high_resolution_clock::now();
    o.open("dataset/allteams.json");
        if (!o.is_open()) {
        std::cerr << "Failed to open allteams the file." << std::endl;
        return;
    }
    j = json::parse(o);
    o.close();
    Team team;
    for (json jj : j) {
        team = jj;
        Game::addTeam(team);
    }
    //end = chrono::high_resolution_clock::now();
    //duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    //cout << "Time taken To insert all teams: " << duration.count() << " milliseconds" << endl;
    //start = chrono::high_resolution_clock::now();
    o.open("dataset/allgames.json");
        if (!o.is_open()) {
        std::cerr << "Failed to open allgames the file." << std::endl;
        return;
    }
    json jGames = json::parse(o);
    o.close();
    //end = chrono::high_resolution_clock::now();
   // duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    for(json& game : jGames) {
            Game newGame;
            newGame = game;
            bst.insert(newGame);
    }

    cout<<"Done Inserting"<<endl;
}

void DataLoading::printLoadingLine(int width, int sleepDuration) {
    std::cout << "\r[";
    for (int i = 0; i <= width; ++i) {
        std::cout << "#";
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
    }
    std::cout << "]";
    std::cout << std::endl;
}

void DataLoading::Loadingtime() {
    int loadingWidth = 40; // Adjust the width of the loading line
    int sleepDuration = 15; // Adjust the sleep duration for animation smoothness

    std::cout << "Loading..." << std::endl;
    printLoadingLine(loadingWidth, sleepDuration);
    std::cout << "Welcome to the football management system !" << std::endl;
}

void mohawrapperFunction() {
    DataLoading::FunctionToFillData();
}

void DataLoading::display() {
    std::thread t1(mohawrapperFunction);
    std::thread t2(&DataLoading::Loadingtime, this);

    // Wait for both threads to finish
    t1.join();
    t2.join();
}
