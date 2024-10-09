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

void blockTest2()
{
    Color::Modifier green(Color::FG_GREEN);
    Block b1(green, 3, 2, 8, 7, {1, 3});
    cout << b1 << endl;
    Block b2(green, 2, 4, 8, 7, {0, 1, 2});
    cout << b2 << endl;
    Block b3(green, 3, 2, 8, 7, {4});
    cout << b3 << endl;
    Block b4(green, 2, 3, 8, 7, {1});
    cout << b4 << endl;
    Block b5(green, 3, 3, 8, 7, {0, 2, 3, 5});
    cout << b5 << endl;
    Block b6(green, 1, 4, 8, 7, {});
    cout << b6 << endl;
    Block b7(green, 2, 4, 8, 7, {0, 1, 7});
    cout << b7 << endl;
    Block b8(green, 2, 3, 8, 7, {0, 5});
    cout << b8 << endl;
    Block b9(green, 3, 3, 8, 7, {0, 1, 3, 4});
    cout << b9 << endl;
    Block b10(green, 3, 3, 8, 7, {1, 2, 6, 7});
    cout << b10 << endl;
}

void blockTest3()
{
    Color::Modifier red(Color::FG_RED);
    vector<Block> vb;

    vector<int> tmp;
    tmp = {2, 4};
    vb.emplace_back(red, 3, 2, 6, 6, tmp);
    cout << vb[0] << endl;
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

void solveBoard(Month m, int d, DayOfWeek dow)
{
    Color::Modifier defbg(Color::BG_DEFAULT);
    vector<int> unavailableCells =
          {6, 13, 49, 50, 51, 52};
    Board b(defbg, unavailableCells, 8,  7);
    b.setDate(m, d,  dow);
    b.initBoard();
    cout << "initial board:" << endl << b;
    Color::Modifier red(Color::FG_RED);
    Color::Modifier redBg(Color::BG_RED);
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier greenBg(Color::BG_GREEN);
    Color::Modifier cyan(Color::FG_CYAN);
    Color::Modifier white(Color::FG_WHITE);
    Color::Modifier yellow(Color::FG_YELLOW);
    Color::Modifier magenta(Color::FG_MAGENTA);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier blueBg(Color::BG_BLUE);
    vector<Block> vb;
    vector<int> tmp;
    tmp = {0, 1, 2};
    vb.emplace_back(red, 2, 4, 8, 7, tmp);
//    cout << vb[0] << endl;

    tmp = {0, 5};
    vb.emplace_back(redBg, 2, 3, 8, 7, tmp);
//    cout << vb[1] << endl;

    tmp = {1, 3};
    vb.emplace_back(green, 3, 2, 8, 7, tmp);
//    cout << vb[2] << endl;

    tmp = {4};
    vb.emplace_back(yellow, 3, 2, 8, 7, tmp);
//    cout << vb[3] << endl;

    tmp = {1};
    vb.emplace_back(blue, 2, 3, 8, 7, tmp);
//    cout << vb[4] << endl;

    tmp = {0, 2, 3, 5};
    vb.emplace_back(white, 3, 3, 8, 7, tmp);
//    cout << vb[5] << endl;

    tmp = {};
    vb.emplace_back(cyan, 1, 4, 8, 7, tmp);
//    cout << vb[6] << endl;

    tmp = {0, 1, 7};
    vb.emplace_back(magenta, 2, 4, 8, 7, tmp);
//    cout << vb[7] << endl;

    tmp = {0, 1, 3, 4};
    vb.emplace_back(greenBg, 3, 3, 8, 7, tmp);
//    cout << vb[8] << endl;

    tmp = {1, 2, 6, 7};
    vb.emplace_back(blueBg, 3, 3, 8, 7, tmp);
//    cout << vb[9] << endl;

    cout << endl;
    if(b.fit(vb))
    {
        cout << "solved" << endl;
    }
    else
    {
        cout << "unsolvable" << endl;
    }
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
    vector<int> unavailableCells = {1, 3};
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
//    cout << "before fitting1" << endl;
    vb.emplace_back(bk1);
//    cout << "before fitting2" << endl;
    vb.emplace_back(bk2);
//    cout << "before fitting3" << endl;
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

void solveTest3()
{
    Color::Modifier cyan(Color::BG_CYAN);
    //vector<int> unavailableCells = {2, 3, 4, 7, 8, 9};
    vector<int> unavailableCells = {4,7,11,12,13,14};
    //vector<int> unavailableCells = {5};
    Board b(cyan, unavailableCells, 3, 5);
    cout << "board:\n" << b;
    Color::Modifier green(Color::FG_GREEN);
    Block bk1(green, 2, 3, 3, 5, {3});
    cout << "bk1:" << bk1 << endl;
    Color::Modifier red(Color::FG_RED);
    Block bk2(red, 2, 3, 3, 5, {2, 3});
    cout << "bk2:" << bk2 << endl;
    vector<Block> vb;
    vb.emplace_back(bk1);
    vb.emplace_back(bk2);
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

void solveTest4()
{
    Color::Modifier cyan(Color::BG_CYAN);
    vector<int> unavailableCells = {13, 14, 16, 17, 18, 19};
    Board b(cyan, unavailableCells, 4, 5);
    cout << "board:\n" << b;
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier red(Color::FG_RED);
    Color::Modifier yellow(Color::FG_YELLOW);
    int cntr = 0;
    vector<Block> vb;
    vector<int> tmp = {1, 3};
    vb.emplace_back(green, 3, 2, 4, 5, tmp);
    cout << vb[cntr++] << endl;

    tmp = {0, 1, 2};
    vb.emplace_back(red, 2, 4, 4, 5, tmp);
    cout << vb[cntr++] << endl;

    tmp = {4};
    vb.emplace_back(yellow, 3, 2, 4, 5, tmp);
    cout << vb[cntr++] << endl;

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

void solveTest5()
{
    Color::Modifier cyan(Color::BG_CYAN);
    vector<int> unavailableCells = {10};
    Board b(cyan, unavailableCells, 5, 3);
    cout << "board:\n" << b;
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier red(Color::FG_RED);
    Color::Modifier yellow(Color::FG_YELLOW);
    Color::Modifier blue(Color::FG_BLUE);
    vector<Block> vb;
    vector<int> tmp = {1, 3};
    vb.emplace_back(green, 3, 2, 5, 3, tmp);
    cout << vb[0] << endl;
    tmp = {0, 1, 2};
    vb.emplace_back(red, 2, 4, 5, 3, tmp);
    cout << vb[1] << endl;
    tmp = {4};
    vb.emplace_back(yellow, 3, 2, 5, 3, tmp);
    cout << vb[2] << endl;
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

void solveTest6_1()
{
    Color::Modifier cyan(Color::BG_CYAN);
    vector<int> unavailableCells = {12};
    Board b(cyan, unavailableCells, 5, 4);
    cout << "board:\n" << b;
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier red(Color::FG_RED);
    Color::Modifier yellow(Color::FG_YELLOW);
    Color::Modifier blue(Color::FG_BLUE);
    vector<Block> vb;
    vector<int> tmp;
    tmp = {1, 3, 6};
    vb.emplace_back(green, 4, 2, 5, 4, tmp);
    cout << vb[0] << endl;
    tmp = {4};
    vb.emplace_back(red, 2, 3, 5, 4, tmp);
    cout << vb[1] << endl;
    tmp = {1};
    vb.emplace_back(yellow, 3, 2, 5, 4, tmp);
    cout << vb[2] << endl;
    tmp = {};
    vb.emplace_back(blue, 1, 4, 5, 4, tmp);
    cout << vb[3] << endl;
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

void solveTest6_2()
{
    Color::Modifier cyan(Color::BG_CYAN);
    vector<int> unavailableCells = {12};
    Board b(cyan, unavailableCells, 5, 4);
    cout << "board:\n" << b;
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier red(Color::FG_RED);
    Color::Modifier yellow(Color::FG_YELLOW);
    Color::Modifier blue(Color::FG_BLUE);
    vector<Block> vb;
    vector<int> tmp = {};
    vb.emplace_back(blue, 1, 4, 5, 4, tmp);
    cout << vb[0] << endl;
    tmp = {1, 3, 6};
    vb.emplace_back(green, 4, 2, 5, 4, tmp);
    cout << vb[1] << endl;
    tmp = {4};
    vb.emplace_back(red, 2, 3, 5, 4, tmp);
    cout << vb[2] << endl;
    tmp = {4};
    vb.emplace_back(yellow, 3, 2, 5, 4, tmp);
    cout << vb[3] << endl;
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

void solveTest7()
{
    Color::Modifier cyan(Color::BG_CYAN);
    Color::Modifier defBg(Color::BG_DEFAULT);
    vector<int> unavailableCells = {16, 17};
    Board b(defBg, unavailableCells, 5, 5);
    cout << "board:\n" << b;
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier red(Color::FG_RED);
    Color::Modifier yellow(Color::FG_YELLOW);
    Color::Modifier blue(Color::FG_BLUE);
    vector<Block> vb;

    vector<int> tmp;

    tmp = {3, 4, 6, 7};
    vb.emplace_back(red, 3, 3, 5, 5, tmp);
    cout << vb[0] << endl;

    tmp = {};
    vb.emplace_back(blue, 4, 1, 5, 5, tmp);
    cout << vb[1] << endl;

    tmp = {1, 2, 3};
    vb.emplace_back(green, 2, 4, 5, 5, tmp);
    cout << vb[2] << endl;

    tmp = {3, 5};
    vb.emplace_back(cyan, 3, 2, 5, 5, tmp);
    cout << vb[3] << endl;

    tmp = {0, 3, 5, 8};
    vb.emplace_back(yellow, 3, 3, 5, 5, tmp);
    cout << vb[4] << endl;

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

void solveTest8()
{
    Color::Modifier defBg(Color::BG_DEFAULT);
    vector<int> unavailableCells = {5, 9, 11, 25, 26, 27, 30, 31};
    //vector<int> unavailableCells = {5, 9, 11, 18, 19, 20, 24, 25, 26, 27, 30, 31};
    //vector<int> unavailableCells = {5, 9, 11, 25, 26, 27, 29, 30, 31, 32, 33, 34, 35};
    Board b(defBg, unavailableCells, 6, 6);
    cout << "board:\n" << b;
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier red(Color::FG_RED);
    Color::Modifier yellow(Color::FG_YELLOW);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier cyanBg(Color::BG_CYAN);
    Color::Modifier redBg(Color::BG_RED);
    vector<Block> vb;

    vector<int> tmp;
    int cntr = 0;

    tmp = {1, 2, 3};
    vb.emplace_back(green, 2, 4, 6, 6, tmp);
    cout << vb[cntr++] << endl;

    tmp = {3, 4, 6, 7};
    vb.emplace_back(red, 3, 3, 6, 6, tmp);
    cout << vb[cntr++] << endl;

    tmp = {2, 3};
    vb.emplace_back(blue, 2, 3, 6, 6, tmp);
    cout << vb[cntr++] << endl;

    tmp = {2, 4};
    vb.emplace_back(redBg, 3, 2, 6, 6, tmp);
    cout << vb[cntr++] << endl;

    tmp = {2, 3, 4};
    vb.emplace_back(cyanBg, 2, 4, 6, 6, tmp);
    cout << vb[cntr++] << endl;

    tmp = {4};
    vb.emplace_back(yellow, 3, 2, 6, 6, tmp);
    cout << vb[cntr++] << endl;

    if(b.fit(vb))
    {
        cout << "solved" << endl;
    }
    else
    {
        cout << "unsolvable" << endl;
    }
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

Month getMonth(const char* str)
{
    if(strcasecmp(str, "jan") == 0) return JAN;
    if(strcasecmp(str, "feb") == 0) return FEB;
    if(strcasecmp(str, "mar") == 0) return MAR;
    if(strcasecmp(str, "apr") == 0) return APR;
    if(strcasecmp(str, "may") == 0) return MAY;
    if(strcasecmp(str, "jun") == 0) return JUN;
    if(strcasecmp(str, "jul") == 0) return JUL;
    if(strcasecmp(str, "aug") == 0) return AUG;
    if(strcasecmp(str, "sep") == 0) return SEP;
    if(strcasecmp(str, "oct") == 0) return OCT;
    if(strcasecmp(str, "nov") == 0) return NOV;
    if(strcasecmp(str, "dec") == 0) return DEC;
    cout << "unknown month, program exits" << endl;
    exit(-1);
}
int getDayOfMonth(const char* str)
{
    int d = atoi(str);
    if(d < 0 || d > 31) 
    {
        cout << "unknown day of month, program exits" << endl;
        exit(-1);
    }
    return d;
}

DayOfWeek getDayOfWeek(const char* str)
{
    if(strcasecmp(str, "mon") == 0) return MON;
    if(strcasecmp(str, "tue") == 0) return TUE;
    if(strcasecmp(str, "wed") == 0) return WED;
    if(strcasecmp(str, "thu") == 0) return THU;
    if(strcasecmp(str, "fri") == 0) return FRI;
    if(strcasecmp(str, "sat") == 0) return SAT;
    if(strcasecmp(str, "sun") == 0) return SUN;
    cout << "unknown day of week, program exits" << endl;
    exit(-1);
}
int main(int argc, char** argv)
{
    //blockTest();
    //blockTest2();
    //blockTest3();
//    flipTest();
//    rotateTest();
    //equalityTest();
    //boardTest();
    Month m = OCT;
    int d = 8;
    DayOfWeek dow = TUE;
    if(argc == 4)
    {
        m = getMonth(argv[1]);
        d = getDayOfMonth(argv[2]);
        dow = getDayOfWeek(argv[3]);
        solveBoard(m, d, dow);
    }
    else
    {
        cerr << "provide month(in first 3 letter), day, day of week(in first 3 letter)" << endl;
        exit(-1);
    }
    //solveTest1();
    //solveTest2();
    //solveTest3();
    //solveTest4();
    //solveTest5();
    //solveTest6_1();
    //solveTest6_2();
    //solveTest7();
    //solveTest8();
    //fitTest();
    return 0;
}
