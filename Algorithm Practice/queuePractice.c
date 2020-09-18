/**
 * @Author: John W. Smith, V and Robert (Big Man) McHugh
 * @Date: 09/15/2020
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	float currentTime;
    int threadID;
    int remainingTime;
    int threadPriority;
} Node;

typedef struct Queue{
	Node *threadValue;
	struct Queue *next;
} Queue;

/**
 * Once the thread is done it is going to call Schedule_me again
 * 
 */ 
// When a thread comes in, it is going to be appended to this queue
static Queue *readyQueue;
// Going to be added to in a function like STRF
static Queue *blockedQueue;
// When this is empty it is going to be populated with the first thing that comes in; 
// 
static Queue *runningQueue;

void printLinkedList(Queue * queue){
    while(queue){
        printf("CT %f | TID %d | RT %d | TP %d -> ", queue->threadValue->currentTime, queue->threadValue->threadID, queue->threadValue->remainingTime, queue->threadValue->threadPriority);
        queue = queue->next;
        if(queue == NULL){
            printf(" NULL\n");
        }
    }
}

/**
 * So we aren't repeating the same code 100 Times. This is a simple function
 * to fill in the metadata for the Queue Data Structure
 * 
 */ 
Queue *fillMetaData(float currentTime, int threadID, int remainingTime, int threadPriority){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->threadValue = (Node *)malloc(sizeof(Node));
    queue->threadValue->currentTime = currentTime;
    queue->threadValue->threadID = threadID;
    queue->threadValue->remainingTime = remainingTime;
    queue->threadValue->threadPriority = threadPriority;
    return queue;
}
/**
 * Inputs: 
 *          Queue ** headQueue: A pointer to the head of the queue
 *          float currentTime: The current time when the thread is calling the schedule_me function    
 *          int threadID: the corresponding thread ID to the thread that is being queued
 *          int remainingTime: the remaining time in the CPU Burst for the thread
 *          int threadPriority: This is needed
 * Outputs: We are populating the headQueue object with new members of the linked List
 * 
 * i.e Say we fill in the Queue with three threads. It's going to be as follows:
 * 0 -> 1 -> 2 -> NULL        
 */ 
void firstComeFirstServeEnqueue(Queue **headQueue, float currentTime, int threadID, int remainingTime, int threadPriority){
    // Temporary queue that is going to help with appending the metadata to the headqueue
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    // Queue that is going to hold the headPointer
    Queue *tempQueue = *headQueue;
    queue = fillMetaData(currentTime, threadID, remainingTime, threadPriority);
    // If the head is empty, it'll be null and that means that the first entry of the queue is going to be followed by a NULL
    // Else it is not empty, then we are going to append the elements to the end of the linked list
    if(*headQueue == NULL){
        queue->next = *headQueue;
        *headQueue = queue;
    } else {
        while(tempQueue) {
            if(tempQueue->next == NULL){
                tempQueue->next = queue;
                tempQueue->next->next = NULL;
            }
            tempQueue = tempQueue->next;
        }
    }
    printf("Size of Queue object %d\nSize of Queue %d\n", sizeof(queue), sizeof(Queue *));
}
void firstComeFirstServeDequeue(Queue **headQueue){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue = *headQueue;
    *headQueue = queue->next;
}
/**
 * Obviously when a thread asks to be added to the queue, add it
 * Say we have the following in the queue:
 * Time Received  |  0  |  1  |  1 |
 * ThreadIDs      |  0  |  1  |  2 |
 * Time Remaining |  6  |  4  |  3 |
 * We're going to run thread 0 for one cycle and then pre-empt thread 0 which is in a blocking queue
 * and we are going to run thread 2 and continue until it finishes, 
 * 
 * Here is an example:
 * L = LeftPointer | R = RightPointer
 * We're going to insert a thread with tid of 4 and a remaining time of 5
 * Thread ID      | 0 | 3 | 1 | 2 |   ===>   | 0 | 3 | 4 | 1 | 2 |
 * Remaining Time | 1 | 3 | 7 | 9 |          | 1 | 3 | 5 | 7 | 9 |
 * Pointers             L   R  
 * 
 * If we had the same remaining time like as follows:
 * We're going to insert a thread with tid of 4 and a remaining time of 3
 * What decides where the new thread goes?
 * Thread ID      | 0 | 3 | 1 | 2 |   ===>   | 0 | 3 | 1 | 4 | 2 |
 * Remaining Time | 1 | 3 | 3 | 9 |          | 1 | 3 | 3 | 3 | 9 |
 * Pointers             L   R  
 */  

