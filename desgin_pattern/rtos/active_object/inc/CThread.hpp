#ifndef ACTIVE_OBJECT_INC_CTHREAD_H
#define ACTIVE_OBJECT_INC_CTHREAD_H

#include <pthread.h>
#include <sched.h>
#include <signal.h>

class CThread {
public:

CThread(void *(*thread_func)(void *), void *arg = nullptr, 
         void (*interrupt_handler)(int) =nullptr , int priority = 99)
    : priority(priority) {
    pthread_create(&thread, nullptr, thread_func, arg);

    // Enable interrupt using provided handler
    struct sigaction action;
    action.sa_handler = interrupt_handler;
    action.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, // Replace with the desired signal
                 &action, nullptr) != 0) {
        // Handle signal action error
    }

    set_priority(priority);
}

    ~CThread() {
        pthread_detach(thread);
    }

    // Static function wrapper to pass to pthread_create
    static void *_thread_wrapper(void *obj) {
        CThread *self = static_cast<CThread*>(obj);
        if (self != nullptr) {
            self->run();
        }
        return nullptr;
    }
    const pthread_t get_handle() const { return thread;}
protected:
    int priority;  // Store priority for potential adjustment

    void set_priority(int new_priority) {
        // Implemented as before, but now accessible to derived classes
        struct sched_param param;
        param.sched_priority = new_priority;
        if (pthread_setschedparam(thread, SCHED_FIFO, &param) != 0) {
            // Handle priority setting error
        }
    }

    /*Pure virtual function for thread's main logic */
    virtual void run() = 0;

private:
    pthread_t thread; // Thread handle
};

#endif //ACTIVE_OBJECT_INC_CTHREAD_H

