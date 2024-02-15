#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <memory>

template <typename T>
std::vector<T> generate(std::size_t n, std::function<T(std::size_t)> generator)
{
    std::vector<T> ans;
    ans.reserve(n);
    for (std::size_t i=0; i<n; ++i) {
        ans.push_back(generator(i));
    }
    return ans;
}

class Chair
{
public:
    typedef std::shared_ptr<Chair> Ptr;
public:
    typedef std::function<Ptr (std::size_t)> Generator;

    const double x, y;
    const std::string occupant;

private:
    Chair(double _x, double _y, std::string _occupant = "")
        : x(_x), y(_y), occupant(_occupant) {}

public:
    void report(std::ostream &out) const
    {
        if (occupant != "")
        {
            out << "chair at (" << x << "," << y << ") with " << occupant << std::endl;
        }
        else
        {
            out << "chair at (" << x << "," << y << ")" << std::endl;
        }
    }

public:
    Ptr move(double x, double y) const
    {
        return Ptr(new Chair(x, y, occupant));
    }

public:
    Ptr occupy(std::string occupant) const
    {
        return Ptr(new Chair(x, y, occupant));
    }

public:
    Ptr leave() const
    {
        return Ptr(new Chair(x, y));
    }

public:
    static Ptr build(double x, double y, const std::string &occupant = "")
    {
        return Ptr(new Chair(x, y, occupant));
    }
};

class Room
{
public:
    typedef std::shared_ptr<Room> Ptr;

public:
    const std::vector<Chair::Ptr> chairs;

private:
    Room(std::size_t size, Chair::Generator generator) 
        : chairs(generate(size, generator)) {}

private:
    Room(int rows, double depth, int cols, double width)
        : Room(rows*cols, gridGenerator(rows, depth, cols, width)) {}

private:
    static Chair::Generator gridGenerator(int rows, double depth, int cols, double width)
    {
        auto row = [cols](std::size_t i)
        { return i / cols; };
        auto col = [cols](std::size_t i)
        { return i % cols; };
        auto x = [width, cols, col](std::size_t i)
        { return width * col(i) / cols; };
        auto y = [depth, rows, row](std::size_t i)
        { return depth * row(i) / rows; };
        auto generator = [x, y](std::size_t i)
        { return Chair::build(x(i), y(i)); };
        return generator;
    }

public:
    Ptr adjust(int location, const Chair::Ptr &adjusted) const
    {
        auto generator = [&](std::size_t index)
        {
            return (index != location) ? chairs.at(index) : adjusted;
        };
        return Ptr(new Room(chairs.size(), generator));
    }

public:
    Ptr move(int location, double x, double y) const
    {
        return adjust(location, chairs.at(location)->move(x, y));
    }

public:
    Ptr occupy(int location, std::string occupant) const
    {
        return adjust(location, chairs.at(location)->occupy(occupant));
    }

public:
    Ptr leave(int location) const
    {
        return adjust(location, chairs.at(location)->leave());
    }

public:
    void report(std::ostream &out) const
    {
        for (auto &chair : chairs)
        {
            chair->report(out);
        }
    }

public:
    static Ptr build(int rows, double depth, int cols, double width)
    {
        return Ptr(new Room(rows, depth, cols, width));
    }
};

int main()
{
    int rows = 4;
    int cols = 12;
    double width = 50;
    double depth = 30;

    Room::Ptr room = Room::build(rows, depth, cols, width);
    room->report(std::cout);
    room = room->move(3,33,33);
    room = room->occupy(8,"alice");
    room->report(std::cout);
}
