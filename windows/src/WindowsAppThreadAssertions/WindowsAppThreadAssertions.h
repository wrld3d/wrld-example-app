// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace WindowsAppThreadAssertions
    {
        void NominateCurrentlyRunningThreadAsUiThread();

        void AssertCurrentlyRunningOnNominatedUiThread(const char* file, int line);

        void RemoveNominationForUiThread();

        void NominateCurrentlyRunningThreadAsNativeThread();

        void AssertCurrentlyRunningOnNominatedNativeThread(const char* file, int line);

        void RemoveNominationForNativeThread();
    }
}
