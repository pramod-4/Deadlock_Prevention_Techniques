#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>

class ResourceManager {
private:
    std::vector<int> resources;
    std::mutex mtx;
    std::condition_variable cv;

    bool canAllocate(const std::vector<int>& request) {
        for (size_t i = 0; i < request.size(); ++i) {
            if (request[i] > resources[i]) {
                return false;
            }
        }
        return true;
    }

public:
    ResourceManager(const std::vector<int>& totalResources) : resources(totalResources) {}

    void requestResources(std::vector<int> request, int processId) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return canAllocate(request); });

        std::cout << "Process " << processId << " is granted resources: ";
        for (size_t i = 0; i < request.size(); ++i) {
            resources[i] -= request[i];
            std::cout << request[i] << " ";
        }
        std::cout << std::endl;
    }

    void releaseResources(const std::vector<int>& release, int processId) {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Process " << processId << " is releasing resources: ";
        for (size_t i = 0; i < release.size(); ++i) {
            resources[i] += release[i];
            std::cout << release[i] << " ";
        }
        std::cout << std::endl;
        cv.notify_all();
    }
};

void process(ResourceManager& manager, std::vector<int> request, int id) {
    std::cout << "Process " << id << " requesting resources...\n";
    manager.requestResources(request, id);
    std::cout << "Process " << id << " acquired resources.\n";

    // Simulate process doing some work with the resources
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Process " << id << " releasing resources...\n";
    manager.releaseResources(request, id);
    std::cout << "Process " << id << " released resources.\n";
}

int main() {
    int numResources, numProcesses;
    
    std::cout << "Enter the number of different resources: ";
    std::cin >> numResources;

    std::vector<int> totalResources(numResources);
    std::cout << "Enter the total amount of each resource (space-separated): ";
    for (int i = 0; i < numResources; ++i) {
        std::cin >> totalResources[i];
    }

    ResourceManager manager(totalResources);

    std::cout << "Enter the number of processes: ";
    std::cin >> numProcesses;

    std::vector<std::vector<int>> requests(numProcesses, std::vector<int>(numResources));
    for (int i = 0; i < numProcesses; ++i) {
        std::cout << "Enter the resource request for process " << i + 1 << " (space-separated): ";
        for (int j = 0; j < numResources; ++j) {
            std::cin >> requests[i][j];
        }
    }

    // Ensure each process requests resources in increasing order
    for (auto& request : requests) {
        std::sort(request.begin(), request.end());
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < numProcesses; ++i) {
        threads.push_back(std::thread(process, std::ref(manager), requests[i], i + 1));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
