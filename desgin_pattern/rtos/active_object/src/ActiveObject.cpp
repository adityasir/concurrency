#include <iostream>
#include <cstdarg>
#include "inc/CThread.hpp"
#include "inc/CThreadControl.hpp"
#include <thread>

class CActiveObject : public CThread {
public:
    CActiveObject(ThreadControl &c) : CThread(_thread_wrapper, this, &CActiveObject::interrupt_handler, 40),c(c) {}

protected:
    // Class member interrupt handler
    static void interrupt_handler(int interrupt) {
        // Handle interrupt for CActiveObject
        ThreadControl &c = ThreadControl::GetInstance();
        c.set_continue_loop(false);
        std::cout << "Interrupt received in CActiveObject!\n"; // Example handling
    }

    void run() override {
        while (c.continue_loop()) {
            std::cout << std::endl << ".....Active Object .....\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
private:
 ThreadControl &c;
};
