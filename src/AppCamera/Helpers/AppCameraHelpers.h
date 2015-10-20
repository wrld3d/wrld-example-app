// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace Helpers
        {
            void GetMatrixFromQuaternion(Eegeo::Quaternion& quaternion, Eegeo::m33& out_orientation);
        }
    }
}