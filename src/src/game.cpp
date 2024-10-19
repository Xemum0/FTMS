#include "game.hpp"


Game::Game( Team& homeTeam, Team& awayTeam, const Date& date,
           const int& startTime, const std::string& referee, int duration)
    : homeTeam(&homeTeam), awayTeam(&awayTeam), date(date), startTime(startTime), referee(referee),
      duration(std::max(duration, 90)), score{0, 0} {}


std::vector<Team> Game::teams;


void Game::endGame() {
    std::cout << "The game between " << homeTeam->getName()<<" -"<<score[1]<<"-" << " and " << awayTeam->getName()<<" -"<<score[0]<<"-"  << " has ended." << std::endl;
}

void Game::addGoal(const int & team, int playerNumber) {
    score[team]++;
    goalScorers[team].push_back(playerNumber);
}

void Game::addYellowCard(const int & team, int playerNumber) {
    yellowCards[team].push_back(playerNumber);
}

void Game::addRedCard(const int & team, int playerNumber) {
    redCards[team].push_back(playerNumber);
}

void Game::makeSubstitution(const int & team, int inPlayerNumber, int outPlayerNumber, int substitutionTime) {
    substitutions[team].push_back(std::make_tuple(inPlayerNumber, outPlayerNumber, substitutionTime));
}

// void Game::recordPlayerDistance(const int & team, int playerNumber, float distance) {
//     playerDistance[team][playerNumber] += distance;
// }


// Getters
Team Game::getHomeTeam() const {
    return *homeTeam;
}

Team Game::getAwayTeam() const {
    return *awayTeam;
}

Team* Game::getHomeTeam(int i) const {
    return homeTeam;
}

Team* Game::getAwayTeam(int i) const {
    return awayTeam;
}

Date Game::getDate() const {
    return date;
}

int Game::getStartTime() const {
    return startTime;
}

std::string Game::getRefereeName() const {
    return referee;
}

int Game::getDuration() const {
    return duration;
}
std::vector<std::vector<int>> Game::getgoalScorers()
{
    return goalScorers;
}

// Setters
void Game::setHomeTeam( Team& team) {
    homeTeam = &team;
}

void Game::setAwayTeam( Team& team) {
    awayTeam = &team;
}

void Game::setDate(const Date& newDate) {
    date = newDate;
}

void Game::setStartTime(const int& newStartTime) {
    startTime = newStartTime;
}

void Game::setRefereeName(const std::string& newReferee) {
    referee = newReferee;
}

void Game::setDuration(int newDuration) {
    duration = std::max(newDuration, 90);
}



// Overloading the > operator to compare games based on date and start time
bool Game::operator > (const Game& other) const {
    Date thisDate = this->date;
    Date otherDate = other.date;

    if (thisDate > otherDate)
        return true;
    else if (thisDate < otherDate)
        return false;

    // If dates are equal, compare start times
    return startTime > other.startTime;
}

bool Game::operator == (const Game& other) const {
    return this->date == other.date && this->startTime == other.startTime;
}

bool Game::operator < (const Game& other)const{
    return !(*this > other) and !(*this == other);
}

// adding function for json
// friend function:
void to_json(json& j, const Game& g) {
    string date = dateToString(g.date);
    j = json{
        {"homeTeam", g.homeTeam->getName()},
        {"awayTeam", g.awayTeam->getName()},
        {"date", date},
        {"startTime", g.startTime},
        {"referee", g.referee},
        {"duration", g.duration},
        {"score", g.score},
        {"goalScorers", g.goalScorers},
        {"yellowCards", g.yellowCards},
        {"redCards", g.redCards},
        {"substitutions", g.substitutions},
        {"playerDistance", g.playerDistance}
    };
}

