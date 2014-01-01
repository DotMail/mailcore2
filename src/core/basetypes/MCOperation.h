#ifndef __MAILCORE_MCOPERATION_H_

#define __MAILCORE_MCOPERATION_H_

#include <pthread.h>
#include <MailCore/MCObject.h>

#if __APPLE__
#include <dispatch/dispatch.h>
#endif

#ifdef __cplusplus

namespace mailcore {
#ifdef __APPLE__
    // This queue is internal to mailcore and is guaranteed to be a concurrent
    // queue that all callbacks will be delivered on.
    extern const dispatch_queue_t operation_callback_queue;
#endif
    class OperationCallback;
    
    class Operation : public Object {
    public:
        Operation();
        virtual ~Operation();
        
        virtual void setCallback(OperationCallback * callback);
        virtual OperationCallback * callback();
        
        virtual void cancel();
        virtual bool isCancelled();
        
        // Will be called on main thread.
        virtual void beforeMain();
        
        virtual void main();
        
        // Will be called on main thread.
        virtual void afterMain();
        
        virtual void start();
        
    private:
        OperationCallback * mCallback;
        bool mCancelled;
        pthread_mutex_t mLock;
        
    };
    
}

#endif

#endif
