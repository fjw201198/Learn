#include <iostream>
#include <string>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include <boost/ref.hpp>
#include "basic_atom.h"

using std::cout;
using std::endl;
using boost::mutex;
// using atom_int = basic_atom<int>;
typedef basic_atom<int> atom_int;

mutex io_mu;

void Print(atom_int &x, const std::string &str) {
    for (int i = 0; i != 5; ++ i) {
        mutex::scoped_lock lock(io_mu);
        cout << str << ++x << endl;
    }
}

int main() {
    atom_int x;
    boost::thread(Print, boost::ref(x), "hello");
    boost::thread(Print, boost::ref(x), "boost");
    boost::this_thread::sleep(boost::posix_time::seconds(2));
    return 0;
}
