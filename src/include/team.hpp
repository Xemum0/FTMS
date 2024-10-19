#include <iostream>
#include "player.hpp"
#include "json.hpp"
using namespace std;

#ifndef Team_hpp
#define Team_hpp



class Team {
public:
    // Constructor
        Team(int teamId = -1, const string& teamName = "" ,const string& teamCoach = "", const string& teamPresident = "");

    // function to display team information
        void displayTeamInfo() const;

    // adds new player to the  vector
    // void setOneSeason (int, vector<Player>);

    string getName() {return name;}
    string getCoach() {return coach;}
    string getPresident() {return president;}
    int getCurrentSize() {return players.size();}
    int getId() const { return id; }
    vector<pair<vector<pair<Player*,int >>,int > > getVector() {return players;}
    // check if a team has played a season
    bool has_season(int);

    void addGoalScorer(int playerNum, int season);
    Player* getplayer(int number,int season); // by his number on shirt and season

    /*//player to add function
    void addPlayer(const string& line);

    //remove player by number
    void removePlayer(int num);*/

    // json friend function:
    friend void to_json(nlohmann::json& j, const Team& t);
    friend void from_json(const nlohmann::json& j, Team& t);

    // static function
    static Player* getPlayerById(int teamId);
    static int numOfplayers(){return allPlayers.size() - 1;}
    static void addPlayer(const Player& player);
    static void addPlayer(Player&& player);

private:
    // attributes
    int id;
    string name;
    string coach;
    string president;
    vector<pair<vector<pair<Player*,int >>,int > > players;
    // int currentSize;  // Array of Player objects // what is this???????
    static vector<Player> allPlayers;

    //utility function
    pair<vector<Player>,int >  setPlayersSeason (int , vector<Player>);

};

#endif /* Team_hpp */
