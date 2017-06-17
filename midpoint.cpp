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

template <typename T>
bool loadFile(string &filename, T data[])
{
    ifstream din(filename.c_str());
    if (din.fail())
        return false;
    for (int i = 0; i < SIZE; i++)
        din >> data[i];
    return true;
    din.close();
}

template <typename T>
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

template <typename T>
void partition3(T data[], int low, int high, int &mid)
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

template <typename T>
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

template <typename T>
void quicksort3(T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
        // Partition data into two parts
        int mid = 0;
        partition3(data, low, high, mid);
        
        // Recursive calls to sort array
        quicksort3(data, low, mid - 1);
        quicksort3(data, mid + 1, high);
    }
}

void print(string data[])
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
    }
    clock_t end = clock();
    double total = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time: " << total << "(s)" << endl;
    print(data);
    return 0;
}

