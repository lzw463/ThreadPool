#include <vector>
#include <iostream>
#include <functional>
#include <thread>

using namespace std;


//线程类
class Thread
{
public:
    Thread(function<void()> func) :func_(func) {}
    thread start()
    {
        thread t(func_);
        return t;
    }
private:
    function<void()> func_;

};

//线程池类
class ThreadPool
{
public:
    ThreadPool() {}
    ~ThreadPool() {
        //释放Thread对象占用的堆资源
        for (int i = 0; i < pool_.size(); ++i)
        {
            delete pool_[i];
        }
    }

    //开启线程池
    void startPool(int size)
    {
        for (int i = 0; i < size; ++i)
        {
            pool_.push_back(new Thread(bind(&ThreadPool::runInThread, this, i)));
        }
        for (int i = 0; i < size; ++i)
        {
            handler_.push_back(pool_[i]->start());
        }
        for (thread &t : handler_)
        {
            t.join();
        }
    }
private:
    vector<Thread*> pool_;
    vector<thread> handler_;

    //runInThread这个成员方法充当线程函数
    void runInThread(int id)
    {
        cout << "call runInThread id:" << id << endl;
    }


};


int main()
{
    ThreadPool pool;
    pool.startPool(10);
    return 0;
}