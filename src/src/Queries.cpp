//
//  Queries.cpp
//
//

#include "Queries.hpp"
#include "team.hpp"
#include "Game.hpp"
#include "DataInsert.hpp"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <ctime>
#include "pbPlots.hpp"
#include "supportLib.hpp"
using namespace std;
using namespace std::chrono;
int getchoice();//only one and two allowed at input
int getChoice(int start, int end);
void tournamentScorrers();
void teamScorrers();
void query3(int);
void query1(const Date& st, const Date & ed);
void query2(const Date& st, const Date & ed);
bool print_plots(vector<double>& weeks, vector<double>& goals );
void printHorizontalLine(int);
int getseason(const std::string& );
Date getDDMM(const std::string& , const Date&);
bool isValidDate(int year, int month, int day) {
    // Check if the date is valid using the standard C++ library
    std::tm time_in = {0, 0, 0, day, month - 1, year - 1900};
    std::time_t time_temp = std::mktime(&time_in);
    const std::tm* time_out = std::localtime(&time_temp);

    return time_out && time_out->tm_mday == day && time_out->tm_mon == month - 1 && time_out->tm_year == year - 1900;
}

bool print_plots(vector<double>& weeks, vector<double>& goals ){
    bool success;
    StringReference *errorMessage = new StringReference();
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	vector<double> xs = weeks;
	vector<double> ys = goals;
	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &xs;
	series->ys = &ys;
	series->linearInterpolation = true;
	series->lineType = toVector(L"solid");
	series->lineThickness = 2;
	series->color = GetGray(1);

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"number of goals scored against weeks");
	settings->xLabel = toVector(L"number of weeks");
	settings->yLabel = toVector(L"number of goals");
	settings->scatterPlotSeries->push_back(series);
	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if(success){
        vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, "temp.png");
        DeleteImage(imageReference->image);
	}else{
        cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            wcerr << c;
        }
        cerr << endl;
	}

	return success;
}

void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

struct goalers{
    Player* player;
    int numOfgoals;
    int numInteam;
    goalers (const goalers & rh){
    player = rh.player;
    numOfgoals = rh.numOfgoals;
    numInteam = rh.numInteam;
    }
    goalers(Player* t = nullptr, int ng = 1,int num = 0)
        : player(t), numOfgoals(ng), numInteam(num) {}
};
void goalers_display(const vector<goalers>&,int,int ) ;
bool comparegoalers(const goalers&, const goalers&);

struct Teamstand {
    Team* team;
    int gamesPlayed = 0;
    int wins = 0;
    int losses = 0;
    int draws = 0;
    int goalsDifference = 0;
    int points = 0;
    Teamstand (const Teamstand & rh){
    team = rh.team;
    gamesPlayed = rh.gamesPlayed;
    wins = rh.wins;
    losses = rh.losses;
    draws = rh.draws;
    goalsDifference = rh.goalsDifference;
    points = rh.points;
    }
    Teamstand(Team* t = nullptr, int gp = 0, int w = 0, int l = 0, int d = 0, int gd = 0, int p = 0)
        : team(t), gamesPlayed(gp), wins(w), losses(l), draws(d), goalsDifference(gd), points(p) {}
};
void stand_displayer(vector<Teamstand>&);
bool compareTeams(const Teamstand& a, const Teamstand& b);
void printer() {
    while (true) {
        system("cls");
//.................................................................

        std::cout << "moh is page 2 " << std::endl;//your logic is here



//.................................................................

        char input = _getch();

        switch (input) {
            case 75:
                return;
            default:
                break;
        }

        sleep(100);
    }
}

void Queries::displayStandings() {
    system("cls");
    int selectedSeason = getseason("Enter the season year (between 2000 and 2018): ");
    Date firstdate = DataLoading::bst.firstGameInSeason(selectedSeason);
    Date lastdate = DataLoading::bst.LastGameInSeason(selectedSeason);
    Date d1;
    std::cout << "Season start form "<<dateToString(firstdate)<<" to "<<dateToString(lastdate)<<endl;
    d1 = getDDMM("Enter a date to view league standings. (DDMM): ",firstdate);
    while (true) {
        system("cls");

//.................................................................

        std::cout<<"Season "<<selectedSeason<<"/"<<selectedSeason+1<<endl;
        query1(firstdate,d1);
        cout<<"Press left arrow key to return to main menu"<<endl;
//.................................................................
        while (true)
        {
        char input = _getch();
        switch (input) {
            case 75:
                return;
            default:
                break;
        }
        }

    }
}


