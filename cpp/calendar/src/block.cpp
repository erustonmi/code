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
            m_pobVec.m_posVec.push_back(p);
        } while(rotate());
        if(flipped) break;
        if(!flip()) break;
        flipped = true;
    } while(true);
    flip();
    #if _DEBUG
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
    m_seqNo(other.m_seqNo),
    m_state(other.m_state)
{
    size = numRows * numCols;
//    arr = new int[size];
//    cout << "in copy constructor " << arr << endl;
    arr.resize(size);
    for(int i = 0; i < numRows * numCols; ++i)
    {
        arr[i] = other.arr[i];
    }
//    cout << "here in copy, other.posVec.size:"
 //        << other.posVec.size()
  //       << ", posVec.size:" << posVec.size() << endl;
    /*
    for(auto& p : other.posVec)
    {
   //     cout << "p.size:" << p.size() << endl;
        set<int> s;
        for(int i : p) s.insert(i);
    //    cout << "here2 in copy" << endl;
        posVec.push_back(s);
     //   cout << "posVec.size:" << posVec.size() << endl;
    }
    */
    for(auto&p : other.m_pobVec.m_posVec)
    {
        set<int> s;
        for(int i : p) s.insert(i);
        m_pobVec.m_posVec.push_back(s);
    }
//    cout << "other posvec size: " << other.m_pobVec.m_posVec.size() << endl;
//    cout << "my posvec size: " << m_pobVec.m_posVec.size() << endl;
    m_pobVec.m_currIdx = 0;//other.m_pobVec.m_currIdx;
    cout << "leaving copy constructor " << endl;
//    cout << "end of copy constructor" << endl;
}

// returns false if the new state is the same as original
bool Block::rotate()
{
    vector<int> sav = arr;//(arr, arr+numCols*numRows);
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

bool Block::rotatePosition()
{
    //m_state = (m_state + 90) % 360;
    return m_pobVec.rotate();
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
                  int stopPos,
                  set<int>& occupiedPos)
{
    return m_pobVec.fitIn(area, stopPos, occupiedPos, boardNumCols);
/*
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
*/
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
    cout << "posvec size:" << b.m_pobVec.m_posVec.size()
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
    cout << "In pobvector::rotate, m_currIdx:" << m_currIdx
         << ", posVec.size:" << m_posVec.size() << endl;
    return rc;
}

bool Block::POBVector::fitIn(const std::set<int>& area,
                             int stopPos,
                             std::set<int>& occupiedPos,
                             int numCols)
{
    cout << "area=[";
    for(auto i : area) cout << i << " ";
    cout << "]\nin pobvec.fit, m_posVec size:" << m_posVec.size()
         << ", numCols:" << numCols << ", stopPos:" << stopPos
         << ", currIdx:" << m_currIdx << endl;
    while(m_currIdx < m_posVec.size())
    {
        if(stopPos == m_currIdx)
        {
            return false;
            //m_currIdx++;
            //continue;
        }
        const set<int>& p = m_posVec[m_currIdx];
        int shift = *area.begin() - *p.begin();
        if(shift >= 0)
        {
            /*
            int lastIdx = *p.rbegin();
            if(lastIdx + *area.begin() - *p.begin() <
               (lastIdx / numCols + (*area.begin()-*p.begin())/numCols + 1) * numCols)
               */
            {
                cout << "numCols:" << numCols
                     << ", currIdx:" << m_currIdx << ", pos vec:{ ";
                set<int> s;
                bool noFit = false;
                for(auto& i : p)
                {
                    //if(shift > 0 && (i+1) % numCols == 0)
                    if(i + shift >= (i/numCols + shift/numCols + 1) * numCols)
                    {
                        noFit = true;
                        break;
                    }
                    int newPos = i+shift;
                    s.insert(newPos);
                    cout << "(" << i << "," << newPos << ") ";
                }
                cout << "}" << endl;
                if(!noFit)
                {
                    if(includes(area.begin(), area.end(), s.begin(), s.end()))
                    {
                        occupiedPos = s;
                        return true;
                    }
                }
            }
            /*
            else
            {
                cout << "bad currIdx:" << m_currIdx << "," 
                     << lastIdx + *area.begin() - *p.begin()
                     << ","
                     << (lastIdx / numCols + 1) * numCols << endl;
            }
            */
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
