#include <iostream>

class Object {
    public:
        int weight;
        int bounciness;
        char charecter;
        int location[2];
        void printInfo() {
            std::cout << "Object info:\n----------------\n";
            std::cout << "Weight: " << weight << "\n";
            std::cout << "Bounciness: " << bounciness << "\n";
            std::cout << "Charecter as the object: '" << charecter << "'\n";
            std::cout << "Location: {" << location[0] << "," << location[1] << "}\n";
        }
};

Object createBall() {
    Object ball;
    ball.weight = 10;
    ball.charecter = 'o';
    // 10 should be max bounciness
    ball.bounciness = 10;
    // (x,y) <--> ([0],[1])
    ball.location[0]=0;
    ball.location[1]=0;
    return ball;
}

int main() {
    Object ball = createBall();
    ball.printInfo();

    return 0;
}
