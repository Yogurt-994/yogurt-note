#include <stdio.h>

int MaxInt(int a[], int i, int n)
{
    int k;
    if (i < n - 1)
    {
        k = MaxInt(a, i + 1, n);
        if (a[i] > k)
            return a[i];
        return k;
    }
    return a[n - 1];
}

int AverageInt(int a[], int i, int n, int *sum)
{
    if (i < n) // 递归终止条件
    {
        (*sum) += a[i];
        AverageInt(a, i + 1, n, sum); // 递归部分
    }
    return (*sum) / n;
}

int FindNum(int a[], int num, int i, int n)
{
    if (i < n && a[i] != num)             // 递归终止条件
        return FindNum(a, num, i + 1, n); // 递归部分
    if (i == n)                          
        return -1;
    return i;
}

int main()
{
    int arr[] = {5, 10, 15, 20, 25};
    int size = sizeof(arr) / sizeof(arr[0]);

    int max = MaxInt(arr, 0, size);
    printf("Max value: %d\n", max);

    int sum = 0;
    int average = AverageInt(arr, 0, size, &sum);
    printf("Average value: %d\n", average);

    int num = 15;
    int index = FindNum(arr, num, 0, size);
    if (index != -1)
        printf("Number %d found at index: %d\n", num, index);
    else
        printf("Number %d not found\n", num);

    return 0;
}
