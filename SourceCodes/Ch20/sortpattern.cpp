//This is the file sortpattern.cpp.
template <class T>
int split(T a[], int begin, int end);
//Rearranges elements [begin, end) of array a into two intervals
//[begin, split) and [splitPt, end), such that the sorting pattern works.
//Returns splitPt. 

template <class T>
void join(T a[], int begin, int splitPt, int end);
//Combines in the elements in the two intervals [begin, split) and [splitPt, end)
//in such a way that the sorting pattern works.

template <class T>
void sort(T a[], int begin, int end)
//Precondition: Interval [begin, end) of a has elements.
//Postcondition: The values in the interval [begin, end) have
//been rearranged so that a[0] <= a[1] <= ... <= a[(begin - end) - 1].
{
    if ((end - begin) > 1)
    {
        int splitPt = split(a, begin, end);
        sort(a, begin, splitPt);
        sort(a, splitPt, end);
        join(a, begin, splitPt, end);
    }//else sorting one (or fewer) elements so do nothing.
}

template <class T>
void sort(T a[], int numberUsed)
//Precondition: numberUsed <= declared size of the array a.
//The array elements a[0] through a[numberUsed - 1] have values.
//Postcondition: The values of a[0] through a[numberUsed - 1] have
//been rearranged so that a[0] <= a[1] <= ... <= a[numberUsed - 1].
{
    sort(a, 0, numberUsed);
}
