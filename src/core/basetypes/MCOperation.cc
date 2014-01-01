#include "MCOperation.h"

using namespace mailcore;

#if __APPLE__
dispatch_queue_t operation_callback_queue = dispatch_queue_create("com.mailcore2.callbackqueue", DISPATCH_QUEUE_CONCURRENT);
#endif

Operation::Operation()
{
    mCallback = NULL;
    mCancelled = false;
    pthread_mutex_init(&mLock, NULL);
}

Operation::~Operation()
{
    pthread_mutex_destroy(&mLock);
}

void Operation::setCallback(OperationCallback * callback)
{
    mCallback = callback;
}

OperationCallback * Operation::callback()
{
    return mCallback;
}

void Operation::cancel()
{
    pthread_mutex_lock(&mLock);
    mCancelled = true;
    pthread_mutex_unlock(&mLock);
}

bool Operation::isCancelled()
{
    pthread_mutex_lock(&mLock);
    bool value = mCancelled;
    pthread_mutex_unlock(&mLock);
    
    return value;
}

void Operation::beforeMain()
{
}

void Operation::main()
{
}

void Operation::afterMain()
{
}

void Operation::start()
{
}
