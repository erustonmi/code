#include "board.h"
#include <algorithm>

using namespace std;

Board::Board(const Color::Modifier& cm,
             const std::vector<int>& v,
             int numRows, int numCols):
m_numRows(numRows),
m_numCols(numCols),
m_colorMod(cm),
m_unavailableCells(v),
m_cellsLeft(0)
{
    initBoard();
}

void Board::initBoard()
{
    const vector<int>& v = m_unavailableCells;
    m_cellsLeft = 0;
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
                m_cellsLeft++;
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
#if 0
    for(auto const&[key, val]: m_adjMap)
    {
        cout << key << ":";
        for(const auto i : val)
        {
            cout << i << " ";
        }
        cout << endl;
    }
#endif
}

bool Board::fit2(std::vector<Block>& blocks)
{
    for(auto& b:blocks) b.used = false;
    set<int> area;
    stack<int> seqNums; // sequence numbers of the first matching blocks
    stack<set<int>> boardStates;
    //stack<Block> savedBlocks;
    stack<int> savedBlocks;
    cout << "CHKPT1, area empty:" << area.empty()
         << ", block size:" << blocks.size() << endl;
    //bool recNextSeqNo = false;
    while(!area.empty() || findNextOpenArea(area))
    {
        set<int> savedState;
        saveState(savedState);
        auto it = fit(area, blocks);
        cout << "conditions: " << (it!=blocks.end())
             << ", " << seqNums.empty() << endl;
        if(it != blocks.end() &&
           (seqNums.empty() || it->m_seqNo != seqNums.top()))
        {
            cout << "found a fitting block, pushing " << it->m_seqNo << endl;
            boardStates.push(savedState);
            it->used = true;
            savedBlocks.push(it->m_seqNo);
            /*
            if(recNextSeqNo)
            {
                seqNums.push(it->m_seqNo);
                recNextSeqNo = false;
            }
            */
            //blocks.erase(it);
            area.clear();    
            //recNextSeqNo = true;
        }
        else
        {
            cout << "no block fits, stack size: "
                 << boardStates.size() << ", "
                 << savedBlocks.size() << ", "
                 << seqNums.size() << endl;
            if(it != blocks.end())
            {
                // the block has previously been tested
                cout << "popping seqNum " << it->m_seqNo << endl;
                seqNums.pop();
            }
            // if can't find a fitting block
            if(boardStates.empty()) return false;
            area = boardStates.top();
            boardStates.pop();
            restoreState(area);
            int seqNo = savedBlocks.top();
            cout << "popping " << seqNo << endl;
            auto it = blocks.begin();
            for(; it != blocks.end(); ++it)
            {
                if(it->m_seqNo == seqNo)
                {
                    break;
                }
            }
            it->used = false;
            if(!it->rotatePosition())
            {
                cout << "pushing seqNum " << it->m_seqNo << endl;
                seqNums.push(it->m_seqNo);
                rotate(it, it+1, blocks.end());
            }
            cout << "after popping, adjmap size:" << m_adjMap.size() << ", current board:\n" << *this << endl;
            savedBlocks.pop();
            //recNextSeqNo = false;
        }
    }
    while(!boardStates.empty()) boardStates.pop();
    while(!savedBlocks.empty())
    {
        savedBlocks.pop();
    }
    cout << "CHKPT2, stack size:"
         << savedBlocks.size() << endl;
    return true;
}

