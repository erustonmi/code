#include "board.h"
#include <algorithm>

using namespace std;

Board::Board(const Color::Modifier& cm,
             const std::vector<int>& v,
             int numRows, int numCols):
m_numRows(numRows),
m_numCols(numCols),
m_colorMod(cm),
m_unavailableCells(v)
{}

void Board::initBoard()
{
    const vector<int>& v = m_unavailableCells;
    for(int i = 0; i < m_numRows; ++i)
    {
        for(int j = 0; j < m_numCols; ++j)
        {
            if(find(v.begin(), v.end(), i*m_numCols+j) != v.end())
            {
                m_cells[i][j].status = CellStatus::UNAVAILABLE;
            }
            else
            {
                m_cells[i][j].status = CellStatus::EMPTY;
                int myIdx = i * m_numCols + j;
                if(i > 0 && m_cells[i-1][j].status == CellStatus::EMPTY)
                {
                    // if the cell above is free, establish a connection
                    int otherIdx = (i - 1) * m_numCols + j;
                    m_adjMap[myIdx].insert(otherIdx);
                    m_adjMap[otherIdx].insert(myIdx);
                }
                if(j > 0 && m_cells[i][j-1].status == CellStatus::EMPTY)
                {
                    // if the left cell is free, establish a connection
                    int otherIdx = i * m_numCols + j - 1;
                    m_adjMap[myIdx].insert(otherIdx);
                    m_adjMap[otherIdx].insert(myIdx);
                }
            }
        }
    }
}

void Board::setDate(Month m, int d, int dow)
{
    m_unavailableCells.push_back(m);
    m_unavailableCells.push_back(d+13);
    m_unavailableCells.push_back(dow);
}

bool Board::fit(std::vector<Block>& blocks)
{
    int cntr = 0;
    for(auto& b:blocks) b.used = false;
    set<int> area;
    stack<set<int>> boardStates;
    map<int, int> startIdx; // the starting index of blocks for each round
    stack<int> savedBlocks;
    //cout << "CHKPT1, area empty:" << area.empty()
    //     << ", block size:" << blocks.size() << endl;
    while(findNextOpenArea(area))
    {
        set<int> savedState;
        saveState(savedState);
        auto tmpIt = startIdx.find(cntr);
        int idx = (tmpIt == startIdx.end() ? 0 : tmpIt->second);
        idx = fit(area, blocks, idx);
        if(idx != -1)
        {
            //cout << "setting startIdx[" << cntr
            //     << "] to " << blocks[idx].m_seqNo << "," << idx << endl;
            startIdx[cntr] = blocks[idx].m_seqNo;
            boardStates.push(savedState);
            blocks[idx].used = true;
            savedBlocks.push(blocks[idx].m_seqNo);
            area.clear();    
            //cout << "found a fitting block, pushing " << blocks[idx].m_seqNo
            //     << " to block stack"
            //     << ", cntr:" << cntr << endl;
            cntr++;
        }
        else
        {
            if(boardStates.empty())
            {
                //cout << "boardStates empty, unsolvable" << endl;
                return false;
            }
            set<int>& topArea = boardStates.top();
            restoreState(topArea);
            boardStates.pop();
            area.clear();    
            int seqNo = savedBlocks.top();
            //cout << "popping " << seqNo << endl;
            auto it = blocks.begin();
            for(; it != blocks.end(); ++it)
            {
                if(it->m_seqNo == seqNo)
                {
                    break;
                }
            }
            it->used = false;
            startIdx.erase(cntr);
            cntr--;
            if(!it->rotatePosition())
            {
                //cout << "setting startIdx[" << cntr
                //     << "] to " << it->m_seqNo+1 << endl;
                startIdx[cntr] = it->m_seqNo + 1;
            }
            savedBlocks.pop();
#if 0
            cout << "no block fits, cntr:" << cntr
                 << ", stack size: "
                 << boardStates.size() << ", "
                 << savedBlocks.size() << ", "
                 << "adjmap size:" << m_adjMap.size()
                 << ", current board:\n" << *this << endl;
#endif
        }
    }
    while(!boardStates.empty()) boardStates.pop();
    while(!savedBlocks.empty())
    {
        savedBlocks.pop();
    }
    //cout << "CHKPT2, stack size:"
    //     << savedBlocks.size() << endl;
    return true;
}

void Board::markOccupied(const set<int>& pos, const Color::Code& c)
{
    int i, j;
    //cout << "Marking ";
    for(int p : pos)
    {
        //cout << p << " ";
        i = p / m_numCols;
        j = p % m_numCols;
        m_cells[i][j].status = CellStatus::OCCUPIED;
        m_cells[i][j].color = c;
        for(int idx : m_adjMap[p])
        {
            m_adjMap[idx].erase(p);
        }
        m_adjMap.erase(p);
    }
#if 0
    cout << "occupied" << endl
         << "adjmap size:" << m_adjMap.size()
         << ", current board:\n" << *this << endl;
#endif
    //printAdjMap();
}

int Board::fit(set<int>& area, vector<Block>& blocks, int startIdx)
{
#if 0
    cout << "board::fit, area.size: " << area.size()
         << ", startIdx:" << startIdx
         << ", blocks.vector.size:" << blocks.size() << endl;
#endif
    if(areaUnsolvable(area)) return -1;
    set<int> pos;
    int i = startIdx;
    for(; i < blocks.size(); ++i)
    {
#if 0
        cout << "block:(" << blocks[i].m_seqNo
             << "," << blocks[i].getPosIdx()
             << "), used: " << blocks[i].used << endl;
#endif
        if(blocks[i].used) continue;
        if(blocks[i].fitIn(area, pos))
        {
//            cout << "here3, seqNo:" << blocks[i].m_seqNo
//                 << ", posIdx:" << blocks[i].getPosIdx() << endl;
            markOccupied(pos, blocks[i].colorMod.code);
            return i;
        }
        else
        {
            //cout << "here4" << endl;
        }
    }
    return -1;
}

