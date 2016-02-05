using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ExampleAppWPF
{
    public class CustomAppAnimation
    {
        public Point m_widthHeight;

        public Point m_offscreenPos;
        public Point m_closedPos;
        public Point m_openPos;

        public bool m_animating;
        public Point m_animationEndPos;
        public Point m_animationStartPos;
        public Point m_animationCurrentPos;

        public Point m_containerAnimationEndPos;
        public Point m_containerAnimationStartPos;
        public Point m_containerAnimationCurrentPos;

        public FrameworkElement m_uiElement;

        public CustomAppAnimation(FrameworkElement uiElement)
        {
            m_widthHeight = new Point();

            m_offscreenPos = new Point();
            m_closedPos = new Point();
            m_openPos = new Point();

            m_animating = false;
            m_animationEndPos = new Point();
            m_animationStartPos = new Point();
            m_animationCurrentPos = new Point();

            m_containerAnimationEndPos = new Point();
            m_containerAnimationStartPos = new Point();
            m_containerAnimationCurrentPos = new Point();

            m_uiElement = uiElement;
            m_uiElement.RenderTransformOrigin = new Point(0.0, 0.0);
        }
    }
}
