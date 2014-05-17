#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>
#include <boost/ref.hpp>
#include "basic_atom.h"

typedef basic_atom<int> atom_int;
boost::mutex io_mu;

void to_interrupt(atom_int& x, const std::string& str) {
    try {
        for (int i = 0; i != 5; ++ i) {
            boost::mutex::scoped_lock lock(io_mu);
            std::cout << str << ++ x << std::endl;
            boost::this_thread::interruption_point();
        }
    } catch(boost::thread_interrupted &) {
        std::cout << "thread_interrupted" << std::endl;
    }
}

int main(int argc, char** argv) {
    atom_int x;
    boost::thread t(to_interrupt, boost::ref(x), "hello");
    t.interrupt();
    t.join();
    return 0;
}
