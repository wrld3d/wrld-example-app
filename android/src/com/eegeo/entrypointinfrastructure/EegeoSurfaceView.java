// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.entrypointinfrastructure;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceView;

public class EegeoSurfaceView extends SurfaceView
{
    public static native void processNativePointerDown(int primaryActionIndex, int primaryActionIdentifier, int pointerCount, float[] x, float y[], int[] pointerIdentity, int[] pointerIndex);
    public static native void processNativePointerUp(int primaryActionIndex, int primaryActionIdentifier, int pointerCount, float[] x, float y[], int[] pointerIdentity, int[] pointerIndex);
    public static native void processNativePointerMove(int primaryActionIndex, int primaryActionIdentifier, int pointerCount, float[] x, float y[], int[] pointerIdentity, int[] pointerIndex);

    private INativeMessageRunner m_nativeMessageRunner;

    public EegeoSurfaceView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }

    public void setActivity(INativeMessageRunner nativeMessageRunner)
    {
        m_nativeMessageRunner = nativeMessageRunner;
    }

    @Override
    public boolean onTouchEvent(MotionEvent e)
    {
        //we need to convert multi-touch event handling into struct of arrays for many pointers to send over JNI

        //C++ event representation is like;
        /*
        	float x, y;
        	int pointerIdentity;
        	int pointerIndex;
         */

        final int pointerCount = e.getPointerCount();
        final int primaryActionIndex = e.getActionIndex();
        final int primaryActionIdentifier = e.getPointerId(primaryActionIndex);

        final float[] xArray = new float[pointerCount];
        final float[] yArray = new float[pointerCount];
        final int[] pointerIdentityArray = new int[pointerCount];
        final int[] pointerIndexArray = new int[pointerCount];

        for(int pointerIndex = 0; pointerIndex < pointerCount; ++pointerIndex)
        {
            xArray[pointerIndex] = e.getX(pointerIndex);
            yArray[pointerIndex] = e.getY(pointerIndex);
            pointerIdentityArray[pointerIndex] = e.getPointerId(pointerIndex);
            pointerIndexArray[pointerIndex] = pointerIndex;
        }

        switch (e.getActionMasked())
        {
        case MotionEvent.ACTION_DOWN:
        case MotionEvent.ACTION_POINTER_DOWN:
        {
            m_nativeMessageRunner.runOnNativeThread(new Runnable()
            {
                public void run()
                {
                    processNativePointerDown(primaryActionIndex, primaryActionIdentifier, pointerCount, xArray, yArray, pointerIdentityArray, pointerIndexArray);
                }
            });
        }
        break;

        case MotionEvent.ACTION_POINTER_UP:
        case MotionEvent.ACTION_UP:
        {
            m_nativeMessageRunner.runOnNativeThread(new Runnable()
            {
                public void run()
                {
                    processNativePointerUp(primaryActionIndex, primaryActionIdentifier, pointerCount, xArray, yArray, pointerIdentityArray, pointerIndexArray);
                }
            });
        }
        break;

        case MotionEvent.ACTION_MOVE:
        {
            m_nativeMessageRunner.runOnNativeThread(new Runnable()
            {
                public void run()
                {
                    processNativePointerMove(primaryActionIndex, primaryActionIdentifier, pointerCount, xArray, yArray, pointerIdentityArray, pointerIndexArray);
                }
            });
        }
        break;
        }

        return true;
    }
}
