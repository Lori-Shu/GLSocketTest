#pragma once
#include<cstdint>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<thread>
#include<functional>
#include<queue>
namespace mystd{
template<typename T>
class GGLThreadPool  final{
  using TaskFunc = std::function<void ()>;

 public:
  GGLThreadPool(T size);
  ~GGLThreadPool();
  void submit(std::function<void(T &)> func,T & t);

 private:
  void mainTask();
  void createThreads(int32_t size);
  std::vector<std::thread> threads;
  const int32_t GGLTaskSize = 20;
  std::queue<TaskFunc> taskQueue;
  std::mutex mtx;
  std::condition_variable produConVa;
  std::condition_variable consuConVa;
  bool shutDownFlag = false;
};
template <typename T>
GGLThreadPool<T>::GGLThreadPool(T size) {
  createThreads(size);
}
template <typename T>
GGLThreadPool<T>::~GGLThreadPool() {
  shutDownFlag = true;
  consuConVa.notify_all();
  for (auto &td : threads) {
    td.join();
  }
}
template <typename T>
void GGLThreadPool<T>::submit(std::function<void(T &)> func, T &t) {
  std::unique_lock<std::mutex> queueLock(mtx,std::defer_lock);
  queueLock.lock();
  for (; taskQueue.size() == GGLTaskSize;) {
    consuConVa.notify_one();
    produConVa.wait(queueLock);
  }
  TaskFunc fc = std::bind(func, t);
  taskQueue.push(fc);
  queueLock.unlock();
  produConVa.notify_one();
}

template <typename T>
void GGLThreadPool<T>::mainTask() {
    // 
    // “巨坑”c++unique_lock在多个线程共用时会抛出异常，其本身线程不安全,需要每个线程单独一份
    // 
  std::unique_lock<std::mutex> queueLock(mtx,std::defer_lock);
  TaskFunc t;
  for (;;) {
    queueLock.lock();
    if (taskQueue.size() > 0) {
      t = taskQueue.front();
      taskQueue.pop();
    //   std::cout << "queueSize:" << taskQueue.size() <<std:: endl;
      queueLock.unlock();
      produConVa.notify_one();
      consuConVa.notify_one();
      t();
      } else {
      produConVa.notify_one();
      consuConVa.wait(queueLock);
      queueLock.unlock();
      if (shutDownFlag) {
        break;
        }
      }
    }
}
template <typename T>
void GGLThreadPool<T>::createThreads(int32_t size) {
    for (int32_t index = 0; index < size;) {
      threads.emplace_back(&GGLThreadPool<T>::mainTask, this);
      ++index;
    }
}
}