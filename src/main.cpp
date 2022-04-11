#include <iostream> // for non curses text output
#include <ncurses.h> // custom char location
#include <cstdlib> // random
#include <chrono> // chrono and thread for waiting in milliseconds
#include <thread> // key input for quitting
int key = 0;
bool running = true;

class Object {
    public:
        int weight;
        int bounciness;
        char character;
        int location[4];
        void printInfo() {
            std::cout << "Object info:\n----------------\n";
            std::cout << "Weight: " << weight << "\n";
            std::cout << "Bounciness: " << bounciness << "\n";
            std::cout << "Character as the object: '" << character << "'\n";
            std::cout << "Location: {" << location[0] << "," << location[1] << "}\n";
        }
};

Object createBall(int weight,char character,int bounciness) {
    Object ball;
    ball.weight = weight;
    ball.character = character;
    // 10 should be max bounciness although no stopping making it higher rn
    ball.bounciness = bounciness;
    // (currentX, currentY, previousX, previousY)
    ball.location[0]=0;
    ball.location[1]=0;
    ball.location[2]=0;
    ball.location[3]=0;
    return ball;
}

Object moveObject(Object object,int amountX,int amountY) {
    object.location[2] = object.location[0];
    object.location[3] = object.location[1];
    object.location[0] += amountX;
    object.location[1] += amountY;
    mvaddch(object.location[2],object.location[3],' ');
    mvaddch(object.location[0],object.location[1],object.character);
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
    Object ball = createBall(10,'o',10); 
    // Start curses mode
    initscr();
    noecho();
    curs_set(0);
    int rows,cols;
    getmaxyx(stdscr,rows,cols);
    rows--;
    cols--;
    std::thread key_thread(update_key);
    while (running) {
        ball = moveObject(ball,1,1);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    key_thread.join();
    endwin(); 
    // Exit curses mode
    printf("\x1b[2J"); // clear screen
    printf("\x1b[d"); // return to home position
    return 0;
}
