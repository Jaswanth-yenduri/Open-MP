#include <iostream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <omp.h>
using namespace std::chrono;

int partition(int*, int, int);

void quickSort(int* arr,int low, int high)
{
    if(low<high)
    {
        int m;
        m=partition(arr, low, high);

        #pragma omp task shared(arr) if (high-low > 10000)
        quickSort(arr, low, m - 1);

        #pragma omp task shared(arr) if (high-low > 10000)
        quickSort(arr, m + 1, high);
    }
    //#pragma omp taskwait
}

int partition(int* arr,int low,int high)
{
    int pivot,i,j;
    pivot = arr[low];

    i = low;
    j = high;

    while(i<=j)
    {
        while(arr[i]<=pivot && i <= high){
            i++;
        }

        while(arr[j]>pivot && j >= low){
            j--;
        }

        if(i<j)
        {
            int temp;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp;
    temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;
    return j;

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

    /**    
    for(int i = 0; i < size; i++) {
        std::cout<<array[i]<<" ";
    }
    */
    
    //omp_set_dynamic(0);
    //omp_set_num_threads(4);
    
    std::cout<<"\n";

    high_resolution_clock::time_point start = high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single
        quickSort(array, 0, size - 1);
        
    }

    high_resolution_clock::time_point end = high_resolution_clock::now();
    
    /**
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