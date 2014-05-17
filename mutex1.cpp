#include <boost/thread.hpp>
#include <iostream>

int main() {
    boost::mutex mu;
    try {
        mu.lock();
        std::cout << "Some operations" << std::endl;
        mu.unlock();
    } catch(...) {
        mu.unlock();
    }
    return 0;
}
