using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    class SearchMenuListAdapter : MenuListAdapter
    {
        private int m_indexOfFirstDropDown;

        private double m_dropDownSeparatorHeight;

        public SearchMenuListAdapter(bool shouldAlignIconRight,
                                        ListBox list,
                                        Storyboard slideInAnimation,
                                        Storyboard slideOutAnimation,
                                        Storyboard itemShutterOpenAnimation,
                                        Storyboard itemShutterCloseAnimation,
                                        string controlToAnimate,
                                        bool isInKioskMode,
                                        int indexOfFirstDropDown,
                                        double separatorHeight)
                                    : base(shouldAlignIconRight,
                                          list,
                                          slideInAnimation,
                                          slideOutAnimation,
                                          itemShutterOpenAnimation,
                                          itemShutterCloseAnimation,
                                          controlToAnimate,
                                          isInKioskMode)
        {
            m_indexOfFirstDropDown = indexOfFirstDropDown - 1;

            m_dropDownSeparatorHeight = separatorHeight;
        }

        protected override void NotifyDataSetChanged()
        {
            base.NotifyDataSetChanged();

            for (int i = 0; i < Children.Count; ++i)
            {
                MenuListItem menuItem = Children[i];
                if (menuItem is MenuListItem)
                {
                    Thickness margin = menuItem.ListItemMargin;
                    margin.Top = 0;
                    if (i == m_indexOfFirstDropDown)
                    {
                        menuItem.HasCustomSeparator = true;
                    }
                    else if (i - 1 == m_indexOfFirstDropDown)
                    {
                        margin.Top = m_dropDownSeparatorHeight;
                    }
                    menuItem.ListItemMargin = margin;
                }
            }
        }
    }
}
