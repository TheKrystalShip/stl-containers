#include "TKS/ConcurrentQueue.hpp"

#include <string>
#include <iostream>
#include <thread>
#include <mutex>

/**
* An example of 2 threads interacting with the queue at the same time.
* writingQueue will put messages into the queue
* readingThread will get messages from the queue
*
* Note: std::cout output will be ugly because there's no output locking
* to avoid overriding the queue locks.
*/
int main()
{
    TKS::Concurrency::ConcurrentQueue<std::string> queue;

    std::thread writeThread(
        [&queue]()
        {
            // Delay startup to showcase blocking functionality in
            // queue.front() and queue.pop() [line 45-46]
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "Writing thread ID " << std::this_thread::get_id() << std::endl;

            for (int i = 1; i <= 20; i++)
            {
                std::string x = std::to_string(i);
                std::cout << x << " " << std::flush;
                queue.push(x);
            }

            std::cout << std::endl;
        });

    std::thread readThread(
        [&queue]()
        {
            std::cout << "Reading thread ID " << std::this_thread::get_id() << std::endl;

            while (true)
            {
                std::cout << queue.front() << std::flush;
                queue.pop();
            }

            std::cout << std::endl;
        });

    // Don't exit the main thread, close it down with SIGTERM / CTRL+C
    while (true)
        std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}
