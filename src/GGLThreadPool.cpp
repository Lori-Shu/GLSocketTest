#include "GGLThreadPool.h"

namespace mystd {
using namespace std;

GGLThreadPool::GGLThread::GGLThread(
    void (*task)(GGLThreadPool::GGLThread*, GGLThreadPool*),
    GGLThreadPool* poolPtr) {
  threadPool = poolPtr;
  tdPtr = new thread(task, this, poolPtr);
}
GGLThreadPool::GGLThread ::~GGLThread() {
  cout << "析构GGLThread的线程 thread id:" << this_thread::get_id() << endl;
  cout << "被析构GGLThread的线程 thread id:" << tdPtr->get_id() << endl;
   shutDownFlag = true;
  threadPool->consuConVa.notify_all();
  tdPtr->join();
  delete tdPtr;
}

GGLThreadPool::GGLThreadPool() {
  createThreads(defaultMinSize);
  getHarderWareThreadConfig();
  createSizeManager();
}

GGLThreadPool::~GGLThreadPool() {
  cout << "threadpool deconstructor---" << endl;
  // sizeManager->shutDownFlag=true;
  // sizeManager->tdPtr->join();
  delete sizeManager;
   busyThreads.clear();
  for(int32_t index=0;index<threads.size();){
    delete threads[index];
    ++index;
  }
}
void GGLThreadPool::getHarderWareThreadConfig() {
#ifdef WindowsVersion
  SYSTEM_INFO info{};
  GetSystemInfo(&info);
  coreSize = info.dwNumberOfProcessors;
#endif
#ifdef LinuxVersion
  coreSize = sysconf(_SC_NPROCESSORS_ONLN);
#endif
  maxThreadSize = coreSize * 3 / 2;
  cout << "hardware coreSize :" << coreSize << endl;
  cout << "max poolSize :" << maxThreadSize << endl;
}

void managePoolSize(GGLThreadPool::GGLThread* tdPtr, GGLThreadPool* poolPtr) {
  cout << "管理线程 thread id:" << this_thread::get_id() << endl;
  int32_t busyThreadCount = 0, temp = 0, index = 0;
  unique_lock<mutex> threadsLock(poolPtr->threadsMtx,std::defer_lock);
  unique_lock<mutex> busyLock(poolPtr->busyThreadsMtx, std::defer_lock);
  for (;;) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    if (tdPtr->shutDownFlag) {
      cout << "管理线程退出" << endl;
      return;
    }
    busyLock.lock();
    busyThreadCount = poolPtr->busyThreads.size();
    if (busyThreadCount > poolPtr->threads.size() * 3 / 4) {
      cout << "开始扩容" << endl;
      temp = poolPtr->threads.size() * 3 / 2;
      temp = min<int32_t>(temp, poolPtr->maxThreadSize);
      threadsLock.lock();
      for (; poolPtr->threads.size() < temp;) {
        poolPtr->threads.push_back(
            new GGLThreadPool::GGLThread(mainTask, poolPtr));
      }
      threadsLock.unlock();
      cout << "自动扩容结果：size：" << poolPtr->threads.size() << endl;
      continue;
    }
    if (busyThreadCount < poolPtr->threads.size() / 2) {
      if (poolPtr->threads.size() > poolPtr->defaultMinSize) {
        cout << "开始缩容" << endl;
        threadsLock.lock();
        index = 0;
        for (; index < poolPtr->threads.size();) {
          if (poolPtr->busyThreads.end() ==
              poolPtr->busyThreads.find(poolPtr->threads[index])) {
            poolPtr->threads.erase(poolPtr->threads.begin() + index);
            if (poolPtr->threads.size() == poolPtr->defaultMinSize) {
              break;
            }
            continue;
          }
          ++index;
        }
        threadsLock.unlock();
        cout << "自动缩容结果：size：" << poolPtr->threads.size() << endl;
      }
    }
    busyLock.unlock();
  }
}
void GGLThreadPool::createSizeManager() {
  sizeManager = new GGLThread(managePoolSize, this);
}


void mainTask(GGLThreadPool::GGLThread* tdPtr, GGLThreadPool* poolPtr) {
  cout<<"工作线程："<<this_thread::get_id()<<endl;
  //
  // “巨坑”c++unique_lock在多个线程共用时会抛出异常，其本身线程不安全,需要每个线程单独一份
  //

  std::unique_lock<std::mutex> queueLock(poolPtr->queueMtx, std::defer_lock);
  std::unique_lock<std::mutex> busyLock(poolPtr->busyThreadsMtx,
                                        std::defer_lock);
  std::unique_lock<std::mutex> threadsLock(poolPtr->threadsMtx,
                                           std::defer_lock);
  
  
   for (;;) {
    busyLock.lock();
    poolPtr->busyThreads.insert(tdPtr);
    busyLock.unlock();
    queueLock.lock();
    if (poolPtr->taskQueue.size() > 0) {
      TaskFunc t = poolPtr->taskQueue.front();
      poolPtr->taskQueue.pop();
      //   std::cout << "queueSize:" << taskQueue.size() <<std:: endl;
      queueLock.unlock();
      poolPtr->produConVa.notify_one();
      poolPtr->consuConVa.notify_one();
      t();
    } else {
      poolPtr->produConVa.notify_one();
      busyLock.lock();
      poolPtr->busyThreads.erase(poolPtr->busyThreads.find(tdPtr));
      busyLock.unlock();
      poolPtr->consuConVa.wait(queueLock);
      queueLock.unlock();
      poolPtr->produConVa.notify_one();
      poolPtr->consuConVa.notify_one();
    }
    if (tdPtr->shutDownFlag) {
      cout<<"工作线程退出"<<endl;
      break;
    }
  }
}

void GGLThreadPool::createThreads(int32_t size) {
  unique_lock<mutex> threadsLock(threadsMtx);
  for (int32_t index = 0; index < size;) {
    // 巨坑不要使用右值智能指针，可能会导致立即析构,并且要注意不能循环引用
    threads.push_back(new GGLThread(mainTask, this));
    ++index;
  }
}

}  // namespace mystd