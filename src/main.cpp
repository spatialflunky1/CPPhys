#include <iostream> // for non curses text output
#include <ncurses.h> // custom char location
#include <cstdlib> // random
#include <thread> // key input for quitting
#include <string>
// variables used in other threads
int key = 0;
bool running = true;

class Object {
    public:
        int weight;
        int bounciness;
        char character;
        float location[4];
        int angle; // I have no clue how I can use this but I know for a fact it is necessary
        void printInfo() {
            std::cout << "Object info:\n----------------\n";
            std::cout << "Weight: " << weight << "\n";
            std::cout << "Bounciness: " << bounciness << "\n";
            std::cout << "Character as the object: '" << character << "'\n";
            std::cout << "Location: {" << location[0] << "," << location[1] << "}\n";
        }
};

Object createBall(int weight,char character,int bounciness,int angle) {
    Object ball;
    ball.weight = weight;
    ball.character = character;
    // 10 should be max bounciness although no stopping making it higher rn
    // ^ above is a plan for later
    ball.bounciness = bounciness;
    // (currentX, currentY, previousX, previousY)
    ball.location[0]=0;
    ball.location[1]=0;
    ball.location[2]=0;
    ball.location[3]=0;
    ball.angle = angle;
    return ball;
}

Object moveObject(Object object,float amountX,float amountY,int rows,int cols) {
    object.location[2] = object.location[0];
    object.location[3] = object.location[1];
    if (object.location[0] <= rows) object.location[0] += amountX;
    if (object.location[1] <= cols) object.location[1] += amountY;
    mvaddch(object.location[2],object.location[3],' ');
    mvaddch(object.location[0],object.location[1],object.character);
    //mvprintw(object.location[0], object.location[1],std::to_string(object.location[0]).c_str());
    return object;
}

void update_key() {
    while (key != 113) {
        key = getch();
        refresh();
    }
    running = false;
}

int main() {
    Object ball = createBall(10,'o',10,0); 
    initscr(); // start curses mode
    noecho();
    curs_set(0);
    int rows,cols;
    getmaxyx(stdscr,rows,cols);
    // max screen size is outside screen
    rows--;
    cols--;
    std::thread key_thread(update_key);
    while (running) {
        ball = moveObject(ball,0.0004,0.0004,rows,cols); // goes fast at the end for some dumb reason
        refresh();
    }
    key_thread.join();
    endwin(); // exit curses mode
    printf("\x1b[2J"); // clear screen
    printf("\x1b[d"); // return to home position
    return 0;
}