void Queries::displayGoalScorers() {
    system("cls");
    int selectedSeason = getseason("Enter the season year (between 2000 and 2018): ");
    Date firstdate = DataLoading::bst.firstGameInSeason(selectedSeason);
    Date lastdate = DataLoading::bst.LastGameInSeason(selectedSeason);
    Date d1;
    std::cout << "Season start form "<<dateToString(firstdate)<<" to "<<dateToString(lastdate)<<endl;
    d1 = getDDMM("Enter a date to view Goal scorrers. (DDMM): ",firstdate);
    while (true) {
        system("cls");

//.................................................................
        std::cout<<"Season "<<selectedSeason<<"/"<<selectedSeason+1<<endl;
        query2(firstdate,d1);
        system("cls");
        cout<<"\nPress left arrow key to return to main menu"<<endl;
//.................................................................
        while (true)
        {
        char input = _getch();
        switch (input) {
            case 75:
                return;
            default:
                break;
        }
        }
}
}

void Queries::displayKilometers() {
        system("cls");
    std::cout << "\nPlayer Kilometers:" << std::endl;
    int selectedSeason = getseason("Enter the season year (between 2000 and 2018): ");
    query3(selectedSeason);
    cout<<"\nPress left arrow key to return to main menu"<<endl;
//.................................................................
        while (true)
        {
        char input = _getch();
        switch (input) {
            case 75:
                return;
            default:
                break;
        }
        }
}

void Queries::displayBestScorers() {
    system("cls");
    std::cout << "\nBest Scorers:" << std::endl;
    std::cout << "1. Display The Best Scorers of a Team" << std::endl;
    std::cout << "2. Display The Best Scorers in the Tournament" << std::endl;
    int choice = getchoice();
    if (choice == 2)
        tournamentScorrers();
    else if (choice == 1)
        teamScorrers();
    system("cls");
    cout<<"\nPress left arrow key to return to main menu"<<endl;
    while (true)
    {
    char input = _getch();
    switch (input) {
        case 75:
            return;
        default:
            break;
    }
    }
}

int getchoice(){
    char ch;
    std::string input;
    while (true)
    {
        ch = getch();
        if (isdigit(ch) && input.length() == 0){
            if (ch== '1'||ch =='2'){
                input.push_back(ch);
                cout<<ch;
                }
        }
        else if (ch == 13){
            return stoi(input);
        }
        else if (ch == 8 && !input.empty()) {
            input.pop_back();
            std::cout << "\b \b";
        }
        else if (ch == 27) { // esc
            return 0;
        }
    }
}


int getseason(const std::string& prompt) {
    std::string input;
    char ch;
    std::cout << prompt;

    while (true) {
        ch = _getch();

        if (isdigit(ch) && input.length() < 4) {
            input.push_back(ch);
            std::cout << ch;
        } else if (ch == 13 && input.length() == 4) {
            int season = stoi(input);
            if (2000 <= season && season <= 2018) {
                std::cout << "/" << season + 1 << std::endl;
                return season;
            } else {
                system("cls");
                input.clear();
                std::cout << "Seasons available are from 2000/2001 to 2018/2019" << std::endl;
                std::cout << prompt;
            }
        } else if (ch == 8 && !input.empty()) {
            input.pop_back();
            std::cout << "\b \b";
        }
    }
}



