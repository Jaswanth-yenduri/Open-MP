#include <iostream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <omp.h>
using namespace std::chrono;

void merge(int*, int, int*);

void mergeSort(int *arr, int n, int *tempArr)
{
    if (n < 2) return;

    #pragma omp task shared(arr) if (n > 10000)
    mergeSort(arr, n/2, tempArr);

    #pragma omp task shared(arr) if (n > 10000)
    mergeSort(arr+(n/2), n-(n/2), tempArr + n/2);

    #pragma omp taskwait
    merge(arr, n, tempArr);
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
    omp_set_num_threads(8);
    omp_set_dynamic(0);

    high_resolution_clock::time_point start = high_resolution_clock::now();
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergeSort(array, size, tempArr);
        }
    }

    high_resolution_clock::time_point end = high_resolution_clock::now();
    
    /*
    for(int i = 0; i < size; i++) {
        std::cout<<array[i]<<" ";
    }
    */

    std::cout<<"\n";

    delete[] array;
    delete[] tempArr;

    duration<double> time_span = (end - start);

    std::cout << "Time: " << time_span.count() << " secs" << std::endl;
    return 0;
}