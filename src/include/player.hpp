#ifndef Player_hpp
#define Player_hpp
#include <iostream>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;
//#include "PositionStats.cpp"
using namespace std;
class Team;

enum playerPosition {
  GoalKeeper ,
  RightFullback,
  LeftFullback,
  CentreBack1,
  CentreBack2,
  DefensiveMidfielder,
  RightMidfielder,
  CentreMidfielder,
  Striker,
  AttackingMidfielder,
  LeftMidfielder
  };

playerPosition stringToEnum(const std::string& str) ;

string playerPositionToString(playerPosition position) ;

// one season stats
struct seasonStats{
  int numOfGoals;
  Team* team;
  int season;
};

class Player {
public:
    //////constructors
        //Copy Constructor
        
        Player(int playerId = -1, const string& playerName="", int playerNumber=1, playerPosition pos= GoalKeeper)
            : id(playerId), name(playerName), position(pos){
                setNumber(playerNumber);
                numberOfGoals = 0;
                }


    //functions to access attributes
        string getName() const { return name; }
        int getNumber() const { return number; }
        playerPosition getPosition() const { return position; }
        vector<seasonStats > getStats() const { return Stats; }
        int getId() const { return id; }
        int getNumOfGoals() const {return numberOfGoals;}
        void setId(int playerId) { id = playerId; }
        void print();
        void addGoal(int season, Team* team);
        Team* getTeam(int season) const;

    //functions to set the attributes
        void setName (const string& playerName) {name = playerName;}
        void setSeasonStats  ( vector<seasonStats >playerSeason){Stats = playerSeason;}
        bool setNumber (int playerNumber) ;
        void setPostion ( playerPosition  pos) {position = pos;}
        void setID (int playerID) {id = playerID;}
        void setOneSeasonStats(int , Team*, int);

    // json friend function:
    friend void to_json(json& j, const Player& p);
    friend void from_json(const json& j, Player& p);

private:
    // attributes
        int id;
        string name;
        int number;
        playerPosition position;
        vector<seasonStats > Stats;
        int numberOfGoals;
        ////num of goals / team/ season
};

#endif /* Player_hpp */