Date Queries::getHiddenInput(const std::string& prompt) {
    std::string input;
    char ch;

    std::cout << prompt;

    while (true) {
        ch = _getch();  // Use _getch() from conio.h to get a character without echoing

        if (ch == 13) {  // Enter key pressed
            break;  // Stop reading input when Enter is pressed
        }

        if (isdigit(ch)) {
            input.push_back(ch);
            std::cout << ch;  // Display a visual representation for each entered character

            if (input.length() == 2 || input.length() == 4) {
                std::cout << "-";
            }

            if (input.length() == 8) {
                break;  // Stop reading input after 8 characters (DD-MM-YYYY)
            }
        } else if (ch == 8 && !input.empty()) {
            // Backspace key pressed
            input.pop_back();
            std::cout << "\b \b";  // Erase the last character from the visual representation
        }
    }

    std::cout << std::endl;  // Move to the next line after input
        // Extract day, month, and year as integers
    int day = std::stoi(input.substr(0, 2));
    int month = std::stoi(input.substr(2, 2));
    int year = std::stoi(input.substr(4, 4));
    Date d1(year,month,day);
    return d1;
}


Date getDDMM(const std::string& prompt, const Date& st) {
    std::string input;
    char ch;
    std::cout << prompt;

    while (true) {
        ch = _getch();

        if (isdigit(ch) && input.length() < 4) {
            input.push_back(ch);// ===
            std::cout << ch;
            if (input.length() == 2) {
                    std::cout << "-";
                }
        } else if (ch == 13 && input.length() == 4) { // pressed enter
            int month = std::stoi(input.substr(2, 2));
            int day = std::stoi(input.substr(0, 2));


            if (month < 1 || month > 12 || day < 1 || day > 31) {
                std::cout << "\nError: Invalid month or day. Please enter a valid date." << std::endl;
                input.clear();
                std::cout << prompt;
                continue;
            }

            int finalYear;
            if (month == 8)
                if (day<st.GetDay())
                finalYear = st.GetYear();
                else
                    finalYear = st.GetYear()+1;
            else
            finalYear = (month > 8) ? st.GetYear() : st.GetYear()+1;
            if (!isValidDate(finalYear, month, day)) {
                std::cout << "\nError: Invalid date. Please enter a valid date." << std::endl;
                input.clear();
                std::cout << prompt;
                continue;
            }

            return Date(finalYear, month, day);
        } else if (ch == 8 && !input.empty()) {

            input.pop_back();
            std::cout << "\b \b";
        }
    }
}


void query1(const Date& st, const Date & ed){
    Date d1=st;
    Date d2 = ed;
    vector<Game> dgames;
    auto start = chrono::high_resolution_clock::now();
    dgames = DataLoading::bst.search(d1,d2);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken To retreive matches: " << duration.count() << " milliseconds" << endl;
    cout<<"number of matches: "<<dgames.size()<<endl;
    unordered_map<int, Teamstand> teamst;
    {
        vector<Team*> temp = Game::get_Steams(st.GetYear());
        for (size_t i = 0; i < 20; i++)
        {
            teamst.insert({temp[i]->getId(), Teamstand(temp[i])});
        }
    }
    int score0, score1;
    int t0, t1;
    for (Game game : dgames)
    {
        t0 = game.getAwayTeam().getId();
        t1 = game.getHomeTeam().getId();
        teamst[t1].gamesPlayed++;
        teamst[t0].gamesPlayed++;
        score0 = game.getScore()[0];
        score1 = game.getScore()[1];
        if (score0 == score1 ) {
            teamst[t1].draws++;
            teamst[t0].draws++;
            teamst[t1].points++;
            teamst[t0].points++;
        }
        else if (score0 > score1 ) {
            teamst[t1].losses++;
            teamst[t0].wins++;
            teamst[t0].points+=3;
        }
        else if (score0 < score1 ) {
            teamst[t1].wins++;
            teamst[t0].losses++;
            teamst[t1].points+=3;
        }
        teamst[t0].goalsDifference += score0 - score1;
        teamst[t1].goalsDifference += score1 - score0;
    }


    vector<Teamstand> go;
    for (auto i : teamst)
    {
        go.push_back(i.second);
    }
    stand_displayer(go);
}
void printHorizontalLine(int width) {
    cout << setfill('-') << setw(width) << "" << setfill(' ') << endl;
}
void stand_displayer(vector<Teamstand>& teams){
        sort(teams.begin(), teams.end(), compareTeams);
        std::cout << "\nFootball League Standings:\n";
        printHorizontalLine(71);  // Adjust the width based on the total width of the table
        std::cout << std::left << std::setw(25) << "| TEAM" << std::setw(10) << "| PTS" << std::setw(10) <<"| PL" << std::setw(10) << "| GD" << std::setw(15) << "| W-D-L" << "|\n";
        printHorizontalLine(71);
        for (const auto& team : teams) {
            std::cout << std::left << std::setw(25) << "| " + team.team->getName()
                    << std::setw(10) << "| " + std::to_string(team.points)
                    << std::setw(10) << "| " + std::to_string(team.gamesPlayed)
                    << std::setw(10) << "| " + std::to_string(team.goalsDifference)
                    << std::setw(15) << "| " + std::to_string(team.wins) + "-" + std::to_string(team.draws) + "-" + std::to_string(team.losses) << "|\n";
        }
        printHorizontalLine(71);
        cout << "*PTS : Points,PL: Games played, GD: Goal difference, W: Wins, D: Draws, L: Loses\n"<<endl;
}
bool compareTeams(const Teamstand& a, const Teamstand& b) {
    if (a.points != b.points)
        return a.points > b.points;
    return a.goalsDifference > b.goalsDifference;
}


