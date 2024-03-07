#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <atomic>

#include "lock_based.h"

std::atomic<long long> globalSum(0);

void producer(const std::string& filename, MessageQueue& messageQueue) {
    std::ifstream inFile(filename, std::ios::binary);

    if (!inFile.is_open()) {
        std::cerr << "Error opening input file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        messageQueue.push(line);
    }

    inFile.close();
}

void consumer(MessageQueue& messageQueue) {
    while (true) {
        std::string binaryNumber = messageQueue.waitAndPop();
        if (binaryNumber.empty()) {
            break; // Exit the loop when the queue is empty
        }

        // Convert binary to decimal and update global sum
        long long decimalValue = std::stoll(binaryNumber, nullptr, 2);
        globalSum += decimalValue;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <num_threads>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int numThreads = std::stoi(argv[2]);

    // Create lock-based message queue
    MessageQueue messageQueue;

    // Vector to hold thread objects
    std::vector<std::thread> threads;

    // Start producer thread to read binary numbers from file
    std::thread producerThread(producer, filename, std::ref(messageQueue));

    // Start consumer threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(consumer, std::ref(messageQueue));
    }

    // Wait for producer thread to finish
    producerThread.join();

    // Notify consumer threads that no more data will be pushed into the queue
    messageQueue.notifyConsumers();

    // Wait for consumer threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the final sum
    std::cout << "Final Sum: " << globalSum << std::endl;

    return 0;
}

