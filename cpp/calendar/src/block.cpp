#include "block.h"
#include <algorithm>
using namespace std;

Block::Block(const Color::Modifier& cm,
                         int r, int c,
                         const vector<int>& v)
                         :colorMod(cm),numRows(r),numCols(c),numRep(0)
{
    size = r * c;
    arr = new int[size];
    for(int i = 0; i < r*c; ++i)
    {
        if(find(v.begin(), v.end(), i) != v.end())
        {
            //cout << i << " invalid" << endl;
            arr[i] = 0;
            size--;
        }
        else
        {
            //cout << i << " valid" << endl;
            arr[i] = 1;
        }
        numRep = numRep * 10 + arr[i];
    }
    origNumRep = numRep;
}

Block::Block(const Block& other):
    colorMod(other.colorMod),
    numRows(other.numRows),
    numCols(other.numCols),
    numRep(other.numRep),
    origNumRep(other.origNumRep)
{
    size = numRows * numCols;
    arr = new int[size];
    for(int i = 0; i < numRows * numCols; ++i)
    {
        arr[i] = other.arr[i];
    }
}

bool Block::rotate()
{
    vector<int> sav(arr, arr+numCols*numRows);
    for(int i = 0; i < numRows; ++i)
    {
        for(int j = 0; j < numCols; ++j)
        {
            //cout << j*numRows+numRows-i-1 << "=" << i*numCols+j<< endl;
            arr[j*numRows+numRows-i-1] = sav[i*numCols+j];
        }
    }
    int tmp = numRows;
    numRows = numCols;
    numCols = tmp;
    updateNumRep();
    return (numRep != origNumRep);
}

bool Block::flip()
{
    long oldNumRep = numRep;
    for(int i = 0; i < numRows; ++i)
    {
        for(int j = 0; j < numCols/2; ++j)
        {
            //cout << i*numCols+j << "<==>" << i*numCols+(numCols-j-1) << endl;
            int tmp = arr[i*numCols+j];
            arr[i*numCols+j] = arr[i*numCols+(numCols-j-1)];
            arr[i*numCols+(numCols-j-1)] = tmp;
        }
    }
    updateNumRep();
    origNumRep = numRep;
    return (oldNumRep != numRep);
}

void Block::updateNumRep()
{
    numRep = 0;
    for(int i = 0; i < numRows * numCols; ++i)
    {
        numRep = numRep * 10 + arr[i];
    }
}
bool Block::sameAs(const Block& other) const
{
    return (numRows == other.numRows &&
            numCols == other.numCols &&
            numRep == other.numRep);
}

bool Block::operator==(const Block& other)
{
    if(size != other.size) return false;
    if(numRows*numCols != other.numRows*other.numCols) return false;
    if(sameAs(other)) return true;
    cout << "chkpt1" << endl;
    Block copy1(other);
    while(copy1.rotate())
    {
        if(sameAs(copy1)) return true;
    }
    cout << "chkpt2" << endl;
    Block copy2(other);
    if(copy2.flip())
    {
        if(sameAs(copy2)) return true;
        cout << "chkpt3" << endl;
        while(copy2.rotate())
        {
            if(sameAs(copy2)) return true;
        }
        cout << "chkpt4" << endl;
    }
    cout << "chkpt5" << endl;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Block& b)
{
    for(int i = 0; i < b.numRows; ++i)
    {
        for(int j = 0; j < b.numCols; ++j)
        {
            if(b.arr[i*b.numCols+j] > 0)
            {
                os << b.colorMod << "O";
            }
            else
            {
                os << b.colorMod << "X";
            }
        }
        os << "\n";
    }
    return os;
}
