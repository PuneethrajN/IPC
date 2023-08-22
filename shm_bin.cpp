#include <iostream>
#include<thread>
#include <mutex>
#include <vector>
using namespace std;

mutex semaphore;  // Binary semaphore

void process(int id, vector<char>& shared_memory) {
    cout << "Process " << id << " is trying to take semaphore" << endl;
    semaphore.lock();
    cout << "Process " << id << " takes semaphore" << endl;

    char data[100] = "Hello";
    int i;  // Declare i here

    for (i = 0; data[i]; i++) {
        shared_memory[i] = data[i];
        this_thread::sleep_for(chrono::seconds(3));
        cout << "Process " << id << " writing" << endl;
	cout<<"read : "<< data[i] <<endl;

    }
    
    shared_memory[i] = '\0';  // Set the null terminator at the correct index
    cout << "Process " << id << " finishes writing" << endl;

    cout << "Process " << id << " is trying to release semaphore" << endl;
    semaphore.unlock();
    cout << "Process " << id << " releases semaphore" << endl;
}

int main() {
    vector<char> shared_memory(100, '\0');  // Shared memory simulation

    const int numThreads = 3;  // Number of threads to create
    thread threads[numThreads];

    for (int i = 0; i < numThreads; i++) {
        threads[i] = thread(process, i + 1, ref(shared_memory));
    }

    for (int i = 0; i < numThreads; i++) {
        threads[i].join();
    }

    return 0;
}


