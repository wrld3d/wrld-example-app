
using System.Collections.Generic;

namespace ExampleAppWPF
{
    public class MenuDelayedSourceUpdateAnimatorListener
    {
        private List<string> m_groups;
        private List<bool> m_groupsExpandable;
        private Dictionary<string, List<string>> m_groupToChildren;
        private MenuListAdapter m_adapter;
        

        public MenuDelayedSourceUpdateAnimatorListener(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren,
            MenuListAdapter adapter)
        {
            m_groups = groups;
            m_groupsExpandable = groupsExpandable;
            m_groupToChildren = groupToChildren;
            m_adapter = adapter;
        }

        public void OnCompleted()
        {
            m_adapter.UpdateSources(m_groups, m_groupsExpandable, m_groupToChildren);
            m_adapter.ForceSetAnimatedSizes();
            m_adapter.NotifyDataSetChanged();
        }
    }
}