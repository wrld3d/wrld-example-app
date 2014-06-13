// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef FRAMERATEREGULATOR_H_
#define FRAMERATEREGULATOR_H_

#include "Types.h"
#include <deque>

class FrameRateRegulator : protected Eegeo::NonCopyable
{
public:
	FrameRateRegulator(float targetFramesPerSecond);
	~FrameRateRegulator();

	bool TryStartFrame(float& out_deltaTimeInSeconds);
	float WaitForFrameStart();

private:
	double m_targetFrameDurationInSeconds;

	double m_pendingFrameStartTimeInSeconds;
	typedef std::deque<double> TFrameDeltaTimes;
	TFrameDeltaTimes m_frameDeltaTimes;

	void StartPendingFrame(const double frameStartTimeInSeconds);
	void UpdatePendingFrameDuration(const double pendingFrameDurationInSeconds);
	double CalcSmoothedDeltaTimeInSeconds() const;
};

#endif
