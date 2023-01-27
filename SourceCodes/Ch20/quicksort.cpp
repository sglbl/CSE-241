//File quicksort.cpp: the quick sort realization of the sorting pattern.
#include <algorithm>
using std::swap;

template <class T>
int split(T a[], int begin, int end)
{ 
    T *temp;
    int size = (end - begin);
    temp = new T[size];

    T splitV = a[begin];
    int up = 0;
    int down = size - 1;
    //Note that a[begin] = splitV is skipped.
    for (int i = begin + 1; i < end; i++)
    {
        if (a[i] <= splitV)
        {
            temp[up] = a[i];
            up++;
        }
        else
        {
            temp[down] = a[i];
            down--;
        }
    }
    //0 <= up = down < size

    temp[up] = a[begin]; //Positions the split value, spliV.

    //temp[i] <= splitV for i < up; temp[up] = splitV; temp[i] > splitV for i > up.
    //So, temp[i] <= temp[j] for i in [0, up) and j in [up, end).

    for (i = 0; i < size; i++)
        a[begin + i] = temp[i];

    if (up > 0)
        return (begin + up);
    else
        return (begin + 1); //Ensures that both pieces are nonempty.
}

template <class T>
void join(T a[], int begin, int splitPt, int end)
{
    //Nothing to do.    
}
