#include <iostream>
#include <boost/thread.hpp>

int main(int argc, char** argv) {
    boost::mutex mu;
    boost::mutex::scoped_lock lock(mu);
    std::cout << "some operations" << std::endl;
    return 0;
}
