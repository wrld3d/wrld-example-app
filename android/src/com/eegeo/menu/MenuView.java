// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.menu;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

import android.graphics.PointF;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;
import android.widget.RelativeLayout;

import com.eegeo.BloombergApp.R;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.menu.MenuViewJniMethods;

public abstract class MenuView implements View.OnTouchListener, View.OnClickListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    protected View m_view = null;
    protected ListView m_list = null;
    protected View m_dragTabView = null;
    protected Boolean m_dragInProgress = false;
    protected OnItemClickListener m_menuItemSelectedListener = null;
    protected Boolean m_loggingEnabled = false;

    protected final int m_stateChangeAnimationTimeMilliseconds = 200;
    protected final int m_mainContainerVisibleOnScreenWhenClosedDip = 0;

    protected int m_offscreenYPx;
    protected int m_closedYPx;
    protected int m_openYPx;

    protected int m_mainContainerOffscreenOffsetXPx;
    protected int m_totalWidthPx;
    protected int m_offscreenXPx;
    protected int m_closedXPx;
    protected int m_openXPx;

    protected int m_dragStartPosXPx;
    protected int m_controlStartPosXPx;

    protected int m_touchAnchorXPx;
    protected int m_touchAnchorYPx;

    protected int m_dragThresholdPx;

    protected boolean m_dragAnchorSet = false;
    protected boolean m_canBeginDrag = false;

    protected boolean m_animating = false;
    protected PointF m_animationEndPos = new PointF();
    protected PointF m_animationStartPos = new PointF();
    protected PointF m_animationCurrentPos = new PointF();

    protected boolean m_isFirstAnimationCeremony = true;

    protected abstract void refreshListData(List<String> groups, List<Boolean> groupsExpandable, HashMap<String, List<String>> groupToChildrenMap);

    public MenuView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        final int dragThesholdDip = 10;
        m_dragThresholdPx = m_activity.dipAsPx(dragThesholdDip);
    }

    public void destroy()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        uiRoot.removeView(m_view);
        m_view = null;
    }

    public boolean isAnimating()
    {
        return m_animating;
    }

    public boolean isDragging()
    {
        return m_dragInProgress;
    }

    public void updateAnimation(final float deltaSeconds)
    {
        PointF totalDelta = PointFExtensions.vectorSubtract(m_animationEndPos, m_animationStartPos);
        float totalDeltaLen = totalDelta.length();
        boolean done;

        if(totalDeltaLen > 0.001)
        {
            float animationUnitsPerSecond =  (totalDeltaLen / (float)(m_stateChangeAnimationTimeMilliseconds/1e3));
            float frameDeltaUnits = animationUnitsPerSecond * deltaSeconds;
            PointF norm = PointFExtensions.vectorNormal(totalDelta);
            PointF delta = PointFExtensions.vectorScale(norm, frameDeltaUnits);
            m_animationCurrentPos = PointFExtensions.vectorAdd(m_animationCurrentPos, delta);

            PointF currentPosDirToEnd = PointFExtensions.vectorNormal(
                                            PointFExtensions.vectorSubtract(m_animationEndPos, m_animationCurrentPos)
                                        );

            float dp = PointFExtensions.vectorDot(currentPosDirToEnd, norm);
            done = dp < 0.f;
        }
        else
        {
            done = true;
        }

        animateToCurrentPos(false);

        if(done)
        {
            m_animationCurrentPos.x = m_animationEndPos.x;
            m_animationCurrentPos.y = m_animationEndPos.y;

            animateToCurrentPos(false);

            log("animation complete", "("+m_animationCurrentPos.x + "," + m_animationCurrentPos.y + ")");

            boolean closed = (m_animationEndPos.x == m_closedXPx && m_animationStartPos.x != m_animationEndPos.x) ||
                             (m_animationEndPos.y == m_closedYPx && m_animationStartPos.y != m_animationEndPos.y);

            boolean open = (m_animationEndPos.x == m_openXPx && m_animationStartPos.x != m_animationEndPos.x) ||
                           (m_animationEndPos.y == m_openYPx && m_animationStartPos.y != m_animationEndPos.y);

            if(closed)
            {
                MenuViewJniMethods.ViewCloseCompleted(m_nativeCallerPointer);
            }
            else if(open)
            {
                animateToCurrentPos(true);
                MenuViewJniMethods.ViewOpenCompleted(m_nativeCallerPointer);
            }

            m_animating = false;
        }
    }

    void animateToCurrentPos(boolean animationCompleteAndOpen)
    {
        setViewX(m_animationCurrentPos.x);
        setViewY(m_animationCurrentPos.y);
        m_list.setEnabled(animationCompleteAndOpen);
    }

    public float normalisedAnimationProgress()
    {
        float totalDistance = PointFExtensions.vectorLen(m_animationEndPos, m_animationStartPos);
        float currentDistance = PointFExtensions.vectorLen(m_animationEndPos, m_animationCurrentPos);
        float result = currentDistance/totalDistance;
        result = clamp(result, 0.f, 1.f);

        if(m_animationEndPos.x != m_animationStartPos.x)
        {
            if(m_animationEndPos.x == m_openXPx)
            {
                result = 1.f - result;
            }
        }
        else if(m_animationEndPos.y != m_animationStartPos.y)
        {
            if(m_animationEndPos.y == m_openYPx)
            {
                result = 1.f - result;
            }
        }

        return result;
    }

    public void animateToClosedOnScreen()
    {
        final boolean shouldRunAnimationBasedOnCurrentViewLocation = (!m_dragInProgress && viewXPx() != m_closedXPx);

        if(shouldRunAnimationBasedOnCurrentViewLocation || (m_animating && m_animationEndPos.x != m_closedXPx))
        {
            int newXPx = m_closedXPx;
            log("animateToClosedOnScreen", "x: " + newXPx);
            animateViewToX(newXPx);
        }
    }

    public void animateToOpenOnScreen()
    {
        final boolean shouldRunAnimationBasedOnCurrentViewLocation = (!m_dragInProgress && viewXPx() != m_openXPx);

        if(shouldRunAnimationBasedOnCurrentViewLocation || (m_animating && m_animationEndPos.x != m_openXPx))
        {
            int newXPx = m_openXPx;
            log("animateToOpenOnScreen", "x: " + newXPx);
            animateViewToX(newXPx);
        }
    }

    public void animateOffScreen()
    {
        final boolean shouldRunAnimationBasedOnCurrentViewLocation = (!m_dragInProgress && viewXPx() != m_offscreenXPx);

        if(shouldRunAnimationBasedOnCurrentViewLocation || (m_animating && m_animationEndPos.x != m_offscreenXPx))
        {
            int newXPx = m_offscreenXPx;
            log("animateOffScreen", "x: " + newXPx);
            animateViewToX(newXPx);
        }
    }

    public void animateToIntermediateOnScreenState(final float onScreenState)
    {
        if(m_animating)
        {
            return;
        }

        int viewXPx = viewXPx();
        int newXPx = m_offscreenXPx + (int)(((m_closedXPx - m_offscreenXPx) * onScreenState) + 0.5f);

        if(!m_dragInProgress && viewXPx != newXPx)
        {
            log("animateToIntermediateOnScreenState", "x: " + newXPx);
            setViewX(newXPx);
        }
    }

    public void animateToIntermediateOpenState(final float openState)
    {
        if(m_animating)
        {
            return;
        }

        int newXPx = m_closedXPx + (int)(((m_openXPx - m_closedXPx) * openState) + 0.5f);

        if(!m_dragInProgress && viewXPx() != newXPx)
        {
            log("animateToIntermediateOpenState", "x: " + newXPx);
            setViewX(newXPx);
        }
    }

    public void populateData(
        final long nativeCallerPointer,
        final String[] groupNames,
        final int[] groupSizes,
        final boolean[] groupIsExpandable,
        final String[] childJson)
    {
        List<String> groups = Arrays.asList(groupNames);
        List<Boolean> groupsExpandable = toBooleanList(groupIsExpandable);
        HashMap<String, List<String>> childMap = new HashMap<String,List<String>>();
        int childIndex = 0;
        for(int groupIndex = 0; groupIndex < groups.size(); groupIndex++)
        {
            int size = groupSizes[groupIndex];
            ArrayList<String> children = new ArrayList<String>();
            for(int i = 0; i < size; i++)
            {
                children.add(childJson[childIndex]);
                childIndex++;
            }
            childMap.put(groupNames[groupIndex], children);
        }

        refreshListData(groups, groupsExpandable, childMap);
    }

    protected List<Boolean> toBooleanList(boolean[] booleanArray)
    {
        ArrayList<Boolean> list = new ArrayList<Boolean>();
        for(int i = 0; i < booleanArray.length; i++)
        {
            list.add(booleanArray[i]);
        }
        return list;
    }

    protected void handleDragStart(int xPx, int yPx)
    {
        m_dragInProgress = true;
        m_dragStartPosXPx = xPx;
        m_controlStartPosXPx = viewXPx();
        log("ACTION_DOWN", "x: " + Integer.toString(xPx));

        MenuViewJniMethods.ViewDragStarted(m_nativeCallerPointer);
    }

    protected abstract void handleDragUpdate(int xPx, int yPx);

    protected abstract void handleDragFinish(int xPx, int yPx);

    public void onClick(View view)
    {
        if(m_animating)
        {
            return;
        }

        MenuViewJniMethods.ViewClicked(m_nativeCallerPointer);
    }

    public boolean onTouch(View view, MotionEvent event)
    {
        if(m_animating || !canInteract())
        {
            m_dragAnchorSet = false;
            return true;
        }

        if(!m_canBeginDrag)
        {
            m_canBeginDrag = MenuViewJniMethods.TryBeginDrag(m_nativeCallerPointer);
        }

        final int xPx = (int)(event.getRawX());
        final int yPx = (int)(event.getRawY());

        switch (event.getAction() & MotionEvent.ACTION_MASK)
        {
        case MotionEvent.ACTION_DOWN:
            m_touchAnchorXPx = xPx;
            m_touchAnchorYPx = yPx;
            m_dragAnchorSet = true;
            break;
        case MotionEvent.ACTION_UP:
            m_canBeginDrag = false;
            if(m_dragInProgress)
            {
                handleDragFinish(xPx, yPx);
            }
            else if(m_dragAnchorSet)
            {
                view.performClick();
            }
            m_dragAnchorSet = false;
            break;
        case MotionEvent.ACTION_MOVE:

            if(m_dragInProgress)
            {
                handleDragUpdate(xPx, yPx);
            }
            else if(m_canBeginDrag && m_dragAnchorSet)
            {
                double mag = Math.sqrt((m_touchAnchorXPx - xPx)*(m_touchAnchorXPx - xPx) + (m_touchAnchorYPx - yPx)*(m_touchAnchorYPx - yPx));
                if(mag >= m_dragThresholdPx)
                {
                    handleDragStart(xPx, yPx);
                }
            }
            break;
        }

        return true;
    }

    protected void animateViewToX(final int xAsPx)
    {
        if(xAsPx == m_offscreenXPx || xAsPx == m_closedXPx)
        {
            m_animationStartPos.x = m_isFirstAnimationCeremony ? m_offscreenXPx : m_openXPx;
        }
        else if(xAsPx == m_openXPx)
        {
            m_animationStartPos.x = m_closedXPx;
        }
        else
        {
            throw new IllegalArgumentException("Invalid animation target + " + Float.toString(xAsPx));
        }

        m_isFirstAnimationCeremony = false;

        m_animationStartPos.y =
            m_animationCurrentPos.y =
                m_animationEndPos.y = viewYPx();

        m_animationCurrentPos.x = viewXPx();
        m_animationEndPos.x = xAsPx;

        m_animating = true;
    }

    protected void animateViewToY(final int yAsPx)
    {
        boolean fromOffScreen = (viewYPx() == m_offscreenYPx);

        if(yAsPx == m_offscreenYPx || yAsPx == m_closedYPx)
        {
            m_animationStartPos.y = (m_isFirstAnimationCeremony || fromOffScreen) ? m_offscreenYPx : m_openYPx;
        }
        else if(yAsPx == m_openYPx)
        {
            m_animationStartPos.y = m_closedYPx;
        }
        else
        {
            throw new IllegalArgumentException("Invalid animation target + " + Float.toString(yAsPx));
        }

        m_isFirstAnimationCeremony = false;

        m_animationStartPos.x =
            m_animationCurrentPos.x =
                m_animationEndPos.x = viewXPx();

        m_animationCurrentPos.y = viewYPx();
        m_animationEndPos.y = yAsPx;

        m_animating = true;
    }

    protected void log(String label, String message)
    {
        if(m_loggingEnabled)
        {
            Log.v("Eegeo", label + " :: " + message);
        }
    }

    protected void setViewX(float viewXPX)
    {
        log("setViewX", String.valueOf(viewXPX));
        m_view.setX(viewXPX);
    }

    protected void setViewY(float viewYPX)
    {
        m_view.setY(viewYPX);
    }

    protected int viewXPx()
    {
        int x = (int)m_view.getX();
        return x;
    }

    protected int viewYPx()
    {
        int y = (int)m_view.getY();
        return y;
    }

    protected Boolean startedClosed(int controlStartPosXDip)
    {
        int deltaClosed = Math.abs(controlStartPosXDip - m_closedXPx);
        int deltaOpen = Math.abs(controlStartPosXDip - m_openXPx);
        return deltaClosed < deltaOpen;
    }

    protected float clamp(float v, float min, float max)
    {
        if(v < min) return min;
        if(v > max) return max;
        return v;
    }

    protected boolean canInteract()
    {
        return m_dragInProgress || isClosed() || isOpen();
    }

    protected boolean isClosed()
    {
        return viewXPx() == m_closedXPx;
    }

    protected boolean isOpen()
    {
        return viewXPx() == m_openXPx;
    }

    static class PointFExtensions
    {
        public static PointF vectorSubtract(PointF a, PointF b)
        {
            return new PointF(a.x - b.x, a.y - b.y);
        }

        public static PointF vectorAdd(PointF a, PointF b)
        {
            return new PointF(a.x + b.x, a.y + b.y);
        }

        public static float vectorLen(PointF a, PointF b)
        {
            return vectorSubtract(a, b).length();
        }

        public static float vectorDot(PointF a, PointF b)
        {
            return (a.x * b.x) + (a.y * b.y);
        }

        public static PointF vectorNormal(PointF a)
        {
            float length = a.length();
            float x = a.x / length;
            float y = a.y / length;
            return new PointF(x, y);
        }

        public static PointF vectorScale(PointF a, float scale)
        {
            return new PointF(a.x * scale, a.y * scale);
        }
    }
}
