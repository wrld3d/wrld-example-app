// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__UIActionHandler__
#define __ExampleApp__UIActionHandler__

#include "IUIActionHandler.h"
#include "Types.h"

namespace Examples
{
template <class T> class UIActionHandler : public IUIActionHandler, private Eegeo::NonCopyable
{
private:
	void (T::*m_callback)();
	T* m_pContext;
public:
	UIActionHandler(T* context, void (T::*callback)())
		: m_pContext(context)
		, m_callback(callback)
	{
	}

	virtual void operator()()
	{
		(*m_pContext.*m_callback)();
	}
};
}


#endif /* defined(__ExampleApp__UIActionHandler__) */
