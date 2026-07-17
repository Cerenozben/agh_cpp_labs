#include "SmartPointers/ProducerConsumer.h"

#include <iostream>
#include <thread>

namespace smartPointers
{
// student code begin
ProducerConsumer::ProducerConsumer(int numProducedItems, std::chrono::milliseconds productionDelay, std::chrono::milliseconds consumerADelay, std::chrono::milliseconds consumerBDelay) :
        numProducedItems_(numProducedItems),
        productionDelay_(productionDelay),
        consumerADelay_(consumerADelay),
        consumerBDelay_(consumerBDelay),
        queue_(),
        queueMutex_(),
        coutMutex_(),
        productionFinished_(false)
{}
void ProducerConsumer::start()
{
    std::thread prodThread(&ProducerConsumer::producer, this);
    std::thread consAThread(&ProducerConsumer::consumer, this, "A", (consumerADelay_));
    std::thread consBThread(&ProducerConsumer::consumer, this, "B", (consumerBDelay_));

    prodThread.join();
    consAThread.join();
    consBThread.join();
}

void ProducerConsumer::producer()
{
    for (int i = 0; i < numProducedItems_; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(productionDelay_));
        {
            std::lock_guard<std::mutex> lock(coutMutex_);
            std::cout << "Produced " << i << "\n";
        }
        {
            std::lock_guard<std::mutex> lock(queueMutex_);
            queue_.push(i);
        }
    }
    {
        std::lock_guard<std::mutex> lock(queueMutex_);
        productionFinished_ = true;
    }
}

void ProducerConsumer::consumer(const std::string &type, std::chrono::milliseconds delay)
{
    while (true)
    {
        int item = -1;
        bool itemFetched = false;
        {
            std::lock_guard<std::mutex> lock(queueMutex_);
            if (!queue_.empty())
            {
                item = queue_.front();
                queue_.pop();
                itemFetched = true;
            }
            else
            {
                if (productionFinished_)
                {
                    break;
                }
            }
        }
        if (itemFetched)
        {
            std::this_thread::sleep_for(delay);
            {
                std::lock_guard<std::mutex> lock(coutMutex_);
                std::cout << "Consumer " << type << " consumed " << item << "\n";
            }
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}
// student code end

}  // namespace smartPointers
