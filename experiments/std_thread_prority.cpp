#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstring>
#include <pthread.h>
#include <unordered_map>

class ThreadManager {
public:
    ThreadManager() {}

    void printThreadAttributes(pthread_t thread_handle, bool bf = true) {
        sched_param sch;
        int policy;
        pthread_getschedparam(thread_handle, &policy, &sch);
        std::string BorA = bf == true ? "Before:\n" : "After:\n"; 
        std::lock_guard<std::mutex> lk(iomutex);

        std::cout << BorA;
        std::cout << "Thread priority: " << sch.sched_priority <<std::endl;

        if (auto it = policyMap.find(policy); it != policyMap.end()) {
            std::cout << "Scheduling policy: " << it->second << std::endl;
        } else {
            std::cout <<"Unknown Scheduling policy." << std::endl;
        }
    }

    void setThreadAttributes(std::thread& trd, const int priority, const int policy) {
        sched_param sch;
        sch.sched_priority = priority;
        auto result = pthread_setschedparam(trd.native_handle(), policy, &sch);
        if (result != 0) {
            print_result(result);
        }
    }

private:
    std::mutex iomutex;
    std::unordered_map<int, std::string> policyMap = {
        {SCHED_OTHER, "SCHED_OTHER"},
        {SCHED_FIFO, "SCHED_FIFO"},
        {SCHED_RR, "SCHED_RR"}
    };

    void print_result(const int result){
       if(result){
           std::cout<<"\nError :Fail to set thread attribute. please use root privilage.";
       }
    }
};

// A Class for thread.
class Task {
public:
    static void task() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }
    }
};

int main() {
    ThreadManager manager;

    std::thread sensorThread(Task::task);
    std::thread loggingThread(Task::task);

    manager.printThreadAttributes(sensorThread.native_handle());

    manager.setThreadAttributes(sensorThread, 20, SCHED_FIFO);

    manager.printThreadAttributes(sensorThread.native_handle(), false);

    sensorThread.join();
    loggingThread.join();

    return EXIT_SUCCESS;
}

