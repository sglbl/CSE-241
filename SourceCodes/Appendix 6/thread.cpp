#include <iostream>
#include <thread>

using namespace std;

void func(int a)
{
    cout << "Hello World: " << a << " " << this_thread::get_id() << endl;
}

int main()
{
    thread t1(func, 10);
    thread t2(func, 20);
    t1.join();
    t2.join();

    return 0;
}
