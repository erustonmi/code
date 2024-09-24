#ifndef BLOCK_H
#define BLOCK_H
#include "colormod.h"
#include <vector>
#include <iostream>
//#include <utility>
class Block
{
public:
    Block(const Color::Modifier&, int, int, const std::vector<int>&);
    Block(const Block& other);
    ~Block(){ delete[] arr;}
    int getSize() const { return size; }
    bool rotate();
    bool flip();
    friend std::ostream& operator<<(std::ostream& os, const Block& b);
    bool operator==(const Block& other);
    long getNumRep() const { return numRep; }
protected:
    Color::Modifier colorMod;
    int numRows;
    int numCols;
    int size;
    int *arr;
    long numRep; // an integer representation of the block
    long origNumRep;
    void updateNumRep();
    bool sameAs(const Block& other) const;
};

#endif
