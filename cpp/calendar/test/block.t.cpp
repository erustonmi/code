#include <block.h>
#include <board.h>
//#include <iostream>

using namespace std;
void flipTest()
{
    Color::Modifier yellow(Color::FG_YELLOW);
    Block b(yellow, 2, 4, 2, 4, {5, 6, 7});
    cout << b << endl;
    b.flip();
    cout << b << endl;
    b.flip();
    cout << b << endl;

    Color::Modifier green(Color::FG_GREEN);
    Block b2(green, 2, 3, 2, 3, {4});
    cout << b2;
    cout << b2.flip() << endl;
    cout << b2;
}

void rotateTest()
{
    Color::Modifier yellow(Color::FG_YELLOW);
    Block b(yellow, 2, 4, 2, 4, {5, 6, 7});
    cout << b;
    cout << b.getNumRep() << endl << endl;
    b.rotate();
    cout << b;
    cout << b.getNumRep() << endl << endl;
    b.rotate();
    cout << b;
    cout << b.getNumRep() << endl << endl;
    b.rotate();
    cout << b;
    cout << b.getNumRep() << endl << endl;
    b.rotate();
    cout << b;
    cout << b.getNumRep() << endl << endl;
}

void blockTest()
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier yellow(Color::FG_YELLOW);
    Block b1(red, 2, 3, 2, 3, {2, 3});
    cout << b1 << endl;
    b1.rotate();
    cout << b1 << endl;
    /*
    set<int> board = {1, 11, 12, 17, 18};
    set<int>pos;
    bool fit = b1.fitIn(board, pos);
    cout << "fit:" << fit << endl;
    */
    Block b2(green, 2, 3, 2, 3, {4});
    cout << b2 << endl;
    b2.rotate();
    cout << b2 << endl;
    b2.rotate();
    cout << b2 << endl;
    b2.rotate();
    cout << b2 << endl;
    b2.rotate();
    cout << b2 << endl;
    b2.rotate();
    cout << b2 << endl;
    /*
    Block b3(yellow, 3, 3, {0, 2, 3, 5});
    cout << b3 << endl;
    Block b4(blue, 2, 4, {5, 6, 7});
    cout << b4 << endl;
    */
}

void equalityTest()
{
    Color::Modifier yellow(Color::FG_YELLOW);
    Block b1(yellow, 2, 4, 2, 4, {5, 6, 7});
    cout << b1;
    Block b2(yellow, 4, 2, 4, 2, {3, 5, 7});
    cout << b2;
    cout << (b1 == b2) << endl;
    cout << (b2 == b1) << endl << endl;

    Color::Modifier green(Color::FG_GREEN);
    Block b3(green, 2, 3, 2, 3, {3});
    cout << b3;
    Block b4(green, 2, 3, 2, 3, {4});
    cout << b4;
    cout << (b3 == b4) << endl;
    cout << (b4 == b3) << endl << endl;

    Color::Modifier red(Color::FG_RED);
    Block b5(red, 4, 2, 4, 2, {1, 3, 6});
    cout << b5;
    Block b6(red, 2, 4, 2, 4, {3, 4, 5});
    cout << b6;
    cout << (b5 == b6) << endl;
    cout << (b6 == b5) << endl << endl;
}

void boardTest()
{
    Color::Modifier cyan(Color::BG_CYAN);
    //vector<int> unavailableCells = {6, 13, 49, 50, 51, 52};
    vector<int> unavailableCells =
          {6, 13, 49, 50, 51, 52};
        //{2, 4, 6, 8, 11, 13, 14, 18, 19, 20, 49, 50, 51, 52};
//        {2, 4, 6, 9, 11, 13, 15, 18, 20, 21, 49, 50, 51, 52};
//        {0, 2, 3, 4, 6, 10, 11, 13, 14, 15, 16, 18, 20, 49, 50, 51, 52};
//        {3, 4, 6, 7, 9, 10, 11, 13, 14, 15, 16, 18, 20, 49, 50, 51, 52};
    Board b(cyan, unavailableCells);
    cout << b;
    /*
    if(b.solvable())
    {
        cout << "board is solvable" << endl;
    }
    else
    {
        cout << "board is unsolvable" << endl;
    }
    */
}

void solveBoard()
{
    Color::Modifier cyan(Color::BG_CYAN);
    vector<int> unavailableCells =
          {6, 13, 49, 50, 51, 52};
    Board b(cyan, unavailableCells);
    cout << b;
    /*
    if(b.solvable())
    {
        cout << "board is solvable" << endl;
    }
    else
    {
        cout << "board is unsolvable" << endl;
    }
    */
}

void solveTest1()
{
    Color::Modifier cyan(Color::BG_CYAN);
    vector<int> unavailableCells = {0, 5};
    Board b(cyan, unavailableCells, 3, 2);
    cout << "board:\n" << b;
    Color::Modifier green(Color::FG_GREEN);
    Block bk(green, 2, 3, 2, 3, {2, 3});
    vector<Block> vb;
    vb.emplace_back(bk);
    if(b.fit(vb))
    {
        cout << "solved" << endl;
    }
    else
    {
        cout << "unsolvable" << endl;
    }
    cout << b;
}

void solveTest2()
{
    Color::Modifier cyan(Color::BG_CYAN);
    //vector<int> unavailableCells = {2, 3, 4, 7, 8, 9};
    vector<int> unavailableCells = {7, 8, 9, 12, 13, 14};
    //vector<int> unavailableCells = {5};
    Board b(cyan, unavailableCells, 3, 5);
    cout << "board:\n" << b;
    Color::Modifier green(Color::FG_GREEN);
    Block bk1(green, 2, 3, 3, 5, {3});
    cout << "bk1:" << bk1 << endl;
    Color::Modifier red(Color::FG_RED);
    Block bk2(red, 1, 4, 3, 5, {});
    cout << "bk2:" << bk2 << endl;
    vector<Block> vb;
    cout << "before fitting1" << endl;
    vb.emplace_back(bk1);
    cout << "before fitting2" << endl;
    vb.emplace_back(bk2);
    cout << "before fitting3" << endl;
    if(b.fit(vb))
    {
        cout << "solved" << endl;
    }
    else
    {
        cout << "unsolvable" << endl;
    }
    cout << b;
}

void fitTest()
{
    Color::Modifier green(Color::FG_GREEN);
    Block bk(green, 2, 3, 2, 3, {2, 3});
    cout << bk;
    set<int> area = {1, 2, 3, 4};
    set<int> p;
    if(bk.fitIn(area, p))
    {
        cout << "fit" << endl;
    }
    else
    {
        cout << "no fit" << endl;
    }
}

int main(int argc, char** argv)
{
//    blockTest();
//    flipTest();
//    rotateTest();
    //equalityTest();
    //boardTest();
    //solveBoard();
    //solveTest1();
    solveTest2();
    //fitTest();
    return 0;
}
