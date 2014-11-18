package com.eegeo.helpers;

import android.content.Intent;

public interface IActivityIntentResultHandler 
{
	void onActivityResult(int requestCode, int resultCode, Intent data);
}
