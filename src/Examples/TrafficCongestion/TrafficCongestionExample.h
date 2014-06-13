// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IExample.h"
#include "TrafficCongestion.h"
#include "ITrafficCongestionService.h"

namespace Examples
{
class TrafficCongestionExample : public IExample
{
private:
	Eegeo::TrafficCongestion::ITrafficCongestionService& m_trafficCongestionService;
	float m_timeAccumulator;
	Eegeo::Streaming::MortonKey m_key;
	int m_congestionValue;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

public:
	TrafficCongestionExample(
	    Eegeo::TrafficCongestion::ITrafficCongestionService& trafficCongestionService,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "TrafficCongestionExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start() {}
	void Update(float dt);
	void Draw() {}
	void Suspend();
};
}
