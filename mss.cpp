#include <iostream>
#include <sstream>
#include <cstdlib>
#include <chrono>
using namespace std::chrono;

void merge(int*, int, int*);

void mergeSort(int *arr, int n, int *tempArr)
{
    if (n > 1) {
        mergeSort(arr, n/2, tempArr);
        mergeSort(arr+(n/2), n-(n/2), tempArr + n/2);
        merge(arr, n, tempArr);
    }
}

void merge(int *arr, int n, int *tempArr) {

   int i = 0;
   int j = n/2;
   int k = 0;

    while (i < n/2 && j < n) {
        if(arr[i] < arr[j]) {
            tempArr[k] = arr[i];
            i++;
            k++;
        }
        else {
            tempArr[k] = arr[j];
            j++;
            k++;
        }
    }

    while (i < n/2) {
        tempArr[k] = arr[i];
        i++;
        k++;
    }
    while (j < n) {
        tempArr[k] = arr[j];
        j++;
        k++;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = tempArr[i];
    }
}

int * randNumArray(const int size, const int seed) {
    srand(seed);
    int *array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = std::rand() % 1000000;
    }

    return array;
}

int main(int argc, char **argv) {

    int * array;
    int size, seed;
    if(argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [amount of random nums to generate] [seed value for rand]" << std::endl;
        exit(-1);
    }

    {
        std::stringstream ss1(argv[1]);
        ss1>>size;
    }
    {
        std::stringstream ss1(argv[2]);
        ss1>>seed;
    }

    array = randNumArray(size, seed);
    int *tempArr = new int[size];

    /*
    for(int i = 0; i < size; i++) {
        std::cout<<array[i]<<" ";
    }
    */

    std::cout<<"\n";

    high_resolution_clock::time_point start = high_resolution_clock::now();
    
    mergeSort(array, size, tempArr);

    high_resolution_clock::time_point end = high_resolution_clock::now();
    
    /*    
    for(int i = 0; i < size; i++) {
        std::cout<<array[i]<<" ";
    }
    */

    std::cout<<"\n";

    delete[] array;

    duration<double> time_span = (end - start);

    std::cout << "Time: " << time_span.count() << " secs" << std::endl;
    return 0;
}