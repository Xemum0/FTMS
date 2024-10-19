//
//  RunProgram.cpp
//
//

// main_program.cpp
#include <iostream>
#include "RunProgram.hpp"
#include "./ball.h"



void MainProgram::run() {
    dataLoading.display();
    reset();

    std::thread highPriorityThread(runqueries);
    std::thread lowPriorityThread(runthBall);

    highPriorityThread.join();
    lowPriorityThread.join();
}
