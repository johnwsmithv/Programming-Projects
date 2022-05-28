#include <pthread.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>

#define THREADS 8
#define ARRAYSIZE 2000000000

static std::vector<long long> globalVector(ARRAYSIZE);

struct threadStruct {
    int threadID;
    long long lowerBounds;
    long long upperBounds;
    bool threadFinished;
} typedef threadStruct;

void singleThreadArrayAccess(){
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(long long i = 0; i < ARRAYSIZE; i++) {
        globalVector[i] = i;
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> finalTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    std::cout << "Single Threaded assignment took: " << finalTime.count() << " seconds.\n";
}

void *accessArray(void * args) {
    threadStruct * localThreadParams = (threadStruct *)args;
    // std::cout << "Thread ID " << localThreadParams->threadID << " | Array Elements: (" << localThreadParams->lowerBounds << ", " << localThreadParams->upperBounds << ")\n"; 
    
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(long long i = localThreadParams->lowerBounds; i <= localThreadParams->upperBounds; i++){
        globalVector[i] = i;
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> finalTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    std::cout << "Thread ID " << localThreadParams->threadID << " took " << finalTime.count() << " seconds on (" << localThreadParams->lowerBounds << ", " << localThreadParams->upperBounds << ")!\n";
    localThreadParams->threadFinished = true;

    pthread_exit(NULL);
    return 0;
}

int main(int argc, char ** argv){
    if(argc != 2) {
        std::cerr << "You need to enter either 1 for single threaded or 2 for multi-threaded!\n";
        exit(1);
    }
    int option = std::atoi(argv[1]);
    if(option == 1) {
        std::cout << "Single Threaded Array Access!\n";
        singleThreadArrayAccess();
    } else if(option == 2){
        std::cout << "Mulit-threaded Array Access!\n";
        pthread_t threads[THREADS];
        threadStruct *threadParams = new threadStruct[THREADS];

        // This loop simply divides up the work for the threads
        long long elementsPerThread = ARRAYSIZE / THREADS;
        for(int i = 0; i < THREADS; i++) {
            threadParams[i].threadID = i;
            threadParams[i].lowerBounds = i * elementsPerThread;
            long long upperBound = ((i + 1) * elementsPerThread) - 1;
            if(upperBound > ARRAYSIZE || ((i + 1 == THREADS) && upperBound < ARRAYSIZE)) {
                threadParams[i].upperBounds = ARRAYSIZE - 1;
            } else {
                threadParams[i].upperBounds = upperBound;
            }
            threadParams[i].threadFinished = false;
        }

        for(int i = 0; i < THREADS; i++){
            std::cout << "Master Thread spawned thread ID " << threadParams[i].threadID << "\n";
            pthread_create(&threads[i], NULL, &accessArray, &threadParams[i]);
        }

        bool allThreadDone = false;

        // The point of this while loop is so the main thread which is driving this program waits for the 8 threads to work on the array
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        while(!allThreadDone) {
            bool tempBool = true;
            for(int i = 0; i < THREADS; i++) {
                tempBool &= threadParams[i].threadFinished;
            }
            if(tempBool) {
                std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> finalTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
                std::cout << "All threads are done; it took " << finalTime.count() << " seconds!\n";
                allThreadDone = true;
            }
        }

        std::cout << "Master thread done.\n";
        pthread_exit(NULL);
        
    }
}