void goalers_display(const vector<goalers>& go,int startIdx, int endIdx) {
    std::cout << "\n Goal scorers:\n";
    printHorizontalLine(46);
    std::cout << std::left << std::setw(35) << "| Player" << std::setw(10) << "| goals"<< "|\n";;
    printHorizontalLine(46);
    for (int i = startIdx; i < endIdx && i< go.size(); ++i)
    {
        std::cout << std::left << std::setw(35) << "| "+ std::to_string(i+1)+". " + go[i].player->getName()
                    << std::setw(10) << "| " + std::to_string(go[i].numOfgoals)<< "|\n";
    }
    printHorizontalLine(46);

}
bool comparegoalers(const goalers& a, const goalers& b) {
        return a.numOfgoals > b.numOfgoals;
}

void query2(const Date& st, const Date & ed){
    Date d1=st;
    Date d2 = ed;
    vector<Game> dgames;
    dgames = DataLoading::bst.search(d1,d2);
    unordered_map<int, goalers> players_go;
    std::vector<std::vector<int>> goalScorers;
    Player *ptemp;
    int plId;
    for (Game game : dgames)
    {
        goalScorers = game.getgoalScorers();
        for (int j : goalScorers[0])
        {
            ptemp = game.getAwayTeam().getplayer(j,d1.GetYear());
            if(ptemp->getTeam(d1.GetYear())->getName()!= game.getAwayTeam().getName()){
                ptemp = game.getAwayTeam().getplayer(j+6,d1.GetYear());
            }
            plId = ptemp->getId();
            if (players_go.find(plId) == players_go.end()){
                players_go.insert({plId,goalers(ptemp,1,j)});
            }
            else {
                players_go[plId].numOfgoals++;
            }
        }
        for (int j : goalScorers[1])
        {
            ptemp = game.getHomeTeam().getplayer(j,d1.GetYear());
            if(ptemp->getTeam(d1.GetYear())->getName()!= game.getHomeTeam().getName()){
                ptemp = game.getAwayTeam().getplayer(j+6,d1.GetYear());
            }
            plId = ptemp->getId();
            if (players_go.find(plId) == players_go.end()){
                players_go.insert({plId, goalers(ptemp,1,j)});
            }
            else {
                players_go[plId].numOfgoals++;
            }
        }

    }
    vector<goalers> go;
    for (auto i : players_go)
    {
        go.push_back(i.second);
    }
    sort(go.begin(), go.end(), comparegoalers);
    int currentPage = 0;
    int totalPages = go.size() / 20;
    int num = 0;
    std::string input;
    while (true) {
        int startIdx = currentPage * 20;
        int endIdx = (currentPage + 1) * 20;
        system("cls");
        goalers_display(go, startIdx, endIdx);
        std:: cout<<"use left and right arrows to navigate, esc to exit or Enter to choose player \nPlease enter the player's number To display graph of goal scored against weeks  : "<<input;
        char ch = _getch();
        if (ch == 77) {
            if (currentPage < totalPages - 1) {
                ++currentPage;
            }
        } else if (ch == 75) {
            if (currentPage > 0) {
                --currentPage;
            }
        }
        else if (ch == 27) {
            return;
        }
        else if (isdigit(ch)&& input.length()<4){
            input.push_back(ch);
            std::cout<<ch;
        }
        else if (ch == 13 && input.length() != 0){
            num = std::stoi(input);
            if (num > go.size() || num == 0){
                cout<<"Please enter a number in the range 1 to "<<go.size()<<endl;
                num = 0;
                input.clear();
                continue;
                }
            break;
        }
    }
    if (num == 0) return; // that's a safety trigger
        Team* selTeam = go[num-1].player->getTeam(d1.GetYear());
        int numInteam = go[num-1].numInteam;
        int weeks = 0;
        int totgoal = 0;
        vector<double> goalspl;
        vector<double> weekspl;
    for (Game game : dgames)
    {
        if (game.getHomeTeam().getId() == selTeam->getId()){
            goalScorers = game.getgoalScorers();
            weeks++;
            for (int j : goalScorers[1]){
                if (j == numInteam)
                totgoal++;
            }
            goalspl.push_back(totgoal);
            weekspl.push_back(weeks);

        }
        else if (game.getAwayTeam().getId() == selTeam->getId()){
            goalScorers = game.getgoalScorers();
            weeks++;
            for (int j : goalScorers[0]){
            if (j == numInteam)
            totgoal++;
            }
            goalspl.push_back(totgoal);
            weekspl.push_back(weeks);
        }
    }
    char y;
    if (weekspl.size()!= goalspl.size())
        cout<<"Something wrong happend!!"<<endl;
    else{
        if(print_plots(weekspl,goalspl))
        {
            system("temp.png");
	    }
        else
	        cout<<"Something Wrong happend\n";
        }

}

