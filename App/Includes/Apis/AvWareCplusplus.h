#ifndef _AVWARECPLUSPLUS_H_
#define _AVWARECPLUSPLUS_H_

#include <map>
#include <list>
#include <queue>


#include "AvWareType.h"

#include <assert.h>
#include <pthread.h>
#include <functional>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName&); \
void operator=(const TypeName&)

#define DISALLOW_COPY_AND_ASSIGN_11(TypeName)   \
TypeName(const TypeName&)=delete;             \
TypeName& operator=(const TypeName&)=delete

/*TODO:�ﲻ����ҵ�� ���Ľ�
1.������mutex������Ӧ����PTHREAD_MUTEX_NORMAL(linux��PTHREAD_MUTEX_NORMAL��PTHREAD_MUTEX_DEFAULTһ��û��ϵ)
2.û���쳣����
*/
class MutexLock{
public:
	MutexLock()
	{
		pthread_mutex_init(&mutex_, NULL);
	}
	~MutexLock()
	{
		pthread_mutex_destroy(&mutex_);
	}
	void lock()
	{
		pthread_mutex_lock(&mutex_);
	}
	void unlock()
	{
		pthread_mutex_unlock(&mutex_);
	}
	pthread_mutex_t* getPthreadMutex(void)
	{
		return &mutex_;
	}
private:
	pthread_mutex_t mutex_;
	DISALLOW_COPY_AND_ASSIGN(MutexLock);
};


class MutexLockGuard{
public:
	explicit MutexLockGuard(MutexLock &mutex)
		: mutex_(mutex)
	{
		mutex_.lock();
	}
	~MutexLockGuard()
	{
		mutex_.unlock();
	}
private:
	MutexLock &mutex_;
	DISALLOW_COPY_AND_ASSIGN(MutexLockGuard);
};
#define MutexLockGuard(x) static_assert(false, "miss gurad lock var name")


class PthreadCondition{
public:
	explicit PthreadCondition(MutexLock &mutex)
		:mutex_(mutex)
	{
		pthread_cond_init(&cond_, NULL);
	}

	~PthreadCondition()
	{
		pthread_cond_destroy(&cond_);
	}

	void wait()
	{
		pthread_cond_wait(&cond_, mutex_.getPthreadMutex());
	}
	void notify()
	{
		pthread_cond_signal(&cond_);
	}
	void notifyAll()
	{
		pthread_cond_broadcast(&cond_);
	}
private:
	MutexLock &mutex_;
	pthread_cond_t cond_;
	DISALLOW_COPY_AND_ASSIGN(PthreadCondition);
};


class ScopeGuard
{
public:
    explicit ScopeGuard(std::function<void()> onExitScope)
        : onExitScope_(onExitScope), dismissed_(false)
    { }

    ~ScopeGuard()
    {
        if(!dismissed_)
        {
            onExitScope_();
        }
    }

    void Dismiss()
    {
        dismissed_ = true;
    }

private:
    std::function<void()> onExitScope_;
    bool dismissed_;

private: // noncopyable
    ScopeGuard(ScopeGuard const&);
    ScopeGuard& operator=(ScopeGuard const&);
};
#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)

#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

#endif



