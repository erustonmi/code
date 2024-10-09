#ifndef BLOCK_H
#define BLOCK_H
#include "colormod.h"
#include <bits/stdc++.h>
//#include <vector>
//#include <iostream>
//#include <utility>
class Block
{
    class POBVector
    {
    public:
        std::vector<std::set<int>> m_posVec;
        int m_currIdx;
        int m_startingIdx;
        POBVector():m_currIdx(0){}
        bool fitIn(const std::set<int>&, std::set<int>&, int);
        bool rotate();
    };
public:
    static int count;
    Block(const Color::Modifier&, int, int, int, int, const std::vector<int>&);
    Block(const Block& other);
    ~Block(){}
    int getSize() const { return size; }
    bool rotate();
    bool rotatePosition();
    bool flip();
    friend std::ostream& operator<<(std::ostream& os, const Block& b);
    bool operator==(const Block& other);
    long getNumRep() const { return numRep; }
    bool fitIn(const std::set<int>&, std::set<int>&);
    int getPosIdx() const { return m_pobVec.m_currIdx; }

    Color::Modifier colorMod;
    bool used;
    int m_seqNo;
protected:
    void updateNumRep();
    bool sameAs(const Block& other) const;

    int numRows;
    int numCols;
    int boardNumCols;
    int size;
    std::vector<int> arr;
    long numRep; // an integer representation of the block
    int origNumRows;
    int origNumCols;
    long origNumRep;
    POBVector m_pobVec;
};

#endif