void shortestTimeRemainingEnqueue(Queue **headQueue, float currentTime, int threadID, int remainingTime, int threadPriority){
    Queue *rightPointer = *headQueue;
    Queue *leftPointer = NULL;
    Queue *newProcess = (Queue *)malloc(sizeof(Queue));
    newProcess->threadValue = (Node *)malloc(sizeof(Node));
    newProcess = fillMetaData(currentTime, threadID, remainingTime, threadPriority);
    // If the head is empty, it'll be null and that means that the first entry of the queue is going to be followed by a NULL
    // Else it is not empty, then we need to do some fun linked list operations
    if(*headQueue == NULL) {
        newProcess->next = *headQueue;
        *headQueue = newProcess;    
    } else {
        // Going through the pointer that is saving the head pointer
        while(rightPointer) {
            // If we are entering the linked list and the value the right pointer is on is less than the new process then we are going
            // to set our left pointer equal to the right pointer and set the right pointer to the next element in the linked list; this
            // process will continue until a match is found which will be handled by the else-if statement. The embedded if-statement is 
            // checking to see if the head-node which the rightPointer is pointing at's next value is NULL and the outer if-statement is true.
            // If it is, then we are going to append the newProcess as next.
            if(rightPointer->threadValue->remainingTime < newProcess->threadValue->remainingTime) {
                //printf("We're in the first if statement\n");
                if(rightPointer->next == NULL) {
                    //printf("1\n");
                    rightPointer->next = newProcess;
                    rightPointer->next->next = NULL;
                    return;
                } else {
                    //printf("2\n");
                    leftPointer = rightPointer;
                    rightPointer = rightPointer->next;
                }
            } else if(rightPointer->threadValue->remainingTime > newProcess->threadValue->remainingTime){
                //printf("We're in the else-if statement\n");
                // We are going to be inserting the entry into the linked list; the first if statment is basically saying that the 
                // entry coming in has a remaining time smaller than the head, so we are going to swap; the else statement is 
                // inserting the new procecss in between the left and right node

                // This is if the new nodes value is the first entry in the linked list
                if(leftPointer == NULL) {
                    newProcess->next = *headQueue;
                    *headQueue = newProcess;
                    return;
                } else {
                    // This is going to happen if the value that is going to be inserted into the list is like the example in the 
                    // description above
                    leftPointer->next = newProcess;
                    leftPointer->next->next = rightPointer;
                    return;
                }
            } else {
                //printf("We're in the else-statement\n");
                // This one they're equal so we're going to check if the next entry is equal or greater than
                leftPointer = rightPointer;
                rightPointer = rightPointer->next;
            }
        }
    }
}

Queue *shortestTimeRemainingDequeue(Queue **headQueue){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue = *headQueue;
    *headQueue = queue->next;
}

