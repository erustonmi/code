#ifndef BOARD_H
#define BOARD_H

#include <vector>

struct Position
{
    int x;
    int y;
    int seq;
};

class Cell
{
protected:
    Position p;
    bool available;
    bool occupied;
};

class Block
{
protected:
    int width;
    int height;
    bool **arr;
};

class Board
{
public:
    Board(int w, int h);
    void markUnavailablePositions(const std::vector<Position>&);
    void reset();
    bool addBlock(Block&);
    void removeBlock(const Position&);
    ~Board();
protected:
    int width;
    int height;
    Cell **cells;
};

class Game
{
protected:
    Board b;
    std::vector<Block> blocks;
};

#endif
