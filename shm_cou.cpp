#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include<cstring>
#include <semaphore.h>
using namespace std;

sem_t semaphore;  // Counting semaphore

void process(int id, vector<char>& shared_memory) {
    cout << "Process " << id << " is trying to acquire semaphore: " << endl;
    sem_wait(&semaphore);
    cout << "Process " << id << " acquires semaphore: " << endl;

    char data[100] = "Hello"; // Shared memory Controlled by semaphore";
    for (int i = 0; data[i]; i++) 
    {
        shared_memory[i] = data[i];
        this_thread::sleep_for(chrono::seconds(5));

        cout << "Process " << id << " writing" << endl;
	cout<<"read: "<<data[i]<<endl;
    }

    shared_memory[strlen(data)] = '\0';
    cout << "Process " << id << " finishes writing" << endl;

    cout << "Process " << id << " is releasing semaphore" << endl;
    sem_post(&semaphore);

    cout << "Process " << id << " releases semaphore" << endl;
}

int main() {
    vector<char> shared_memory(100, '\0');  // Shared memory simulation

    const int numThreads = 5;  // Number of threads to create
    thread threads[numThreads];

    sem_init(&semaphore, 0, 2);  // Initialize semaphore with limit 2

    for (int i = 0; i < numThreads; i++) {
        threads[i] = thread(process, i + 1, ref(shared_memory));
    }

    for (int i = 0; i < numThreads; i++) {
        threads[i].join();
    }

    sem_destroy(&semaphore);  // Clean up semaphore

    return 0;
}

