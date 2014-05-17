#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <iostream>

int main() {
    boost::this_thread::sleep(boost::posix_time::seconds(2));
    std::cout << "sleep 2 seconds" << std::endl;
}
