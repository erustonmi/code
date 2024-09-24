
#include <stdio.h>

int binarySearch(int arr[], int num, int start, int end);
int main()
{
    int arr[] = {1, 2, 5, 12, 25, 26, 29, 34, 51, 100};
    int num = 26;
    int pos = binarySearch(arr, num, 0, 9);
    if(pos >= 0)
    {
        printf("number [%d] found at pos[%d]\n", num, pos);
    }
    else
    {
        printf("number [%d] not found\n", num);
    }
    return 0;
}

int binarySearch(int arr[], int num, int start, int end)
{
    int pos = -1;
    while(start <= end)
    {
        int mid = (start + end) / 2;
        if(arr[mid] > num)
        {
            end = mid - 1;
        }
        else if(arr[mid] < num)
        {
            start = mid + 1;
        }
        else
        {
            pos = mid;
            break;
        }
    }
    return pos;
}
