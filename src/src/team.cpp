//
//  Team.cpp
//  project
//
//  Created by mac on 9/12/2023.
//
#include <iostream>
#include "Team.hpp"

// Implementations of the Team class member functions

// Implementations of the Team class member functions

    Team::Team(int playerId, const string& teamName, const string& teamCoach, const string& teamPresident)
        : id(playerId) ,name(teamName), coach(teamCoach), president(teamPresident) { 
        }

    vector<Player> Team::allPlayers;

    void Team::displayTeamInfo() const {
        cout << "-------Team Name: " << name <<  "--------" << endl;
        cout << "Team Coach: " << coach << endl;
        cout << "Team President: " << president << endl;

        cout << "Players For Every Season: " << endl;
        int i = 1;
        for (const auto& element : players) {
        cout << "***** Season: " << i << " *****" << endl;
        cout << "Season: " << element.second << " - " << element.second + 1 << endl;
        cout << "Players: " << endl;
        int j = 1;
        for (const auto& player : element.first) {
            
            cout << j << ": " << player.first->getName()
                    << " (Position: " << playerPositionToString(player.first->getPosition())  << ")"
                    << endl;
                j++;
        }
        cout << "********************" << endl;
        i++;
        }
        cout << "------------------------------" << endl;
    }

    Player* Team::getplayer(int number,int season){
            for(auto a: players) {
            if(a.second == season) {
                return a.first[number-1].first;
            }
        }
        return nullptr;
    }

    pair<vector<Player>,int > Team::setPlayersSeason(int season, vector<Player> teamPlayers){
        pair<vector<Player>,int > playerSeason;
        playerSeason.second = season;
        for (const auto& element : teamPlayers) {
            playerSeason.first.push_back(element);
        }
        return playerSeason;
    }

    void Team::addGoalScorer(int playerNum, int season) {
        for(auto a: players) {
            if(a.second == season) {
                a.first[playerNum-1].first->addGoal(season, this);
                return;
            }
        }
    }

    // void Team::setOneSeason(int season, vector<Player> teamPlayers){
    //     pair<vector<Player*>,int > playerSeason = setPlayersSeason(season, teamPlayers);
    //     players.push_back(playerSeason);
    //     currentSize++;
    // }

    Player* Team::getPlayerById(int playerId) {
        if(playerId >= 0 && playerId < allPlayers.size())
            return &allPlayers[playerId];
        return nullptr;
    }

    void Team::addPlayer(const Player& player) {
        int playerId = player.getId();
        int playerSize = allPlayers.size();
        if(playerId < 0) return;
        if (playerId < playerSize) {
            allPlayers[playerId] = player;
        } else {
            for(int i=0; i < playerId - playerSize; i++)
                allPlayers.push_back(Player(-19, "", 1));
            allPlayers.push_back(player);
        }
    }

    void Team::addPlayer(Player&& player) {
        int playerId = player.getId();
        int playerSize = allPlayers.size();
        if(playerId < 0) return;
        if (playerId < playerSize) {
            allPlayers[playerId] = move(player);
        } else {
            for(int i=0; i < playerId - playerSize; i++)
                allPlayers.push_back(Player(-19, "", 1));
            allPlayers.push_back(move(player));
        }
    }

    void to_json(nlohmann::json& j, const Team& t) {
        j["team_id"] = t.id;
        j["team_name"] = t.name;
        j["team_coach"] = t.coach;
        j["team_president"] = t.president;
        // vector<pair<vector<int>,int >> playerIds;
        // for(auto p : t.players){
        //     vector<int> ids;
        //     for(auto player : p.first){
        //         ids.push_back(player->getId());
        //     }
        //     playerIds.push_back({ids,p.second});
        // }
        // j["players"] = playerIds;
    }
    
    void from_json(const nlohmann::json& j, Team& t) {
        j.at("team_id").get_to(t.id);
        j.at("team_name").get_to(t.name);
        j.at("team_coach").get_to(t.coach);
        j.at("team_president").get_to(t.president);
        vector<pair<vector<int>,int >> playerIds;
        json JplayerIds = j.at("players");

        for (auto yearIt = JplayerIds.begin(); yearIt != JplayerIds.end(); ++yearIt) {
            vector<pair<Player*, int>> players;
            json Jplayers = yearIt.value();
            for (size_t i = 1; i < 21; i++)
            {
                
                players.push_back({Team::getPlayerById(Jplayers.at(std::to_string(i))), i});
            }
            int year = stoi(yearIt.key());
            t.players.push_back({players, year});
        }
    }

bool Team::has_season(int i) {
    for (auto p : players)
        {
            if (p.second == i)
            return true;
        }
    return false;
}