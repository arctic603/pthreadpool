#ifndef _TASKQUEUE_H_
#define _TASKQUEUE_H_


#include <iostream>
#include <queue>
#include <pthread.h>
// 任务结构体
// 定义任务结构体

using callback = void(*)(void*);


template<typename T>
struct Task
{
    Task()
    {
        function = nullptr;
        arg = nullptr;
    }
    Task(callback f, T* arg)
    {
        function = f;
        this->arg = arg;
    }
    callback function;
    T* arg;
};

// 任务队列
template<typename T>
class TaskQueue
{
public:
    TaskQueue();
    ~TaskQueue();

    // 添加任务
    void addTask(Task<T>& task);
    void addTask(callback func, void* arg);

    // 取出一个任务
    Task<T> takeTask();

    // 获取当前队列中任务个数
    inline size_t taskNumber()
    {
        return m_queue.size();
    }

private:
    pthread_mutex_t m_mutex;    // 互斥锁
    std::queue<Task<T>> m_queue;   // 任务队列
};


#endif
