#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex global_lock;

void func(int a)
{
    global_lock.lock();
    cout << "Hello World: " << a << " " << this_thread::get_id() << endl;
    global_lock.unlock();
}

int main()
{
    thread tarr[10];
    for (int i =0; i < 10; i++)
        tarr[i] = thread(func, i);
    for (int i =0; i < 10; i++)
        tarr[i].join();

    return 0;
}
