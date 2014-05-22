//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "FrameRateRegulator.h"
#include <time.h>

FrameRateRegulator::FrameRateRegulator(float targetFramesPerSecond)
: m_targetFrameDurationInSeconds(1.0 / targetFramesPerSecond)
, m_pendingFrameStartTimeInSeconds(0.0)
{
	m_frameDeltaTimes.push_back(0.0);
}

FrameRateRegulator::~FrameRateRegulator()
{
}

namespace
{
	double GetTimeNowInSeconds()
	{
		 struct timespec res;
		 clock_gettime(CLOCK_REALTIME, &res);
		 return res.tv_sec + (double) res.tv_nsec * 1e-9;
	}
}

bool FrameRateRegulator::TryStartFrame(float& out_deltaTimeInSeconds)
{
	double currentTimeInSeconds = GetTimeNowInSeconds();
	double pendingFrameDurationInSeconds = currentTimeInSeconds - m_pendingFrameStartTimeInSeconds;

	UpdatePendingFrameDuration(pendingFrameDurationInSeconds);

	double smoothedDeltaTimeInSeconds = CalcSmoothedDeltaTimeInSeconds();

	const double OverrunDurationInSeconds = 0.005;
	if
	(
		(smoothedDeltaTimeInSeconds < m_targetFrameDurationInSeconds)
		&& (pendingFrameDurationInSeconds < (m_targetFrameDurationInSeconds + OverrunDurationInSeconds))
	)
	{
		out_deltaTimeInSeconds = 0.0;
		return false;
	}
	else
	{
		StartPendingFrame(currentTimeInSeconds);
		out_deltaTimeInSeconds = smoothedDeltaTimeInSeconds;
		return true;
	}
}

float FrameRateRegulator::WaitForFrameStart()
{
	float deltaTime;
	volatile int preventCompilerFromOptimisingLoopAway;
	while(TryStartFrame(deltaTime) == false)
	{
		preventCompilerFromOptimisingLoopAway = 0;
	}

	return deltaTime;
}


void FrameRateRegulator::StartPendingFrame(const double frameStartTimeInSeconds)
{
	m_pendingFrameStartTimeInSeconds = frameStartTimeInSeconds;

	m_frameDeltaTimes.push_front(0.0);

	const int smoothedFrameDeltaEntries = 4;
	if (m_frameDeltaTimes.size() > smoothedFrameDeltaEntries)
	{
		m_frameDeltaTimes.pop_back();
	}
}

void FrameRateRegulator::UpdatePendingFrameDuration(const double deltaTimeInSeconds)
{
	TFrameDeltaTimes::iterator iterFront = m_frameDeltaTimes.begin();
	*iterFront = deltaTimeInSeconds;
}

double FrameRateRegulator::CalcSmoothedDeltaTimeInSeconds() const
{
	if(m_frameDeltaTimes.empty())
	{
		return 0.0;
	}

	double summedDeltas = 0.0;
	for(TFrameDeltaTimes::const_iterator it = m_frameDeltaTimes.begin(); it != m_frameDeltaTimes.end(); ++it)
	{
		summedDeltas += (*it);
	}

	return summedDeltas / m_frameDeltaTimes.size();
}





