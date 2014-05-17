#include <iostream>
#include <boost/thread.hpp>
#include <stack>
#include <boost/date_time.hpp>

boost::mutex io_mu;

class Buffer {
private:
    boost::mutex mu;
    boost::condition_variable_any cond_put;
    boost::condition_variable_any cond_get;
    std::stack<int> stk;
    int un_read;
    int capacity;
    bool is_full() {
        return un_read == capacity;
    }
    bool is_empty() {
        return un_read == 0;
    }
public:
    Buffer(size_t n):un_read(0), capacity(n) {}
    void put(int x) {
        {
            boost::mutex::scoped_lock lock(mu);
            while (is_full()) {
                {
                    boost::mutex::scoped_lock lock(io_mu);
                    std::cout << "full waiting... " << std::endl;
                }
                cond_put.wait(mu);
            }
            stk.push(x);
            ++un_read;
        }
        cond_get.notify_one();
    }
    void get(int *x) {
        {
            boost::mutex::scoped_lock lock(mu);
            while (is_empty()) {
                {
                    boost::mutex::scoped_lock lock(io_mu);
                    std::cout << "empty waitting... " << std::endl;
                }
                cond_get.wait(mu);
            }
            --un_read;
            *x = stk.top();
            stk.pop();
        }
        cond_put.notify_one();
    }
};

Buffer buf(5);
void producer(int n) {
    for (int i = 0; i != n; ++i) {
        {
            boost::mutex::scoped_lock lock(io_mu);
            std::cout << "put " << i << std::endl;
        }
        buf.put(i);
    }
}

void consumer(int n) {
    int x;
    for (int i = 0; i != n; ++i) {
        buf.get(&x);
        boost::mutex::scoped_lock lock(io_mu);
        std::cout << "get " << x << std::endl;
    }
}

int main(int argc, char** argv) {
    boost::thread t1(producer, 20);
    boost::thread t2(consumer, 10);
    boost::thread t3(consumer, 10);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
