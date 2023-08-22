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

    cout <<"Shared memory id: "<< shmid << endl; 
    mutex mtx; 
    while (true) {
        {
            lock_guard<mutex>lock(mtx); 
          
            cout << "Read thread: " << ptr << endl;
        } 
       this_thread::sleep_for(chrono::seconds(3));
    }

    shmdt(ptr);

	shmctl(shmid, IPC_RMID, nullptr);
    return 0;
}
