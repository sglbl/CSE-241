//File selectionsort.cpp: the selection sort realization
//of the sorting pattern.
#include <algorithm>
using std::swap;

template <class T>
int indexOfSmallest(const T a[], int startIndex, 
                                 int sentinelIndex)
{
    int min = a[startIndex],
        indexOfMin = startIndex;
    for (int index = startIndex + 1; 
                     index < sentinelIndex; index++)
        if (a[index] < min)
        {
            min = a[index];
            indexOfMin = index;
            //min is the smallest of a[startIndex]
             //through a[index]
        }

    return indexOfMin;
}

template <class T>
int split(T a[], int begin, int end)
{ 
    int index = indexOfSmallest(a, begin, end);
    swap(a[begin], a[index]);
    return (begin + 1);
}

template <class T>
void join(T a[], int begin, int splitPt, int end)
{
    //Nothing to do.
}