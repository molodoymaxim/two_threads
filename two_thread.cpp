#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;
int sharedData = 0;

void writerThread() {
    for (int i = 1; i <= 5; ++i) {
        mtx.lock();

        sharedData = i;
        std::cout << "Writer thread writes: " << sharedData << std::endl;\

        mtx.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void readerThread() {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();

        std::cout << "Reader thread reads: " << sharedData << std::endl;

        mtx.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::thread writer(writerThread);
    std::thread reader(readerThread);

    writer.join();
    reader.join();

    return 0;
}
