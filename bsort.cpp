#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void parallel()
{
    int n = 100;
    int temp;
    int a[n];

    cout << " Before Sorting : " << endl;

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % n;

        cout << a[i] << " ";
    }

    cout << endl;

    // use any both works

    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;

        #pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
    }

    cout << " After Sorting : " << endl;

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
}

void serial()
{
    int n = 100;
    int temp;
    int a[n];

    cout << " Before Sorting : " << endl;
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % n;

        cout << a[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < n - i; j += 1)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
    }

    cout << " After Sorting : " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
}

int main()
{
    // ignore clock part
    clock_t s, e, s1, e1;
    s = clock();
    parallel();
    e = clock();

    s1 = clock();
    serial();
    e1 = clock();

    cout << endl
         << "Time taken Parallel : " << double(e - s) / double(CLOCKS_PER_SEC);
    cout << endl
         << "Time taken Serial : " << double(e1 - s1) / double(CLOCKS_PER_SEC);
    return 0;
}
