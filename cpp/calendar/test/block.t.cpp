#include <block.h>
#include <board.h>
//#include <iostream>

using namespace std;
void flipTest()
{
    Color::Modifier yellow(Color::FG_YELLOW);
    Block b(yellow, 2, 4, {5, 6, 7});
    cout << b << endl;
    b.flip();
    cout << b << endl;
    b.flip();
    cout << b << endl;

    Color::Modifier green(Color::FG_GREEN);
    Block b2(green, 2, 3, {4});
    cout << b2;
    cout << b2.flip() << endl;
    cout << b2;
}

void rotateTest()
{
    Color::Modifier yellow(Color::FG_YELLOW);
    Block b(yellow, 2, 4, {5, 6, 7});
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
    Block b1(red, 2, 3, {2, 3});
    cout << b1 << endl;
    Block b2(green, 2, 3, {4});
    cout << b2 << endl;
    Block b3(yellow, 3, 3, {0, 2, 3, 5});
    cout << b3 << endl;
    Block b4(blue, 2, 4, {5, 6, 7});
    cout << b4 << endl;
}

void equalityTest()
{
    Color::Modifier yellow(Color::FG_YELLOW);
    Block b1(yellow, 2, 4, {5, 6, 7});
    cout << b1;
    Block b2(yellow, 4, 2, {3, 5, 7});
    cout << b2;
    cout << (b1 == b2) << endl;
    cout << (b2 == b1) << endl << endl;

    Color::Modifier green(Color::FG_GREEN);
    Block b3(green, 2, 3, {3});
    cout << b3;
    Block b4(green, 2, 3, {4});
    cout << b4;
    cout << (b3 == b4) << endl;
    cout << (b4 == b3) << endl << endl;

    Color::Modifier red(Color::FG_RED);
    Block b5(red, 4, 2, {1, 3, 6});
    cout << b5;
    Block b6(red, 2, 4, {3, 4, 5});
    cout << b6;
    cout << (b5 == b6) << endl;
    cout << (b6 == b5) << endl << endl;
}

int main(int argc, char** argv)
{
//    blockTest();
//    flipTest();
//    rotateTest();
    //equalityTest();
    Color::Modifier cyan(Color::BG_CYAN);
    Board b(cyan, {6, 13, 49, 50, 51, 52});
    cout << b;
    return 0;
}
