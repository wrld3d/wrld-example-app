// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinAddedToMenuMessage.h"

namespace ExampleApp
{
	namespace MyPins
	{
		MyPinAddedToMenuMessage::MyPinAddedToMenuMessage(MyPinModel* myPinModel)
		: m_pMyPinModel(myPinModel)
		{

		}

		MyPinModel* MyPinAddedToMenuMessage::GetMyPinModel() const
		{
			return m_pMyPinModel;
		}
	}
}
