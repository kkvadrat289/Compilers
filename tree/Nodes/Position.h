#ifndef POSITION_H
#define POSITION_H

struct Position
{
    int Line;
    int Column;
    Position(int line, int column) :
        Line(line),
        Column(column)
    {}
    Position(){}
    Position(const Position& coordinates) :
        Line(coordinates.Line),
        Column(coordinates.Column)
    {}
};

#endif // POSITION_H
