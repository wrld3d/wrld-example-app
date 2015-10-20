// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppCameraHelpers.h"
#include "VectorMath.h"
#include "Quaternion.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace Helpers
        {
            void GetMatrixFromQuaternion(Eegeo::Quaternion& quaternion, Eegeo::m33& out_orientation)
            {
                const float x = quaternion.x;
                const float y = quaternion.y;
                const float z = quaternion.z;
                const float w = quaternion.w;
                out_orientation.SetRow(0, Eegeo::v3(1 - 2 * (y*y + z*z), 2 * (x*y - z*w), 2 * (x*z + y*w)));
                out_orientation.SetRow(1, Eegeo::v3(2 * (x*y + z*w), 1 - 2 * (x*x + z*z), 2 * (y*z - x*w)));
                out_orientation.SetRow(2, Eegeo::v3(2 * (x*z - y*w), 2 * (y*z + x*w), 1 - 2 * (x*x + y*y)));
                out_orientation.Transpose(out_orientation, out_orientation);
            }
        }
    }
}