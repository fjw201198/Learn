#include <iostream>
#include <boost/timer.hpp>

int main() {
    boost::timer t;
    std::cout << "Max Timespan: " << t.elapsed_max()/3600 << "h" << std::endl;
    std::cout << "Min Timespan: " << t.elapsed_min() << "s" << std::endl;
    std::cout << "now time elapsed: " << t.elapsed() << "s" << std::endl;
    return 0;
}
