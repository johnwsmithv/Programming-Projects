#include <pthread.h>
#include <iostream>

#define THREADS 8

/**
 * @brief Simple function to show threads printing out Hello World along with their thread ID
 * 
 * @param threadID The ID of the Thread calling this function
 * @return void* 
 */
void * helloWorld(void * threadID) {
    long tid;
    tid = reinterpret_cast<long>(threadID);

    std::cout << "Hello world! Thread ID: " << tid << "\n";
    pthread_exit(NULL);
} 

int main() {
    pthread_t threads[THREADS];

    for(uintptr_t i = 0; i < THREADS; i++){
        pthread_create(&threads[i], NULL, helloWorld, (void *)i);
    }
    pthread_exit(NULL);
}