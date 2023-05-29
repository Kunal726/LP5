#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

void merge(int a[], int left, int middle, int right)
{
    int i, j, k;

    int n1 = middle - left + 1;
    int n2 = right - middle;

    int l[n1], r[n2];

    // Add left to left array
    for (i = 0; i < n1; i++)
    {
        l[i] = a[left + i];
    }

    // Add right to right array
    for (j = 0; j < n2; j++)
    {
        r[j] = a[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (l[i] <= r[j])
        {
            a[k++] = l[i++];
        }
        else
        {
            a[k++] = r[j++];
        }
    }
    while (i < n1)
    {
        a[k++] = l[i++];
    }

    while (j < n2)
    {
        a[k++] = r[j++];
    }
}

void merge_sort(int a[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

#pragma omp task
        merge_sort(a, left, middle);

#pragma omp task
        merge_sort(a, middle + 1, right);

        merge(a, left, middle, right);
    }
}

void parallel_merge_sort(int a[], int n)
{
#pragma omp parallel_merge_sort
    {
#pragma omp single
        merge_sort(a, 0, n);
    }
}

int main()
{
    int n = 10;
    int a[n];

    cout << " Before Sorting : " << endl;

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 25 * n;

        cout << a[i] << " ";
    }

    merge_sort(a, 0, n);

    cout << endl
         << " After Sorting : " << endl;

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}