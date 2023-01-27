//File mergesort.cpp: the merge sort realization of the sorting pattern.
template <class T>
int split(T a[], int begin, int end)
{ 
    return ((begin + end)/2);
}

template <class T>
void join(T a[], int begin, int splitPt, int end)
{
    T *temp;
    int intervalSize = (end - begin);
    temp = new T[intervalSize];
    int nextLeft = begin; //index for first chunk
    int nextRight = splitPt; //index for second chunk
    int i = 0; //index for temp

    //Merge till one side is exhausted:
    while ((nextLeft < splitPt) && (nextRight < end))
    {
        if (a[nextLeft] < a[nextRight])
        {
            temp[i] = a[nextLeft];
            i++; nextLeft++;
        }
        else
        {
            temp[i] = a[nextRight];
            i++; nextRight++;
        }
    }

    while (nextLeft < splitPt)//Copy rest of left chunk, if any.
    {
        temp[i] = a[nextLeft];
        i++; nextLeft++;
    }

    while (nextRight < end) //Copy rest of right chunk, if any.
    {
        temp[i] = a[nextRight];
        i++; nextRight++;
    }

    for (i = 0; i < intervalSize; i++)
        a[begin + i] = temp[i];
}

