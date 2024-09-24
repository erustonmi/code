//#include <block.h>
//#include <iostream>
#include <iostream>
using namespace std;

// Function to set the console text color using ANSI escape
// codes
void SetColor(int textColor)
{
    cout << "\033[" << textColor << "m";
}

// Function to reset the console color
void ResetColor() { cout << "\033[0m"; }

int main()
{
    // Set text color to bright white (97) and background
    // color to blue (44)
    SetColor(32);
    SetColor(47);
    cout
        << "This text is bright white on a blue background."
        << endl;

    // Reset to default colors
    ResetColor();
    cout << "This text is the default color." << endl;
    cout << "This text2 is the default color." << endl;
    cout << "This text3 is the default color." << endl;

    return 0;
}
