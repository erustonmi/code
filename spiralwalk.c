/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int a[20][20];
enum {DOWN, LEFT, UP, RIGHT};

// given the current position, direction, n, and the number
// to be printed, figure out the next position and return
// the direction.
int next(int* i, int* j, int dir, int n, int this_n)
{
    int x = *i, y = *j;
    int max = n * n;
     // adj tells when to change direction
    int adj = 1;
    
    for(int m = n - 2; m > 0; m = m - 2)
    {
        if(m <= 0) break;
        if(max - this_n > m * m)
        {
            break;
        }
        else if(max - this_n <= m * m)
        {
            adj++;
        }
    }
    
    if(DOWN == dir)
    {
        y++;
        if(y == n - adj) dir = LEFT;
    }
    else if(LEFT == dir)
    {
        x--;
        if(x == adj - 1) dir = UP;
    }
    else if(UP == dir)
    {
        y--;
        if(y == adj - 1) dir = RIGHT;
    }
    else
    {
        x++;
        if(x == n - adj) dir = DOWN;
    }
//    printf("adj(%d), this_n(%d), dir(%d), curr pos:(%d,%d), next pos(%d,%d)\n", adj, this_n, dir, *i, *j, x, y);
    *i = x;
    *j = y;
    return dir;
}

void printn_2(int n)
{
    int cnt = n * n;
    memset(a, 0, sizeof(a));
    int x = n - 1, y = 0; // starting position
    int dir = DOWN;
    for(int i = 0; i < cnt; ++i)
    {
        a[x][y] = i + 1;
        //printf("pos(%d,%d), val(%d)\n", x, y, a[x][y]);
        dir = next(&x, &y, dir, n, a[x][y] + 1);
    }
}


int main(int argc, char** argv)
{
    if(argc != 2) return -1;
    int n = atoi(argv[1]);
    //printn(n);
    printn_2(n);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            printf("%02d ", a[j][i]);
        }
        printf("\n");
    }
    return 0;
}

