#include <iostream>
#include <ctime>
#include <thread>

using namespace std;

// 1. Створити два класи з будь-якими приватними даними типу doube/float та паблік-методами доступу до них (read/write).
class Hello
{
private:
    double num = 0;
    mutex _mutex;

public:
    double getNum()
    {
        return num;
    }
    void setNum(double num_)
    {
        try
        {
            lock_guard<mutex> lock(_mutex);
            num = num_;
        }
        catch (logic_error)
        {
            cout << "exception caught" << endl;
        }
    }
};

class Bye
{
private:
    double num;
    mutex _mutex;

public:
    double getNum()
    {
        return num;
    }
    void setNum(double num_)
    {
        try
        {
            lock_guard<mutex> lock(_mutex);
            num = num_;
        }
        catch (logic_error)
        {
            cout << "exception caught" << endl;
        }
    }
};

// 2. Створити по одному екземпляру (обʼєкту) кожного класу.
Hello obj1;
Bye obj2;

// 4. Перші N/2 потоків, K1 разів (де K1 - довільне згенероване число від 10000 до 20000) кожен генерують довільне число double/float та додають до існуючого числа в обʼєкті 1, а потім генерують довільне число double/float та додають до існуючого числа в обʼєкті 2.
void call_from_thread_1()
{
    int k1 = rand() % (20000 - 10000) + 10000;
    int add = 0;
    for (int i = 0; i < k1; i++)
    {
        add = rand() % 2;
        obj1.setNum(obj1.getNum() + add);
        add = rand() % 2;
        obj2.setNum(obj2.getNum() + add);
    }
}

// 5. Всі інші потоки, K2 разів (де K2 - довільне згенероване число від 10000 до 20000) кожен генерують довільне число double/float та додають до існуючого числа в обʼєкті 2, а потім генерують довільне число double/float та додають до існуючого числа в обʼєкті 1.
void call_from_thread_2()
{
    int k2 = rand() % (20000 - 10000) + 10000;
    int add = 0;
    for (int i = 0; i < k2; i++)
    {
        add = rand() % 2;
        obj2.setNum(obj2.getNum() + add);
        add = rand() % 2;
        obj1.setNum(obj1.getNum() + add);
    }
}

int main()
{
    clock_t start, end;
    start = clock();

    // 3. Створити N (згенероване довільне число від 10 до 20) потоків так, що перші N/2 та другі N/2 потоків мають різну логіку.
    srand((unsigned int)time(NULL));
    int num_threads = rand() % 11 + 10;
    thread t[num_threads];

    for (int i = 0; i < num_threads / 2; ++i)
    {
        t[i] = thread(call_from_thread_1);
    }
    for (int i = num_threads / 2; i < num_threads; ++i)
    {
        t[i] = thread(call_from_thread_2);
    }

    //  6. Головний потік чекає завершення всіх 20 потоків та повідомляє про закінчення та виводить час виконання програми. Не використовувати принцип “холостого ходу”.
    for (int i = 0; i < num_threads; ++i)
    {
        t[i].join();
    }
    end = clock();

    cout << num_threads << " threads finished execution in: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
    cout << "The num of obj1 = " << obj1.getNum() << endl;
    cout << "The num of obj2 = " << obj2.getNum() << endl;

    return 0;
}