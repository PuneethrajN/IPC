#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <thread>
#include <chrono>
#include <mutex> 
using namespace std;

#define SHARED_MEMORY_SIZE 1024

int main() {
    int key = 65553;
    int shmid;

    shmid = shmget(key, SHARED_MEMORY_SIZE, IPC_CREAT | 0666);
    char *ptr = static_cast<char*>(shmat(shmid, nullptr, 0));
    
    cout <<" Shared memory Id: "<< shmid << endl;
    mutex mtx; 

    while (true) {
        string message;
        cout << "Enter a message to write to shared memory: " << endl;
        getline(cin, message);

        {
            lock_guard<mutex> lock(mtx); // Lock the mutex for the critical section
 
            snprintf(ptr, SHARED_MEMORY_SIZE, "%s", message.c_str());
        } 

        this_thread::sleep_for(chrono::seconds(2));
    }

    shmdt(ptr);

    return 0;
}
