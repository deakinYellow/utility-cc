#include <pthread.h>
#include "utility/tpthread.h"

////创建线程
class TPThreadImpl
{
public:
    TPThreadImpl() {}
    int  create( TPThread::Callback_t cb, void* arg ){
        int ret = pthread_create(&_thread, NULL, cb, arg);
        return ret;
    }
    int destroy() {
        pthread_join( _thread, NULL);
        return 0;
    }
private:
    pthread_t _thread;
};

///=====================TPThread About==============================

TPThread::TPThread()
{
  impl = new TPThreadImpl();
}

TPThread::~TPThread()
{
  delete impl;
  impl = NULL;
}

int TPThread::create(Callback_t cb, void* arg )
{
  return impl->create(cb, arg);
}

int TPThread::destroy()
{
  return impl->destroy();
}

int num_g = 0;
///=====================TPThread TEST==============================
///只要不含全局变量或局部静态变量，两线程可以共用函数,线程会独立开辟堆栈存储局部变量
void* testFun1( void* param ){
    int i = *(int *)param;   //引用参数
    //num_g = *(int *)param;   //引用参数
    while (true) {
        std::cout << "testThread: " << i << std::endl;
        //std::cout << "testThread: " << num_g << std::endl;

        long t = 1e10; while ( t-- != 0);
        //i++;
        //if( i > 1e6 ){
            //return NULL;
        //}
    }
}

void* testFun2( void* param ){
    int i = *(int *)param;   //引用参数
    while (true) {
        std::cout << "testThread: " << i << std::endl;
    }
}


int TPThreadTest( void ){

    std::cout << "UDPCom test1." << std::endl;
    TPThread  testThread;
    int a = 1;
    if( 0 != testThread.create( testFun1, &a ) ){
//        std::cout << "creat thread fial." << std::endl;
        return -1;
    }
    int b = 2;
    if( 0 != testThread.create( testFun1, &b ) ){
        std::cout << "creat thread fial." << std::endl;
        return -1;
    }
    while( true ){
        long t = 1e10; while ( t-- != 0);
        //printf("testThread runing\n");
        a++;
    }
    return 0;
}

