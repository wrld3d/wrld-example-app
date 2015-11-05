
using System;
using System.Collections.Generic;

namespace ExampleAppWPF
{
    class MenuDelayedSourceUpdateAnimatorListener
    {
        private int m_toBeRemovedCount;
        private List<string> m_groups;
        private List<bool> m_groupsExpandable;
        private Dictionary<string, List<string>> m_groupToChildren;
        private MenuListAdapter m_adapter;

        public MenuDelayedSourceUpdateAnimatorListener(
            int toBeRemovedCount,
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren,
            MenuListAdapter adapter)
        {
            m_toBeRemovedCount = toBeRemovedCount;
            m_groups = groups;
            m_groupsExpandable = groupsExpandable;
            m_groupToChildren = groupToChildren;
            m_adapter = adapter;
        }

        public void FadeOutStoryBoard_Completed(object sender, EventArgs e)
        {
            if (--m_toBeRemovedCount == 0)
            {
                m_adapter.UpdateSources(m_groups, m_groupsExpandable, m_groupToChildren);
                m_adapter.ForceSetAnimatedSizes();
                m_adapter.NotifyDataSetChanged();
            }
        }
    }
}