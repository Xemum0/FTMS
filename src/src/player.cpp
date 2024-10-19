//
//  Player.cpp
//  project
//
//  Created by mac on 9/12/2023.
//
#include <iostream>
#include "Player.hpp"
#include "team.hpp"

void Player::print(){
    cout << "----Player----" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Number: " << number << endl;
    cout << "Position: " << playerPositionToString(position) << endl;
    cout << "Stats: " << endl;
    int i = 1;
    for (const auto& element : Stats) {
        cout << "***** " << i << " *****" << endl;
        cout << "Season: " << element.season << " - " << element.season + 1 << endl;
        cout << "Team: " << element.team->getName() << endl;
        cout << "Number of Goals: " << element.numOfGoals <<endl;
        i++;
    }
    cout << "---------------" << endl;
}


Team* Player::getTeam(int season) const{
    for (auto i : Stats)
    {
        if(i.season == season)
            return i.team;
    }
    return nullptr;
};

bool Player::setNumber (int playerNumber) {
    if(playerNumber >= 1 && playerNumber <= 23){
        number = playerNumber;
        return true;
        }
    cout << "The Player Number Should be between 1 and 23" << endl;
    return false;
}

void Player::setOneSeasonStats(int ssn, Team* tem, int goals=0){
    seasonStats newStat;
    newStat.season = ssn;
    newStat.numOfGoals = goals;
    newStat.team = tem;
    Stats.push_back(newStat);
}

playerPosition stringToEnum(const std::string& str) {
if (str == "GoalKeeper") return GoalKeeper;
if (str == "RightFullback") return RightFullback;
if (str == "LeftFullback") return LeftFullback;
if (str == "CentreBack1") return CentreBack1;
if (str == "CentreBack2") return CentreBack2;
if (str == "DefensiveMidfielder") return DefensiveMidfielder;
if (str == "RightMidfielder") return RightMidfielder;
if (str == "CentreMidfielder") return CentreMidfielder;
if (str == "Striker") return Striker;
if (str == "AttackingMidfielder") return AttackingMidfielder;
if (str == "LeftMidfielder") return LeftMidfielder;
// Handle the case where the string is not a valid enum value
throw std::invalid_argument("Invalid enum string: " + str);}

string playerPositionToString(playerPosition position) {
switch (position) {
    case GoalKeeper: return "GoalKeeper";
    case RightFullback: return "RightFullback";
    case LeftFullback: return "LeftFullback";
    case CentreBack1: return "CentreBack1";
    case CentreBack2: return "CentreBack2";
    case DefensiveMidfielder: return "DefensiveMidfielder";
    case RightMidfielder: return "RightMidfielder";
    case CentreMidfielder: return "CentreMidfielder";
    case Striker: return "Striker";
    case AttackingMidfielder: return "AttackingMidfielder";
    case LeftMidfielder: return "LeftMidfielder";
    default: return "Unknown";
}
}

void Player::addGoal(int season, Team* team){
    for(auto& stat : Stats){
        if(stat.season == season && stat.team == team){
            stat.numOfGoals++;
            numberOfGoals++;
            return;
        }
    }
    setOneSeasonStats(season, team, 1);
    numberOfGoals++;
}

// season stats struct json function
// void to_json(json& j, const seasonStats& s){
//     j["numOfGoals"] = s.numOfGoals;
//     j["Team"] = s.Team;
//     j["season"] = s.season;
// }

// void from_json(const json& j, seasonStats& s){
//     j.at("numOfGoals").get_to(s.numOfGoals);
//     j.at("Team").get_to(s.Team);
//     j.at("season").get_to(s.season);
// }

// player json function

void to_json(json& j, const Player& p) {
    j["player_id"] = p.id;
    j["player_name"] = p.name;
    j["player_position"] = playerPositionToString(p.position);
}

void from_json(const json& j, Player& p) {
    j.at("player_id").get_to(p.id);
    j.at("player_name").get_to(p.name);
    string plPosition;
    j.at("player_position").get_to(plPosition);
    p.position = stringToEnum(plPosition);
}

