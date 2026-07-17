#include <mutex>
#include <queue>
#include <string>

namespace smartPointers
{
// student code begin
class ProducerConsumer
{
public:
    ProducerConsumer(int numProducedItems,
                     std::chrono::milliseconds productionDelay,
                     std::chrono::milliseconds consumerADelay,
                     std::chrono::milliseconds consumerBDelay);

    void start();

private:
    int numProducedItems_;
    std::chrono::milliseconds productionDelay_;
    std::chrono::milliseconds consumerADelay_;
    std::chrono::milliseconds consumerBDelay_;

    std::queue<int> queue_;
    std::mutex queueMutex_;
    std::mutex coutMutex_;

    bool productionFinished_;

    void producer();
    void consumer(const std::string &type, std::chrono::milliseconds delay);
};
// student code end

}  // namespace smartPointers
