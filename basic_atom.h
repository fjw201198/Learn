#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>

template<typename T>
class basic_atom : boost::noncopyable {
private:
    T n;
    typedef boost::mutex mutex_t;
    mutex_t mu;
public:
    basic_atom(T x = T()):n(x) {}
    T operator++() {
        mutex_t::scoped_lock lock(mu);
        return ++n;
    }
    operator T() { return n; }
};
