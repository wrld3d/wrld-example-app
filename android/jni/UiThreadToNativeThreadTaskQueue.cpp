/*
 * UiThreadToNativeThreadTaskQueue.cpp
 *
 *  Created on: Dec 11, 2013
 *      Author: kimbleoperations
 */

#include "UiThreadToNativeThreadTaskQueue.h"

UiThreadToNativeThreadTaskQueue::UiThreadToNativeThreadTaskQueue()
{
	pthread_mutex_init(&m_mutex, 0);
}

UiThreadToNativeThreadTaskQueue::~UiThreadToNativeThreadTaskQueue()
{
	pthread_mutex_destroy(&m_mutex);

	for(std::vector<IBufferedWork*>::iterator i = m_workBuffer.begin(); i != m_workBuffer.end(); ++ i)
	{
		IBufferedWork& workItem = **i;
		workItem.DoWork();
	}

	m_workBuffer.clear();
}

void UiThreadToNativeThreadTaskQueue::PostWork(IBufferedWork* work)
{
	pthread_mutex_lock(&m_mutex);
	m_workBuffer.push_back(work);
	pthread_mutex_unlock(&m_mutex);
}

bool UiThreadToNativeThreadTaskQueue::TryExectuteBufferedWork()
{
	std::vector<IBufferedWork*> work;
	bool executedWork = false;

	if(pthread_mutex_trylock(&m_mutex) == 0)
	{
		m_workBuffer.swap(work);
		executedWork = true;
		pthread_mutex_unlock(&m_mutex);
	}

	for(std::vector<IBufferedWork*>::iterator i = work.begin(); i != work.end(); ++ i)
	{
		IBufferedWork& workItem = **i;
		workItem.DoWork();
	}

	return executedWork;
}
