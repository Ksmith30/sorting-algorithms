/* 
 * File:   main.cpp
 * Author: kyle
 *
 * Created on June 9, 2017, 2:28 PM
 */

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
const int SIZE = 20;

template <class T>
bool loadFile(string &filename, T data[])
{
    ifstream din(("/Users/kyle/Downloads/unsorted.txt" + filename).c_str());
    if (din.fail())
        return false;
    for (int i = 0; i < SIZE; i++)
        din >> data[i];
    return true;
    din.close();
}

template <class T>
void partition(T data[], int low, int high, int &mid)
{
    // Select pivot value
    T pivot = data[high];
    int left = low;
    int right = high;
    
    // Partition array into two parts
    while (left < right)
    {
        // Scan left to right
        while ((left < right) && (data[left] < pivot))
            left++;
        
        // Scan right to left
        while ((left < right) && (data[right] >= pivot))
            right--;
        
        // Swap data values
        swap(data[left], data[right]);
    }
    
    // Swap pivot to mid
    mid = left;
    data[high] = data[mid];
    data[mid] = pivot;
}

template <class T>
void quicksort(T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
        // Partition data into two parts
        int mid = 0;
        partition(data, low, high, mid);

        // Recursive calls to sort array
        quicksort(data, low, mid - 1);
        quicksort(data, mid + 1, high);
    }
}

template <class T>
void partition3(T array[], int low, int high, int &i, int &j)
{
    // To handle 2 elements
    if (high - low <= 1)
    {
        if (array[high] < array[low])
            swap(array[high], array[low]);
        i = low;
        j = high;
        return;
    }
 
    int mid = low;
    T pivot = array[high];
    while (mid <= high)
    {
        if (array[mid] < pivot)
            swap(array[low++], array[mid++]);
        else if (array[mid] == pivot)
            mid++;
        else if (array[mid] > pivot)
            swap(array[mid], array[high--]);
    }
 
    //update i and j
    i = low-1;
    j = mid;
}

template <class T>
void quicksort3(T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
        // Partition data into two parts
        int i, j;
        partition3(data, low, high, i, j);
        
        // Recursive calls to sort array
        quicksort3(data, low, i);
        quicksort3(data, j, high);
    }
}

template <class T>
void medianPartition(T data[], int low, int high, int &mid)
{
    // Select pivot value
    mid = (high - low) / 2;
    int median = max(min(low, mid), min(max(low, mid), high));
    T pivot = data[median];
        
    int left = low;
    int right = high;
    
    // Partition array into two parts
    while (left < right)
    {
        // Scan left to right
        while ((left < right) && (data[left] < pivot))
            left++;
        
        // Scan right to left
        while ((left < right) && (data[right] >= pivot))
            right--;
        
        // Swap data values
        swap(data[left], data[right]);
    }
    
    // Swap pivot to mid
    mid = left;
    data[high] = data[mid];
    data[mid] = pivot;
}

template <class T>
void medianQuicksort(T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
        // Partition data into two parts
        int mid = 0;
        medianPartition(data, low, high, mid);

        // Recursive calls to sort array
        medianQuicksort(data, low, mid - 1);
        medianQuicksort(data, mid + 1, high);
    }
}

template<class T>
void insertionSort(T data[], int low, int high)
{
    // Insert each element of unsorted list into sorted list
    for (int unsorted = low + 1; unsorted <= high; unsorted++)
    {
        // Select unsorted value to be inserted
        T value = data[unsorted];
        int posn  = unsorted;

        // Make room for new data value
        while ((posn > 0) && (data[posn - 1] > value))
        {
            data[posn] = data[posn - 1];
            posn--;
        }

        // Put new value into array
        data[posn] = value;
    }
}

template <class T>
void print(T data[])
{
    for (int i = 0; i < SIZE; i++)
        cout << data[i] << ' ';
    cout << endl;
}

int main()
{
    //Get File Name
    string filename;
    cout << "Input Filename: ";
    getline(cin, filename);
    
    //Load File
    string data[SIZE];
    if (!loadFile(filename, data))
    {
        cout << "Sorry your file was not able to load." << endl;
        return 1;
    }
    print(data);
    
    //Get Test Type
    cout << "Test Types: " << endl
            << "(1) Baseline" << endl
            << "(2) 3-Way" << endl
            << "(3) Median" << endl
            << "(4) Hybrid" << endl
            << "(5) 3-Way + Median" << endl
            << "(6) 3-Way + Hybrid" << endl
            << "(7) Median + Hybrid" << endl
            << "(8) 3-Way + Median + Hybrid" << endl
            << "Input test type: ";
    int testType;
    cin >> testType;
    //int iTest = atoi(testType.c_str());
    
    //Execute Test
    int low = 0; 
    int high = SIZE;
    clock_t start = clock();
    switch (testType)
    {
        case 1: quicksort(data, low, high); 
        case 2: quicksort3(data, low, high);
        case 3: medianQuicksort(data, low, high);
        case 4: insertionSort(data, low, high);
        case 5: ;
        
    }
    clock_t end = clock();
    double total = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time: " << total << "(s)" << endl;
    print(data);
    return 0;
}

