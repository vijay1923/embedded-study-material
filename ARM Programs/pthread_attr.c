#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thread_func(void* arg) {
    printf("Detached thread running\n");
    return NULL;
}

int main() {
    pthread_attr_t attr;
    pthread_t thread;
    
    // Initialize attribute object
    pthread_attr_init(&attr);
    
    // Set as detached
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    // Set custom stack size (1MB)
    pthread_attr_setstacksize(&attr, 1024*1024);
    
    // Create thread
    if(pthread_create(&thread, &attr, thread_func, NULL) != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Clean up attribute object
    pthread_attr_destroy(&attr);
    
    // Main thread continues while detached thread runs independently
    printf("Main thread continuing\n");
    
    // No need to join the detached thread
    sleep(1); // Give detached thread time to complete
    
    return 0;
}