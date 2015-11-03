// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.interiorsexplorer;

import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;

public class InteriorsFloorSelectedListener implements OnItemClickListener
{

    private final long m_nativeCallerPointer;
    private int m_numOfFloors;

    public InteriorsFloorSelectedListener(
        long nativeCallerPointer,
        final InteriorsExplorerView menuView)
    {
        m_nativeCallerPointer = nativeCallerPointer;
    }
    
    public void SetNumFloors(int floors)
    {
    	m_numOfFloors = floors - 1;
    }

    @Override
    public void onItemClick (AdapterView<?> parent, View itemClicked, int position, long id)
    {
        final int index = position;

        InteriorsExplorerViewJniMethods.OnFloorSelected(m_nativeCallerPointer, m_numOfFloors - index);
    }
}

