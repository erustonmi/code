#ifndef BOARD_H
#define BOARD_H
#include "colormod.h"
#include <vector>
#include <iostream>
struct Cell
{
    int type;     // 0:month, 1:day, 2:dayOfWeek, 3:other
    int value;    // month:1-12, day:1-31, dayOfWeek:0-6, other:-1
    int status;   // 0:fillable, 1:unknown, 2:occupied, -1:unavailable
};

class Board
{
public:
    const static int NUM_ROWS = 8;
    const static int NUM_COLS = 7;
    Board(const Color::Modifier&, const std::vector<int>&);
    bool solvable() const;
    friend std::ostream& operator<<(std::ostream& os, const Board& p);
protected:
    Color::Modifier colorMod;
    std::vector<int> m_unavailableCells;
    int m_cellsLeft;
    Cell cells[NUM_ROWS][NUM_COLS];
    void initBoard();
};
#endif