void priortyBasedSchedulingEnqueue(Queue **headQueue, float currentTime, int threadID, int remainingTime, int threadPriority){
    Queue *rightPointer = *headQueue;
    Queue *leftPointer = NULL;
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->threadValue = (Node *)malloc(sizeof(Node));
    queue = fillMetaData(currentTime, threadID, remainingTime, threadPriority);

    if(*headQueue == NULL) {
        queue->next = *headQueue;
        *headQueue = queue;  
    }  
    else {
        while(rightPointer) {
            if(rightPointer->threadValue->threadPriority < queue->threadValue->threadPriority) {
                if(rightPointer->next == NULL) {
                    rightPointer->next = queue;
                    rightPointer->next->next = NULL;
                    return;
                } else {
                    leftPointer = rightPointer;
                    rightPointer = rightPointer->next;
                }
            }
            else if(rightPointer->threadValue->threadPriority > queue->threadValue->threadPriority) {
                if(leftPointer->next == NULL) {
                    queue->next = *headQueue;
                    *headQueue = queue;
                } else {
                    
                }
            }
        }
    }
    
}
Queue *priortyBasedSchedulingDequeue(Queue **headQueue){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue = *headQueue;
    *headQueue = queue->next;
}

/**
 * We are going to need to make an array of Queues with each entry in the array being another level
 * The levels are going to be from 1 to 5.
 * The time quanta for the levels are 5, 10, 15, 20, 25 respectively
 * When the threads in the higher levels finish their quanta they're going to be added to the lower levels
 */ 
void multiLevelFeedBackEnqueue(Queue **headQueue[5], float currentTime, int threadID, int remainingTime, int threadPriority){
    // if time quanta for process on level then move to another level
    printf("We're in the function\n");
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    // Queue that is going to hold the headPointer
    Queue *tempQueue[5];
    for(int i = 0; i < 5; i++){
        tempQueue[i] = *headQueue[i];
    }
    printf("Filling in the METADATA\n");
    queue = fillMetaData(currentTime, threadID, remainingTime, threadPriority);
    // tempQueue[1] = queue;
    if(*headQueue == NULL){
        queue->next = *headQueue[0];
        *headQueue[0] = queue;
    } else {
        while(tempQueue) {
            if(tempQueue[0]->next == NULL){
                tempQueue[0]->next = queue;
                tempQueue[0]->next->next = NULL;
            }
            tempQueue[0] = tempQueue[0]->next;
        }
    }
}

Queue *multiLevelFeedBackDequeue(Queue **headQueue){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue = *headQueue;
    *headQueue = queue->next;
}
int main(void){
    float currentTime = 6.0;
    int threadID = 0;
    int remainingTime = 2;
    int threadPriority = 1;
    
    int numThreads = 4;
    printf("Hello\n");
    Queue *headQueue = NULL;
    Queue **headMLFQueue[5];
    for(int i = 0; i < 5; i++){
        headMLFQueue[i] = NULL;
    }
    // Queue *queue = NULL;
    // Queue *head = (Queue *)malloc(sizeof(Queue));
    printf("After declaring the Queue structs\n");
    while(numThreads > 0){
        // firstComeFirstServeEnqueue(&headQueue, currentTime, threadID, remainingTime, threadPriority);
        multiLevelFeedBackEnqueue(&headMLFQueue[0], currentTime, threadID, remainingTime, threadPriority);
        printLinkedList(*headMLFQueue[0]);
        //shortestTimeRemainingEnqueue(&headQueue, currentTime, threadID, remainingTime, threadPriority);
        //printLinkedList(headQueue);
        //printf("Queue Current time: %f\n", headQueue->threadValue->currentTime);
        currentTime += 1.0;
        threadID += 1;
        remainingTime += 2;
        threadPriority += 1;
        // headQueue->next = NULL;
        //headQueue = headQueue->next;
        numThreads--;
    }
    // shortestTimeRemainingEnqueue(&headQueue, 10, 4, 4, 1);
    // printLinkedList(headQueue);
    // shortestTimeRemainingEnqueue(&headQueue, 11, 5, 1, 1);
    // printLinkedList(headQueue);
    // printLinkedList(headQueue);
    // firstComeFirstServeDequeue(&headQueue);
    // printLinkedList(headQueue);
    free(headQueue);
    printf("Outside the while loop\n");
    // printf("Here is the value at the queue: %d", queue->value->random);
}