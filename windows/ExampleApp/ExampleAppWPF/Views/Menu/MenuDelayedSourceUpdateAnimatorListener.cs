
using System.Collections.Generic;
using System.Linq;

namespace ExampleAppWPF
{
    public class MenuDelayedSourceUpdateAnimatorListener
    {
        private List<string> m_groups;
        private List<bool> m_groupsExpandable;
        private Dictionary<string, List<string>> m_groupToChildren;
        private MenuListAdapter m_adapter;
        private int m_groupIndex;
        private int m_itemCount;


        public MenuDelayedSourceUpdateAnimatorListener(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren,
            MenuListAdapter adapter,
            int groupIndex = -1,
            int itemCount = 0)
        {
            m_groups = groups;
            m_groupsExpandable = groupsExpandable;
            m_groupToChildren = groupToChildren;
            m_adapter = adapter;
            m_groupIndex = groupIndex;
            m_itemCount = itemCount;
        }

        public void OnCompleted()
        {
            m_adapter.UpdateSources(m_groups, m_groupsExpandable, m_groupToChildren);

            if (m_groupIndex >= 0)
            {
                var startIndex = m_adapter.CalcFirstChildIndex(m_groupIndex);

                var itemsToAnimate = m_adapter.GetListBoxItemsInRange(startIndex, m_itemCount);

                if (itemsToAnimate.Any())
                {
                    var controls = m_adapter.ChildStackPanelsFor(itemsToAnimate);

                    m_adapter.GetSlideInStoryboardRunner().Begin(itemsToAnimate);
                    m_adapter.GetItemShutterOpenStoryboardRunner().Begin(controls);
                }
            }

            m_adapter.GetSlideOutStoryboardRunner().AllCompleted -= this.OnCompleted;
        }

            
    }
}