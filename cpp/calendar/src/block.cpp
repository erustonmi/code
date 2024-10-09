#include "block.h"
#include "board.h"
//#include <algorithm>
using namespace std;

int Block::count = 0;
Block::Block(const Color::Modifier& cm,
             int r, int c, int boardRow, int boardCol,
             const vector<int>& v)
             :used(false),colorMod(cm),
             numRows(r),numCols(c),
             boardNumCols(boardCol),numRep(0)
{
    size = r * c;
    arr.resize(size);
    //arr = new int[size];
    //cout << "in constructor " << arr << endl;
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
    m_seqNo = count;
    count++;
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
            m_pobVec.m_posVec.push_back(p);
        } while(rotate());
        if(flipped) break;
        if(!flip()) break;
        flipped = true;
    } while(true);
    flip();
//    cout << "block size:" << size << endl;
#if 0
    cout << "on board position vector:" << endl;
    for(int i = 0; i < m_pobVec.m_posVec.size(); ++i)
    {
        cout << i << " -- ";
        for(int j : m_pobVec.m_posVec[i]) cout << j << " ";
        cout << endl;
    }
    cout << "end of constructor.  m_posvec size:" << m_pobVec.m_posVec.size() << endl;
#endif
}

Block::Block(const Block& other):
    colorMod(other.colorMod),
    numRows(other.numRows),
    numCols(other.numCols),
    boardNumCols(other.boardNumCols),
    numRep(other.numRep),
    origNumRows(other.origNumRows),
    origNumCols(other.origNumCols),
    origNumRep(other.origNumRep),
    used(false),
    m_seqNo(other.m_seqNo)
{
    size = numRows * numCols;
    arr.resize(size);
    for(int i = 0; i < numRows * numCols; ++i)
    {
        arr[i] = other.arr[i];
    }
    for(auto&p : other.m_pobVec.m_posVec)
    {
        set<int> s;
        for(int i : p) s.insert(i);
        m_pobVec.m_posVec.push_back(s);
    }
    m_pobVec.m_currIdx = 0;
}

// returns false if the new state is the same as original
bool Block::rotate()
{
    vector<int> sav = arr;
    for(int i = 0; i < numRows; ++i)
    {
        for(int j = 0; j < numCols; ++j)
        {
            arr[j*numRows+numRows-i-1] = sav[i*numCols+j];
        }
    }
    int tmp = numRows;
    numRows = numCols;
    numCols = tmp;
    updateNumRep();
    return (numRows != origNumRows ||
            numCols != origNumCols ||
            numRep != origNumRep);
}

bool Block::rotatePosition()
{
    return m_pobVec.rotate();
}

bool Block::flip()
{
    long oldNumRep = numRep;
    for(int i = 0; i < numRows; ++i)
    {
        for(int j = 0; j < numCols/2; ++j)
        {
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
    /*
    int diff = area.size() - size;
    if(diff < 0 || (diff <=3 && diff >= 1) ||
       diff == 6 || diff == 7)
    {
        m_pobVec.m_currIdx = 0;
        return false;
    }
    */
    return m_pobVec.fitIn(area, occupiedPos, boardNumCols);
}

bool Block::operator==(const Block& other)
{
    if(size != other.size) return false;
    if(numRows*numCols != other.numRows*other.numCols) return false;
    if(sameAs(other)) return true;
    //cout << "chkpt1" << endl;
    Block copy1(other);
    while(copy1.rotate())
    {
        if(sameAs(copy1)) return true;
    }
    //cout << "chkpt2" << endl;
    Block copy2(other);
    if(copy2.flip())
    {
        if(sameAs(copy2)) return true;
        //cout << "chkpt3" << endl;
        while(copy2.rotate())
        {
            if(sameAs(copy2)) return true;
        }
        //cout << "chkpt4" << endl;
    }
    //cout << "chkpt5" << endl;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Block& b)
{
    cout << "posvec size:" << b.m_pobVec.m_posVec.size()
         << ", seq:" << b.m_seqNo << endl;
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

// advance m_currIdx to point to the next position in m_posVec
// return false if the updated current index goes back to 0
bool Block::POBVector::rotate()
{
    bool rc = true;
    m_currIdx++;
    if(m_currIdx == m_posVec.size())
    {
        m_currIdx = 0;
        rc = false;
    }
    /*
    cout << "In pobvector::rotate, m_currIdx:" << m_currIdx
         << ", posVec.size:" << m_posVec.size() << endl;
    */
    return rc;
}

bool Block::POBVector::fitIn(const std::set<int>& area,
                             std::set<int>& occupiedPos,
                             int numCols)
{
#if 0
    cout << "area=[";
    for(auto i : area) cout << i << " ";
    cout << "]\nin pobvec.fit, m_posVec size:" << m_posVec.size()
         << ", numCols:" << numCols
         << ", currIdx:" << m_currIdx << endl;
#endif
    int diff = area.size() - m_posVec[0].size();
    if(diff < 0 || (diff <=3 && diff >= 1) ||
       diff == 6 || diff == 7)
    {
        m_currIdx = 0;
        return false;
    }
    while(m_currIdx < m_posVec.size())
    {
        const set<int>& p = m_posVec[m_currIdx];
        int shift = *area.begin() - *p.begin();
        if(shift >= 0)
        {
            {
#if 0
                cout << "numCols:" << numCols
                     << ", currIdx:" << m_currIdx << ", pos vec:{ ";
#endif
                set<int> s;
                bool noFit = false;
                for(auto& i : p)
                {
                    if(i + shift >= (i/numCols + shift/numCols + 1) * numCols)
                    {
                        noFit = true;
                        break;
                    }
                    int newPos = i+shift;
                    s.insert(newPos);
//                    cout << "(" << i << "," << newPos << ") ";
                }
 //               cout << "}" << endl;
                if(!noFit)
                {
                    if(includes(area.begin(), area.end(), s.begin(), s.end()))
                    {
                        occupiedPos = s;
                        return true;
                    }
                }
            }
        }
        m_currIdx++;
        if(m_currIdx == m_posVec.size())
        {
            m_currIdx = 0;
            break;
        }
    }
    return false;
}
