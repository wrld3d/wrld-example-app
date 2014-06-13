// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef SELECTEXAMPLEMESSAGE_H_
#define SELECTEXAMPLEMESSAGE_H_

#include "AndroidExampleControllerView.h"
#include "IAndroidExampleMessage.h"
#include <string>

namespace Examples
{
class SelectExampleMessage : public AndroidExampleMessage<AndroidExampleControllerView>
{
	std::string m_exampleName;

public:
	SelectExampleMessage(Examples::AndroidExampleControllerView* pExample, const std::string& exampleName);

	virtual bool Handle(AndroidExampleControllerView& dispatcher) const;
};
}

#endif /* SELECTEXAMPLEMESSAGE_H_ */
