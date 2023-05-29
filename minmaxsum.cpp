#include <iostream>
#include <omp.h>
using namespace std;
void min_reduction(int arr[], int n)
{
    int min_value = 99999;

    cout << "Min : \n";

#pragma omp parallel for reduction(min \
                                   : min_value)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min_value)
        {
            min_value = arr[i];
        }

        cout << "\n  Thread id : " << omp_get_thread_num() << " i = " << i;
    }
    cout << "\n Minimum value: " << min_value << endl;
}
void max_reduction(int arr[], int n)
{
    int max_value = 0;
    cout << "Max : \n";
#pragma omp parallel for reduction(max \
                                   : max_value)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }

        cout << "\n Thread id : " << omp_get_thread_num() << " i = " << i;
    }
    cout << "\n Maximum value: " << max_value << endl;
}
void sum_reduction(int arr[], int n)
{
    int sum = 0;
    cout << "Sum : \n";
#pragma omp parallel for reduction(+ \
                                   : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
        cout << "\n Thread id : " << omp_get_thread_num() << " i = " << i;
    }
    cout << "\n Sum: " << sum << endl;
}
void average_reduction(int arr[], int n)
{
    int sum = 0;
    cout << "Avg : \n";
#pragma omp parallel for reduction(+ \
                                   : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
        cout << "\n Thread id : " << omp_get_thread_num() << " i = " << i;
    }
    cout << "\n  Average: " << (double)sum / n << endl;
}
int main()
{
    int n = 10;
    int arr[] = {5, 2, 9, 1, 7, 6, 8, 3, 4, 10};
    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    average_reduction(arr, n);
}