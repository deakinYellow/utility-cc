#ifndef TPTHREAD_H
#define TPTHREAD_H

#include <iostream>

class TPThreadImpl;

/**
 * @brief 创建一个新线程
 * @note
 */
class TPThread
{
public:
    typedef void* (*Callback_t)(void*);
    TPThread();
    int create(Callback_t cb, void* arg);
    int destroy();
    ~TPThread();

private:
    TPThreadImpl* impl;

};

int TPThreadTest( void );


#endif // TPTHREAD_H


