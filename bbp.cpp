/**
 * 
 * Jaswanth Yenduri (jyendur@siue.edu)
 * 800746158
 * 
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <omp.h>
#include <chrono>
using namespace std::chrono;

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

    std::cout<<"\n";

    omp_set_num_threads(4);
    omp_set_dynamic(0);

    high_resolution_clock::time_point start = high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        int itr = i%2;

        #pragma omp parallel for shared(array, itr)
        for (int j = itr; j < size - 1; j=j+2) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
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