void from_json(const json& j, Game& g) {

    string sDate, Time;
    int HteamId, AteamId;
    j["homeTeamID"].get_to(HteamId);
    j["awayTeamID"].get_to(AteamId);
    g.homeTeam = Game::getTeamById(HteamId);
    g.awayTeam = Game::getTeamById(AteamId);
    j["date"].get_to(sDate);
    g.date = stringToDate(sDate);
    j["startTime"].get_to(Time);
    g.startTime = stoi(Time.substr(0,2));
    j["referee"].get_to(g.referee);
    j["duration"].get_to(g.duration);
    string Hteam, Ateam;
    j["homeTeam"].get_to(Hteam);
    j["awayTeam"].get_to(Ateam);
    g.score = {j["score"][Ateam], j["score"][Hteam]};
    vector<int> temp;
    for(auto i : j["goalScorers"][Ateam]) {
        temp.push_back(i);
    }
    g.goalScorers.push_back(temp);
    for(auto i : j["goalScorers"][Hteam]) {
        temp.push_back(i);
    }
    g.goalScorers.push_back(temp);
    int season = dateToSeason(g.date);
    for(int i:g.goalScorers[0]) {
        g.awayTeam->addGoalScorer(i, season);
    }
    for(int i:g.goalScorers[1]) {
        g.homeTeam->addGoalScorer(i, season);
    }
    for(auto i : j["yellowCards"][Hteam]) {
        temp.push_back(i);
    }
    g.yellowCards.push_back(temp);
    for(auto i : j["yellowCards"][Ateam]) {
        temp.push_back(i);
    }
    g.yellowCards.push_back(temp);

    for(auto i : j["redCards"][Hteam]) {
        temp.push_back(i);
    }
    g.redCards.push_back(temp);
    for(auto i : j["redCards"][Ateam]) {
        temp.push_back(i);
    }
    g.redCards.push_back(temp);
    vector<tuple<int, int, int>> temp2;
    for(auto i : j["substitutions"][Hteam]) {
        temp2.push_back(tuple<int,int,int>{i["inPlayerNumber"], i["outPlayerNumber"], i["substitutionTime"]});
    }
    g.substitutions.push_back(temp2);
    for(auto i : j["substitutions"][Ateam]) {
        temp2.push_back(tuple<int,int,int>{i["inPlayerNumber"], i["outPlayerNumber"], i["substitutionTime"]});
    }
    g.substitutions.push_back(temp2);
    vector<pair<int,float>> temp3;
    vector<pair<int,float>> temp4;
    for(auto it2 = j["playerDistance"][Hteam].begin(); it2!= j["playerDistance"][Hteam].end(); it2++) {
        pair<int,float> t = {stoi(it2.key()), it2.value()};
        temp3.push_back(t);
    }
    g.playerDistance.push_back(temp3);
    for(auto it2 = j["playerDistance"][Ateam].begin(); it2!= j["playerDistance"][Ateam].end(); it2++) {
        pair<int,float> t = {stoi(it2.key()), it2.value()};
        temp4.push_back(t);
    }
    g.playerDistance.push_back(temp4);
    g.playerDistance.push_back(temp3);

}

Team* Game::getTeamById(int teamId) {
    if(teamId >= 0 && teamId < teams.size())
        return &teams[teamId];
    return nullptr;
}

void Game::DisplayTeams(){
    for (size_t i = 1; i < teams.size(); i++)
    {
        std::cout<< i << ". " << teams[i].getName()<<std::endl;
    }
}
void Game::DisplayTeams(int season){
    std::cout<<std::left<<setw(10)<< "Team ID"<<setw(35) << "|  Team Name " <<std::endl;
    cout << setfill('-') << setw(46) << "" << setfill(' ') << endl;
    for (size_t i = 1; i < teams.size(); i++)
    {
        if (teams[i].has_season(season))
        std::cout<<std::left<<setw(10)<< std::to_string(i)<<setw(35) << "| " +teams[i].getName() <<std::endl;
    }
}

Team * Game::getTeamByName(string teamName)
{
    for (int i = 0; i < teams.size(); i++)
    {

        if (teams[i].getName() == teamName)
        {
            return &teams[i];
        }
    }
    return nullptr;
}

void Game::addTeam(const Team& team) {
    int teamId = team.getId();
    int teamsSize = teams.size();
    if(teamId < 0) return;
    if (teamId < teamsSize) {
        teams[teamId] = team;
    } else {
        for(int i=0; i < teamId - teamsSize; i++)
            teams.push_back(Team(-19));
        teams.push_back(team);
    }
}

void Game::addTeam(Team&& team) {
    int teamId = team.getId();
    int teamsSize = teams.size();
    if(teamId < 0) return;
    if (teamId < teamsSize) {
        teams[teamId] = move(team);
    } else {
        for(int i=0; i < teamId - teamsSize; i++)
            teams.push_back(Team(-19));
        teams.push_back(move(team));
    }
}


// Mohanned Again

vector<Team*> Game::get_Steams(int seas) {
    vector<Team*> toreturn;
    bool t = true;
    for (size_t i = 1; i < teams.size(); i++)
    {
        if (teams[i].has_season(seas))
            toreturn.push_back(&teams[i]);
    }

    return toreturn;
}

vector<int> Game::getScore() const{
    return score;
}