void Board::restoreState(const std::set<int>& s)
{
    for (int i = 0; i < m_numRows; ++i)
    {
        for(int j = 0; j < m_numCols; j++)
        {
            if(find(s.begin(), s.end(), i*m_numCols+j) != s.end())
            {
                m_cells[i][j].status = CellStatus::EMPTY;
            }
        }
    }
    restoreAdjMap();
}

void Board::restoreAdjMap()
{
    m_adjMap.clear();
    for(int i = 0; i < m_numRows; ++i)
    {
        for(int j = 0; j < m_numCols; ++j)
        {
            if(m_cells[i][j].status == CellStatus::EMPTY)
            {
                int myIdx = i * m_numCols + j;
                if(i > 0)
                {
                    int otherIdx = (i - 1) * m_numCols + j;
                    if(m_cells[i-1][j].status == CellStatus::EMPTY)
                    {
                        m_adjMap[myIdx].insert(otherIdx);
                        m_adjMap[otherIdx].insert(myIdx);
                    }
                }
                if(j > 0)
                {
                    int otherIdx = i * m_numCols + j - 1;
                    if(m_cells[i][j-1].status == CellStatus::EMPTY)
                    {
                        m_adjMap[myIdx].insert(otherIdx);
                        m_adjMap[otherIdx].insert(myIdx);
                    }
                }
            }
        }
    }
}

void Board::printAdjMap()
{
    for(auto const&[key, val]:m_adjMap)
    {
        cout << key << "==>";
        for(auto i: val) cout << i << " ";
        cout << endl;
    }
}

void Board::saveState(std::set<int>& s)
{
    for (int i = 0; i < m_numRows; ++i)
    {
        for(int j = 0; j < m_numCols; j++)
        {
            if(m_cells[i][j].status == CellStatus::EMPTY)
            {
                s.insert(i*m_numCols+j);
            }
        }
    }
}

bool Board::findNextOpenArea(set<int>& s)
{
    // Mark all the vertices as not visited
    //bool* visited = new bool[V];
    set<int> tmp;
    memset(m_visited, 0, sizeof(m_visited));
 
    for (int i = 0; i < m_numRows; ++i)
    {
        for(int j = 0; j < m_numCols; ++j)
        {
            if(m_cells[i][j].status == CellStatus::EMPTY &&
               m_visited[i*m_numCols+j] == false)
            {
                // print all reachable vertices
                // from v
                //set<int> group;
                tmp.clear();
                DFSUtil(i*m_numCols+j, tmp);//, m_visited);
#if 0
                cout << "area size:" << tmp.size() << ", [ ";
                for(const auto i: tmp)
                {
                    cout << i << " ";
                }
                cout << "]" << endl;
#endif
                if(tmp.empty()) return true;
                if(s.size() == 0 || s.size() > tmp.size())
                {
                    s = tmp;
                }
//                return !tmp.empty();
            }
        }
    }
    return !s.empty();
    //delete[] visited;
}

int Board::DFSUtil(int v, set<int>& group)//, bool visited[])
{
    int c = 1;
    // Mark the current node as visited and print it
    m_visited[v] = true;
    //cout << v << " ";
    group.insert(v);
 
    // Recur for all the vertices
    // adjacent to this vertex
    for (auto it = m_adjMap[v].begin();
         it != m_adjMap[v].end(); ++it)
    {
        if (!m_visited[*it])
        {
            c = c + DFSUtil(*it, group);//, m_visited);
        }
    }
    return c;
}

bool Board::areaUnsolvable(const set<int>& area)
{
    int size = area.size();
    if(size <= 3 || size == 6 ||
       size == 7) return true;
    if(size == 4 && m_numCols > 2)
    {
        vector<int> v(area.begin(), area.end());
        // square area is unsolvable
        if(v[1] - v[0] == v[3] - v[2] &&
           v[3] - v[1] == m_numCols) return true;
        // 3-way intersections are unsolvable
        if(v[3] - v[1] == 2 && v[2] - v[0] == m_numCols ||
           v[2] - v[0] == 2 && v[3] - v[1] == m_numCols ||
           v[2] - v[1] == 1 && v[3] - v[0] == 2*m_numCols ||
           v[2] - v[1] == 1 && v[3] - v[0] == 2*m_numCols) return true;
    }
    else if(size == 5)
    {
        // 4-way intersection is unsolvable
        vector<int> v(area.begin(), area.end());
        if(v[0] + v[4] == v[3] + v[1] &&
           v[3] - v[1] == 2) return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    const char* RESET_COLOR = "\033[0m";
    for(int i = 0; i < b.m_numRows; ++i)
    {
        for(int j = 0; j < b.m_numCols; ++j)
        {
            if(b.m_cells[i][j].status == CellStatus::UNAVAILABLE)
            {
                os << b.m_colorMod << "X" << RESET_COLOR;
            }
            else if(b.m_cells[i][j].status == CellStatus::OCCUPIED)
            {
                os << Color::Modifier(b.m_cells[i][j].color) << "O" << RESET_COLOR;
            }
            else
            {
                os << b.m_colorMod << "+" << RESET_COLOR;
            }
        }
        os << b.m_colorMod << "\n" << RESET_COLOR;
    }
    os << RESET_COLOR;
    return os;
}
