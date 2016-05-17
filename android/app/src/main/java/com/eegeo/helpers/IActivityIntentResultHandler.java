// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.helpers;

import android.content.Intent;

public interface IActivityIntentResultHandler
{
    void onActivityResult(int requestCode, int resultCode, Intent data);
}