bool compPlayer(const Player* p1,const Player* p2){
    return p1->getNumOfGoals() > p2->getNumOfGoals();
}
void displayPage(vector<Player*> arr,int startIdx,int endIdx){

    std::cout << "\n Goal scorers:\n";
    printHorizontalLine(46);
    std::cout << std::left << std::setw(35) << "| Player" << std::setw(10) << "| goals"<< "|\n";;
    printHorizontalLine(46);
    for (int i = startIdx; i < endIdx; ++i)
    {
        std::cout << std::left << std::setw(35) << "| "+ std::to_string(i+1)+". " + arr[i]->getName()
                    << std::setw(10) << "| " + std::to_string(arr[i]->getNumOfGoals())<< "|\n";
    }
    printHorizontalLine(46);
}

void tournamentScorrers(){
    int numOfplayers = Team::numOfplayers();
    vector<Player*> allpl;
    for (int i = 1; i<=numOfplayers;i++)
        allpl.push_back(Team::getPlayerById(i));
    sort(allpl.begin(),allpl.end(),compPlayer);
        int currentPage = 0;
    int totalPages = allpl.size() / 20;
    while (true) {
        int startIdx = currentPage * 20;
        int endIdx = (currentPage + 1) * 20;
        system("cls");
        displayPage(allpl, startIdx, endIdx);
        std:: cout<<"use left and right arrows to navigate, esc to exit"<<std::endl;
        std::string input;

        char ch = _getch();
        if (ch == 77) {
            if (currentPage < totalPages - 1) {
                ++currentPage;
            }
        } else if (ch == 75) {
            if (currentPage > 0) {
                --currentPage;
            }
        }
        else if (ch == 27) {
            return;
        }
    }
}

