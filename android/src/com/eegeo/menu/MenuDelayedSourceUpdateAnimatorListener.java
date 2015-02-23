// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.menu;

import java.util.HashMap;
import java.util.List;

import android.animation.Animator;
import android.animation.Animator.AnimatorListener;

/*
 * The MenuDelayedSourceUpdateAnimatorListener is used by the MenuListAdapter when contracting groups.
 * It ensures that when the animation has finished, the adapter is updated with the new, contracted sources.
 */
public class MenuDelayedSourceUpdateAnimatorListener implements AnimatorListener
{
    private MenuListAdapter m_adapter;
    private List<String> m_groups;
    private List<Boolean> m_expandableGroups;
    private HashMap<String, List<String>> m_groupToChildrenMap;

    public MenuDelayedSourceUpdateAnimatorListener(
        MenuListAdapter adapter,
        List<String> groups,
        List<Boolean> expandableGroups,
        HashMap<String, List<String>> groupsToChildren)
    {
        m_adapter = adapter;
        m_groups = groups;
        m_expandableGroups = expandableGroups;
        m_groupToChildrenMap = groupsToChildren;
    }

    @Override
    public void onAnimationCancel(Animator animator)
    {
    }

    @Override
    public void onAnimationEnd(Animator animator)
    {
        // On completion, update the sources of the adapter.
        m_adapter.updateSources(m_groups, m_expandableGroups, m_groupToChildrenMap);
    }

    @Override
    public void onAnimationRepeat(Animator animator)
    {
    }

    @Override
    public void onAnimationStart(Animator animator)
    {
    }

}
