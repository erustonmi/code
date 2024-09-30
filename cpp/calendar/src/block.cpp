#include "block.h"
#include "board.h"
//#include <algorithm>
using namespace std;

int Block::count = 0;
Block::Block(const Color::Modifier& cm,
             int r, int c, int boardRow, int boardCol,
             const vector<int>& v)
             :used(false),colorMod(cm),
             numRows(r),numCols(c),numRep(0)
{
    size = r * c;
    arr = new int[size];
    cout << "in constructor " << arr << endl;
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
            int posOnBoard = i % numCols + i / numCols * boardCol;
        }
        numRep = numRep * 10 + arr[i];
    }
    origNumRep = numRep;
    origNumRows = numRows;
    origNumCols = numCols;
    count++;
    m_seqNo = count;
    m_state = 0;
    bool flipped = false;
    do
    {
        do
        {
            set<int> p;
            for(int i = 0; i < numRows * numCols; ++i)
            {
                if(arr[i] == 1)
                {
                    int posOnBoard = i % numCols + i / numCols * boardCol;
                    p.insert(posOnBoard);
                }
            }
            posVec.push_back(p);
        } while(rotate());
        if(flipped) break;
        if(!flip()) break;
        flipped = true;
    } while(true);
    flip();
    #if _DEBUG
    cout << "on board position vector:" << endl;
    for(auto& p : posVec)
    {
        for(int i : p) cout << i << " ";
        cout << endl;
    }
    cout << "posvec size:" << posVec.size() << endl;
    #endif
}

Block::Block(const Block& other):
    colorMod(other.colorMod),
    numRows(other.numRows),
    numCols(other.numCols),
    numRep(other.numRep),
    origNumRows(other.origNumRows),
    origNumCols(other.origNumCols),
    origNumRep(other.origNumRep),
    m_seqNo(other.m_seqNo),
    m_state(other.m_state)
{
    size = numRows * numCols;
    arr = new int[size];
    cout << "in copy constructor " << arr << endl;
    for(int i = 0; i < numRows * numCols; ++i)
    {
        arr[i] = other.arr[i];
    }
//    cout << "here in copy, other.posVec.size:"
 //        << other.posVec.size()
  //       << ", posVec.size:" << posVec.size() << endl;
    for(auto& p : other.posVec)
    {
   //     cout << "p.size:" << p.size() << endl;
        set<int> s;
        for(int i : p) s.insert(i);
    //    cout << "here2 in copy" << endl;
        posVec.push_back(s);
     //   cout << "posVec.size:" << posVec.size() << endl;
    }
    cout << "end of copy constructor" << endl;
}

// returns false if the new state is the same as original
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
    m_state = (m_state + 90) % 360;
    return (numRows != origNumRows ||
            numCols != origNumCols ||
            numRep != origNumRep);
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

bool Block::fitIn(const set<int>& area,
                  set<int>& occupiedPos)
{
    cout << "posvec size:" << posVec.size() << endl;
    for(auto& s : posVec)
    {
        set<int> s2;
        for(auto& i : s)
        {
            int newPos = i+*area.begin()-*s.begin();
            s2.insert(newPos);
            cout << newPos << " ";
        }
        cout << endl;
        //for(int i : s2) cout << i << " ";
        cout << endl;
        if(includes(area.begin(), area.end(), s2.begin(), s2.end()))
        {
            occupiedPos = s2;
            return true;
        }
    }
    return false;
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
    cout << "posvec size:" << b.posVec.size()
         << ", seq:" << b.m_seqNo
         << ", state:" << b.m_state << endl;
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
