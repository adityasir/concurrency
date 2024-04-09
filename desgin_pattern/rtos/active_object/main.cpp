#include <iostream>
#include <cstdarg>
#include "inc/CThread.hpp"
#include <thread>
#include <chrono>
#include <mutex>

class Control {
public:
    static Control& GetInstance() {
        // Double-checked locking for thread safety
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        static Control instance;  // Initialize only once within the lock
        return instance;
    }

    bool continue_loop() {return run_ok;}
    void set_continue_loop(const bool b) { run_ok = b;}


private:
    int run_ok;
    Control() : run_ok(true) {} // Initialize run_ok in constructor
    // Disallow copying and moving
    Control(const Control&) = delete;
    Control& operator=(const Control&) = delete;
};


class MyThread : public CThread {
public:
    MyThread(Control &c) : CThread(_thread_wrapper, this, &MyThread::interrupt_handler, 40),c(c) {}

protected:
    // Class member interrupt handler
    static void interrupt_handler(int interrupt) {
        // Handle interrupt for MyThread
        Control &c = Control::GetInstance();
        c.set_continue_loop(false);
        std::cout << "Interrupt received in MyThread!\n"; // Example handling
    }

    void run() override {
        while (c.continue_loop()) {
            std::cout << std::endl << ".....Active Object .....\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // Check for interrupt flags or use non-blocking I/O to respond to interrupts
            // ... (interrupt handling logic)
        }
    }
private:
 Control &c;
};

int main() {
    Control &c = Control::GetInstance();
    MyThread trd(c);
    pthread_join(trd.get_handle(), NULL);
    return EXIT_SUCCESS;
}

