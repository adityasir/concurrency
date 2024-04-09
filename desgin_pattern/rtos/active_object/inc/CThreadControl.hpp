#ifndef ACTIVE_OBJECT_INC_CTHREAD_CONTROLH
#define ACTIVE_OBJECT_INC_CTHREAD_CONTROLH
#include <iostream>
#include <mutex>

class ThreadControl {
public:
    static ThreadControl& GetInstance() {
        // Double-checked locking for thread safety
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        static ThreadControl instance;  // Initialize only once within the lock
        return instance;
    }

    bool continue_loop() {return run_ok;}
    void set_continue_loop(const bool b) { run_ok = b;}


private:
    int run_ok;
    ThreadControl() : run_ok(true) {} // Initialize run_ok in constructor
    // Disallow copying and moving
    ThreadControl(const ThreadControl&) = delete;
    ThreadControl& operator=(const ThreadControl&) = delete;
};

#endif
