#ifndef BOARD_H
#define BOARD_H
#include "colormod.h"
#include "block.h"
#include <bits/stdc++.h>
//#include <vector>
//#include <iostream>
enum CellStatus {EMPTY=0, OCCUPIED=1, UNAVAILABLE=-1};
enum DayOfWeek {SUN=45, MON, TUE, WED, THU=53, FRI, SAT};
enum Month {JAN=0, FEB, MAR, APR, MAY, JUN, JUL=7,
            AUG, SEP, OCT, NOV, DEC};
struct Cell
{
    Cell():color(Color::FG_DEFAULT){};
    CellStatus status;
    Color::Code color;
};

class Board
{
public:
    const static int NUM_ROWS = 8;
    const static int NUM_COLS = 7;
    Board(const Color::Modifier&, const std::vector<int>&,
          int numRows=NUM_ROWS, int numCols=NUM_COLS);
    void setDate(Month m, int d, int dow);
    void initBoard();
    bool fit(std::vector<Block>&);
    friend std::ostream& operator<<(std::ostream& os, const Board& p);
protected:
    std::map<int, std::set<int>> m_adjMap;
    int m_numRows;
    int m_numCols;
    Color::Modifier m_colorMod;
    std::vector<int> m_unavailableCells;
    Cell m_cells[NUM_ROWS][NUM_COLS];
    bool m_visited[NUM_ROWS*NUM_COLS];

    int DFSUtil(int v, std::set<int>&);
    bool solve(std::set<int>&, std::vector<Block>&);
    bool findNextOpenArea(std::set<int>&);

    int fit(std::set<int>&, std::vector<Block>&, int);
    void markOccupied(const std::set<int>& pos, const Color::Code&);
    void saveState(std::set<int>&);
    void restoreState(const std::set<int>&);
    void restoreAdjMap();
    void printAdjMap();
    bool areaUnsolvable(const std::set<int>& area);
};
#endif
