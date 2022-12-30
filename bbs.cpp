/**
 * 
 * Jaswanth Yenduri (jyendur@siue.edu)
 * 800746158
 * 
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <vector>
using namespace std::chrono;

using high_resolution_clock = system_clock;

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

    high_resolution_clock::time_point start = high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
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