bool Board::fit(std::vector<Block>& blocks)
{
    int cntr = 0;
    for(auto& b:blocks) b.used = false;
    set<int> area;
    map<int, pair<int, int>> seqNumMap; // sequence numbers of the first matching blocks
    stack<set<int>> boardStates;
    //stack<Block> savedBlocks;
    stack<int> savedBlocks;
    cout << "CHKPT1, area empty:" << area.empty()
         << ", block size:" << blocks.size() << endl;
    //bool recNextSeqNo = false;
    while(!area.empty() || findNextOpenArea(area))
    {
        set<int> savedState;
        saveState(savedState);
        auto it = fit(area, blocks);
        if(it != blocks.end() &&
           (seqNumMap.find(cntr) == seqNumMap.end() ||
            it->m_seqNo != seqNumMap[cntr].first ||
            it->getPosIdx() != seqNumMap[cntr].second))
        {
            if(seqNumMap.find(cntr) == seqNumMap.end())
            {
                cout << "cntr:" << cntr
                     << ", saving seqNum:" << it->m_seqNo
                     <<" and posIdx:" << it->getPosIdx() << endl;
                seqNumMap[cntr] = make_pair(it->m_seqNo, it->getPosIdx());
            }
            else
            {
                cout << "seqNumMap[" << cntr
                     << "]:(" << seqNumMap[cntr].first
                     << "," << seqNumMap[cntr].second
                     << ")" << endl;
            }
            cntr++;
            boardStates.push(savedState);
            it->used = true;
            savedBlocks.push(it->m_seqNo);
            area.clear();    
            cout << "found a fitting block, pushing " << it->m_seqNo
                 << " to block stack"
                 << ", cntr:" << cntr
                 << ", seqNuMap.size:" << seqNumMap.size() << endl;
        }
        else
        {
            //if(it != blocks.end())
            auto mit = seqNumMap.find(cntr);
            if(mit != seqNumMap.end())
            {
                cout << "erasing cntr:" << cntr
                     << ", (seqNum:" << mit->second.first
                     << ",posIdx:" << mit->second.second << ")" << endl;
                seqNumMap.erase(mit);
            }
            cntr--;
            // if can't find a fitting block
            if(boardStates.empty())
            {
                cout << "boardStates empty, unsolvable" << endl;
                return false;
            }
            area = boardStates.top();
            boardStates.pop();
            restoreState(area);
            int seqNo = savedBlocks.top();
            cout << "popping " << seqNo << endl;
            auto it = blocks.begin();
            for(; it != blocks.end(); ++it)
            {
                if(it->m_seqNo == seqNo)
                {
                    break;
                }
            }
            it->used = false;
            /*
            if(seqNumMap.find(cntr) == seqNumMap.end())
            {
                cout << "cntr:" << cntr
                     << ", saving seqNum:" << it->m_seqNo
                     <<" and posIdx:" << it->getPosIdx() << endl;
                seqNumMap[cntr] = make_pair(it->m_seqNo, it->getPosIdx());
            }
            else
            {
                cout << "seqNumMap[" << cntr
                     << "]:(" << seqNumMap[cntr].first
                     << "," << seqNumMap[cntr].second
                     << ")" << endl;
            }
            */
            if(!it->rotatePosition())
            {
                rotate(it, it+1, blocks.end());
            }
            savedBlocks.pop();
            cout << "no block fits, cntr:" << cntr
                 << ", seqNuMap.size:" << seqNumMap.size()
                 << ", stack size: "
                 << boardStates.size() << ", "
                 << savedBlocks.size() << ", "
                 << ", adjmap size:" << m_adjMap.size()
                 << ", current board:\n" << *this << endl;
            //recNextSeqNo = false;
        }
    }
    while(!boardStates.empty()) boardStates.pop();
    while(!savedBlocks.empty())
    {
        savedBlocks.pop();
    }
    cout << "CHKPT2, stack size:"
         << savedBlocks.size() << endl;
    return true;
}

void Board::markOccupied(const set<int>& pos, const Color::Code& c)
{
    int i, j;
    cout << "Marking ";
    for(int p : pos)
    {
        cout << p << " ";
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
    cout << "occupied" << endl;
    cout << "adjmap size:" << m_adjMap.size()
         << ", current board:\n" << *this << endl;
}

vector<Block>::iterator Board::fit(set<int>& area, vector<Block>& blocks)
{
    cout << "board::fit, area.size: " << area.size()
         << ", blocks.vector.size:" << blocks.size() << endl;
    if(area.size() <= 3) return blocks.end();
    /*
    if(area.size() == 4)
    {
        if(*area.rbegin() - *area.begin() == m_numCols + 1 &&
           *area.rbegin() - *area.begin() != m_numRows)
        {
            cout << "here in fit" << endl;
            return blocks.end();
        }
    }
    */
    set<int> pos;
    auto it = blocks.begin();
    for(; it != blocks.end(); ++it)
    {
        cout << "block:" << it->m_seqNo << ", used: " << it->used << endl;
        if(it->used) continue;
        if(it->fitIn(area, pos))
        {
            cout << "here3, seqNo:" << it->m_seqNo << endl;
            markOccupied(pos, it->colorMod.code);
            return it;
        }
        else
        {
            cout << "here4" << endl;
        }
    }
    return blocks.end();
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
//                cout << i*m_numCols+j << " empty" << endl;
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
//    cout << "in findNextOpen, current board:\n" << *this << endl;
    set<int> tmp;
    memset(m_visited, 0, sizeof(m_visited));
    //for (int v = 0; v < V; v++)
    //    m_visited[v] = false;
 
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
#if _DEBUG
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

bool Board::findNextOpenArea2(set<int>& s)
{
    // Mark all the vertices as not visited
    //bool* visited = new bool[V];
//    cout << "in findNextOpen, current board:\n" << *this << endl;
    memset(m_visited, 0, sizeof(m_visited));
    //for (int v = 0; v < V; v++)
    //    m_visited[v] = false;
 
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
                DFSUtil(i*m_numCols+j, s);//, m_visited);
#if _DEBUG
                cout << "area size:" << s.size() << ", [ ";
                for(const auto i: s)
                {
                    cout << i << " ";
                }
                cout << "]" << endl;
#endif
                return !s.empty();
            }
        }
    }
    return false;
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

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    //os << "num empty cells:" << b.m_cellsLeft << endl;
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
                //os << b.m_colorMod << "O" << RESET_COLOR;
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