void teamScorrers(){
    int numOfteams = Game::numOfteams();
    vector<Team*> seasont;
    for (int i = 1; i <= numOfteams; i++)
    {
            seasont.push_back(Game::getTeamById(i));
    }
    system("cls");
    for (int i = 0; i < seasont.size(); i++)
    {
        std::cout<<i+1<<". "<<seasont[i]->getName()<<endl;
    }
    cout<<"\nPlease enter the number of the Team: \n";
    int teamsel;
    teamsel = getChoice(1,seasont.size());
    int numOfplayers = Team::numOfplayers();
    vector<Player*> allpl;
    for (int i = 1; i<=numOfplayers;i++)
        allpl.push_back(Team::getPlayerById(i));
    vector<goalers> goalas;
    for (auto player : allpl)
    {
        bool has = false; // if the player has entered the list or not
        for (const auto& stat: player->getStats()){
            if(stat.team->getId() == seasont[teamsel-1]->getId()){
                if(!has){
                    goalas.push_back(goalers(player,stat.numOfGoals));
                    has = true;
                }
                else {
                    goalas.back().numOfgoals += stat.numOfGoals;
                }
            }
        }
    }
    sort(goalas.begin(), goalas.end(), comparegoalers);

    int currentPage = 0;
    int totalPages = goalas.size() / 20;
    while (true) {
        int startIdx = currentPage * 20;
        int endIdx = (totalPages != 0) ? (currentPage + 1) * 20 : goalas.size();
        system("cls");
        goalers_display(goalas, startIdx, endIdx);
        std:: cout<<"use left and right arrows to navigate, esc to exit";
        char ch = _getch();
        if (ch == 77) {
            if (currentPage < totalPages - 1) {
                ++currentPage;
            }
        } else if (ch == 75) {
            if (currentPage > 0) {
                --currentPage;
            }
        }
        else if (ch == 27) {
            return;
        }
    }
}

int getChoice(int start, int end) {
    char ch;
    std::string input;

    while (true) {
        ch = _getch();

        if (isdigit(ch)&& input.length()<=2) {
            {
                input.push_back(ch);
                std::cout << ch;
            }
        } else if (ch == 13) { // Enter key
            if (!input.empty()&&  (stoi(input) >= start && stoi(input) <= end)) {
                return stoi(input);
            }
            std::cout<<"\nreenter your choice: "<<std::endl;
            input.clear();
        } else if (ch == 8 && !input.empty()) { // Backspace key
            input.pop_back();
            std::cout << "\b \b";
        } else if (ch == 27) { // Escape key
            return 0;
        }
    }
}

void query3(int selectedSeason){
    int numOfteams = Game::numOfteams();
    vector<Team*> seasonteams;
    for (int i = 1; i <= numOfteams; i++)
    {   if (Game::getTeamById(i)->has_season(selectedSeason))
            seasonteams.push_back(Game::getTeamById(i));
    }
    system("cls");
    for (int i = 0; i < seasonteams.size(); i++)
    {
        std::cout<<i+1<<". "<<seasonteams[i]->getName()<<endl;
    }
    cout<<"\nPlease enter the number of the Team: \n";
    int teamsel;
    teamsel = getChoice(1,seasonteams.size());
    system("cls");
    std::cout<<"You selected "<<seasonteams[teamsel-1]->getName()<<std::endl;
    Date firstdate = DataLoading::bst.firstGameInSeason(selectedSeason);
    Date lastdate = DataLoading::bst.LastGameInSeason(selectedSeason);
    Date d2;
    std::cout << "Season start form "<<dateToString(firstdate)<<" to "<<dateToString(lastdate)<<endl;
    d2 = getDDMM("Enter a date to view Games played by the team. (DDMM): ",firstdate);
    cout<<endl;
    vector<Game> dgames;
    dgames = DataLoading::bst.search(firstdate,d2);
    vector<Game> teamgames;
    for (Game game : dgames)
    {
        if (game.getHomeTeam().getId() == seasonteams[teamsel-1]->getId()
        ||game.getAwayTeam().getId() == seasonteams[teamsel-1]->getId() ){
        teamgames.push_back(game);
        cout<<teamgames.size()<<" ";
        game.endGame();
        }
    }
   int gamesel;
    gamesel = getChoice(1,teamgames.size());
    cout<<"\n";
    std::vector<std::vector<pair<int,float>>> distances =teamgames[gamesel-1].getDistances();
    vector<pair<int,float>> temp3;
    if (teamgames[gamesel-1].getHomeTeam().getId() == seasonteams[teamsel-1]->getId())
    {

        temp3 = distances[1];
    }
    else if (teamgames[gamesel-1].getAwayTeam().getId() == seasonteams[teamsel-1]->getId())
    {

        temp3 = distances[0];
    }
    std::cout << std::fixed << std::setprecision(2);
    for (auto i : temp3)
    {

        cout<<std::left<<std::setw(25)<<seasonteams[teamsel-1]->getplayer(i.first,selectedSeason)->getName()<<setw(12)<<i.second<<endl;
    }
}
