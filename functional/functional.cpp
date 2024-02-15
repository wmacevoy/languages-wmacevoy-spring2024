#include <vector>
#include <string>
#include <iostream>
#include <functional>

// create a "sequence" type of iterator that calls a function to obtain a value
template <typename T>
class Sequence {
public:
    typedef std::function<T(std::size_t)> Generator;
private:
    std::size_t index;
    Generator generator;
public:
    Sequence(std::size_t _index, const Generator& _generator)
        : index(_index), generator(_generator) {}

    T operator*() const { return generator(index); }

    Sequence& operator++() {
        ++index;
        return *this;
    }

    // Adding comparison operators for iterator functionality
    bool operator==(const Sequence& other) const { return index == other.index; }
    bool operator!=(const Sequence& other) const { return !(*this == other); }
};

// use the Sequence to generate a vector from a lambda function
template <typename T>
std::vector<T> generate(std::size_t n, const typename Sequence<T>::Generator& generator) {
    return std::vector < T > (Sequence(0,generator),Sequence(n,generator));
}

struct Chair {
    const double x,y;
    const std::string occupant;
    Chair(double _x, double _y, std::string _occupant="") 
        : x(_x), y(_y), occupant(_occupant) {}
    void report(std::ostream &out) const {
        if (occupant != "") {
            out << "chair at (" << x << "," << y << ") with " << occupant << std::endl;
        } else {
            out << "chair at (" << x << "," << y << ")" << std::endl;
        }
    }

    Chair move(double x, double y) const {
        return Chair(x,y,occupant);

    }

    Chair occupy(std::string occupant) const {
        return Chair(x,y,occupant);
    }

    Chair leave() const {
        return Chair(x,y);
    }
};


struct Room {
    const std::vector < Chair > chairs;
    Room() {}
    Room(const std::vector < Chair > &_chairs) : chairs(_chairs) {}
    Room(int rows, double depth, int cols, double width) 
    : chairs(Sequence(0,grid(rows,depth,cols,width)) {}

    static Sequence<Chair>::Generator gridGenerator(int rows, double depth, int cols, double width) {
        auto row = [cols](std::size_t i) { return i / cols; };
        auto col = [cols](std::size_t i) { return i % cols; };
        auto x = [width,cols,col](std::size_t i) { return width*col(i)/cols; };
        auto y = [depth,rows,row](std::size_t i) { return depth*row(i)/rows; };
        return [x,y](std::size_t i) { return Chair(x(i),y(i)); };
    }

    Room adjust(int location, const Chair &adjusted) const {
        auto generator = [&](std::size_t index) { 
            return (index != location) ? chairs.at(index) : adjusted;
        };
        return Room(generate<Chair>(chairs.size(),generator));
    }

    Room move(int location, double x, double y) const {
        return adjust(location,chairs.at(location).move(x,y));
    }

    Room occupy(int location, std::string occupant) const {
        return adjust(location,chairs.at(location).occupy(occupant));
    }

    Room leave(int location) const {
        return adjust(location,chairs.at(location).leave());
    }

    void report(std::ostream &out) const {
        for (auto &chair : chairs) {
            chair.report(out);
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

