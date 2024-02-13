#include <vector>
#include <string>
#include <iostream>

struct Chair {
    double x,y;
    std::string occupant;
    Chair(double _x, double _y) : x(_x), y(_y) {}
    void report(std::ostream &out) {
        if (occupant != "") {
            out << "chair at (" << x << "," << y << ") with " << occupant << std::endl;
        } else {
            out << "chair at (" << x << "," << y << ")" << std::endl;
        }
    }
};

struct Room {
    std::vector < Chair > chairs;

    void arrange(int rows, double depth, int cols, double width) {
        chairs.resize(rows*cols,Chair(0.0,0.0));
        int index = 0;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                double x = col*width/cols;
                double y = row*depth/rows;
                chairs.at(index) = Chair(x,y);
                ++index;
            }
        }
    }

    void move(int index, double x, double y) {
        auto &chair=chairs.at(index);
        chair.x = x;
        chair.y = y;
    }

    void occupy(int index, std::string occupant) {
        auto &chair=chairs.at(index);
        chair.occupant = occupant;
    }

    void leave(int index) {
        auto &chair=chairs.at(index);
        chair.occupant = "";
    }

    void report(std::ostream &out) {
        for (int index = 0; index < chairs.size(); ++index) {
            chairs.at(index).report(out);
        }
    }
};

int main() {
    int rows = 4;
    int cols = 12;
    double width = 50;
    double depth = 30;
    Room room1;
    Room room2;

    room1.arrange(rows,depth,cols,width);
    room1.move(3,0,0);
    room1.occupy(5,"alice");

    room1.report(std::cout);
}

