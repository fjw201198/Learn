#include <iostream>
#include <string>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "basic_atom.h"

typedef basic_atom<int> atom_int;
boost::mutex io_mu;

void to_interrupt(atom_int& x, const std::string& str) {
    try {
        assert(boost::this_thread::interruption_enabled());
        for (int i = 0; i != 5; ++ i) {
            boost::this_thread::disable_interruption di;
            assert(!boost::this_thread::interruption_enabled());
            boost::mutex::scoped_lock lock(io_mu);
            std::cout << str << ++ x << std::endl;
            std::cout << boost::this_thread::interruption_requested()
                << std::endl;
            boost::this_thread::interruption_point();
            boost::this_thread::restore_interruption ri(di);
            assert(boost::this_thread::interruption_enabled());
            std::cout << "can interrupted" << std::endl;
            std::cout << boost::this_thread::interruption_requested()
                << std::endl;
            boost::this_thread::interruption_point(); 
        }
        assert(boost::this_thread::interruption_enabled());
    } catch(boost::thread_interrupted&) {
        std::cout << "thread_interrupted" << std::endl; 
    }
}

int main() {
    atom_int x;
    boost::thread t(to_interrupt, boost::ref(x), "Hello");
    t.interrupt();
    t.join();
    return 0;
}
