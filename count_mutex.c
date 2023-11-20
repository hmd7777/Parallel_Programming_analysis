#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <time.h>
#include "helpers.h"

// Shared data structure
typedef struct {
    const int *array;
    int start;      // Start index for this thread
    int end;        // End index for this thread
    int count;
    pthread_mutex_t *mutex; // Pointer to the shared mutex
} ThreadData;

// Thread function to count ones in a segment of the array
void *count_ones(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    for (int i = data->start; i < data->end; i++) {
        if (data->array[i] == 1) {
            pthread_mutex_lock(data->mutex); // Lock the mutex before updating count
            data->count++;
            pthread_mutex_unlock(data->mutex); // Unlock the mutex after updating count
        }
    }
    return NULL;
}

// Function to create threads and calculate the total count
int parallel_count_ones(const int *array, int size, int num_threads) {
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    int segment_size = size / num_threads;

    // Creating threads
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].array = array;
        thread_data[i].start = i * segment_size;
        thread_data[i].end = (i == num_threads - 1) ? size : (i + 1) * segment_size;
        thread_data[i].count = 0;
        thread_data[i].mutex = &mutex;
        pthread_create(&threads[i], NULL, count_ones, &thread_data[i]);
    }

    // Joining threads and summing up results
    int total_count = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_count += thread_data[i].count;
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return total_count;
}
void time_experiment(int num_threads){
    for (int size = 10; size < 1000000000; size*=10){
        int *myArray = create_random_array(size);
        double avg_time=0;
        for(int i = 0;i<100;i++){
            clock_t start = clock();
            int parallel_ones_count = parallel_count_ones(myArray, size, num_threads);
            clock_t end = clock();
            avg_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        printf("with size %d and %d threads, Avarage time: %f sec\n",size,num_threads,avg_time);
        free(myArray);
    }
}
void experiment(int num_threads){
    for (int size = 10; size < 1000000000; size*=10){
        int *myArray = create_random_array(size);
        int trueCount = true_count_ones(myArray,size);
        int sum = 0;
        double avg_time=0;
        for(int i = 0;i<100;i++){
            clock_t start = clock();
            int parallel_ones_count = parallel_count_ones(myArray, size, num_threads);
            clock_t end = clock();
            avg_time = ((double)(end - start)) / CLOCKS_PER_SEC;
            if (trueCount == parallel_ones_count) sum++;
        }
        printf("with size %d and %d threads there were %d/100 correct parallel counts. Avarage time: %f sec\n",size,num_threads,sum,avg_time);
        free(myArray);
    }
}
int main(){
    
experiment(1);
    printf("\n");
    experiment(2);
    printf("\n");
    experiment(4);
    printf("\n");
    experiment(32);
    /*
    time_experiment(1);
    printf("\n");
    time_experiment(2);
    printf("\n");
    time_experiment(4);
    printf("\n");
    time_experiment(32);
    */
    
    return 1;
}