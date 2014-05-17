#include <iostream>
#include <string>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/ref.hpp>
#include "basic_atom.h"

typedef basic_atom<int> atom_int;
boost::mutex io_mu;

void to_interrupt(atom_int &x, const std::string& str) {
    try {
        for (int i = 0; i != 5; ++i) {
            boost::this_thread::sleep(boost::posix_time::seconds(1));
            boost::mutex::scoped_lock(io_mu);
            std::cout << str << ++ x << std::endl;
        }
    } catch(boost::thread_interrupted &) {
        std::cout << "thread_interrupted" << std::endl;
    }
}

int main() {
    atom_int x;
    boost::thread t(to_interrupt,boost::ref(x),"hello");
    boost::this_thread::sleep(boost::posix_time::seconds(2));
    t.interrupt();
    t.join();
    return 0;
}
