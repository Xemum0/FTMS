#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include "date.hpp"
#include "json.hpp"
#include "team.hpp"
using json = nlohmann::json;
class Game
{
public:
    Game(Team &homeTeam, Team &awayTeam, const Date &date,
        const int &startTime, const std::string &referee = "", int duration = 90);

    Game() = default;

    void endGame();

    void addGoal(const int &team, int playerNumber);

    void addYellowCard(const int &team, int playerNumber);

    void addRedCard(const int &team, int playerNumber);

    void makeSubstitution(const int &team, int inPlayerNumber, int outPlayerNumber, int substitutionTime);

    // void recordPlayerDistance(const int &team, int playerNumber, float distance);

    bool operator>(const Game &other) const;
    bool operator<(const Game &other) const;
    bool operator==(const Game &other) const;

    // Getters
    Team getHomeTeam() const;
    Team getAwayTeam() const;
    Team* getHomeTeam(int) const;
    Team* getAwayTeam(int) const;
    Date getDate() const;
    int getStartTime() const;
    std::string getRefereeName() const;
    int getDuration() const;
    vector<int> getScore() const;
    std::vector<std::vector<int>> getgoalScorers();
    std::vector<std::vector<pair<int,float>>> getDistances(){return playerDistance;};

    // Setters
    void setHomeTeam(Team &team);
    void setAwayTeam(Team &team);
    void setDate(const Date &date);
    void setStartTime(const int &startTime);
    void setRefereeName(const std::string &referee);
    void setDuration(int duration);
    std::string TeamIntoString(int num)
    { // 1 for  hometeam and 2 for away team
        if (num == 1)
            return homeTeam->getName();
        else
            return awayTeam->getName();
    }

    // friend function:
    friend void to_json(json &j, const Game &);
    friend void from_json(const json& j, Game& g);
    static void addTeam(const Team& team);
    static void addTeam(Team&& team);
    static Team *getTeamById(int id);
    static Team *getTeamByName(string teamName);
    static void DisplayTeams();
    static void DisplayTeams(int season);
    static int numOfteams(){return teams.size() -1;}

    // a wild mohanned entered the conversation
    // a function that return teams that has played in a season
    static vector<Team*> get_Steams(int);

private:
    Team *homeTeam;
    Team *awayTeam;
    Date date;
    int startTime;
    std::string referee;
    int duration;
    static std::vector<Team> teams;
    std::vector<int> score; // Assuming teams are identified by indices 1 for hometeam and 0 for away team
    std::vector<std::vector<int>> goalScorers;
    std::vector<std::vector<int>> yellowCards;
    std::vector<std::vector<int>> redCards;
    std::vector<std::vector<std::tuple<int, int, int>>> substitutions;
    std::vector<std::vector<pair<int,float>>> playerDistance; // Assuming teams and players are identified by indices
};

#endif // game_hpp
