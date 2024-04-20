#include <iostream>
#include <cstdarg>
#include "inc/CThread.hpp"
#include "inc/CThreadControl.hpp"
#include <thread>
#include <chrono>
#include <mutex>

class MyThread : public CThread {
public:
    MyThread(ThreadControl &c) : CThread(_thread_wrapper, this, &MyThread::interrupt_handler, 40),c(c) {}

protected:
    // Class member interrupt handler
    static void interrupt_handler(int interrupt) {
        // Handle interrupt for MyThread
        ThreadControl &c = ThreadControl::GetInstance();
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
 ThreadControl &c;
};




int main() {
    ThreadControl &c = ThreadControl::GetInstance();
    MyThread trd(c);
    pthread_join(trd.get_handle(), NULL);
    return EXIT_SUCCESS;
}

