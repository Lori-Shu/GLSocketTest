#include "GGLThreadPool.h"

namespace mystd{
using namespace std;

GGLThreadPool::GGLThreadPool(int32_t size) { createThreads(size); }

GGLThreadPool::~GGLThreadPool() {
  shutDownFlag = true;
  consuConVa.notify_all();
  for (auto &td : threads) {
    td.join();
  }
}


void GGLThreadPool::mainTask() {
  //
  // “巨坑”c++unique_lock在多个线程共用时会抛出异常，其本身线程不安全,需要每个线程单独一份
  //
  std::unique_lock<std::mutex> queueLock(mtx, std::defer_lock);
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

void GGLThreadPool::createThreads(int32_t size) {
  for (int32_t index = 0; index < size;) {
    threads.emplace_back(&GGLThreadPool::mainTask, this);
    ++index;
  }
}


}