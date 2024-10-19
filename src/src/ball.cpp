// ball_simulation.cpp

#include "ball.h"
#define RESET "\033[0m"
#define RED "\033[1;31m"
std::atomic<bool> stopThreads(false);  // Flag to signal threads to stop
Pixel display[WIDTH * HEIGHT];
V2f pos;
V2f vel;

string myoptions[] = {" Display Team Standings", " Display Goal Scorers", " Display Player Kilometers", " Display Best Scorers", " Quit"};

void fill(Pixel p) {
    Pixel *ptr = display;
    size_t n = WIDTH * HEIGHT;
    while (n-- > 0) *ptr++ = p;
}

void circle(V2f c, float r) {
    V2i b = v2i2f(v2f_floor(v2f_sub(c, v2ff(r))));
    V2i e = v2i2f(v2f_ceil(v2f_sum(c, v2ff(r))));

    for (int y = b.y; y <= e.y; ++y) {
        for (int x = b.x; x <= e.x; ++x) {
            V2f p = v2f_sum(v2f2i(v2i(x, y)), v2ff(0.5f));
            V2f d = v2f_sub(c, p);
            if (v2f_sqrlen(d) <= r * r) {
                if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT) {
                    display[y * WIDTH + x] = FORE;
                }
            }
        }
    }
}

void show(void) {
    static char row[WIDTH];
    static char *table = " _^C";
    for (int y = 0; y < HEIGHT / 2; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            Pixel t = display[(2 * y + 0) * WIDTH + x];
            Pixel b = display[(2 * y + 1) * WIDTH + x];
            assert(0 <= t);
            assert(t < PIXEL_N);
            assert(0 <= b);
            assert(b < PIXEL_N);
            row[x] = table[(t << 1) | b];
        }
        fwrite(row, WIDTH, 1, stdout);
        fputc('\n', stdout);
    }
}

void back(void) {
    printf("\x1b[%dD", WIDTH);
    printf("\x1b[%dA", HEIGHT / 2);
}

void reset(void) {
    pos = v2ff(-RADIUS);
    vel = v2f(50.0f, 0.0f);
}

void runthBall() {
    while (!stopThreads) {
        vel = v2f_sum(vel, v2f(0.0f, GRAVITY * DT));
        pos = v2f_sum(pos, v2f_mul(vel, v2ff(DT)));

        if (pos.y > HEIGHT - RADIUS) {
            pos.y = HEIGHT - RADIUS;
            vel.y *= -DAMPER;
        }

        if (pos.x >= WIDTH + RADIUS + RADIUS * 2.0f) {
            reset();
        }

        fill(BACK);
        circle(pos, RADIUS);
        show();
        back();

        usleep(1000 * 1000 / FPS);
        std::this_thread::sleep_for(std::chrono::milliseconds(65));
    }
}

void displayMenu(int selectedOption) {
    system("cls");
    std::cout << "\t==============================" << std::endl;
    std::cout << "\t|      Soccer Stats Menu     |" << std::endl;
    std::cout << "\t==============================" << std::endl;
    std::cout << "\t------------ Menu ------------\n\n";
    for (int i = 0; i < 5; ++i) {
        if (i == selectedOption) {
            std::cout << "\t" << RED << "  -> " << myoptions[i] << RESET << "\n";
        } else {
            std::cout << "\t " << myoptions[i] << "\n";
        }
    }
    std::cout << "\t==============================" << std::endl;
}

void processSelection(int selectedOption) {
    Queries queries;
    switch (selectedOption) {
        case 1:
            stopThreads = true;
            queries.displayStandings();
            stopThreads = false;
            break;
        case 2:
            stopThreads = true;
            queries.displayGoalScorers();
            stopThreads = false;
            break;
        case 3:
            stopThreads = true;
            queries.displayKilometers();
            stopThreads = false;
            break;
        case 4:
            stopThreads = true;
            queries.displayBestScorers();
            stopThreads = false;
            break;
        case 5:
            std::cout << "\nExiting the program. Goodbye!" << std::endl;
            stopThreads = true;
            exit(0);
    }
}

int runqueries() {
    int selectedOption = 0;

    while (!stopThreads) {

        system("cls");
        displayMenu(selectedOption);

        // Check arrow key input
        char input = _getch();

        switch (input) {
            case 72: // Arrow key up
                if (selectedOption > 0) {
                    --selectedOption;
                } else
                    selectedOption = 4;
                break;
            case 80: // Arrow key down
                if (selectedOption < 4) {
                    ++selectedOption;
                } else
                    selectedOption = 0;
                break;
            case 13: // Enter key
                processSelection(selectedOption + 1);
                break;
            case 27: // Escape key
                return 0; // Exit the program on Escape key
        }
    }
}
