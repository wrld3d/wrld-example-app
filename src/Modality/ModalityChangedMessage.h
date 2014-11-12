// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
namespace Modality
{
class ModalityChangedMessage
{
	float m_modality;

public:
	ModalityChangedMessage(float modality)
		: m_modality(modality)
	{

	}

	float Modality() const
	{
		return m_modality;
	}
};
}
}
