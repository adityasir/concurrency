#include <iostream>
#include <cstdarg>
#include "inc/CThread.hpp"
#include <thread>
#include <chrono>

class MyThread : public CThread {
public:
    MyThread() : CThread(_thread_wrapper, this, &MyThread::interrupt_handler, 40) {}

protected:
    // Class member interrupt handler
    static void interrupt_handler(int interrupt) {
        // Handle interrupt for MyThread
        std::cout << "Interrupt received in MyThread!\n"; // Example handling
    }

    void run() override {
        while (true) {
            std::cout << std::endl << ".....Active Object .....\n";
            // Check for interrupt flags or use non-blocking I/O to respond to interrupts
            // ... (interrupt handling logic)
        }
    }
};

int main() {
    MyThread thread;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Trigger an interrupt here to test (e.g., using pthread_kill)
    return EXIT_SUCCESS;
}

