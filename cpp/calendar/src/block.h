#ifndef BLOCK_H
#define BLOCK_H
#include "colormod.h"
#include <bits/stdc++.h>
//#include <vector>
//#include <iostream>
//#include <utility>
class Block
{
public:
    static int count;
    Block(const Color::Modifier&, int, int, int, int, const std::vector<int>&);
    Block(const Block& other);
    ~Block(){ if(arr) { delete[] arr; arr = 0; } }
    int getSize() const { return size; }
    bool rotate();
    bool flip();
    friend std::ostream& operator<<(std::ostream& os, const Block& b);
    bool operator==(const Block& other);
    long getNumRep() const { return numRep; }
    bool fitIn(const std::set<int>&, std::set<int>&);
    Color::Modifier colorMod;
    bool used;
    int m_seqNo;
protected:
    int numRows;
    int numCols;
    int size;
    int *arr;
    long numRep; // an integer representation of the block
    int origNumRows;
    int origNumCols;
    long origNumRep;
    int m_state;
    void updateNumRep();
    bool sameAs(const Block& other) const;
    std::vector<std::set<int>> posVec;
};

#endif
