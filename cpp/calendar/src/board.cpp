#include "board.h"
#include <algorithm>

using namespace std;

Board::Board(const Color::Modifier& cm, const std::vector<int>& v):
colorMod(cm),
m_unavailableCells(v),
m_cellsLeft(0)
{
    initBoard();
}

void Board::initBoard()
{
    const vector<int>& v = m_unavailableCells;
    m_cellsLeft = 0;
    for(int i = 0; i < NUM_ROWS; ++i)
    {
        for(int j = 0; j < NUM_COLS; ++j)
        {
            if(find(v.begin(), v.end(), i*NUM_COLS+j) != v.end())
            {
                cells[i][j].status = -1;
            }
            else
            {
                cells[i][j].status = 1;
                m_cellsLeft++;
            }
        }
    }
}

bool Board::solvable() const
{
    for(int i = 0; i < NUM_ROWS; ++i)
    {
        for(int j = 0; j < NUM_COLS; ++j)
        {
            if(cells[i][j].status == -1 ||
               cells[i][j].status == 2) continue;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    //os << "num empty cells:" << b.m_cellsLeft << endl;
    const char* RESET_COLOR = "\033[0m";
    for(int i = 0; i < Board::NUM_ROWS; ++i)
    {
        for(int j = 0; j < Board::NUM_COLS; ++j)
        {
            if(b.cells[i][j].status == -1)
            {
                os << b.colorMod << "X" << RESET_COLOR;
            }
            else if(b.cells[i][j].status == 2)
            {
                os << b.colorMod << "O" << RESET_COLOR;
            }
            else
            {
                os << b.colorMod << "-" << RESET_COLOR;
            }
        }
        os << b.colorMod << "\n" << RESET_COLOR;
    }
    os << RESET_COLOR;
    return os;
}
