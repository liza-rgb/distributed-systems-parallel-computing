#include <iostream>
#include <thread>

using namespace std;

void helloWorld1()
{
    cout << "Hello World from Thread Do1" << endl;
}

void helloWorld3()
{
    cout << "Hello World from Thread Do3" << endl;
}

void eatEggs(int num)
{
    for (int i = 2; i <= num; i++)
    {
        cout << "I ate " << i << " eggs" << endl;
    }
}

int main()
{
    thread Do1(helloWorld1);
    thread Do2(eatEggs, 4);
    thread Do3(helloWorld3);

    // syncronization of threads
    Do1.join();
    Do2.join();
    Do3.join();

    cout << "Execution of Do1, Do2 and Do3 is completed" << endl;

    return 0;
}