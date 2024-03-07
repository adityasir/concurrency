#include <queue>
#include <mutex>
#include <condition_variable>

class MessageQueue {
public:
    void push(const std::string& message) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            queue.push(message);
        }
        cv.notify_one();
    }

    std::string waitAndPop() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this] { return !queue.empty() || consumersShouldFinish; });

        if (consumersShouldFinish && queue.empty()) {
            return ""; // Signal to consumers that they should finish
        }

        std::string message = queue.front();
        queue.pop();
        return message;
    }

    void notifyConsumers() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            consumersShouldFinish = true;
        }
        cv.notify_all();
    }

private:
    std::queue<std::string> queue;
    mutable std::mutex mutex;
    std::condition_variable cv;
    bool consumersShouldFinish = false;
};

