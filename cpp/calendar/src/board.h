#ifndef BOARD_H
#define BOARD_H
#include "colormod.h"
#include "block.h"
#include <bits/stdc++.h>
//#include <vector>
//#include <iostream>
enum CellStatus {EMPTY=0, OCCUPIED=1, UNAVAILABLE=-1};
enum CellType {MONTH=0, DAY=1, DAY_OF_WEEK=2};
struct Cell
{
    Cell():color(Color::FG_DEFAULT){};
    CellType type;     // 0:month, 1:day, 2:dayOfWeek, 3:other
    CellStatus status;   // 0:fillable, 1:occupied, -1:unavailable
    int value;    // month:1-12, day:1-31, dayOfWeek:0-6, other:-1
    Color::Code color;
};

class Board
{
public:
    const static int NUM_ROWS = 8;
    const static int NUM_COLS = 7;
    Board(const Color::Modifier&, const std::vector<int>&,
          int numRows=NUM_ROWS, int numCols=NUM_COLS);
    bool fit(std::vector<Block>&);
    //bool fit2(std::vector<Block>&);
    friend std::ostream& operator<<(std::ostream& os, const Board& p);
protected:
    std::map<int, std::set<int>> m_adjMap;
    int m_numRows;
    int m_numCols;
    Color::Modifier m_colorMod;
    std::vector<int> m_unavailableCells;
    int m_cellsLeft;
    Cell m_cells[NUM_ROWS][NUM_COLS];
    bool m_visited[NUM_ROWS*NUM_COLS];

    void initBoard();
    int DFSUtil(int v, std::set<int>&);//, bool visited[]);
    void updateCellStatus(int r, int c, CellStatus s);
    bool solve(std::set<int>&, std::vector<Block>&);
    bool findNextOpenArea(std::set<int>&);
    //bool findNextOpenArea2(std::set<int>&);

//    std::vector<Block>::iterator fit(std::set<int>&,
 //                                    std::vector<Block>&);
    std::vector<Block>::iterator fit(std::set<int>& area,
                                std::vector<Block>& blocks,
                                const std::pair<int, int>& blockToSkip);
    void markOccupied(const std::set<int>& pos, const Color::Code&);
    void saveState(std::set<int>&);
    void restoreState(const std::set<int>&);
    void restoreAdjMap();
    void printAdjMap();
};
#endif
