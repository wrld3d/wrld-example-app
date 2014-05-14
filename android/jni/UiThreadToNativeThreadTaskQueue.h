/*
 * UiThreadToNativeThreadTaskQueue.h
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#ifndef UITHREADTONATIVETHREADTASKQUEUE_H_
#define UITHREADTONATIVETHREADTASKQUEUE_H_

#include "Types.h"
#include <pthread.h>
#include <vector>

class UiThreadToNativeThreadTaskQueue : public Eegeo::NonCopyable
{
public:
	class IBufferedWork
	{
	public:
		virtual ~IBufferedWork() {}
		virtual void DoWork() = 0;
	};

private:
	pthread_mutex_t m_mutex;
	std::vector<IBufferedWork*> m_workBuffer;

public:
	UiThreadToNativeThreadTaskQueue();

	~UiThreadToNativeThreadTaskQueue();

    void PostWork(IBufferedWork* work);

    bool TryExectuteBufferedWork();
};

#endif /* UITHREADTONATIVETHREADTASKQUEUE_H_ */
